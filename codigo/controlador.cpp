#include "controlador.h"

//Manejador de cola de datos para grafica
QueueHandle_t dataplot;

//Variable para control convencional
float  Kp_1 = 7.0, Kp_2 = 12, Kd = 7;

//Set point
float set_point = 0.0;

//Variable para tipo de control
uint8_t tipoControl = 0;

//Semaforos externos accionados por Timers
extern SemaphoreHandle_t muestrea;
extern SemaphoreHandle_t test;

//instancia de clase ControlPD
ControladorPD ctrlPD(Kp_2, Kd, Kp_1, set_point);

//instancia de clase Control Difuso sin ajustar
Difuso controlDifuso(0);

//instancia de clase Control Difuso ajustado
Difuso controlDifusoOpt(1);

//instancia de clase Adc1 para medir angulo
Adc1 angulo_adc( input_angulo, ADC_WIDTH_BIT_12, ADC_ATTEN_DB_11, NO_OF_SAMPLES);

//instancia de clase Dac para salida a motor
Dac motor_dac(output_motor);

//instancia de clase Adc1 para medir posicion
Adc1 posicion_adc(input_posicion, ADC_WIDTH_BIT_12, ADC_ATTEN_DB_11, NO_OF_SAMPLES);

//instancia de clase Dac para debug de timepo de muestreo
Dac debug_dac(output_debug);

//Variable booleana para envio de datos para grafica
bool plot = false;

//Tarea para activar bandera para envio de datos
void send_plot(void *param){

	while(1){

		if( xSemaphoreTake( test, portMAX_DELAY) == pdTRUE ){
			//Se limpia bandera
			plot = !plot;
			ESP_LOGI("PLOT","Datos enviados");
		}

	}
	vTaskDelete(NULL);

}

//Funcion para debug del tiempo de muestreo
void control_debug(){

	//Genera funcion cuadrada
	if(bandera_debug){
		debug_dac.dac_output(127);
	}else{
		debug_dac.dac_output(0);
	}
	bandera_debug = !bandera_debug;

}

//Tarea de control del sistema
void control(void *parama){
	ESP_LOGI(CONTROL,"Inicio tarea de Control");
	float posicion, angulo;
	uint16_t posicion_value, angulo_value;
	uint8_t salida = 0;
	dataplot = xQueueCreate(5,2);
	uint16_t count = 0;
	while(1){
		if( xSemaphoreTake( muestrea, portMAX_DELAY) == pdTRUE ){

			//Muestrea en 4095-0
			posicion_value = (uint16_t)posicion_adc.get_muestra();
			angulo_value = (uint16_t)angulo_adc.get_muestra();

			//Escalar en un rango 3.3-0 V
			posicion = posicion_value*3.3/4095;
			angulo = angulo_value*3.3/4095;

			//Elige tipo de controlador
			switch(tipoControl){

			case 2:
				//Asigna a salida controlador PD
				salida = (uint8_t)ctrlPD.controlPD(posicion,angulo, set_point);
				break;

			case 0:
				//Asigna a salida controlador difuso sin ajustar
				salida = (uint8_t)controlDifuso.output(posicion,angulo,set_point);
				break;

			case 1:
				//Asigna a salida controlador difuso ajustado
				salida = (uint8_t)controlDifusoOpt.output(posicion,angulo,set_point);
				break;

			default:
				salida = 127;
				break;

			}

			if(plot){
				//Envio de datos para grafica
				xQueueSendToFront(dataplot,&posicion_value,pdMS_TO_TICKS(1000));
			}
			//Asigna salida
			motor_dac.dac_output(salida);
			//Debug tiempo de muestreo
			control_debug();
		}

	}
	vTaskDelete(NULL);
}
