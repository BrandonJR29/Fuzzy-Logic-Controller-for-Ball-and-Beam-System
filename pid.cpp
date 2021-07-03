#include "pid.h"

//Constructor para clase Controlador PD
ControladorPD::ControladorPD(int Kp_p, int Kd_p, int Kp_a, float consigna){

	this->Kp_p = Kp_p;
	this->Kd_p = Kd_p;
	this->Kp_a = Kp_a;
	this->error_posicion[0] = 0;
	this->error_posicion[1] = 0;
	this->output[0] = 0;
	this->output[1] = 0;
	this->dac_value = 0;
	this->error_angulo = 0;
	this->posicion_value = 0;
	this->angulo_value = 0;
	this->set_angulo = 0;

	ESP_LOGI(PID,"Controlador Listo");


}

//Set de variable Kp para control de posicion
void ControladorPD::set_Kp_p(int valor){

	this->Kp_p = valor;
	ESP_LOGI(PID,"Cambio Kp_p %d", this->Kp_p);

}

//Set de variable Kd para control de posicion
void ControladorPD::set_Kd_p(int valor){

	this->Kd_p = valor;
	ESP_LOGI(PID,"Cambio Kd_p %d", this->Kd_p);

}

//Set de variable Kp para control de angulo
void ControladorPD::set_Kp_a(int valor){

	this->Kp_a = valor;
	ESP_LOGI(PID,"Cambio Kp_a %d", this->Kp_a);

}

//Funcion de control
float ControladorPD::controlPD(float posicion, float angulo, float set_point){

	this->error_posicion[0] = this->error_posicion[1];

	posicion = posicion * (0.13468) - 0.2222;

	this->error_posicion[1] = set_point - posicion;

	this->output[0] = this->output[1];

	//Filtro para derivada
	this->output[1] = 0.314 * this->error_posicion[0] + this->output[0] * 0.686;

	if(this->output[1] < -0.76){
		this->output[1] = -0.76;
	}
	if(this->output[1] > 0.76){
		this->output[1] = 0.76;
	}

	this->set_angulo = this->output[1] * -1;


	angulo = (angulo * (-0.6058) + 1.0904);

	this->error_angulo = this->set_angulo - angulo;

	//Angulo de offset
	if(this->error_angulo<0){
		this->error_angulo-=0.1745;
	}else{
		this->error_angulo+=0.0175;
	}

	if(this->error_angulo < -0.76){
		this->error_angulo = -0.76;
	}
	if(this->error_angulo > 0.76){
		this->error_angulo = 0.76;
	}

	this->dac_value = this->Kp_a*this->error_angulo;

	if(this->dac_value < -5.0){
		this->dac_value = -5.0;
	}
	if(this->dac_value > 5.0){
		this->dac_value = 5.0;
	}

	this->dac_value = -(this->dac_value / 10.0) + 0.5;
	this->dac_value = this->dac_value * 255.0;

	return this->dac_value;
}
