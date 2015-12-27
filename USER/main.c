#include <stdio.h>

#include "stm32f4xx.h"

#include "clock.h"
#include "encoder.h"
#include "movement.h"
#include "pwm.h"
#include "switch.h"
#include "usart.h"
#include "utils.h"

int main(void)
{
	system_clk_set();
	systick_config();

	uart_config(115200);

	encoder_config();
	switch_config();

	pwm_config();


	//move_x(314);

	printf("\n\nEntering main loop\n\n");
	while(1)
	{
		printf("shabi xuedi\r\n");
		delay_ms(10);
	}

	return 0;
}
