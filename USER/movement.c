#include "clock.h"
#include "debug.h"
#include "encoder.h"
#include "fan.h"
#include "movement.h"


uint32_t arg_speeds[3] = {0};

uint32_t get_speed(uint8_t wheel)
{
	return arg_speeds[wheel];
}

void stop_all(void)
{
	uprintf(USART1, "V0\r");
	delay_ms(10);
}

void move_x(float x)
{
	#ifdef DEBUG
	printf("move_x(%f)\n", x);
	#endif
	
	#ifdef USE_THREE_WHEEL
	t_move_x(x);
	#endif
}

void move_y(float y)
{
	#ifdef DEBUG
	printf("move_y(%f)\n", y);
	#endif

	#ifdef USE_THREE_WHEEL
	t_move_y(y);
	#endif
}

void stop(void)
{
	uprintf(USART1, "1V0\r2V0\r3V0\r");
	delay_ms(10);
}

void move_up(void)
{
	uprintf(USART1, "4V-8000\r");
	delay_ms(1);
	uprintf(USART1, "3V8000\r");
	delay_ms(1);
	
	start_fan(0);
}

void stop_move_up(void)
{
	uprintf(USART1, "4V0\r");
	delay_ms(1);
	uprintf(USART1, "3V0\r");
	delay_ms(1);
	
	stop_fan(0);
}
