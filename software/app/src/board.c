#include "board.h"
#include "target.h"
#include <string.h>

static void led_init(void);

void board_hardware_init(void)
{
    /* Set default RCC clock -> 16MHz */
    RCC_DeInit();
    SystemCoreClockUpdate();

    /* Init Led */
    led_init();
}

void set_led(bool value)
{
    BitAction v = (value) ? Bit_SET : Bit_RESET;
    GPIO_WriteBit(LED1_PORT, LED1_PIN, v);
}

void toggle_led()
{
    GPIO_ToggleBits(LED1_PORT, LED1_PIN);
}

static void led_init(void)
{
    /* Init struct */
    GPIO_InitTypeDef gpio_init_struct;

    memset(&gpio_init_struct, 0, sizeof(gpio_init_struct));

    GPIO_StructInit(&gpio_init_struct);

    /* Start clock */
    RCC_AHB1PeriphClockCmd(LED1_RCC_Periph, ENABLE);

    gpio_init_struct.GPIO_Pin = LED1_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(LED1_PORT, &gpio_init_struct);

    /* Set led to 0 */
    set_led(false);
}