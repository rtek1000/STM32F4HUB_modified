/**
 ******************************************************************************
 * @file    usbh_hid.c
 * @author  MCD Application Team
 * @brief   This file is the HID Layer Handlers for USB Host HID class.
 *
 * @verbatim
 *
 *          ===================================================================
 *                                HID Class  Description
 *          ===================================================================
 *           This module manages the HID class V1.11 following the "Device Class Definition
 *           for Human Interface Devices (HID) Version 1.11 Jun 27, 2001".
 *           This driver implements the following aspects of the specification:
 *             - The Boot Interface Subclass
 *             - The Mouse and Keyboard protocols
 *
 *  @endverbatim
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                      www.st.com/SLA0044
 *
 ******************************************************************************
 */

/* BSPDependencies
 - "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
 - "stm32xxxxx_{eval}{discovery}_io.c"
 - "stm32xxxxx_{eval}{discovery}{adafruit}_lcd.c"
 - "stm32xxxxx_{eval}{discovery}_sdram.c"
 EndBSPDependencies */

/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "usbh_hid.h"
#include "usbh_hid_parser.h"
//#include "main.h"

/** @addtogroup USBH_LIB
 * @{
 */

/** @addtogroup USBH_CLASS
 * @{
 */

/** @addtogroup USBH_HID_CLASS
 * @{
 */

/** @defgroup USBH_HID_CORE
 * @brief    This file includes HID Layer Handlers for USB Host HID class.
 * @{
 */

/** @defgroup USBH_HID_CORE_Private_TypesDefinitions
 * @{
 */
/**
 * @}
 */

/** @defgroup USBH_HID_CORE_Private_Defines
 * @{
 */
/**
 * @}
 */

/** @defgroup USBH_HID_CORE_Private_Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup USBH_HID_CORE_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup USBH_HID_CORE_Private_FunctionPrototypes
 * @{
 */

