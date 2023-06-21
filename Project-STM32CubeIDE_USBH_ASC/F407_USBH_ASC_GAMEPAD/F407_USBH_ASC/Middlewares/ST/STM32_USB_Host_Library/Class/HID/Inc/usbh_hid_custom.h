/*
 * usbh_hid_custom.h
 *
 *  Created on: Jun 20, 2023
 *      Author: user
 */

#ifndef __USBH_HID_CUSTOM_H
#define __USBH_HID_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbh_hid.h"

//typedef struct {
//	uint8_t x1;
//	uint8_t y1;
//	uint8_t x2;
//	uint8_t y2;
//	uint8_t buttons[16];
//	uint8_t raw_length;
//	uint8_t valid;
//} HID_CUSTOM_Info_TypeDef;

typedef struct {
	uint32_t raw_data32[2];
	uint8_t raw_length;
} HID_CUSTOM_Info_TypeDef;

typedef enum
{
	CUSTOM_EMPTY = 0,
	CUSTOM_VALID,
}
HID_CUSTOM_enum_TypeDef;

USBH_StatusTypeDef USBH_HID_CustomInit(USBH_HandleTypeDef *phost);
HID_CUSTOM_Info_TypeDef* USBH_HID_GetCustomInfo(USBH_HandleTypeDef *phost);

#ifdef __cplusplus
}
#endif

#endif /* __USBH_HID_CUSTOM_H */
