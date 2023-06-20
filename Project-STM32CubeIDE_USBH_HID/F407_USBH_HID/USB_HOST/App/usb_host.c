/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file            : usb_host.c
  * @version         : v1.0_Cube
  * @brief           : This file implements the USB Host
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "usbh_core.h"
#include "usbh_hid.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USB Host core handle declaration */
USBH_HandleTypeDef hUsbHostFS;
ApplicationTypeDef Appli_state = APPLICATION_IDLE;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */
HID_KEYBD_Info_TypeDef *keybd_info1;
extern HID_MOUSE_Info_TypeDef mouse_info;

void USBH_HID_EventCallback(USBH_HandleTypeDef *phost) {
	uint8_t idx = phost->device.current_interface;

	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];
	if (HID_Handle->Init == USBH_HID_KeybdInit) {
		keybd_info1 = USBH_HID_GetKeybdInfo(phost);

		USBH_UsrLog("KB action: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x",
					keybd_info1->keys[0], keybd_info1->keys[1],
					keybd_info1->keys[2], keybd_info1->keys[3],
					keybd_info1->keys[4], keybd_info1->keys[5]); // USBH_DbgLog

		USBH_UsrLog(
					"lalt: %d, ralt: %d, lctrl: %d, rctrl: %d, lgui: %d, rgui: %d, lshift: %d, rshift: %d, state: %d",
					keybd_info1->lalt, keybd_info1->ralt, keybd_info1->lctrl,
					keybd_info1->rctrl, keybd_info1->lgui, keybd_info1->rgui,
					keybd_info1->lshift, keybd_info1->rshift,
					keybd_info1->state);
	} else if (HID_Handle->Init == USBH_HID_MouseInit) {
		USBH_HID_GetMouseInfo(phost);

		USBH_UsrLog(
				"Mouse action: x=  0x%x, y=  0x%x, button1= 0x%x, button2= 0x%x, button3= 0x%x \n",
				mouse_info.x, mouse_info.y, mouse_info.buttons[0],
				mouse_info.buttons[1], mouse_info.buttons[2]);
	}
}
/* USER CODE END 0 */

/*
 * user callback declaration
 */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * Init USB host library, add supported class and start the library
  * @retval None
  */
void MX_USB_HOST_Init(void)
{
  /* USER CODE BEGIN USB_HOST_Init_PreTreatment */

  /* USER CODE END USB_HOST_Init_PreTreatment */

  /* Init host Library, add supported class and start the library. */
  if (USBH_Init(&hUsbHostFS, USBH_UserProcess, HOST_FS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_RegisterClass(&hUsbHostFS, USBH_HID_CLASS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_Start(&hUsbHostFS) != USBH_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_HOST_Init_PostTreatment */

  /* USER CODE END USB_HOST_Init_PostTreatment */
}

/*
 * Background task
 */
void MX_USB_HOST_Process(void)
{
  /* USB Host Background task */
  USBH_Process(&hUsbHostFS);
}
/*
 * user callback definition
 */
static void USBH_UserProcess  (USBH_HandleTypeDef *phost, uint8_t id)
{
  /* USER CODE BEGIN CALL_BACK_1 */
  switch(id)
  {
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

/**
  * @}
  */

/**
  * @}
  */

