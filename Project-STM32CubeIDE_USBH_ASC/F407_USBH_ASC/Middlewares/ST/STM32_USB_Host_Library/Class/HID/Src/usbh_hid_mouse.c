/**
 ******************************************************************************
 * @file    usbh_hid_mouse.c
 * @author  MCD Application Team
 * @brief   This file is the application layer for USB Host HID Mouse Handling.
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
#include "usbh_hid_mouse.h"
#include "usbh_hid_parser.h"

// See file usbh_conf.h
// Path: USB_HOST/Target/usbh_conf.h
// #define PRINT_BINARY_MOUSE_DATA 1

/** @addtogroup USBH_LIB
 * @{
 */

/** @addtogroup USBH_CLASS
 * @{
 */

/** @addtogroup USBH_HID_CLASS
 * @{
 */

/** @defgroup USBH_HID_MOUSE
 * @brief    This file includes HID Layer Handlers for USB Host HID class.
 * @{
 */

/** @defgroup USBH_HID_MOUSE_Private_TypesDefinitions
 * @{
 */
/**
 * @}
 */

/** @defgroup USBH_HID_MOUSE_Private_Defines
 * @{
 */
/**
 * @}
 */

/** @defgroup USBH_HID_MOUSE_Private_Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup USBH_HID_MOUSE_Private_FunctionPrototypes
 * @{
 */
static USBH_StatusTypeDef USBH_HID_MouseDecode(USBH_HandleTypeDef *phost);

/**
 * @}
 */

/** @defgroup USBH_HID_MOUSE_Private_Variables
 * @{
 */
HID_MOUSE_Info_TypeDef mouse_info;

// The size of the "mouse_report_data variable" affects the
// value of "HID_Handle->length_array[0]"

#define mouse_report_data_index 2
uint32_t mouse_report_data[mouse_report_data_index] = { 0 };
uint32_t mouse_rx_report_buf[mouse_report_data_index] = { 0 };

/* Structures defining how to access items in a HID mouse report */
/* Access button 1 state. */
static const HID_Report_ItemTypedef prop_b1 = {
		(uint8_t*) (void*) mouse_report_data + 0, /*data*/
		1, /*size*/
		0, /*shift*/
		0, /*count (only for array items)*/
		0, /*signed?*/
		0, /*min value read can return*/
		1, /*max value read can return*/
		0, /*min value device can report*/
		1, /*max value device can report*/
		1 /*resolution*/
};

/* Access button 2 state. */
static const HID_Report_ItemTypedef prop_b2 = {
		(uint8_t*) (void*) mouse_report_data + 0, /*data*/
		1, /*size*/
		1, /*shift*/
		0, /*count (only for array items)*/
		0, /*signed?*/
		0, /*min value read can return*/
		1, /*max value read can return*/
		0, /*min value device can report*/
		1, /*max value device can report*/
		1 /*resolution*/
};

/* Access button 3 state. */
static const HID_Report_ItemTypedef prop_b3 = {
		(uint8_t*) (void*) mouse_report_data + 0, /*data*/
		1, /*size*/
		2, /*shift*/
		0, /*count (only for array items)*/
		0, /*signed?*/
		0, /*min value read can return*/
		1, /*max value read can return*/
		0, /*min vale device can report*/
		1, /*max value device can report*/
		1 /*resolution*/
};

/* Access x coordinate change. */
static const HID_Report_ItemTypedef prop_x = {
		(uint8_t*) (void*) mouse_report_data + 1, /*data*/
		8, /*size*/
		0, /*shift*/
		0, /*count (only for array items)*/
		1, /*signed?*/
		0, /*min value read can return*/
		0xFFFF,/*max value read can return*/
		0, /*min vale device can report*/
		0xFFFF,/*max value device can report*/
		1 /*resolution*/
};

/* Access y coordinate change. */
static const HID_Report_ItemTypedef prop_y = {
		(uint8_t*) (void*) mouse_report_data + 2, /*data*/
		8, /*size*/
		0, /*shift*/
		0, /*count (only for array items)*/
		1, /*signed?*/
		0, /*min value read can return*/
		0xFFFF,/*max value read can return*/
		0, /*min vale device can report*/
		0xFFFF,/*max value device can report*/
		1 /*resolution*/
};

/* Access scroll coordinate change. */
static const HID_Report_ItemTypedef prop_scroll = {
		(uint8_t*) (void*) mouse_report_data + 3, /*data*/
		8, /*size*/
		0, /*shift*/
		0, /*count (only for array items)*/
		1, /*signed?*/
		0, /*min value read can return*/
		0xFF,/*max value read can return*/
		0, /*min vale device can report*/
		0xFF,/*max value device can report*/
		1 /*resolution*/
};

/**
 * @}
 */

/** @defgroup USBH_HID_MOUSE_Private_Functions
 * @{
 */

