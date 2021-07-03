#ifndef INTERRUPCION_H_
#define INTERRUPCION_H_

#include "controlador.h"
//Drivers para control de Timers
#include "driver/periph_ctrl.h"
#include "driver/timer.h"

//Variables para control de los Timers
#define TIMER_DIVIDER         16  //  Hardware timer clock divider
#define TIMER_SCALE           (TIMER_BASE_CLK / TIMER_DIVIDER)  // convert counter value to seconds
#define TEST_WITHOUT_RELOAD   0        // testing will be done without auto reload
#define TEST_WITH_RELOAD      1        // testing will be done with auto reload

//Log Timer
static char* TIMER_TAG = "TIMERS";

//Clase Timer
class Timer{

	public:
		Timer(timer_group_t timer_group, timer_idx_t timer_idx, bool interrupcion, bool start, double timer_interval_sec);
		timer_idx_t timer_idx;
		timer_group_t timer_group;
		double timer_interval_sec;
		esp_err_t pause();
		esp_err_t timer_inicio();

	private:
		bool interrupcion;
		bool inicio;
		void timer_config();
		typedef struct {
		    int type;  // the type of timer's event
		    int timer_group = this->timer_group;
		    int timer_idx = this->timer_idx;
		    uint64_t timer_counter_value;
		} timer_event_t;

	protected:
		intr_handle_t manejador_timer;
		static void start_timer_group0_isr(void *para);
		void timer_group0_isr();

};

#endif

