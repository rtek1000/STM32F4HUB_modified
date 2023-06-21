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
#include "usbh_audio.h"
#include "usbh_cdc.h"
#include "usbh_msc.h"
#include "usbh_hid.h"
#include "usbh_mtp.h"
#include "usbh_hub.h"

/* USER CODE BEGIN Includes */
#include "usbh_hid_parser.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
HID_MOUSE_Info_TypeDef *mouse_info_local;

HID_CUSTOM_Info_TypeDef *custom_info_local;

// M.W.K.B.T.: Mini Wireless Keyboard with Built-in Touchpad
typedef enum {
	CODE_BTN_NEXT = 0xB5,
	CODE_BTN_PREV = 0xB6,
	CODE_BTN_PLAY_PAUSE = 0xCD,
	CODE_BTN_MUTE = 0xE2,
	CODE_BTN_VOL_UP = 0xE9,
	CODE_BTN_VOL_DOWN = 0xEA,
	CODE_BTN_MEDIA_PLAYER = 0x83,
	CODE_BTN_EMAIL = 0x8A,
	CODE_BTN_BROWSER = 0x96,
	CODE_BTN_SEARCH = 0x21,
	CODE_BTN_HOME = 0x23,
} MWKBT1_TypeTypeDef;

typedef enum {
	MWKBT_EMPTY = 0,
	MWKBT_VALID,
	MWKBT_NEXT,
	MWKBT_PREV,
	MWKBT_PLAY_PAUSE,
	MWKBT_MUTE,
	MWKBT_VOL_UP,
	MWKBT_VOL_DOWN,
	MWKBT_MEDIA_PLAYER,
	MWKBT_EMAIL,
	MWKBT_BROWSER,
	MWKBT_SEARCH,
	MWKBT_HOME,
} MWKBT2_TypeTypeDef;

uint8_t MWKBT_array_cod[11] = { CODE_BTN_NEXT, CODE_BTN_PREV,
		CODE_BTN_PLAY_PAUSE, CODE_BTN_MUTE, CODE_BTN_VOL_UP, CODE_BTN_VOL_DOWN,
		CODE_BTN_MEDIA_PLAYER, CODE_BTN_EMAIL, CODE_BTN_BROWSER,
		CODE_BTN_SEARCH, CODE_BTN_HOME };

uint8_t MWKBT_array_ref[11] = { MWKBT_NEXT, MWKBT_PREV, MWKBT_PLAY_PAUSE,
		MWKBT_MUTE, MWKBT_VOL_UP, MWKBT_VOL_DOWN, MWKBT_MEDIA_PLAYER,
		MWKBT_EMAIL, MWKBT_BROWSER, MWKBT_SEARCH, MWKBT_HOME };

char *MWKBT_array_name[11] = { "Next", "Previous", "Play/Pause", "Mute",
		"Volume Up", "Volume Down", "Media Player", "e-mail", "Browser",
		"Search", "Home" };

typedef struct _HID_Multimedia_Touchpad {
	uint8_t x;
	uint8_t y;
	uint8_t scroll;
	uint8_t valid;
	uint8_t buttons[3];
	uint8_t multimedia;
	uint8_t multimedia_size;
//	uint8_t valid;
} HID_MWKBT_TypeDef;

HID_MWKBT_TypeDef MWKBT_decoded;

HID_KEYBD_Info_TypeDef *keybd_info1;

// M.K.LITE-ON: Multimedia Keyboard Lite-On
typedef enum {
	MKLITEON_COD_NEXT = 0xB5,
	MKLITEON_COD_PREV = 0xB6,
	MKLITEON_COD_PLAY_PAUSE = 0xCD,
	MKLITEON_COD_MUTE = 0xE2,
	MKLITEON_COD_VOL_UP = 0xE9,
	MKLITEON_COD_VOL_DOWN = 0xEA,
	MKLITEON_COD_STOP = 0xB7
} MKLITEON1_TypeTypeDef;

