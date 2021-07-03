#include "adc.h"

//Contructor de clase Adc1
Adc1::Adc1(adc_channel_t canal, adc_bits_width_t precision, adc_atten_t atenuacion, uint8_t muestras){

	this->canal = (adc1_channel_t)canal;
	this->precision = precision;
	this->atenuacion = atenuacion;
	this->muestras = muestras;
	adc_config();

}

//Se configura el adc
bool Adc1 :: adc_config(){

	esp_adc_cal_characteristics_t *adc_chars;

	esp_err_t error;

	adc1_config_width(this->precision);

	error = adc1_config_channel_atten(this->canal, this->atenuacion);

	if(error==ESP_OK){
		ESP_LOGI(ADC_MUESTRA,"GPIO %d se configuro a 12 Bits", this->canal + 30);
	}else{
		ESP_LOGE(ADC_MUESTRA,"GPIO %d se configuro a 12 Bits", this->canal + 30);

		return false;
	}

	return true;
}

//Obtener muestra del Adc
int Adc1 :: get_muestra(){

	int adc_reading = 0;

	for (int i = 0; i < this->muestras; i++) {
		adc_reading += adc1_get_raw((adc1_channel_t)this->canal);
	}
	adc_reading/=this->muestras;

	if(adc_reading > 4095){
		adc_reading = 4095;
	}
	if(adc_reading < 0){
		adc_reading = 0;
	}

	return(adc_reading);
}

//Contructor de clase Dac
Dac::Dac(dac_channel_t dac_input){
	this->dac_input = dac_input;
	ESP_LOGI(ADC_MUESTRA,"DAC %d Inicializado", this->dac_input);
	dac_habilitado();
}


//Habilitador del Dac
bool Dac::dac_habilitado(){
	esp_err_t error;

	error = dac_output_enable(this->dac_input);
	if(error==ESP_OK){
		ESP_LOGI(ADC_MUESTRA,"DAC %d habilitado", this->dac_input);
		return true;
	}else{
		ESP_LOGE(ADC_MUESTRA,"No se inicio DAC %d Motor", this->dac_input);
		return false;
	}

}

//Salida del Dac
esp_err_t Dac::dac_output(uint8_t valor){

	esp_err_t error;

	error = dac_output_voltage(this->dac_input, valor);

	return error;

}
