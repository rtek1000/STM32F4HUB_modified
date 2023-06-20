/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file            : usb_host.c
 * @version         : v1.0_Cube
 * @brief           : This file implements the USB Host
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "usb_host.h"
#include <usbh_core.h>
#include <usbh_hid.h>
#include <usbh_hub.h>
#include <usbh_msc.h>

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USB Host core handle declaration */
USBH_HandleTypeDef hUSBHost[5];
ApplicationTypeDef Appli_state = APPLICATION_IDLE;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*
 * user callback declaration
 */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);
static void hub_process(void);
/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
 * Init USB host library, add supported class and start the library
 * @retval None
 */
void MX_USB_HOST_Init(void) {
	/* USER CODE BEGIN USB_HOST_Init_PreTreatment */

	/* USER CODE END USB_HOST_Init_PreTreatment */

	/* Init host Library, add supported class and start the library. */
//	memset(&hUSBHost[0], 0, sizeof(USBH_HandleTypeDef));
//
//	hUSBHost[0].valid = 1;
//	hUSBHost[0].address = USBH_DEVICE_ADDRESS;
//	hUSBHost[0].Pipes[0] = USBH_malloc(sizeof(uint32_t) * USBH_MAX_PIPES_NBR);
//
//	USBH_Init(&hUSBHost[0], USBH_UserProcess, ID_USB_HOST_HS);
//	USBH_RegisterClass(&hUSBHost[0], USBH_MSC_CLASS);
//	USBH_RegisterClass(&hUSBHost[0], USBH_HID_CLASS);
//	USBH_RegisterClass(&hUSBHost[0], USBH_HUB_CLASS);
//
//	USBH_Start(&hUSBHost[0]);

	memset(&hUSBHost[0], 0, sizeof(USBH_HandleTypeDef));

	hUSBHost[0].valid = 1;
	hUSBHost[0].address = USBH_DEVICE_ADDRESS;
	hUSBHost[0].Pipes[0] = USBH_malloc(sizeof(uint32_t) * USBH_MAX_PIPES_NBR);

	USBH_Init(&hUSBHost[0], USBH_UserProcess, ID_USB_HOST_FS);
	USBH_RegisterClass(&hUSBHost[0], USBH_HID_CLASS);
	USBH_RegisterClass(&hUSBHost[0], USBH_MSC_CLASS);
	USBH_RegisterClass(&hUSBHost[0], USBH_HUB_CLASS);

	USBH_Start(&hUSBHost[0]);
	/* USER CODE BEGIN USB_HOST_Init_PostTreatment */

	/* USER CODE END USB_HOST_Init_PostTreatment */
}

/*
 * Background task
 */
void MX_USB_HOST_Process(void) {
	/* USB Host Background task */
	hub_process();
}
/*
 * user callback definition
 */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id) {
	/* USER CODE BEGIN CALL_BACK_1 */
	switch (id) {
	case HOST_USER_SELECT_CONFIGURATION:
		break;

	case HOST_USER_DISCONNECTION:
		Appli_state = APPLICATION_DISCONNECT;
		break;

	case HOST_USER_CLASS_ACTIVE:
		Appli_state = APPLICATION_READY;
		break;

	case HOST_USER_CONNECTION:
		Appli_state = APPLICATION_START;
		break;

	default:
		break;
	}
	/* USER CODE END CALL_BACK_1 */
}

static void hub_process(void) {
	static uint8_t current_loop = -1;
	static USBH_HandleTypeDef *_phost = 0;

	if (_phost != NULL && _phost->valid == 1) {
		USBH_Process(_phost);

		if (_phost->busy)
			return;
	}

	while (1) {
		current_loop++;

		if (current_loop > MAX_HUB_PORTS) {
			current_loop = 0;
		}

		if (hUSBHost[current_loop].valid) {
			_phost = &hUSBHost[current_loop];
			USBH_LL_SetupEP0(_phost);

			if (_phost->valid == 3) {
				LOG("PROCESSING ATTACH %d", _phost->address);
				_phost->valid = 1;
				_phost->busy = 1;
			}

			break;
		}
	}

	if (_phost != NULL && _phost->valid) {
		HID_MOUSE_Info_TypeDef *minfo;
		minfo = USBH_HID_GetMouseInfo(_phost);

		if (minfo != NULL) {
			LOG("Btn %d%d%d %d%d%d%d%d %d%d%d %d%d%d; X %d; Y %d",
					minfo->buttons[0], minfo->buttons[1], minfo->buttons[2],
					minfo->buttons[3], minfo->buttons[4], minfo->buttons[5],
					minfo->buttons[6], minfo->buttons[7], minfo->buttons[8],
					minfo->buttons[9], minfo->buttons[10], minfo->buttons[11],
					minfo->buttons[12], minfo->buttons[13], minfo->x, minfo->y);
		} else {
			HID_KEYBD_Info_TypeDef *kinfo;
			kinfo = USBH_HID_GetKeybdInfo(_phost);
			if (kinfo != NULL) {
				LOG("KEYB %d", kinfo->keys[0]);
			}
		}
	}
}

/**
 * @}
 */

/**
 * @}
 */

