#include "clock.h"
#include "debug.h"
#include "encoder.h"
#include "fan.h"
#include "movement.h"
#include "mti.h"

bool stop_flag = false;
bool move_up_flag = true;

int16_t get_speed(uint8_t wheel)
{
	return arg_speeds[wheel];
}

void stop_all(void)
{
	uprintf(USART1, "\rDEC10000\rV0\r");
	delay_ms(10);
}

void rotate(float rad)
{
	rotate_r(rad - get_mti_value());
}

void rotate_r(float rad)
{
	#ifdef USE_FOUR_WHEEL
	f_rotate_r(rad);
	#endif
}

void rotate_c(int8_t arg_spd)
{
	#ifdef DEBUG
	printf("\rotate_c(%d)\n", arg_spd);
	#endif
	
	#ifdef USE_THREE_WHEEL
	t_rotate_c(arg_spd);
	#endif
	
	#ifdef USE_FOUR_WHEEL
	f_rotate_r_c(arg_spd);
	#endif
}

void move_arc(float y, float rad)
{
	#ifdef USE_FOUR_WHEEL
	f_move_arc(y, rad);
	#endif
}

void move_xy_c(int8_t spd_x, int8_t spd_y)
{
	#ifdef DEBUG
	printf("\nmove_xy_c(%d, %d)\n", spd_x, spd_y);
	#endif
	
	#ifdef USE_THREE_WHEEL
	t_move_xy_c(spd_x, spd_y);
	#endif
	
	#ifdef USE_FOUR_WHEEL
	f_move_xy_c(spd_x, spd_y);
	#endif
}


void move_xy(float x, float y)
{
	#ifdef DEBUG
	printf("\nmove_xy(%f, %f)\n", x, y);
	#endif

	#ifdef USE_FOUR_WHEEL
	f_move_xy(x, y);
	#endif
}

void move_x(float x)
{
	#ifdef DEBUG
	printf("\nmove_x(%f)\n", x);
	#endif
	
	#ifdef USE_THREE_WHEEL
	t_move_x(x);
	#endif
}

void move_x_c(int16_t arg_spd)
{
	#ifdef USE_THREE_WHEEL
	t_move_x_c(arg_spd);
	#endif
}

void move_y(float y)
{
	#ifdef DEBUG
	printf("\nmove_y(%f)\n", y);
	#endif

	#ifdef USE_THREE_WHEEL
	t_move_y(y);
	#endif
}

void move_y_c(int16_t arg_spd)
{
	#ifdef USE_THREE_WHEEL
	t_move_y_c(arg_spd);
	#endif
}

void stop(void)
{
	#ifdef USE_THREE_WHEEL
	t_stop();
	#endif

	#ifdef USE_FOUR_WHEEL
	f_stop();
	#endif

	delay_ms(10);
}

void move_up(void)
{
	uprintf(USART1, "\r4V-30000\r");
	delay_ms(1);
	uprintf(USART1, "\r3V-30000\r");
	delay_ms(1);
}

void move_down(void)
{
	uprintf(USART1, "\r4V1000\r");
	delay_ms(1);
	uprintf(USART1, "\r3V1000\r");
	delay_ms(1);
}

void stop_move_up(void)
{
	uprintf(USART1, "\r4V0\r");
	delay_ms(1);
	uprintf(USART1, "\r3V0\r");
	delay_ms(1);
}
