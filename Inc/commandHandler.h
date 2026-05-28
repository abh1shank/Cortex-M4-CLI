#include "commandHandler.h"
#include <string.h>
#include "main.h"


//PRIVATE METHOD

void timed_toggle(int toggle_interval, int toggle_times){
	uint32_t last_toggle_time = 0;
	int toggle_count=0;
	while (toggle_count<toggle_times)
	{
	  /* Get the current system uptime in milliseconds */
	  uint32_t current_time = HAL_GetTick();

	  /* Check if the required time interval has passed */
	  if (current_time - last_toggle_time >= toggle_interval)
	  {
	    /* Toggle the GPIO pin state */
	    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
	    toggle_count++;
	    last_toggle_time = current_time;
	  }

	}
}

}


int command_handler(char *cmd){
	char cmd_check[20];
	strncpy(cmd_check,cmd,6);
	if (strcmp(cmd_check,"LED_ON") == 1){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	}
	if (strcmp(cmd_check,"LED_OF") == 1){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	}
	if (strcmp(cmd_check,"LED_BL") == 1){
		//LED_BLINK5, 5 is at 9th index
		int freq=(*(cmd+9)-'0')*100;
		int toggle_limit = 10000/freq;
		timed_toggle(freq,toggle_limit);
	}

}

int SOS_handler(){
	//six short beeps, 300ms and three long beep 600ms
	timed_toggle(300,3);
	timed_toggle(600,3);
	timed_toggle(300,3);

}

int button_handler(){
	timed_toggle(100,100);

}

