#include "movement.h"

#ifdef USE_THREE_WHEEL

void t_move_y(uint32_t y)
{
	double old_pos[2];
	old_pos[0] = position[0];
	old_pos[1] = position[1];

	speeds[0] = VECT_W1 * 10000;
	speeds[1] = VECT_W2 * speeds[0] * cos(PI / 2);
	speeds[1] = VECT_W3 * speeds[0] * cos(PI / 2);
	
	uprintf(USART1,\
		"1V%lf\r2V%lf\r3V%lf\r",\
		speeds[0],\
		speeds[1],\
		speeds[2]\
		);
	
	while(position[1] - old_pos[1] > ZERO);
	
	speeds[0] = 0;
	speeds[1] = 0;
	speeds[2] = 0;
	
	uprintf(USART1,\
		"1V%lf\r2V%lf\r3V%lf\r",\
		speeds[0],\
		speeds[1],\
		speeds[2]\
		);
}

#endif