/**
 * @brief  USBH_HID_MouseInit
 *         The function init the HID mouse.
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_HID_MouseInit(USBH_HandleTypeDef *phost) {
	uint32_t i;

	uint8_t idx = phost->device.current_interface;

	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];

	mouse_info.x = 0U;
	mouse_info.y = 0U;
	mouse_info.buttons[0] = 0U;
	mouse_info.buttons[1] = 0U;
	mouse_info.buttons[2] = 0U;

	for (i = 0U; i < (sizeof(mouse_report_data) / sizeof(uint32_t)); i++) {
		mouse_report_data[i] = 0U;
		mouse_rx_report_buf[i] = 0U;
	}

	if (HID_Handle->length_array[0] > sizeof(mouse_report_data)) {
		HID_Handle->length_array[0] = (uint16_t) sizeof(mouse_report_data);
	}
	HID_Handle->pData = (uint8_t*) (void*) mouse_rx_report_buf;
	USBH_HID_FifoInit(&HID_Handle->fifo, phost->device.Data,
			(uint16_t) (HID_QUEUE_SIZE * sizeof(mouse_report_data)));

	return USBH_OK;
}

/**
 * @brief  USBH_HID_GetMouseInfo
 *         The function return mouse information.
 * @param  phost: Host handle
 * @retval mouse information
 */
HID_MOUSE_Info_TypeDef* USBH_HID_GetMouseInfo(USBH_HandleTypeDef *phost) {
	if (USBH_HID_MouseDecode(phost) == USBH_OK) {
		return &mouse_info;
	} else {
		return NULL;
	}
}

#if PRINT_BINARY_MOUSE_DATA == 1

static void print_binary_raw_data(void) {
	printf("Binary Raw Data: ");
//	for (int8_t k = (mouse_report_data_index - 1); k >= 0; k--) {
//		for (int8_t i = 31; i >= 0; i--) {

	for (int8_t k = 0; k < mouse_report_data_index; k++) {
		for (int8_t i = 0; i <= 31; i++) {
			uint8_t j = (mouse_report_data[k] >> i) & 1;
			if (j == 1) {
				printf("1");
			} else {
				printf("0");
			}

			if ((((i + 1) % 8) == 0) && (i < 24)) {
				printf(" ");
			}
		}

		if (k < (mouse_report_data_index - 1)) {
			printf(", ");
		}
	}

	printf("\n");
}
#endif // #if PRINT_BINARY_MOUSE_DATA == 1

#if PRINT_HEX_MOUSE_DATA == 1

static void print_hex_raw_data(void) {
	printf("Hex Raw Data: ");
	for (int8_t k = (mouse_report_data_index - 1); k >= 0; k--) {
		printf("0x%08lx ", mouse_report_data[k]);
	}

	printf("\n");
}
#endif // #if PRINT_HEX_MOUSE_DATA == 1

/**
 * @brief  USBH_HID_MouseDecode
 *         The function decode mouse data.
 * @param  phost: Host handle
 * @retval USBH Status
 */
static USBH_StatusTypeDef USBH_HID_MouseDecode(USBH_HandleTypeDef *phost) {
	uint8_t idx = phost->device.current_interface;

	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];

	if (HID_Handle->length_array[0] == 0U) {
		return USBH_FAIL;
	}

#if PRINT_BINARY_MOUSE_DATA == 1 || PRINT_HEX_MOUSE_DATA == 1
	USBH_UsrLog("length_array: 0x%02x", HID_Handle->length_array[0]);
#endif // #if PRINT_BINARY_MOUSE_DATA == 1

	/*Fill report */
	if (USBH_HID_FifoRead(&HID_Handle->fifo, &mouse_report_data,
			HID_Handle->length_array[0]) == HID_Handle->length_array[0]) {

		mouse_info.raw_length = HID_Handle->length_array[0];

#if PRINT_BINARY_MOUSE_DATA == 1
		print_binary_raw_data();
#endif // #if PRINT_BINARY_MOUSE_DATA == 1

#if PRINT_HEX_MOUSE_DATA == 1
		print_hex_raw_data();
#endif // #if PRINT_HEX_MOUSE_DATA == 1

		for (uint8_t i = 0; i < 2; i++) {
			mouse_info.raw_data32[i] = mouse_report_data[i];
		}

		if (HID_Handle->length_array[0] == 4) {
			mouse_info.valid = MOUSE_EMPTY;

			/*Decode report */
			uint8_t x_val = (uint8_t) HID_ReadItem(
								(HID_Report_ItemTypedef*) &prop_x, 0U);

			uint8_t y_val = (uint8_t) HID_ReadItem(
								(HID_Report_ItemTypedef*) &prop_y, 0U);

			if((x_val > 0) || (y_val > 0)){
				mouse_info.x = x_val;
				mouse_info.y = y_val;
			}

			uint8_t scroll_val = (uint8_t) HID_ReadItem(
								(HID_Report_ItemTypedef*) &prop_scroll, 0U);

			mouse_info.scroll = scroll_val;

			uint8_t btn0 = (uint8_t) HID_ReadItem(
					(HID_Report_ItemTypedef*) &prop_b1, 0U);
			uint8_t btn1 = (uint8_t) HID_ReadItem(
					(HID_Report_ItemTypedef*) &prop_b2, 0U);
			uint8_t btn2 = (uint8_t) HID_ReadItem(
					(HID_Report_ItemTypedef*) &prop_b3, 0U);

			mouse_info.buttons[0] = btn0;
			mouse_info.buttons[1] = btn1;
			mouse_info.buttons[2] = btn2;

			if ((btn0 != 0) || (btn1 != 0) || (btn2 != 0) || (x_val > 0)
					|| (y_val > 0) || ((scroll_val & 1) == 1)) {
				mouse_info.valid = MOUSE_VALID;
			}
		}

		return USBH_OK;
	}
	return USBH_FAIL;
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
