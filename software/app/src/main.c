#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"


TaskHandle_t xTaskLedHandle1 = NULL;

void vTask_Led_handler_1(void *params);

int main(void)
{
    /* Hardware board init */
    board_hardware_init();

    while(1)
    {
        /* Create task */
        xTaskCreate(
            vTask_Led_handler_1,
            "Task-LED-1",
            500,
            NULL,
            2,
            &xTaskLedHandle1);

        /* Start scheduler */
        vTaskStartScheduler();
    }

    return 0;
}

void vTask_Led_handler_1(void *params)
{
	while(1)
	{   
        toggle_led();
        vTaskDelay(pdMS_TO_TICKS(1000));
	}
}