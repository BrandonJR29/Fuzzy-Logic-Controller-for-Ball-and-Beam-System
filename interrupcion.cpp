#include "interrupcion.h"

//Semaforo para interrupciones de Timers
SemaphoreHandle_t test = NULL;
SemaphoreHandle_t muestrea = NULL;

//Constructor de clase Timer
Timer :: Timer(timer_group_t timer_group, timer_idx_t timer_idx, bool interrupcion, bool inicio, double timer_interval_sec){
	//Se establecen parametros del Timer
	this->timer_idx = timer_idx;
	this->timer_group = timer_group;
	this->timer_interval_sec = timer_interval_sec;
	this->interrupcion = interrupcion;
	this->timer_interval_sec = timer_interval_sec;
	this->inicio = inicio;
	timer_config();
}

//Se configura Timer
void Timer::timer_config(){

	timer_config_t config;
	config.divider = TIMER_DIVIDER;
	config.counter_dir = TIMER_COUNT_UP;
	config.counter_en = TIMER_PAUSE;
	config.alarm_en = this->interrupcion;
	config.intr_type = TIMER_INTR_LEVEL;
	config.auto_reload = 1;

	timer_init(this->timer_group, this->timer_idx, &config);

	timer_set_counter_value(this->timer_group, this->timer_idx, 0x00000000ULL);

	if(this->interrupcion){
		if(this->timer_idx == 0){
			muestrea = xSemaphoreCreateBinary();
			//Se crea Tarea de interrupcion para muestrear
			xTaskCreatePinnedToCore(control, "interrupcion", 3072*3, NULL, 5, NULL, 1);
		}else{
			test = xSemaphoreCreateBinary();
			//Se crea Tarea que activa bandera de envio de datos
			xTaskCreatePinnedToCore(send_plot, "plot", 1024*2, NULL, 5, NULL, 0);
		}
		timer_set_alarm_value(this->timer_group, this->timer_idx, this->timer_interval_sec * TIMER_SCALE);
		timer_enable_intr(this->timer_group, this->timer_idx);
		timer_isr_register(this->timer_group, this->timer_idx, &(this->start_timer_group0_isr),this, 0, &manejador_timer);
	}

	if(this->inicio){
		this->timer_inicio();
	}


	ESP_LOGI(TIMER_TAG,"Se inicializo el Timer, Grupo %d, Numero: %d, Tiempo Interrupcion: %f s", this->timer_group, this->timer_idx, this->timer_interval_sec);

}

//Pausa timer
esp_err_t Timer::pause(void){

	esp_err_t error;

	error = timer_pause(this->timer_group, this->timer_idx);

	return error;
}

//Inicia Timer
esp_err_t Timer::timer_inicio(void){

	esp_err_t error;

	error = timer_start(this->timer_group, this->timer_idx);

	return error;
}

//Manejo de interrupcion del timer
void IRAM_ATTR Timer::start_timer_group0_isr(void* arg)
{
    reinterpret_cast<Timer*>(arg)->timer_group0_isr();
}

void Timer :: timer_group0_isr(){

    int timer_idx = this->timer_idx;

    uint32_t intr_status = TIMERG0.int_st_timers.val;

    TIMERG0.hw_timer[timer_idx].update = 1;

    uint64_t timer_counter_value =
        ((uint64_t) TIMERG0.hw_timer[timer_idx].cnt_high) << 32
        | TIMERG0.hw_timer[timer_idx].cnt_low;

    timer_event_t evt;
    evt.timer_group = this->timer_group;
    evt.timer_idx = this->timer_idx;
    evt.timer_counter_value = timer_counter_value;

    if ((intr_status & BIT(timer_idx)) && timer_idx == TIMER_0) {
        evt.type = TEST_WITHOUT_RELOAD;
        TIMERG0.int_clr_timers.t0 = 1;
        timer_counter_value += (uint64_t) (this->timer_interval_sec * TIMER_SCALE);
        TIMERG0.hw_timer[timer_idx].alarm_high = (uint32_t) (timer_counter_value >> 32);
        TIMERG0.hw_timer[timer_idx].alarm_low = (uint32_t) timer_counter_value;
    } else if ((intr_status & BIT(timer_idx)) && timer_idx == TIMER_1) {
        evt.type = TEST_WITH_RELOAD;
        TIMERG0.int_clr_timers.t1 = 1;
    } else {
        evt.type = -1;
    }

    TIMERG0.hw_timer[timer_idx].config.alarm_en = TIMER_ALARM_EN;

    if(this->timer_idx == 1){
    	this->pause();
    	//Se activa semaforo para recoleccion de datos de grafica
    	xSemaphoreGiveFromISR(test, NULL);
    }else{
    	//Se activa semaforo para muestrear
    	xSemaphoreGiveFromISR(muestrea, NULL);
    }
}