typedef enum {
	MKLITEON_EMPTY = 0,
	MKLITEON_VALID,
	MKLITEON_NEXT,
	MKLITEON_PREV,
	MKLITEON_PLAY_PAUSE,
	MKLITEON_MUTE,
	MKLITEON_VOL_UP,
	MKLITEON_VOL_DOWN,
	MKLITEON_STOP
} MKLITEON2_TypeTypeDef;

uint8_t MKLITEON_array_cod[7] = { MKLITEON_COD_NEXT, MKLITEON_COD_PREV,
		MKLITEON_COD_PLAY_PAUSE, MKLITEON_COD_MUTE, MKLITEON_COD_VOL_UP,
		MKLITEON_COD_VOL_DOWN, MKLITEON_COD_STOP };

uint8_t MKLITEON_array_ref[7] = { MKLITEON_NEXT, MKLITEON_PREV,
		MKLITEON_PLAY_PAUSE, MKLITEON_MUTE, MKLITEON_VOL_UP, MKLITEON_VOL_DOWN,
		MKLITEON_STOP };

char *MKLITEON_array_name[7] = { "NEXT", "PREV", "PAUSE", "MUTE", "VOL_UP",
		"VOL_DOWN", "STOP" };

typedef struct _HID_MKLITEON {
	uint8_t multimedia;
	uint8_t multimedia_size;
	uint8_t valid;
} HID_MKLITEON_TypeDef;

HID_MKLITEON_TypeDef MKLITEON_decoded;

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
static HID_MWKBT_TypeDef* USBH_HID_Decode_Mini_Keyboard_Touchpad(
		HID_MOUSE_Info_TypeDef *Minfo);
static void USBH_HID_MouseLogiDecode(HID_MOUSE_Info_TypeDef *Minfo);
static void USBH_HID_MultmediaKbDecode(HID_CUSTOM_Info_TypeDef *Cinfo);
/* USER CODE END PFP */

