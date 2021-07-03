/*
 * 		Universidad Central de Venezuela
 *		Controlador Difuso para el Sistema Ball and Beam de Quanser
 *      Autor: Br. Brandon Jimenez
 */

#include "uart1.h"

//Funcion de iniicio
extern "C" void app_main()
{
	//Intancia de clase Timer para inicio del timer para el muestreo
	Timer timer1(TIMER_GROUP_0, TIMER_0, TIMER_ALARM_EN, 1, 0.012);

	//Funcion configuracion del UART
	uart_config();
}
