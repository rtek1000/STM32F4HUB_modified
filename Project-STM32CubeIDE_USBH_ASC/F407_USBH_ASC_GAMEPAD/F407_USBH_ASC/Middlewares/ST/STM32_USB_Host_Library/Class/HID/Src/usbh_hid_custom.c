/*
 * usbh_hid_custom.c
 *
 *  Created on: Jun 20, 2023
 *      Author: user
 */

#include "usbh_hid_parser.h"

HID_CUSTOM_Info_TypeDef custom_info;

#define custom_report_data_index 2
uint32_t custom_report_data[custom_report_data_index] = { 0 };
uint32_t custom_rx_report_buf[custom_report_data_index] = { 0 };

static USBH_StatusTypeDef USBH_HID_CustomDecode(USBH_HandleTypeDef *phost);

/**
 * @brief  USBH_HID_CustomInit
 *         The function init the HID Custom.
 * @param  phost: Host handle
 * @retval USBH Status
 */
USBH_StatusTypeDef USBH_HID_CustomInit(USBH_HandleTypeDef *phost) {
	uint32_t i;

	uint8_t idx = phost->device.current_interface;

	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];

//	custom_info.x1 = 0U;
//	custom_info.y1 = 0U;
//	custom_info.x2 = 0U;
//	custom_info.y2 = 0U;
//
//	for (i = 0U; i < 16; i++) {
//		custom_info.buttons[i] = 0U;
//	}

	for (i = 0U; i < (sizeof(custom_report_data) / sizeof(uint32_t)); i++) {
		custom_report_data[i] = 0U;
		custom_rx_report_buf[i] = 0U;
	}

	if (HID_Handle->length_array[0] > sizeof(custom_report_data)) {
		HID_Handle->length_array[0] = (uint16_t) sizeof(custom_report_data);
	}

	HID_Handle->pData = (uint8_t*) (void*) custom_rx_report_buf;
	USBH_HID_FifoInit(&HID_Handle->fifo, phost->device.Data,
			(uint16_t) (HID_QUEUE_SIZE * sizeof(custom_report_data)));

	return USBH_OK;
}

/**
 * @brief  USBH_HID_CustomInfo
 *         The function return Custom information.
 * @param  phost: Host handle
 * @retval keyboard information
 */
HID_CUSTOM_Info_TypeDef* USBH_HID_GetCustomInfo(USBH_HandleTypeDef *phost) {
	if (USBH_HID_CustomDecode(phost) == USBH_OK) {
		return &custom_info;
	}
	return NULL;
}

#if PRINT_BINARY_CUSTOM_DATA == 1

static void print_binary_raw_data(void) {
	printf("Binary Raw Data: ");
//	for (int8_t k = (mouse_report_data_index - 1); k >= 0; k--) {
//		for (int8_t i = 31; i >= 0; i--) {

	for (int8_t k = 0; k < custom_report_data_index; k++) {
		for (int8_t i = 0; i <= 31; i++) {
			uint8_t j = (custom_report_data[k] >> i) & 1;
			if (j == 1) {
				printf("1");
			} else {
				printf("0");
			}

			if ((((i + 1) % 8) == 0) && (i < 24)) {
				printf(" ");
			}
		}

		if (k < (custom_report_data_index - 1)) {
			printf(", ");
		}
	}

	printf("\n");
}
#endif // #if PRINT_BINARY_CUSTOM_DATA == 1

#if PRINT_HEX_CUSTOM_DATA == 1

static void print_hex_raw_data(void) {
	printf("Hex Raw Data: ");
	for (int8_t k = (custom_report_data_index - 1); k >= 0; k--) {
		printf("0x%08lx ", custom_report_data[k]);
	}

	printf("\n");
}
#endif // #if PRINT_HEX_CUSTOM_DATA == 1

/**
 * @brief  USBH_HID_CustomDecode
 *         The function decode Custom data.
 * @param  phost: Host handle
 * @retval USBH Status
 */
static USBH_StatusTypeDef USBH_HID_CustomDecode(USBH_HandleTypeDef *phost) {
	uint8_t idx = phost->device.current_interface;

	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];

	if (HID_Handle->length_array[0] == 0U) {
		return USBH_FAIL;
	}

#if PRINT_BINARY_CUSTOM_DATA == 1 || PRINT_HEX_CUSTOM_DATA == 1
	USBH_UsrLog("length_array: 0x%02x", HID_Handle->length_array[0]);
#endif // #if PRINT_BINARY_MOUSE_DATA == 1

	/*Fill report */
	if (USBH_HID_FifoRead(&HID_Handle->fifo, &custom_report_data,
			HID_Handle->length_array[0]) == HID_Handle->length_array[0]) {

		custom_info.raw_length = HID_Handle->length_array[0];

#if PRINT_BINARY_CUSTOM_DATA == 1
		print_binary_raw_data();
#endif // #if PRINT_BINARY_MOUSE_DATA == 1

#if PRINT_HEX_CUSTOM_DATA == 1
		print_hex_raw_data();
#endif // #if PRINT_HEX_MOUSE_DATA == 1

		for (uint8_t i = 0; i < 2; i++) {
			custom_info.raw_data32[i] = custom_report_data[i];
		}

//		if (HID_Handle->length_array[0] == 4) {
//			custom_info.valid = CUSTOM_EMPTY;
//
//			/*Decode report */
//			uint8_t x_val = (uint8_t) HID_ReadItem(
//								(HID_Report_ItemTypedef*) &prop_x, 0U);
//
//			uint8_t y_val = (uint8_t) HID_ReadItem(
//								(HID_Report_ItemTypedef*) &prop_y, 0U);
//
//			if((x_val > 0) || (y_val > 0)){
//				mouse_info.x = x_val;
//				mouse_info.y = y_val;
//			}
//
//			uint8_t scroll_val = (uint8_t) HID_ReadItem(
//								(HID_Report_ItemTypedef*) &prop_scroll, 0U);
//
//			mouse_info.scroll = scroll_val;
//
//			uint8_t btn0 = (uint8_t) HID_ReadItem(
//					(HID_Report_ItemTypedef*) &prop_b1, 0U);
//			uint8_t btn1 = (uint8_t) HID_ReadItem(
//					(HID_Report_ItemTypedef*) &prop_b2, 0U);
//			uint8_t btn2 = (uint8_t) HID_ReadItem(
//					(HID_Report_ItemTypedef*) &prop_b3, 0U);
//
//			mouse_info.buttons[0] = btn0;
//			mouse_info.buttons[1] = btn1;
//			mouse_info.buttons[2] = btn2;
//
//			if ((btn0 != 0) || (btn1 != 0) || (btn2 != 0) || (x_val > 0)
//					|| (y_val > 0) || ((scroll_val & 1) == 1)) {
//				mouse_info.valid = MOUSE_VALID;
//			}
//		}

		return USBH_OK;
	}

	return USBH_FAIL;
}