/* USB Host core handle declaration */
USBH_HandleTypeDef hUsbHostFS;
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

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */
// Mini Wireless Keyboard with built-in Touchpad decode:
static HID_MWKBT_TypeDef* USBH_HID_Decode_Mini_Keyboard_Touchpad(
		HID_MOUSE_Info_TypeDef *Minfo) {
	MWKBT_decoded.multimedia = MWKBT_EMPTY;
	MWKBT_decoded.valid = MWKBT_EMPTY;

	MWKBT_decoded.buttons[0] = 0;
	MWKBT_decoded.buttons[1] = 0;
	MWKBT_decoded.buttons[2] = 0;

//	USBH_UsrLog("raw_data32[0]: 0x%08lx", Minfo->raw_data32[0]);
//	USBH_UsrLog("raw_data32[1]: 0x%08lx", Minfo->raw_data32[1]);
//	USBH_UsrLog("raw_length: 0x%02x", Minfo->raw_length);

	uint32_t raw_data32_1 = Minfo->raw_data32[1] & 0xFFFFFF00;

//	USBH_UsrLog("raw_data32_1: 0x%08lX", raw_data32_1);

	if ((Minfo->raw_length == 8) && (raw_data32_1 == 0x00080000)) {
		if ((((Minfo->raw_data32[0] >> 1) & 1) == 0)
				&& ((Minfo->raw_data32[0] & 1) == 1)) {

			uint8_t btn0 = (Minfo->raw_data32[0] >> 8) & 1;
			uint8_t btn1 = (Minfo->raw_data32[0] >> 9) & 1;

			MWKBT_decoded.buttons[0] = btn0;
			MWKBT_decoded.buttons[1] = btn1;

			if ((MWKBT_decoded.buttons[0] == 1)
					&& (MWKBT_decoded.buttons[1] == 1)) {
				MWKBT_decoded.buttons[0] = 0;
				MWKBT_decoded.buttons[1] = 0;
				MWKBT_decoded.buttons[2] = 1;
			}

			uint8_t x_val = (Minfo->raw_data32[0] >> 16) & 0xFF;
			uint8_t y_val = (Minfo->raw_data32[0] >> 24) & 0xFF;

			if ((x_val > 0) || (y_val > 0)) {
				MWKBT_decoded.x = x_val;
				MWKBT_decoded.y = y_val;
			}

			if ((btn0 != 0) || (btn1 != 0) || (x_val > 0) || (y_val > 0)) {
				MWKBT_decoded.valid = MWKBT_VALID;
			}
		} else if ((((Minfo->raw_data32[0] >> 1) & 1) == 1)
				&& ((Minfo->raw_data32[0] & 1) == 0)) {

			//			printf("Multimedia functions\n");

			if (sizeof(MWKBT_array_cod) != sizeof(MWKBT_array_ref)) {
				USBH_UsrLog("Error: the sizes of the arrays do not match");

				return &MWKBT_decoded;
			}

			MWKBT_decoded.multimedia_size = sizeof(MWKBT_array_cod);

			uint8_t new_cod = (Minfo->raw_data32[0] >> 8) & 0xFF;

			//USBH_UsrLog("new_cod: 0x%02X", new_cod);

			USBH_UsrLog("multimedia_size: %d", MWKBT_decoded.multimedia_size);

			if (new_cod != 0) {
				for (uint8_t i = 0; i < MWKBT_decoded.multimedia_size; i++) {
					if (new_cod == MWKBT_array_cod[i]) {
						MWKBT_decoded.multimedia = MWKBT_array_ref[i];

						MWKBT_decoded.valid = MKLITEON_VALID;

						USBH_UsrLog("found");

						break;
					}
				}
			} else {
				MWKBT_decoded.multimedia = MKLITEON_EMPTY;
				MWKBT_decoded.valid = MKLITEON_EMPTY;
			}

//			switch (val1) {
//			case CODE_BTN_NEXT:
//				MWKBT_decoded.multimedia = MWKBT_NEXT;
//				break;
//			case CODE_BTN_PREV:
//				MWKBT_decoded.multimedia = MWKBT_PREV;
//				break;
//			case CODE_BTN_PLAY_PAUSE:
//				MWKBT_decoded.multimedia = MWKBT_PLAY_PAUSE;
//				break;
//			case CODE_BTN_MUTE:
//				MWKBT_decoded.multimedia = MWKBT_MUTE;
//				break;
//			case CODE_BTN_VOL_UP:
//				MWKBT_decoded.multimedia = MWKBT_VOL_UP;
//				break;
//			case CODE_BTN_VOL_DOWN:
//				MWKBT_decoded.multimedia = MWKBT_VOL_DOWN;
//				break;
//			case CODE_BTN_MEDIA_PLAYER:
//				MWKBT_decoded.multimedia = MWKBT_MEDIA_PLAYER;
//				break;
//			case CODE_BTN_EMAIL:
//				MWKBT_decoded.multimedia = MWKBT_EMAIL;
//				break;
//			case CODE_BTN_BROWSER:
//				MWKBT_decoded.multimedia = MWKBT_BROWSER;
//				break;
//			case CODE_BTN_SEARCH:
//				MWKBT_decoded.multimedia = MWKBT_SEARCH;
//				break;
//			case CODE_BTN_HOME:
//				MWKBT_decoded.multimedia = MWKBT_HOME;
//				break;
//			default:
//				MWKBT_decoded.multimedia = MWKBT_EMPTY;
//				break;
//			}
//
//			if (MWKBT_decoded.multimedia != MWKBT_EMPTY) {
//				MWKBT_decoded.valid = MWKBT_VALID;
//			}
		}

		MWKBT_decoded.scroll = Minfo->raw_data32[1] & 0xFF; // 8 bits

		if ((MWKBT_decoded.scroll & 1) == 1) {
			MWKBT_decoded.valid = MWKBT_VALID;
		}
	}

	return &MWKBT_decoded;
}

