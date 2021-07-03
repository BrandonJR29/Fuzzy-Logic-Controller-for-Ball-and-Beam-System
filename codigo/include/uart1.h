#ifndef UART1_H_
#define UART1_H_

#include <string.h>
#include "interrupcion.h"

//Tamano del buffer del UART
#define RD_BUF_SIZE (BUF_SIZE)
#define BUF_SIZE (1024)

//Pines del UART
#define Tx1 4
#define Rx1 5

//LOG UART
static const char *TAG = "uart_events";

//Set point
static int8_t dato_set_point;

//Manejo de cola de recepcion del UART
static QueueHandle_t uart0_queue;

//Funcion de configuracion del UART
void uart_config();

#endif