static USBH_StatusTypeDef USBH_HID_InterfaceInit(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_HID_InterfaceDeInit(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_HID_ClassRequest(USBH_HandleTypeDef *phost);
static void USBH_HID_IncrementInterface(USBH_HandleTypeDef *phost);
static uint8_t USB_Get_Keyboard_LED_Status(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USB_Set_Keyboard_LED_Status(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_HID_Process(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef USBH_HID_SOFProcess(USBH_HandleTypeDef *phost);
static void USBH_HID_ParseHIDDesc(HID_DescTypeDef *desc, uint8_t *buf);

extern USBH_StatusTypeDef USBH_HID_MouseInit(USBH_HandleTypeDef *phost);
extern USBH_StatusTypeDef USBH_HID_KeybdInit(USBH_HandleTypeDef *phost);

USBH_ClassTypeDef HID_Class = { "HID", USB_HID_CLASS, USBH_HID_InterfaceInit,
		USBH_HID_InterfaceDeInit, USBH_HID_ClassRequest, USBH_HID_Process,
		USBH_HID_SOFProcess };

//USBH_ClassTypeDef HID_Class = { "HID",
//USB_HID_CLASS, USBH_HID_InterfaceInit, USBH_HID_InterfaceDeInit,
//		USBH_HID_ClassRequest, USBH_HID_Process, USBH_HID_SOFProcess,
//		NULL, };
/**
 * @}
 */

/** @defgroup USBH_HID_CORE_Private_Functions
 * @{
 */

/**
 * @brief  USBH_HID_InterfaceInit
 *         The function init the HID class.
 * @param  phost: Host handle
 * @retval USBH Status
 */
static USBH_StatusTypeDef USBH_HID_InterfaceInit(USBH_HandleTypeDef *phost) {
	USBH_StatusTypeDef status;
	HID_HandleTypeDef *HID_Handle;
	uint8_t max_ep;
	uint8_t ep_index = 0U;
	uint8_t interface_check;
	uint8_t interface_index;

	USBH_UsrLog("USBH_HID_InterfaceInit");

	// dump everything
	uint8_t num_interfaces = phost->device.CfgDesc.bNumInterfaces;

	for (interface_index = 0; interface_index < num_interfaces;
			interface_index++) {

		interface_check = USBH_CheckInterface(phost, interface_index,
				phost->pActiveClass->ClassCode, HID_BOOT_CODE, 0xFFU);

		if ((interface_check == 0xFFU)
				|| (interface_check >= USBH_MAX_NUM_INTERFACES)) /* No Valid Interface */
				{

//			if (interface_index == 0) {
			USBH_UsrLog("Interface %d, cannot find the HID_BOOT_CODE, skip",
					interface_index);

			USBH_UsrLog("Interface %d, try to find the HID_CUSTOM_BOOT_CODE",
					interface_index);

			interface_check = USBH_CheckInterface(phost, interface_index,
					phost->pActiveClass->ClassCode, HID_CUSTOM_BOOT_CODE,
					0xFFU);
//			}
		}

		// USBH_UsrLog("interface_check: %d", interface_check);

		if ((interface_check == 0xFFU)
				|| (interface_check >= USBH_MAX_NUM_INTERFACES)) /* No Valid Interface */
				{
			phost->device.skip_interface = 1U;
			USBH_UsrLog("Interface %d, cannot find the HID_BOOT_CODE, skip",
					interface_index);
			USBH_UsrLog("(This interface can be for Multimedia functions)\n");
			//return USBH_FAIL;

			HID_Handle =
					(HID_HandleTypeDef*) phost->pActiveClass->pData_array[interface_index];
			//return USBH_OK;
		} else {
			phost->device.skip_interface = 0U;
			status = USBH_SelectInterface(phost, interface_index);

			if (status != USBH_OK) {
				return USBH_FAIL;
			}

			USBH_UsrLog("Class    : %xh",
					phost->device.CfgDesc.Itf_Desc[interface_index].bInterfaceClass);
			USBH_UsrLog("SubClass : %xh",
					phost->device.CfgDesc.Itf_Desc[interface_index].bInterfaceSubClass);
			USBH_UsrLog("Protocol : %xh",
					phost->device.CfgDesc.Itf_Desc[interface_index].bInterfaceProtocol);

			phost->pActiveClass->pData_array[interface_index] =
					(HID_HandleTypeDef*) USBH_malloc(sizeof(HID_HandleTypeDef));
			HID_Handle =
					(HID_HandleTypeDef*) phost->pActiveClass->pData_array[interface_index];

			if (HID_Handle == NULL) {
				USBH_DbgLog("Cannot allocate memory for HID Handle");
				return USBH_FAIL;
			}

			/* Initialize hid handler */
			(void) USBH_memset(HID_Handle, 0U, sizeof(HID_HandleTypeDef));

			HID_Handle->state = HID_ERROR;

			/*Decode Bootclass Protocol: Mouse or Keyboard*/
			uint8_t Iprot =
					phost->device.CfgDesc.Itf_Desc[interface_index].bInterfaceProtocol;

			if ((Iprot == HID_KEYBRD_BOOT_CODE)
					|| (Iprot == HID_MOUSE_BOOT_CODE)
					|| (Iprot == HID_CUSTOM_BOOT_CODE)) {

				if (Iprot == HID_KEYBRD_BOOT_CODE) {
					USBH_UsrLog("KeyBoard device found!");
					HID_Handle->Init = USBH_HID_KeybdInit;
					HID_Handle->state = HID_INIT;
					HID_Handle->ctl_state = HID_REQ_INIT;

					if (USBH_KEYBOARD_LED_NUM_LOCK_START == 1U) {
						phost->device.kbd_LED_status = 0xFFU;
						phost->device.kbd_LED_supported = 1U; // todo
					}

				} else if (Iprot == HID_MOUSE_BOOT_CODE) {
					USBH_UsrLog("Mouse device found!");
					HID_Handle->Init = USBH_HID_MouseInit;
					HID_Handle->state = HID_INIT;
					HID_Handle->ctl_state = HID_REQ_INIT;
					phost->device.kbd_LED_supported = 0U; // todo

				} else { // if (Iprot == HID_CUSTOM_BOOT_CODE) {
					USBH_UsrLog("Custom device found!");
					HID_Handle->Init = USBH_HID_CustomInit;
					HID_Handle->state = HID_INIT;
					HID_Handle->ctl_state = HID_REQ_INIT;
				}

				/* Check of available number of endpoints */
				/* Find the number of EPs in the Interface Descriptor */
				/* Choose the lower number in order not to overrun the buffer allocated */
				if (phost->device.CfgDesc.Itf_Desc[interface_index].bNumEndpoints
						<= USBH_MAX_NUM_ENDPOINTS) {
					max_ep =
							phost->device.CfgDesc.Itf_Desc[interface_index].bNumEndpoints;
				} else {
					max_ep = USBH_MAX_NUM_ENDPOINTS;
				}

				USBH_UsrLog("max_ep: %d", max_ep);

				/* Decode endpoint IN and OUT address from interface descriptor */
				for (ep_index = 0U; ep_index < max_ep; ep_index++) {
					USBH_InterfaceDescTypeDef *interface_x =
							&phost->device.CfgDesc.Itf_Desc[interface_index];

					USBH_EpDescTypeDef *ep_desc =
							&interface_x->Ep_Desc[ep_index];

					if (ep_desc->bEndpointAddress & 0x80U) {
						HID_Handle->InEp =
								(phost->device.CfgDesc.Itf_Desc[interface_index].Ep_Desc[ep_index].bEndpointAddress);
						HID_Handle->InPipe = USBH_AllocPipe(phost,
								HID_Handle->InEp);

						HID_Handle->ep_addr_array[0] =
								phost->device.CfgDesc.Itf_Desc[interface_index].Ep_Desc[ep_index].bEndpointAddress;
						HID_Handle->length_array[0] =
								phost->device.CfgDesc.Itf_Desc[interface_index].Ep_Desc[ep_index].wMaxPacketSize;
						HID_Handle->poll_array[0] =
								phost->device.CfgDesc.Itf_Desc[interface_index].Ep_Desc[ep_index].bInterval;

						if (HID_Handle->poll_array[0] < HID_MIN_POLL) {
							HID_Handle->poll_array[0] = HID_MIN_POLL;
						}

						/* Open pipe for IN endpoint */
						(void) USBH_OpenPipe(phost, HID_Handle->InPipe,
								HID_Handle->InEp, phost->device.address,
								phost->device.speed, USB_EP_TYPE_INTR,
								HID_Handle->length_array[0]);

						(void) USBH_LL_SetToggle(phost, HID_Handle->InPipe, 0U);
					} else {
						HID_Handle->OutEp =
								(phost->device.CfgDesc.Itf_Desc[interface_index].Ep_Desc[ep_index].bEndpointAddress);
						HID_Handle->OutPipe = USBH_AllocPipe(phost,
								HID_Handle->OutEp);

						HID_Handle->ep_addr_array[1] =
								phost->device.CfgDesc.Itf_Desc[interface_index].Ep_Desc[ep_index].bEndpointAddress;
						HID_Handle->length_array[1] =
								phost->device.CfgDesc.Itf_Desc[interface_index].Ep_Desc[ep_index].wMaxPacketSize;
						HID_Handle->poll_array[1] =
								phost->device.CfgDesc.Itf_Desc[interface_index].Ep_Desc[ep_index].bInterval;

						if (HID_Handle->poll_array[1] < HID_MIN_POLL) {
							HID_Handle->poll_array[1] = HID_MIN_POLL;
						}

						/* Open pipe for OUT endpoint */
						(void) USBH_OpenPipe(phost, HID_Handle->OutPipe,
								HID_Handle->OutEp, phost->device.address,
								phost->device.speed, USB_EP_TYPE_INTR,
								HID_Handle->length_array[1]);

						(void) USBH_LL_SetToggle(phost, HID_Handle->OutPipe,
								0U);
					}

					USBH_UsrLog(
							"Interface %u, endpoint #%u: address 0x%02x, attributes 0x%02x\n",
							interface_index, ep_index,
							ep_desc->bEndpointAddress, ep_desc->bmAttributes);
				}
			} else {
				USBH_UsrLog("Protocol not supported.");
				phost->device.skip_interface = 1U;
				//return USBH_FAIL;
			}
		}
	}

	interface_index = 0;

	status = USBH_SelectInterface(phost, interface_index);

	if (status != USBH_OK) {
		return USBH_FAIL;
	}

	return USBH_OK;
}

/**
 * @brief  USBH_HID_InterfaceDeInit
 *         The function DeInit the Pipes used for the HID class.
 * @param  phost: Host handle
 * @retval USBH Status
 */
static USBH_StatusTypeDef USBH_HID_InterfaceDeInit(USBH_HandleTypeDef *phost) {
	uint8_t idx = 0;

	for (; idx < phost->device.CfgDesc.bNumInterfaces; ++idx) {
		HID_HandleTypeDef *HID_Handle =
				(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];

		if (HID_Handle->InPipe != 0x00U) {
			(void) USBH_ClosePipe(phost, HID_Handle->InPipe);
			(void) USBH_FreePipe(phost, HID_Handle->InPipe);
			HID_Handle->InPipe = 0U; /* Reset the pipe as Free */
		}

		if (HID_Handle->OutPipe != 0x00U) {
			(void) USBH_ClosePipe(phost, HID_Handle->OutPipe);
			(void) USBH_FreePipe(phost, HID_Handle->OutPipe);
			HID_Handle->OutPipe = 0U; /* Reset the pipe as Free */
		}

		if ((phost->pActiveClass->pData_array[idx]) != NULL) {
			USBH_free(phost->pActiveClass->pData_array[idx]);
			phost->pActiveClass->pData_array[idx] = 0U;
		}
	}

	return USBH_OK;
}

/**
 * @brief  USBH_HID_ClassRequest
 *         The function is responsible for handling Standard requests
 *         for HID class.
 * @param  phost: Host handle
 * @retval USBH Status
 */
static USBH_StatusTypeDef USBH_HID_ClassRequest(USBH_HandleTypeDef *phost) {

	USBH_StatusTypeDef status = USBH_BUSY;
	USBH_StatusTypeDef classReqStatus = USBH_BUSY;
	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[0];

	/* Switch HID state machine */
	switch (HID_Handle->ctl_state) {
	case HID_REQ_INIT:
	case HID_REQ_GET_HID_DESC:

		USBH_HID_ParseHIDDesc(&HID_Handle->HID_Desc, phost->device.CfgDesc_Raw);

		HID_Handle->ctl_state = HID_REQ_GET_REPORT_DESC;

		break;
	case HID_REQ_GET_REPORT_DESC:

		/* Get Report Desc */
		classReqStatus = USBH_HID_GetHIDReportDescriptor(phost,
				HID_Handle->HID_Desc.wItemLength);
		if (classReqStatus == USBH_OK) {
			/* The descriptor is available in phost->device.Data */

#if PRINT_HID_REPORT_DESCRIPTOR == 1
			USBH_UsrLog("Dump HID Report Descriptor start");
			printf("wItemLength %d\n", HID_Handle->HID_Desc.wItemLength);

			for(uint16_t i = 0; i < HID_Handle->HID_Desc.wItemLength; i++){
				printf("0x%02X ", phost->device.Data[i]);
			}

			printf("\n");
			USBH_UsrLog("Dump HID Report Descriptor end");
#endif // #if PRINT_HID_REPORT_DESCRIPTOR == 1

			HID_Handle->ctl_state = HID_REQ_SET_IDLE;
		} else if (classReqStatus == USBH_NOT_SUPPORTED) {
			USBH_ErrLog(
					"Control error: HID: Device Get Report Descriptor request failed");
			status = USBH_FAIL;
		} else {
			/* .. */
		}

		break;

	case HID_REQ_SET_IDLE:

		classReqStatus = USBH_HID_SetIdle(phost, 0U, 0U);

		/* set Idle */
		if (classReqStatus == USBH_OK) {
			HID_Handle->ctl_state = HID_REQ_SET_PROTOCOL;
		} else {
			if (classReqStatus == USBH_NOT_SUPPORTED) {
				HID_Handle->ctl_state = HID_REQ_SET_PROTOCOL;
			}
		}
		break;

	case HID_REQ_SET_PROTOCOL:
		/* set protocol */
		classReqStatus = USBH_HID_SetProtocol(phost, 0U);
		if (classReqStatus == USBH_OK) {
			HID_Handle->ctl_state = HID_REQ_IDLE;

			/* all requests performed*/
			phost->pUser(phost, HOST_USER_CLASS_ACTIVE);
			status = USBH_OK;
		} else if (classReqStatus == USBH_NOT_SUPPORTED) {
			USBH_ErrLog(
					"Control error: HID: Device Set protocol request failed");
			status = USBH_FAIL;
		} else {
			/* .. */
		}
		break;
	case HID_REQ_IDLE:
	default:
		break;
	}

	return status;
}

static void USBH_HID_IncrementInterface(USBH_HandleTypeDef *phost) {
	uint8_t max_loop = phost->device.CfgDesc.bNumInterfaces;

	while (max_loop--) {
		// switch interface
		phost->device.current_interface++;

		if (phost->device.current_interface
				>= phost->device.CfgDesc.bNumInterfaces) {
			phost->device.current_interface = 0U;
		}

		if (phost->device.skip_interface == 0U) {
			//USBH_UsrLog("current_interface: %d",
			//		phost->device.current_interface);
			break;
		}
	}
}

static uint8_t USB_Get_Keyboard_LED_Status(USBH_HandleTypeDef *phost) {
	uint8_t idx = phost->device.current_interface;

	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];

	if (HID_Handle->Init != USBH_HID_KeybdInit) {
		return 0xFF;
	}

	USBH_StatusTypeDef status;

	for (uint8_t timeout = 0U; timeout < 15; timeout++) {
		status = USBH_HID_GetReport(phost, 0x02U, 0U, HID_Handle->pData,
				(uint8_t) HID_Handle->length_array[0]);

		if (status == USBH_OK) {
			//USBH_UsrLog("USBH_OK USBH_OK");
			return HID_Handle->pData[0];
		}

		USBH_Delay(5);
	}

	return 0xFF;
}

static USBH_StatusTypeDef USB_Set_Keyboard_LED_Status(USBH_HandleTypeDef *phost) {
	if(phost->device.kbd_LED_supported == 0) {
		return HAL_OK;
	}

	if ((phost->Timer - phost->device.kbd_led_status_tick) < 50) {
		return HAL_OK;
	}

	phost->device.kbd_led_status_tick = phost->Timer;

	if (phost->device.kbd_LED_status == 0xFFU) {
		phost->device.kbd_LED_status = 0b001U;
	}

	uint8_t idx = phost->device.current_interface;

	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];

	if (HID_Handle->Init != USBH_HID_KeybdInit) {
		return HAL_OK;
	}

	uint8_t LED_status = phost->device.kbd_LED_status & 7U;

	uint8_t status_get = USB_Get_Keyboard_LED_Status(phost);

	if ((status_get == 0xFF) || (status_get == LED_status)) {
		return HAL_OK;
	}

	HID_Handle->pData[0] = LED_status;
	HID_Handle->pData[1] = 0;

	USBH_StatusTypeDef status_set;

	for (uint8_t timeout = 0U; timeout < 15U; timeout++) {
		status_set = USBH_HID_SetReport(phost, 0x02U, 0U, HID_Handle->pData,
				(uint8_t) HID_Handle->length_array[0]);

		if (status_set == USBH_OK) {
			break;
		}

		USBH_Delay(5);
	}

//	if (status_set == USBH_OK) {
//		uint8_t status_get = USB_Get_Keyboard_LED_Status(phost);
//
//		if (status_get == LED_status) {
	return USBH_OK;
//		}
//	}

//	return USBH_NOT_SUPPORTED;
}

/**
 * @brief  USBH_HID_Process
 *         The function is for managing state machine for HID data transfers
 * @param  phost: Host handle
 * @retval USBH Status
 */
static USBH_StatusTypeDef USBH_HID_Process(USBH_HandleTypeDef *phost) {
	USBH_StatusTypeDef status = USBH_OK;

	uint8_t URBState;

	uint8_t idx = phost->device.current_interface;

	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];

	uint32_t XferSize;

	switch (HID_Handle->state) {
	case HID_INIT:
		//USBH_UsrLog("HID_INIT");
		HID_Handle->Init(phost);
		HID_Handle->state = HID_IDLE;
		HID_Handle->Timeout = USBH_GetTick();

#if (USBH_USE_OS == 1U)
      phost->os_msg = (uint32_t)USBH_URB_EVENT;
#if (osCMSIS < 0x20000U)
      (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
      (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, 0U);
#endif
#endif
		break;

	case HID_IDLE:
		//USBH_UsrLog("HID_IDLE");
		status = USBH_HID_GetReport(phost, 0x01U, 0U, HID_Handle->pData,
				(uint8_t) HID_Handle->length_array[0]);
		if (status == USBH_OK) {
//			USBH_UsrLog("status USBH_OK");
			HID_Handle->state = HID_SYNC;
		} else if (status == USBH_BUSY) {
//			USBH_UsrLog("status USBH_BUSY");
			HID_Handle->state = HID_IDLE;
			status = USBH_OK;
		} else if (status == USBH_NOT_SUPPORTED) {
//			USBH_UsrLog("status USBH_NOT_SUPPORTED");
			HID_Handle->state = HID_SYNC;
			status = USBH_OK;
		} else {
//			USBH_UsrLog("status HID_ERROR");
			HID_Handle->state = HID_ERROR;
			status = USBH_FAIL;
		}

#if (USBH_USE_OS == 1U)
      phost->os_msg = (uint32_t)USBH_URB_EVENT;
#if (osCMSIS < 0x20000U)
      (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
      (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, 0U);
#endif
#endif
		break;

	case HID_SYNC:
		//USBH_UsrLog("HID_SYNC");
		/* Sync with start of Even Frame */
		if ((phost->Timer & 1U) != 0U) {
			HID_Handle->state = HID_GET_DATA;
		}

#if (USBH_USE_OS == 1U)
      phost->os_msg = (uint32_t)USBH_URB_EVENT;
#if (osCMSIS < 0x20000U)
      (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
      (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, 0U);
#endif
#endif
		break;

	case HID_GET_DATA:
		//USBH_UsrLog("HID_GET_DATA");
		(void) USBH_InterruptReceiveData(phost, HID_Handle->pData,
				(uint8_t) HID_Handle->length_array[0], HID_Handle->InPipe);

		HID_Handle->state = HID_POLL;
		HID_Handle->timer = phost->Timer;
		HID_Handle->DataReady = 0U;
		break;

	case HID_POLL:
		//USBH_UsrLog("HID_POLL");
		URBState = (uint8_t) USBH_LL_GetURBState(phost, HID_Handle->InPipe);

		if (URBState == USBH_URB_DONE) {
			HID_Handle->Timeout = USBH_GetTick(); //0;
			//USBH_UsrLog("USBH_URB_DONE, interface: %d", idx);
			XferSize = USBH_LL_GetLastXferSize(phost, HID_Handle->InPipe);

			if ((HID_Handle->DataReady == 0U) && (XferSize != 0U)) {
				(void) USBH_HID_FifoWrite(&HID_Handle->fifo, HID_Handle->pData,
						HID_Handle->length_array[0]);
				HID_Handle->DataReady = 1U;
				USBH_HID_EventCallback(phost);

				if (HID_Handle->Init == USBH_HID_KeybdInit) {
					phost->device.kbd_led_status_tick = phost->Timer;
				}

#if (USBH_USE_OS == 1U)
          phost->os_msg = (uint32_t)USBH_URB_EVENT;
#if (osCMSIS < 0x20000U)
          (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
          (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, 0U);
#endif
#endif
			}
		} else if (URBState == USBH_URB_STALL) {
			//USBH_UsrLog("USBH_URB_STALL");
			/* Issue Clear Feature on interrupt IN endpoint */
			if (USBH_ClrFeature(phost, HID_Handle->ep_addr_array[0])
					== USBH_OK) {
				/* Change state to issue next IN token */
				HID_Handle->state = HID_GET_DATA;

				// switch interface
				USBH_HID_IncrementInterface(phost);

				// USBH_UsrLog("current_interface: %d",
				//		phost->device.current_interface);
			}

		} else {
			if (URBState == USBH_URB_ERROR) {

				//USBH_ErrLog("USBH_URB_ERROR");
			} else if (URBState == USBH_URB_NOTREADY) {
				// USBH_UsrLog("USBH_URB_NOTREADY");
			} else if (URBState == USBH_URB_NYET) {
				// USBH_UsrLog("USBH_URB_NYET");
			} else {
				if (URBState != USBH_URB_IDLE) {
					USBH_UsrLog("URBState: %d", URBState);
				}
			}

			if (URBState == USBH_URB_IDLE) {
				// USBH_UsrLog("Timer: 0x%08lu", phost->Timer);
				if (HID_Handle->Init == USBH_HID_KeybdInit) {
					USB_Set_Keyboard_LED_Status(phost);
				} else if (HID_Handle->Init == USBH_HID_CustomInit) {
					// vibration feedback
				}
			} else {
				if ((USBH_GetTick() - HID_Handle->Timeout)
						> USBH_DEV_RESET_TIMEOUT) {
					//USBH_UsrLog("USB Configuration Failed, Please unplug the Device.");
					HID_Handle->state = HID_ERROR;
					HID_Handle->Timeout = USBH_GetTick(); //0;
				}
			}
		}
		break;
	case HID_ERROR:
		HID_Handle->state = HID_SYNC;
		USBH_UsrLog("case HID_ERROR");
		// USBH_RecoveryPhost(phost);
		break;
	default:
		break;
	}

	return status;
}

/**
 * @brief  USBH_HID_SOFProcess
 *         The function is for managing the SOF Process
 * @param  phost: Host handle
 * @retval USBH Status
 */
static USBH_StatusTypeDef USBH_HID_SOFProcess(USBH_HandleTypeDef *phost) {
	uint8_t idx = phost->device.current_interface;

	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];

	if (HID_Handle->state == HID_POLL) {
		if ((phost->Timer - HID_Handle->timer) >= HID_Handle->poll_array[0]) {
			HID_Handle->state = HID_GET_DATA;

#if (USBH_USE_OS == 1U)
      phost->os_msg = (uint32_t)USBH_URB_EVENT;
#if (osCMSIS < 0x20000U)
      (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
      (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, 0U);
#endif
#endif

			// switch interface
			USBH_HID_IncrementInterface(phost);
		}
	}
	return USBH_OK;
}

/**
 * @brief  USBH_Get_HID_ReportDescriptor
 *         Issue report Descriptor command to the device. Once the response
 *         received, parse the report descriptor and update the status.
 * @param  phost: Host handle
 * @param  Length : HID Report Descriptor Length
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_HID_GetHIDReportDescriptor(USBH_HandleTypeDef *phost,
		uint16_t length) {

	USBH_StatusTypeDef status;

	status = USBH_GetDescriptor(phost,
	USB_REQ_RECIPIENT_INTERFACE | USB_REQ_TYPE_STANDARD,
	USB_DESC_HID_REPORT, phost->device.Data, length);

	/* HID report descriptor is available in phost->device.Data.
	 In case of USB Boot Mode devices for In report handling ,
	 HID report descriptor parsing is not required.
	 In case, for supporting Non-Boot Protocol devices and output reports,
	 user may parse the report descriptor*/

	return status;
}

/**
 * @brief  USBH_Get_HID_Descriptor
 *         Issue HID Descriptor command to the device. Once the response
 *         received, parse the report descriptor and update the status.
 * @param  phost: Host handle
 * @param  Length : HID Descriptor Length
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_HID_GetHIDDescriptor(USBH_HandleTypeDef *phost,
		uint16_t length) {
	USBH_StatusTypeDef status;

	status = USBH_GetDescriptor(phost,
	USB_REQ_RECIPIENT_INTERFACE | USB_REQ_TYPE_STANDARD,
	USB_DESC_HID, phost->device.Data, length);

	return status;
}

/**
 * @brief  USBH_Set_Idle
 *         Set Idle State.
 * @param  phost: Host handle
 * @param  duration: Duration for HID Idle request
 * @param  reportId : Targeted report ID for Set Idle request
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_HID_SetIdle(USBH_HandleTypeDef *phost, uint8_t duration,
		uint8_t reportId) {

	phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE
			|
			USB_REQ_TYPE_CLASS;

	phost->Control.setup.b.bRequest = USB_HID_SET_IDLE;
	phost->Control.setup.b.wValue.w = (uint16_t) (((uint32_t) duration << 8U)
			| (uint32_t) reportId);

	phost->Control.setup.b.wIndex.w = 0U;
	phost->Control.setup.b.wLength.w = 0U;

	return USBH_CtlReq(phost, NULL, 0U);
}

/**
 * @brief  USBH_HID_Set_Report
 *         Issues Set Report
 * @param  phost: Host handle
 * @param  reportType  : Report type to be sent
 * @param  reportId    : Targeted report ID for Set Report request
 * @param  reportBuff  : Report Buffer
 * @param  reportLen   : Length of data report to be send
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_HID_SetReport(USBH_HandleTypeDef *phost,
		uint8_t reportType, uint8_t reportId, uint8_t *reportBuff,
		uint8_t reportLen) {

	phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE
			|
			USB_REQ_TYPE_CLASS;

	phost->Control.setup.b.bRequest = USB_HID_SET_REPORT;
	phost->Control.setup.b.wValue.w = (uint16_t) (((uint32_t) reportType << 8U)
			| (uint32_t) reportId);

	phost->Control.setup.b.wIndex.w = 0U;
	phost->Control.setup.b.wLength.w = reportLen;

	return USBH_CtlReq(phost, reportBuff, (uint16_t) reportLen);
}

/**
 * @brief  USBH_HID_GetReport
 *         retrieve Set Report
 * @param  phost: Host handle
 * @param  reportType  : Report type to be sent
 * @param  reportId    : Targeted report ID for Set Report request
 * @param  reportBuff  : Report Buffer
 * @param  reportLen   : Length of data report to be send
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_HID_GetReport(USBH_HandleTypeDef *phost,
		uint8_t reportType, uint8_t reportId, uint8_t *reportBuff,
		uint8_t reportLen) {

	phost->Control.setup.b.bmRequestType = USB_D2H | USB_REQ_RECIPIENT_INTERFACE
			|
			USB_REQ_TYPE_CLASS;

	phost->Control.setup.b.bRequest = USB_HID_GET_REPORT;
	phost->Control.setup.b.wValue.w = (uint16_t) (((uint32_t) reportType << 8U)
			| (uint32_t) reportId);

	phost->Control.setup.b.wIndex.w = 0U;
	phost->Control.setup.b.wLength.w = reportLen;

	return USBH_CtlReq(phost, reportBuff, (uint16_t) reportLen);
}

/**
 * @brief  USBH_Set_Protocol
 *         Set protocol State.
 * @param  phost: Host handle
 * @param  protocol : Set Protocol for HID : boot/report protocol
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_HID_SetProtocol(USBH_HandleTypeDef *phost,
		uint8_t protocol) {
	phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE
			| USB_REQ_TYPE_CLASS;

	phost->Control.setup.b.bRequest = USB_HID_SET_PROTOCOL;
	if (protocol != 0U) {
		phost->Control.setup.b.wValue.w = 0U;
	} else {
		phost->Control.setup.b.wValue.w = 1U;
	}

	phost->Control.setup.b.wIndex.w = 0U;
	phost->Control.setup.b.wLength.w = 0U;

	return USBH_CtlReq(phost, NULL, 0U);

}

/**
 * @brief  USBH_ParseHIDDesc
 *         This function Parse the HID descriptor
 * @param  desc: HID Descriptor
 * @param  buf: Buffer where the source descriptor is available
 * @retval None
 */
static void USBH_HID_ParseHIDDesc(HID_DescTypeDef *desc, uint8_t *buf) {
	USBH_DescHeader_t *pdesc = (USBH_DescHeader_t*) buf;
	uint16_t CfgDescLen;
	uint16_t ptr;

	CfgDescLen = LE16(buf + 2U);

	if (CfgDescLen > USB_CONFIGURATION_DESC_SIZE) {
		ptr = USB_LEN_CFG_DESC;

		while (ptr < CfgDescLen) {
			pdesc = USBH_GetNextDesc((uint8_t*) pdesc, &ptr);

			if (pdesc->bDescriptorType == USB_DESC_TYPE_HID) {
				desc->bLength = *(uint8_t*) ((uint8_t*) pdesc + 0U);
				desc->bDescriptorType = *(uint8_t*) ((uint8_t*) pdesc + 1U);
				desc->bcdHID = LE16((uint8_t* )pdesc + 2U);
				desc->bCountryCode = *(uint8_t*) ((uint8_t*) pdesc + 4U);
				desc->bNumDescriptors = *(uint8_t*) ((uint8_t*) pdesc + 5U);
				desc->bReportDescriptorType =
						*(uint8_t*) ((uint8_t*) pdesc + 6U);
				desc->wItemLength = LE16((uint8_t* )pdesc + 7U);
				break;
			}
		}
	}
}

/**
 * @brief  USBH_HID_GetDeviceType
 *         Return Device function.
 * @param  phost: Host handle
 * @retval HID function: HID_MOUSE / HID_KEYBOARD
 */
HID_TypeTypeDef USBH_HID_GetDeviceType(USBH_HandleTypeDef *phost) {
	HID_TypeTypeDef type = HID_UNKNOWN;
	uint8_t InterfaceProtocol;

	if (phost->gState == HOST_CLASS) {
		InterfaceProtocol =
				phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bInterfaceProtocol;
		if (InterfaceProtocol == HID_KEYBRD_BOOT_CODE) {
			type = HID_KEYBOARD;
		} else {
			if (InterfaceProtocol == HID_MOUSE_BOOT_CODE) {
				type = HID_MOUSE;
			}
		}
	}
	return type;
}

/**
 * @brief  USBH_HID_GetPollInterval
 *         Return HID device poll time
 * @param  phost: Host handle
 * @retval poll time (ms)
 */
uint8_t USBH_HID_GetPollInterval(USBH_HandleTypeDef *phost) {
	uint8_t idx = phost->device.current_interface;

	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];

	if ((phost->gState == HOST_CLASS_REQUEST) || (phost->gState == HOST_INPUT)
			|| (phost->gState == HOST_SET_CONFIGURATION)
			|| (phost->gState == HOST_CHECK_CLASS)
			|| ((phost->gState == HOST_CLASS))) {
		return (uint8_t) (HID_Handle->poll_array[0]);
	} else {
		return 0U;
	}
}
/**
 * @brief  USBH_HID_FifoInit
 *         Initialize FIFO.
 * @param  f: Fifo address
 * @param  buf: Fifo buffer
 * @param  size: Fifo Size
 * @retval none
 */
void USBH_HID_FifoInit(FIFO_TypeDef *f, uint8_t *buf, uint16_t size) {
	f->head = 0U;
	f->tail = 0U;
	f->lock = 0U;
	f->size = size;
	f->buf = buf;
}

/**
 * @brief  USBH_HID_FifoRead
 *         Read from FIFO.
 * @param  f: Fifo address
 * @param  buf: read buffer
 * @param  nbytes: number of item to read
 * @retval number of read items
 */
uint16_t USBH_HID_FifoRead(FIFO_TypeDef *f, void *buf, uint16_t nbytes) {
	uint16_t i;
	uint8_t *p;

	p = (uint8_t*) buf;

	if (f->lock == 0U) {
		f->lock = 1U;

		for (i = 0U; i < nbytes; i++) {
			if (f->tail != f->head) {
				*p++ = f->buf[f->tail];
				f->tail++;

				if (f->tail == f->size) {
					f->tail = 0U;
				}
			} else {
				f->lock = 0U;
				return i;
			}
		}
	}

	f->lock = 0U;

	return nbytes;
}

/**
 * @brief  USBH_HID_FifoWrite
 *         Write To FIFO.
 * @param  f: Fifo address
 * @param  buf: read buffer
 * @param  nbytes: number of item to write
 * @retval number of written items
 */
uint16_t USBH_HID_FifoWrite(FIFO_TypeDef *f, void *buf, uint16_t nbytes) {
	uint16_t i;
	uint8_t *p;

	p = (uint8_t*) buf;

	if (f->lock == 0U) {
		f->lock = 1U;

		for (i = 0U; i < nbytes; i++) {
			if (((f->head + 1U) == f->tail)
					|| (((f->head + 1U) == f->size) && (f->tail == 0U))) {
				f->lock = 0U;
				return i;
			} else {
				f->buf[f->head] = *p++;
				f->head++;

				if (f->head == f->size) {
					f->head = 0U;
				}
			}
		}
	}

	f->lock = 0U;

	return nbytes;
}

/**
 * @brief  The function is a callback about HID Data events
 *  @param  phost: Selected device
 * @retval None
 */
__weak void USBH_HID_EventCallback(USBH_HandleTypeDef *phost) {
	/* Prevent unused argument(s) compilation warning */
	UNUSED(phost);
}
/**
 * @}
 */

/**
 * @}
 */

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
