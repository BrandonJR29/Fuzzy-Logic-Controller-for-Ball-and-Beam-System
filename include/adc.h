#ifndef ADC_H_
#define ADC_H_

#include "esp_system.h"
#include "driver/adc.h"
#include <driver/dac.h>
#include "esp_adc_cal.h"
#include "esp_log.h"

//Variables para control de ADC
#define DEFAULT_VREF    1100        //Use adc1_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   100          //Multisampling

//Log ADC
static const char *ADC_MUESTRA = "ADC_MUESTRA";

//Clase Adc1
class Adc1{

public:

	Adc1(adc_channel_t canal, adc_bits_width_t precision, adc_atten_t atenuacion, uint8_t muestras);
	int get_muestra();

private:

	adc_bits_width_t precision;
	adc1_channel_t canal;
	adc_atten_t atenuacion;
	uint8_t muestras;
	bool adc_config();
//	void print_char_val_type(esp_adc_cal_value_t val_type);
//	static void check_efuse();


};

//Clase Dac
class Dac{

public:

	Dac(dac_channel_t dac_input);
	esp_err_t dac_output(uint8_t valor);

private:

	bool dac_habilitado();
	dac_channel_t dac_input;

};



#endif
