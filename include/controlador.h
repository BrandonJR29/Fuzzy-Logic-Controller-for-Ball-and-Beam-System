#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

//Manejo de control convencional
#include "pid.h"
//Manejo de control difuso
#include "controlDifuso.h"
//Libreria para manejo del RTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

//Variables para configurar ADC y DAC
static const adc_channel_t input_angulo = ADC_CHANNEL_4;
static const adc_channel_t input_posicion = ADC_CHANNEL_6;
static const dac_channel_t output_motor = DAC_CHANNEL_1;
static const dac_channel_t output_debug =  DAC_CHANNEL_2;

//Log Control
static const char *CONTROL = "CONTROL TASK";

//Bandera para debug tiempo de muestreo
static bool bandera_debug = true;

//Funcion para debug del tiempo de muestreo
void control_debug();

//Tarea de control del sistema
void control(void *param);

//Tarea para activar bandera para envio de datos
void send_plot(void *param);

#endif
