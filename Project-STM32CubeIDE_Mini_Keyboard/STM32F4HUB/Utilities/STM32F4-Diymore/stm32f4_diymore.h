#ifndef __STM32F4_DIYMORE_H
#define __STM32F4_DIYMORE_H

#ifdef __cplusplus
 extern "C" {
#endif
                                              
#include "stm32f4xx_hal.h"
#include <main.h>

typedef enum 
{
  LED2 = 0
} Led_TypeDef;

#define LEDn                             1

#define LED2_PIN                         GPIO_PIN_0
#define LED2_GPIO_PORT                   GPIOE
#define LED2_GPIO_CLK_ENABLE()           __GPIOE_CLK_ENABLE()
#define LED2_GPIO_CLK_DISABLE()          __GPIOE_CLK_DISABLE()

#define LEDx_GPIO_CLK_ENABLE(__INDEX__) do{if((__INDEX__) == 0) LED2_GPIO_CLK_ENABLE(); \
                                           }while(0)

#define LEDx_GPIO_CLK_DISABLE(__INDEX__) do{if((__INDEX__) == 0) LED2_GPIO_CLK_DISABLE(); \
                                           }while(0)

#define USARTx                       	 USART1

#define USARTx_CLK_ENABLE()              __USART1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __UART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __UART1_RELEASE_RESET()

#define USARTx_TX_PIN                    GPIO_PIN_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF7_USART1
#define USARTx_RX_PIN                    GPIO_PIN_10
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_AF                     GPIO_AF7_USART1


void BSP_UART_Init();

void BSP_LED_Init(Led_TypeDef Led);
void BSP_LED_On(Led_TypeDef Led);
void BSP_LED_Off(Led_TypeDef Led);
void BSP_LED_Toggle(Led_TypeDef Led);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4_DIYMORE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