static void USBH_HID_MouseLogiDecode(HID_MOUSE_Info_TypeDef *Minfo) {
	if (Minfo->raw_length == 0x08) { // length_array: 8
		mouse_info_local->valid = MOUSE_EMPTY;

		/*Decode report */
		uint8_t x_val = (mouse_info_local->raw_data32[0] >> 24) & 0xFF;
		x_val |= (mouse_info_local->raw_data32[1] & 0xF) << 8;

		uint8_t y_val = (mouse_info_local->raw_data32[1] >> 4) & 0xFFF;

		if ((x_val > 0) || (y_val > 0)) {
			mouse_info_local->x = x_val;
			mouse_info_local->y = y_val;
		}

		uint8_t scroll_val = 0;

		if (((mouse_info_local->raw_data32[1] >> 16) & 1) == 1) {
			scroll_val = (mouse_info_local->raw_data32[1] >> 16) & 0xFF; // 8 bits
		} else {
			scroll_val = 0;
		}

		mouse_info_local->scroll = scroll_val;

		uint8_t btn0 = (mouse_info_local->raw_data32[0] >> 8) & 0b1;
		uint8_t btn1 = (mouse_info_local->raw_data32[0] >> 9) & 0b1;
		uint8_t btn2 = (mouse_info_local->raw_data32[0] >> 10) & 0b1;

		mouse_info_local->buttons[0] = btn0;
		mouse_info_local->buttons[1] = btn1;
		mouse_info_local->buttons[2] = btn2;

		if ((btn0 != 0) || (btn1 != 0) || (btn2 != 0) || (x_val > 0)
				|| (y_val > 0) || ((scroll_val & 1) == 1)) {
			mouse_info_local->valid = MOUSE_VALID;
		}
	}
}

static void USBH_HID_MultmediaKbDecode(HID_CUSTOM_Info_TypeDef *Cinfo) {
	uint8_t raw_data32 = custom_info_local->raw_data32[0] & 0xFFFF00FF;

	if ((raw_data32 == 1) && (Cinfo->raw_length == 0x03)) { // length_array: 3
		if (sizeof(MKLITEON_array_cod) != sizeof(MKLITEON_array_cod)) {
			USBH_UsrLog("Error: the sizes of the arrays do not match");

			return;
		}

		MKLITEON_decoded.multimedia_size = sizeof(MKLITEON_array_cod);

		/*Decode report */
		uint8_t new_cod = (custom_info_local->raw_data32[0] >> 8) & 0xFF;

		// USBH_UsrLog("new_cod: 0x%02X", new_cod);

		if (new_cod != 0) {
			for (uint8_t i = 0; i < MKLITEON_decoded.multimedia_size; i++) {
				if (new_cod == MKLITEON_array_cod[i]) {
					MKLITEON_decoded.multimedia = MKLITEON_array_ref[i];

					MKLITEON_decoded.valid = MKLITEON_VALID;

					break;
				}
			}
		} else {
			MKLITEON_decoded.multimedia = MKLITEON_EMPTY;
			MKLITEON_decoded.valid = MKLITEON_EMPTY;
		}
	}
}

