/**
  ******************************************************************************
  * @file    TIM2_OC_ActiveMode\main.c
  * @author  MCD Application Team
  * @version  V2.2.0
  * @date     30-September-2014
  * @brief   This file contains the main function for TIM2 OC ActiveMode Example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/**
  * @addtogroup TIM2_OC_ActiveMode
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CCR1_Val  ((uint16_t)500)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void TIM2_Config(void);
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  /* CLK configuration -----------------------------------------*/
  CLK_DeInit();
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8);
  
  GPIO_DeInit(GPIOA);
  GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_FAST);
  
  GPIO_DeInit(GPIOC);
  GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);  


  /* TIM2 configuration -----------------------------------------*/
  TIM2_Config();  
  

  while (1)
  {
    BitStatus bit_status;
    bit_status = GPIO_ReadInputPin(GPIOB, GPIO_PIN_2);
    if (bit_status == RESET)  //SET or RESET
    {
      GPIO_WriteReverse(GPIOC, GPIO_PIN_3);

    }
  
  } 
}



/**
  * @brief  Configure TIM2 peripheral to generate 1 PWM signals 
  * @param  None
  * @retval None
  */
static void TIM2_Config(void)
{
  /* Time base configuration */      
  TIM2_TimeBaseInit(TIM2_PRESCALER_1, 999);


  /* Output PWM1 Mode configuration: Channe2 */
  /*
    TIM2_OCMode = TIM2_OCMODE_PWM1
    TIM2_OutputState = TIM2_OUTPUTSTATE_ENABLE
    TIM2_Pulse = 500
    TIM2_OCPolarity = TIM2_OCPOLARITY_HIGH
  */
  TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, CCR1_Val, TIM2_OCPOLARITY_HIGH);

  
  TIM2_OC2PreloadConfig(ENABLE);


  TIM2_ARRPreloadConfig(ENABLE);
  
  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
