#pragma once

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define LED0_PIN                GPIO_Pin_9
#define LED0_PORT               GPIOB
#define LED0_RCC_Periph         RCC_AHB1Periph_GPIOB
#define LED1_PIN                GPIO_Pin_14
#define LED1_PORT               GPIOA
#define LED1_RCC_Periph         RCC_AHB1Periph_GPIOA

#define SPI1_SCK_PIN            GPIO_Pin_5
#define SPI1_MISO_PIN           GPIO_Pin_6
#define SPI1_MOSI_PIN           GPIO_Pin_7
#define SPI1_PORT               GPIOA

#define SPI1_CS_PIN             GPIO_Pin_2
#define SPI1_CS_PORT            GPIOC

#define UART2_RX_PIN            GPIO_Pin_3
#define UART2_TX_PIN            GPIO_Pin_2
#define UART2_PORT              GPIOA

#define MOTOR_S1_PIN            GPIO_Pin_6
#define MOTOR_S2_PIN            GPIO_Pin_7
#define MOTOR_S3_PIN            GPIO_Pin_8
#define MOTOR_S4_PIN            GPIO_Pin_9
#define MOTOR_PORT              GPIOC

#define MOTOR_S1_TIM            TIM3
#define MOTOR_S2_TIM            TIM8
#define MOTOR_S3_TIM            TIM8
#define MOTOR_S4_TIM            TIM8

#define MOTOR_S1_TIM_CHANNEL    TIM_Channel_1
#define MOTOR_S2_TIM_CHANNEL    TIM_Channel_2
#define MOTOR_S3_TIM_CHANNEL    TIM_Channel_3
#define MOTOR_S4_TIM_CHANNEL    TIM_Channel_4