void USBH_HID_EventCallback(USBH_HandleTypeDef *phost) {
	uint8_t idx = phost->device.current_interface;

	HID_HandleTypeDef *HID_Handle =
			(HID_HandleTypeDef*) phost->pActiveClass->pData_array[idx];
	if (HID_Handle->Init == USBH_HID_KeybdInit) {
		keybd_info1 = USBH_HID_GetKeybdInfo(phost);

		USBH_UsrLog("USBH_HID_KeybdInit");

		if ((keybd_info1->key_ascii != 0U) && (keybd_info1->key_ascii != 0x0AU)
				&& (keybd_info1->keys[0] != KEY_HOME)) {
			if (keybd_info1->keys[0] == KEY_BACKSPACE) {
				USBH_UsrLog("ASCII: [BS]; Hex: 0x%02X; (Keycode: %02X)",
						keybd_info1->key_ascii, keybd_info1->keys[0]);
			} else if (keybd_info1->keys[0] == KEY_ESCAPE) {
				USBH_UsrLog("ASCII: [ESC]; Hex: 0x%02X; (Keycode: %02X)",
						keybd_info1->key_ascii, keybd_info1->keys[0]);
			} else if (keybd_info1->keys[0] == KEY_TAB) {
				USBH_UsrLog("ASCII: [TAB]; Hex: 0x%02X; (Keycode: %02X)",
						keybd_info1->key_ascii, keybd_info1->keys[0]);
			} else if (keybd_info1->keys[0] == KEY_SPACEBAR) {
				USBH_UsrLog("ASCII: [SPC]; Hex: 0x%02X; (Keycode: %02X)",
						keybd_info1->key_ascii, keybd_info1->keys[0]);
			} else {
				USBH_UsrLog("ASCII: [%c]; Hex: 0x%02X; (Keycode: %02X)",
						keybd_info1->key_ascii, keybd_info1->key_ascii,
						keybd_info1->keys[0]);
			}
		} else if (keybd_info1->keys[0] != 0) {
			if ((keybd_info1->keys[0] >= KEY_F1)
					&& (keybd_info1->keys[0] <= KEY_F12)) {
				USBH_UsrLog("Key: [F%d]; Hex: 0x%02X; (Keycode: %02X)",
						keybd_info1->keys[0] - KEY_F1, keybd_info1->key_ascii,
						keybd_info1->keys[0]);
			} else {
				char str1[20];

				switch (keybd_info1->keys[0]) {
				case KEY_CAPS_LOCK:
					sprintf(str1, "Caps");
					break;
				case KEY_ENTER:
				case KEY_KEYPAD_ENTER:
					sprintf(str1, "Enter");
					break;
				case KEY_PAGEUP:
				case KEY_KEYPAD_9_PAGEUP:
					sprintf(str1, "PgUp");
					break;
				case KEY_PAGEDOWN:
				case KEY_KEYPAD_3_PAGEDN:
					sprintf(str1, "PgDn");
					break;
				case KEY_DELETE:
					sprintf(str1, "Del");
					break;
				case KEY_END1:
				case KEY_KEYPAD_1_END:
					sprintf(str1, "End");
					break;
				case KEY_PRINTSCREEN:
					sprintf(str1, "PS");
					break;
				case KEY_UPARROW:
				case KEY_KEYPAD_8_UP_ARROW:
					sprintf(str1, "Up");
					break;
				case KEY_DOWNARROW:
				case KEY_KEYPAD_2_DOWN_ARROW:
					sprintf(str1, "Dn");
					break;
				case KEY_RIGHTARROW:
				case KEY_KEYPAD_6_RIGHT_ARROW:
					sprintf(str1, "Rg");
					break;
				case KEY_LEFTARROW:
				case KEY_KEYPAD_4_LEFT_ARROW:
					sprintf(str1, "Lf");
					break;
				case KEY_HOME:
				case KEY_KEYPAD_7_HOME:
					sprintf(str1, "Home");
					break;
				case KEY_INSERT:
				case KEY_KEYPAD_0_INSERT:
					sprintf(str1, "Ins");
					break;
				case KEY_PAUSE:
					sprintf(str1, "Pause");
					break;
				case KEY_KEYPAD_NUM_LOCK_AND_CLEAR:
					sprintf(str1, "NumLk");
					break;
				default:
					str1[0] = 0;
					break;
				}

				if (str1[0] != 0) {
					USBH_UsrLog("Key: [%s]; Hex: 0x%02X; (Keycode: %02X)", str1,
							keybd_info1->key_ascii, keybd_info1->keys[0]);
				} else {
					USBH_UsrLog(
							"KB action: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X",
							keybd_info1->keys[0], keybd_info1->keys[1],
							keybd_info1->keys[2], keybd_info1->keys[3],
							keybd_info1->keys[4], keybd_info1->keys[5]); // USBH_DbgLog
				}
			}
		}

		if (keybd_info1->key_special == 1U) {
			USBH_UsrLog(
					"lalt: %d, ralt: %d, lctrl: %d, rctrl: %d, lgui: %d, rgui: %d, lshift: %d, rshift: %d, state: %d",
					keybd_info1->lalt, keybd_info1->ralt, keybd_info1->lctrl,
					keybd_info1->rctrl, keybd_info1->lgui, keybd_info1->rgui,
					keybd_info1->lshift, keybd_info1->rshift,
					keybd_info1->state);
		}
	} else if (HID_Handle->Init == USBH_HID_MouseInit) {
		mouse_info_local = USBH_HID_GetMouseInfo(phost);

		uint16_t VID_info = phost->device.DevDesc.idVendor;
		uint16_t PID_info = phost->device.DevDesc.idProduct;

		USBH_UsrLog("VID: 0x%04X, PID: 0x%04X", VID_info, PID_info);

		// Mini Wireless Keyboard
		const uint16_t VID_MWKBT = 0x0513;
		const uint16_t PID_MWKBT = 0x0318;

		// Wireless Logitech M220
		const uint16_t VID_WLogiM220 = 0x046D;
		const uint16_t PID_WLogiM220 = 0xC534;

		if ((VID_info == VID_MWKBT) && (PID_info == PID_MWKBT)) {

			HID_MWKBT_TypeDef *mini_kb_touchpad;

			mini_kb_touchpad = USBH_HID_Decode_Mini_Keyboard_Touchpad(
					mouse_info_local);

			if (mini_kb_touchpad->multimedia != MWKBT_EMPTY) {
				if (MWKBT_decoded.valid == MWKBT_VALID) {
					USBH_UsrLog("Mini Wireless Keyboard Multimidea");

					for (uint8_t i = 0; i < MWKBT_decoded.multimedia_size; i++) {
						if (MWKBT_decoded.multimedia == MWKBT_array_ref[i]) {
							USBH_UsrLog("%s", MWKBT_array_name[i]);
						}
					}
				}

//				switch (mini_kb_touchpad->multimedia) {
//				case MWKBT_NEXT:
//					USBH_UsrLog("Next");
//					break;
//				case MWKBT_PREV:
//					USBH_UsrLog("Previous");
//					break;
//				case MWKBT_PLAY_PAUSE:
//					USBH_UsrLog("Play/Pause");
//					break;
//				case MWKBT_MUTE:
//					USBH_UsrLog("Mute");
//					break;
//				case MWKBT_VOL_UP:
//					USBH_UsrLog("Volume Up");
//					break;
//				case MWKBT_VOL_DOWN:
//					USBH_UsrLog("Volume Down");
//					break;
//				case MWKBT_MEDIA_PLAYER:
//					USBH_UsrLog("Media Player");
//					break;
//				case MWKBT_EMAIL:
//					USBH_UsrLog("e-mail");
//					break;
//				case MWKBT_BROWSER:
//					USBH_UsrLog("Browser");
//					break;
//				case MWKBT_SEARCH:
//					USBH_UsrLog("Search");
//					break;
//				case MWKBT_HOME:
//					USBH_UsrLog("Home");
//					break;
//				default:
//
//					break;
//				}
			} else {
				if (MWKBT_decoded.valid == MWKBT_VALID) {
					USBH_UsrLog(
							"Mini KB Touchpad action: x=  0x%02X, y=  0x%02X, scroll=  0x%02X, button1= 0x%x, button2= 0x%x, button3= 0x%x",
							mini_kb_touchpad->x, mini_kb_touchpad->y,
							mini_kb_touchpad->scroll,
							mini_kb_touchpad->buttons[0],
							mini_kb_touchpad->buttons[1],
							mini_kb_touchpad->buttons[2]);
				}
			}
		} else if ((VID_info == VID_WLogiM220) && (PID_info == PID_WLogiM220)) {
			USBH_UsrLog("(Wireless) Logitech Mouse");

			USBH_HID_MouseLogiDecode(mouse_info_local);

			if (mouse_info_local->valid == MOUSE_VALID) {
				USBH_UsrLog(
						"Logitech Mouse action: x=  0x%03X, y=  0x%03X, scroll=  0x%02X, button1= 0x%x, button2= 0x%x, button3= 0x%x",
						mouse_info_local->x, mouse_info_local->y,
						mouse_info_local->scroll, mouse_info_local->buttons[0],
						mouse_info_local->buttons[1],
						mouse_info_local->buttons[2]);
			}
		} else { // regular mouse (2 buttons + scroll wheel)
			//printf("Mouse action (raw data): ");

			//print_raw_info(mouse_info);
			if (mouse_info_local->valid == MOUSE_VALID) {
				USBH_UsrLog(
						"Mouse action: x=  0x%02X, y=  0x%02X, scroll=  0x%02X, button1= 0x%x, button2= 0x%x, button3= 0x%x",
						mouse_info_local->x, mouse_info_local->y,
						mouse_info_local->scroll, mouse_info_local->buttons[0],
						mouse_info_local->buttons[1],
						mouse_info_local->buttons[2]);
			}
		}
	} else if (HID_Handle->Init == USBH_HID_CustomInit) {
		custom_info_local = USBH_HID_GetCustomInfo(phost);

		uint16_t VID_info = phost->device.DevDesc.idVendor;
		uint16_t PID_info = phost->device.DevDesc.idProduct;

		// USBH_UsrLog("VID: 0x%04X, PID: 0x%04X", VID_info, PID_info);

		// Multimedia Keyboard Lite-On
		const uint16_t VID_MKLiteOn = 0x04CA;
		const uint16_t PID_MKLiteOn = 0x005A;

		if ((VID_info == VID_MKLiteOn) && (PID_info == PID_MKLiteOn)) {
			USBH_HID_MultmediaKbDecode(custom_info_local);

			if (MKLITEON_decoded.valid == MKLITEON_VALID) {
				USBH_UsrLog("Multimedia Keyboard Lite-On");

				for (uint8_t i = 0; i < MKLITEON_decoded.multimedia_size; i++) {
					if (MKLITEON_decoded.multimedia == MKLITEON_array_ref[i]) {
						USBH_UsrLog("%s", MKLITEON_array_name[i]);
					}
				}
			}
		}
	}
}
/* USER CODE END 1 */

