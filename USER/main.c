#include <stdio.h>

#include "stm32f4xx.h"

#include "clock.h"
#include "encoder.h"
#include "movement.h"
#include "pwm.h"
#include "usart.h"

int main(void)
{
	systick_config();

	uart1_config(115200);
	uart2_config(115200);
	uart3_config(115200);
	uart4_config(115200);

	encoder_config();
	pwm_config();

	printf("Entering main loop\n\n");
	while(1)
	{
		printf("%f\n", get_pos_x());
	}

	return 0;
}
