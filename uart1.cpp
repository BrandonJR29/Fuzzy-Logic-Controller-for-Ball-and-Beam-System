#include "uart1.h"

//Variable externa Set point
extern float set_point;
//Variable esterna booleana para grafica
extern bool plot;
//Variable para el tipo de controlador
extern uint8_t tipoControl;

//Variable para Maquina de estados del sistema
enum estado{
	tipo=0,
	controlador
}estado;

//Drivers para control del UART
#include "driver/uart.h"

//Cola de envio de datos para la grafica
extern QueueHandle_t dataplot;

//Intancia de clase Timer para inicio del timer para ltoma de datos para la grafica
Timer timer2(TIMER_GROUP_0, TIMER_1, TIMER_ALARM_EN, 0, 7.0);


//Eventos del UART
static void uart_event_task(void *pvParameters)
{
    uart_event_t event;
    size_t buffered_size;
    uint8_t* dtmp = (uint8_t*) malloc(RD_BUF_SIZE);
    while(1) {
    	//Se espera ocurra un evento en el UART
        if(xQueueReceive(uart0_queue, (void * )&event, (portTickType)portMAX_DELAY)) {
            bzero(dtmp, RD_BUF_SIZE);
            ESP_LOGI(TAG, "uart[%d] event:", UART_NUM_1);
            switch(event.type) {

                case UART_DATA:
                    uart_read_bytes(UART_NUM_1, dtmp, event.size, portMAX_DELAY);

                    //Se identifica el estado
                    switch(estado){

                    case tipo:
                    	switch (*dtmp){
                    	// Se establece el tipo de controlador
							case 0:
								tipoControl = 0;
								ESP_LOGI("FUZZY", "Control Difuso en uso");
								estado = controlador;
							break;

							case 1:
								tipoControl = 1;
								ESP_LOGI("FUZZY", "Control Difuso Ajustado en uso");
								estado = controlador;
							break;

							case 2:
								tipoControl = 2;
								ESP_LOGI("PD", "Control PD en uso");
								estado = controlador;
							break;

							default:
								ESP_LOGI(TAG,"Funcion no valida");
							break;
                    	}
                    	break;

                    case controlador:
                    	// Se establece la consigna
                    	dato_set_point = (int8_t)*dtmp;

						if(dato_set_point >= -15 && dato_set_point <= 15){

							ESP_LOGI(TAG, "[UART DATA] Length: %d", event.size);
							set_point = (float)dato_set_point/100;
							ESP_LOGI(TAG, "[UART DATA]: %f", set_point);
							plot = true;
							timer2.timer_inicio();
							uart_flush_input(UART_NUM_1);

						}else{
							ESP_LOGI(TAG,"Fuera de rango");
						}
						estado = tipo;

                    	break;

                    default:
                    	break;

                    }



                    break;
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow");
                    uart_flush_input(UART_NUM_1);
                    xQueueReset(uart0_queue);
                    break;
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    uart_flush_input(UART_NUM_1);
                    xQueueReset(uart0_queue);
                    break;
                case UART_BREAK:
                    ESP_LOGI(TAG, "uart rx break");
                    break;
                case UART_PARITY_ERR:
                    ESP_LOGI(TAG, "uart parity error");
                    break;
                case UART_FRAME_ERR:
                    ESP_LOGI(TAG, "uart frame error");
                    break;
                default:
                    ESP_LOGI(TAG, "uart event type: %d", event.type);
                    break;
            }
        }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}

//Funcion para envio de datos para grafica
void plot_task(void *params){
	uint16_t hola[1] = {0};
	uint16_t *buffer = hola;
	while(1){
		//Se recibe datos en la cola
		xQueueReceive(dataplot,buffer,portMAX_DELAY);
		//Se envian un uint16 con el valor del ADC
		uart_write_bytes(UART_NUM_1,(const char*)hola,2);
	}
	vTaskDelete(NULL);
}

//Funcion para configuracion del UART
void uart_config(){

	uart_config_t uart_config = {
		.baud_rate = 115200,
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE
	};
	uart_param_config(UART_NUM_1, &uart_config);

	uart_set_pin(UART_NUM_1, Tx1, Rx1, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	uart_driver_install(UART_NUM_1, BUF_SIZE * 2, BUF_SIZE * 2, 20, &uart0_queue, 0);

	//Se crean tareas para el Eventos del UART y la tarea para envio de datos para la grafica
	xTaskCreatePinnedToCore(uart_event_task, "uart_event_task", 2048, NULL, 12, NULL,0);
	xTaskCreatePinnedToCore(plot_task, "plot", 2048*2, NULL, 5, NULL,0);

}