/**
 * Init USB host library, add supported class and start the library
 * @retval None
 */
void MX_USB_HOST_Init(void) {
	/* USER CODE BEGIN USB_HOST_Init_PreTreatment */
#ifdef HOST_HS
	// stm32f4xx_hal_rcc_ex.h
	__HAL_RCC_USB_OTG_HS_FORCE_RESET();
	__HAL_RCC_USB_OTG_HS_RELEASE_RESET();
#endif

#ifdef HOST_FS
	// stm32f4xx_hal_rcc_ex.h
	__HAL_RCC_USB_OTG_FS_FORCE_RESET();
	__HAL_RCC_USB_OTG_FS_RELEASE_RESET();
#endif
	/* USER CODE END USB_HOST_Init_PreTreatment */

	/* Init host Library, add supported class and start the library. */
	if (USBH_Init(&hUsbHostFS, USBH_UserProcess, HOST_FS) != USBH_OK) {
		Error_Handler();
	}
	if (USBH_RegisterClass(&hUsbHostFS, USBH_AUDIO_CLASS) != USBH_OK) {
		Error_Handler();
	}
	if (USBH_RegisterClass(&hUsbHostFS, USBH_CDC_CLASS) != USBH_OK) {
		Error_Handler();
	}
	if (USBH_RegisterClass(&hUsbHostFS, USBH_MSC_CLASS) != USBH_OK) {
		Error_Handler();
	}
	if (USBH_RegisterClass(&hUsbHostFS, USBH_HID_CLASS) != USBH_OK) {
		Error_Handler();
	}
	if (USBH_RegisterClass(&hUsbHostFS, USBH_MTP_CLASS) != USBH_OK) {
		Error_Handler();
	}
	if (USBH_Start(&hUsbHostFS) != USBH_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USB_HOST_Init_PostTreatment */

	/* USER CODE END USB_HOST_Init_PostTreatment */
}

/*
 * Background task
 */
void MX_USB_HOST_Process(void) {
	/* USB Host Background task */
	USBH_Process(&hUsbHostFS);
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

/**
 * @}
 */

/**
 * @}
 */

