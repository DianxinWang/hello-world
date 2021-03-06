/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define MOTOR_1A_Pin GPIO_PIN_0
#define MOTOR_1A_GPIO_Port GPIOA
#define MOTOR_1B_Pin GPIO_PIN_1
#define MOTOR_1B_GPIO_Port GPIOA
#define MOTOR_2A_Pin GPIO_PIN_2
#define MOTOR_2A_GPIO_Port GPIOA
#define MOTOR_2B_Pin GPIO_PIN_3
#define MOTOR_2B_GPIO_Port GPIOA
#define FORCE_5_Pin GPIO_PIN_4
#define FORCE_5_GPIO_Port GPIOA
#define FORCE_4_Pin GPIO_PIN_5
#define FORCE_4_GPIO_Port GPIOA
#define FORCE_3_Pin GPIO_PIN_6
#define FORCE_3_GPIO_Port GPIOA
#define FORCE_2_Pin GPIO_PIN_7
#define FORCE_2_GPIO_Port GPIOA
#define FORCE_1_Pin GPIO_PIN_4
#define FORCE_1_GPIO_Port GPIOC
#define MOTOR_EN_1_Pin GPIO_PIN_0
#define MOTOR_EN_1_GPIO_Port GPIOB
#define MOTOR_EN_2_Pin GPIO_PIN_1
#define MOTOR_EN_2_GPIO_Port GPIOB
#define MOTOR_EN_3_Pin GPIO_PIN_10
#define MOTOR_EN_3_GPIO_Port GPIOB
#define MOTOR_EN_4_Pin GPIO_PIN_11
#define MOTOR_EN_4_GPIO_Port GPIOB
#define ENCODER_EN_1_Pin GPIO_PIN_12
#define ENCODER_EN_1_GPIO_Port GPIOB
#define ENCODER_EN_2_Pin GPIO_PIN_13
#define ENCODER_EN_2_GPIO_Port GPIOB
#define ENCODER_EN_3_Pin GPIO_PIN_14
#define ENCODER_EN_3_GPIO_Port GPIOB
#define MOTOR_3B_Pin GPIO_PIN_6
#define MOTOR_3B_GPIO_Port GPIOC
#define MOTOR_3A_Pin GPIO_PIN_7
#define MOTOR_3A_GPIO_Port GPIOC
#define MOTOR_4A_Pin GPIO_PIN_8
#define MOTOR_4A_GPIO_Port GPIOC
#define MOTOR_4B_Pin GPIO_PIN_9
#define MOTOR_4B_GPIO_Port GPIOC
#define ENCODER_1B_Pin GPIO_PIN_8
#define ENCODER_1B_GPIO_Port GPIOA
#define ENCODER_1A_Pin GPIO_PIN_9
#define ENCODER_1A_GPIO_Port GPIOA
#define USB_EN_Pin GPIO_PIN_10
#define USB_EN_GPIO_Port GPIOA
#define ENCODER_2B_Pin GPIO_PIN_15
#define ENCODER_2B_GPIO_Port GPIOA
#define ENCODER_4Z_Pin GPIO_PIN_10
#define ENCODER_4Z_GPIO_Port GPIOC
#define ENCODER_3Z_Pin GPIO_PIN_11
#define ENCODER_3Z_GPIO_Port GPIOC
#define ENCODER_2Z_Pin GPIO_PIN_12
#define ENCODER_2Z_GPIO_Port GPIOC
#define ENCODER_1Z_Pin GPIO_PIN_2
#define ENCODER_1Z_GPIO_Port GPIOD
#define ENCODER_2A_Pin GPIO_PIN_3
#define ENCODER_2A_GPIO_Port GPIOB
#define ENCODER_3A_Pin GPIO_PIN_4
#define ENCODER_3A_GPIO_Port GPIOB
#define ENCODER_3B_Pin GPIO_PIN_5
#define ENCODER_3B_GPIO_Port GPIOB
#define ENCODER_4A_Pin GPIO_PIN_6
#define ENCODER_4A_GPIO_Port GPIOB
#define ENCODER_4B_Pin GPIO_PIN_7
#define ENCODER_4B_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
