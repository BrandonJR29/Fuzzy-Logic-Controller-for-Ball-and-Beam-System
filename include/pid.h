#ifndef CONTROLADOR_PID_H_
#define CONTROLADOR_PID_H_
#include "controlDifuso.h"

//Se define tiempo de muestreo para calculo de componente derivativa
static float sample_time = 0.012;

//Log PID
static const char *PID = "PID";

//Clase control PD
class ControladorPD{

public:

	ControladorPD(int Kp_p, int Kd_p, int Kp_a, float set_point);
	int Kp_p, Kd_p, Kp_a;
	void set_Kp_p(int valor);
	void set_Kd_p(int valor);
	void set_Kp_a(int valor);
	float controlPD(float posicion, float angulo, float set_point);

private:
	float  error_posicion[2], output[2], dac_value, error_angulo, posicion_value, angulo_value, set_angulo;

};

#endif

