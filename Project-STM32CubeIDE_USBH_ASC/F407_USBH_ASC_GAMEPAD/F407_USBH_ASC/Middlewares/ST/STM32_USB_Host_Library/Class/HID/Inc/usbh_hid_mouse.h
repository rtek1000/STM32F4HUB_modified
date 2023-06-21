/**
  ******************************************************************************
  * @file    usbh_hid_mouse.h
  * @author  MCD Application Team
  * @brief   This file contains all the prototypes for the usbh_hid_mouse.c
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

/* Define to prevent recursive  ----------------------------------------------*/
#ifndef __USBH_HID_MOUSE_H
#define __USBH_HID_MOUSE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbh_hid.h"

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
  * @brief This file is the Header file for usbh_hid_mouse.c
  * @{
  */


/** @defgroup USBH_HID_MOUSE_Exported_Types
  * @{
  */

typedef struct _HID_MOUSE_Info
{
  uint16_t              x;
  uint16_t              y;
  uint8_t              scroll;
  uint8_t              valid;
  uint8_t              buttons[3];
  uint32_t 			   raw_data32[2];
  uint8_t  			   raw_length;
}
HID_MOUSE_Info_TypeDef;

typedef enum
{
	MOUSE_EMPTY = 0,
	MOUSE_VALID,
}
HID_MOUSE_enum_TypeDef;

/**
  * @}
  */

/** @defgroup USBH_HID_MOUSE_Exported_Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup USBH_HID_MOUSE_Exported_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup USBH_HID_MOUSE_Exported_Variables
  * @{
  */
/**
  * @}
  */

/** @defgroup USBH_HID_MOUSE_Exported_FunctionsPrototype
  * @{
  */
USBH_StatusTypeDef USBH_HID_MouseInit(USBH_HandleTypeDef *phost);
HID_MOUSE_Info_TypeDef *USBH_HID_GetMouseInfo(USBH_HandleTypeDef *phost);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __USBH_HID_MOUSE_H */

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
