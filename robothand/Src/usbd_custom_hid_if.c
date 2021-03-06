/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v1.0_Cube
  * @brief          : USB Device Custom HID interface file.
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

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */
#include "rhpacket.h"

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
int16_t dr = 0;
unsigned char tempvar[64];

static void CMD_MotorStatusCTRL(Motor *motor,unsigned char *data);
static void CMD_PIDParaCTRL(Motor *motor,unsigned char *data);
static void CMD_MotionCTRL(Motor *motor,unsigned char *data);
static void CMD_IntervalCTRL(Motor *motor, unsigned char *data);
static void CMD_InteLimitCTRL(Motor *motor, unsigned char *data);
static void CMD_RHStatusRET(Motor *motor, unsigned char *data);

RH_CMD_PROCESS_Itf hCMDProcessfunc = 
{
	CMD_MotorStatusCTRL,
	CMD_PIDParaCTRL,
	CMD_MotionCTRL,
	CMD_IntervalCTRL,
	CMD_InteLimitCTRL,
	CMD_RHStatusRET,
};

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
	0x05, 0x8c, /* USAGE_PAGE (ST Page) */
	0x09, 0x01, /* USAGE (Demo Kit) */
	0xa1, 0x01, /* COLLECTION (Application) */
	/* 6 */ 

	// The Input report
	0x09,0x03, // USAGE ID - Vendor defined
	0x15,0x00, // LOGICAL_MINIMUM (0)
	0x26,0x00, 0xFF, // LOGICAL_MAXIMUM (255)
	0x75,0x08, // REPORT_SIZE (8)
	0x95,0x40, // REPORT_COUNT (40)
	0x81,0x02, // INPUT (Data,Var,Abs)
	//19
	// The Output report
	0x09,0x04, // USAGE ID - Vendor defined
	0x15,0x00, // LOGICAL_MINIMUM (0)
	0x26,0x00,0xFF, // LOGICAL_MAXIMUM (255)
	0x75,0x08, // REPORT_SIZE (8)
	0x95,0x40, // REPORT_COUNT (40)
	0x91,0x02, // OUTPUT (Data,Var,Abs)
//32
  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */
extern Motor motor[];
/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
	USBD_CUSTOM_HID_HandleTypeDef     *hhid;
  hhid = (USBD_CUSTOM_HID_HandleTypeDef*) hUsbDeviceFS.pClassData;

	static unsigned char *data = NULL;
	static uint8_t data_size = 0;
	if(IsPacketValid(hhid->Report_buf))
	{
		switch(GetPacketInfo(hhid->Report_buf, &data, &data_size))
		{
			case CMD:
				ProcessCMD(hCMDProcessfunc, motor, data, data_size);
				break;
			default:
				//Todo Send Error Log
				break;				
		}
	}
  return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */

int8_t USB_Send_64_bytes(void *report)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *) report, 64);
}

/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */



static void CMD_MotorStatusCTRL(Motor *motor, unsigned char *data)
{
	for(int i = 0; i < 4; i++)
	{
		if (data[i+1] == 1)
			motor[i].enable();
		else
			motor[i].disable();
	}
}

static void CMD_PIDParaCTRL(Motor *motor, unsigned char *data)
{
	int index = data[1];
	memcpy(&motor[index].m_pid, &data[2], 3*sizeof(float));
}

static void CMD_MotionCTRL(Motor *motor, unsigned char *data)
{
	int16_t *motion = (int16_t *) &data[1];
	for(int i = 0;i < 4; i++)
	{
		motor[i].setTrace(motion[i]);
	}
}

static void CMD_IntervalCTRL(Motor *motor, unsigned char *data)
{
	uint16_t interval = *(uint16_t *)&data[1];
	Motor::m_interval = interval;
	for(int i = 0;i < 4; i++)
	{
		motor[i].setInterval();
	}
}

static void CMD_InteLimitCTRL(Motor *motor, unsigned char *data)
{
	float intelimit;
	memcpy(&intelimit, &data[1], sizeof(float));
	for(int i = 0;i < 4; i++)
	{
		motor[i].setInteLimit(intelimit);
	}
}

static void CMD_RHStatusRET(Motor *motor, unsigned char *data)
{
	uint8_t msg[64];
  BuildRH_StatusMsg(motor, msg);
	USB_Send_64_bytes(msg);
}

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

