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

#include "main.h"
#include "usb_host.h"
#include <usbh_core.h>
#include <usbh_hid.h>
#include <usbh_hub.h>
#include <usbh_msc.h>
#include "usbh_hid_keybd.h"

#ifdef DiscoveryBoard
#include "stm32f4_discovery.h"
#endif

#ifdef DiyMoreBoard
#include "stm32f4_diymore.h"
#endif
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USB Host core handle declaration */
USBH_HandleTypeDef hUSBHostFS[10];
USBH_HandleTypeDef hUSBHostHS[10];
ApplicationTypeDef Appli_state_FS = APPLICATION_IDLE;
ApplicationTypeDef Appli_state_HS = APPLICATION_IDLE;
USBH_HandleTypeDef hUSB_Host;
//ApplicationTypeDef Appli_state_MSC = APPLICATION_IDLE;

uint8_t keyboard_insert = FALSE;
extern uint8_t kbd_LED_status[1];
uint32_t keyboard_led_timeout = 0;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */
#include "ff.h"
#include "fatfs.h"

uint8_t USBHostMscId = 0;
uint8_t USBDISKFatReady = USBH_NOT_SUPPORTED;
FATFS USBDISKFatFs; /* File system object for USB disk logical drive */
char USBDISKPath[4] = { 48, 58, 47, 0 }; /* USB Host logical drive path */
FATFS USBH_fatfs;
FIL MyFile;
FRESULT res;
UINT bytesWritten;
uint8_t rtext[200];
uint8_t wtext[] = "USB Host Library : Mass Storage Example";
char name[10]; //name of the file
uint16_t counter = 0;
uint32_t i = 0;
//static int32_t uart_length=0;
//extern char USBHPath[]; /* USBH logical drive path */

extern UART_HandleTypeDef huart3;
uint8_t uart_tx_buffer[100];

/*
 * user callback declaration
 */
static void USB_HOST_Init_FS(void);
static void USB_HOST_Init_HS(void);
static void USBH_UserProcess_FS(USBH_HandleTypeDef *phost, uint8_t id);
static void USBH_UserProcess_HS(USBH_HandleTypeDef *phost, uint8_t id);
static void hub_process(USBH_HandleTypeDef *hUSBHost);

void userFunction(void) {
	UINT bytesread;
	if (USBDISKFatReady == USBH_OK) {
		if ((HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_PIN) == GPIO_PIN_RESET)
				&& i > 0xfffff) {
			i = 0;

			LOG("userFunction start");

			// Begin TO DO 3 MSC_HOST_HANDS_ON: Complete the code skeleton
			// #warning "TO DO 3 MSC_HOST_HANDS_ON: Add the call to userFunction"
			//Code Skeleton
#if 1
			//File name creation
			sprintf(name, "%d.txt", counter++);
			/*Create a file*/
			if (f_open(&MyFile, name, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) {
				/* Creation failed */
				LOG("Cannot open %s file \n", name);
			} else {
				LOG("file %s created \n", name);
				/*write message to the file. Use variable wtext, bytesWritten*/
				res = f_write(&MyFile, wtext, sizeof(wtext), &bytesWritten);

				/*close the file*/
				f_close(&MyFile);

				/*check number of written bytes*/
				if ((bytesWritten == 0) || (res != FR_OK)) {
					/*error during writing*/
					LOG("write error \n");
				} else {
					/*open file to verification*/
					if (f_open(&MyFile, name, FA_READ) != FR_OK) {
						/*file open failure*/
						LOG("Cannot open %s file for verify \n", name);
					} else {
						/*Read file content. Use variable : rtext, bytesread*/
						res = f_read(&MyFile, rtext, sizeof(rtext), &bytesread);

						if ((bytesread == 0) || (res != FR_OK)) {
							/*read fail*/
							LOG("Cannot read file for verification \n");
						} else {
							/*read success*/
						}

						/*close the file*/
						if (f_close(&MyFile) != FR_OK) {
							/*check number of written bytes*/
							LOG("fclose fail \n");
							while (1) {
							}
						}
					}
					/* Compare read data with the expected data */
					if ((bytesread == bytesWritten)) {
						/*verification success full - number of written bytes is equal to number of read bytes*/
						LOG(
								"verification OK - read number of bytes is equal to written number of bytes \n");

						USBH_DeInit(&hUSB_Host);

						if (hUSB_Host.id == ID_USB_HOST_FS) {
							USB_HOST_Init_FS();
						} else { // if(phost->id == ID_USB_HOST_HS) {
							USB_HOST_Init_HS();
						}
					} else {
						/*verification failed - number of written bytes is not equal to number of read bytes*/
						LOG("verify fail \n");
					}
					/*end program execution after verification*/
				}
			}
#endif
		}
		i++;

		// End MSC_HOST_HANDS_ON: Add the call to userFunction()
	}
}
/* USER CODE END 0 */

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
	USB_HOST_Init_FS();

	USB_HOST_Init_HS();

	/* USER CODE BEGIN USB_HOST_Init_PostTreatment */

	/* USER CODE END USB_HOST_Init_PostTreatment */
}

static void USB_HOST_Init_FS(void) {
	/* Init FS */
	hUSBHostFS->id = ID_USB_HOST_FS;

	memset(&hUSBHostFS[0], 0, sizeof(USBH_HandleTypeDef));

	hUSBHostFS[0].valid = 1;
	hUSBHostFS[0].address = USBH_DEVICE_ADDRESS;
	hUSBHostFS[0].Pipes[0] = USBH_malloc(sizeof(uint32_t) * USBH_MAX_PIPES_NBR);

	USBH_Init(&hUSBHostFS[0], USBH_UserProcess_FS, ID_USB_HOST_FS);
	USBH_RegisterClass(&hUSBHostFS[0], USBH_HUB_CLASS);
	USBH_RegisterClass(&hUSBHostFS[0], USBH_HID_CLASS);
	USBH_RegisterClass(&hUSBHostFS[0], USBH_MSC_CLASS);

	USBH_Start(&hUSBHostFS[0]);
}

static void USB_HOST_Init_HS(void) {
	/* Init HS */
	hUSBHostHS->id = ID_USB_HOST_HS;

	memset(&hUSBHostHS[0], 0, sizeof(USBH_HandleTypeDef));

	hUSBHostHS[0].valid = 1;
	hUSBHostHS[0].address = USBH_DEVICE_ADDRESS;
	hUSBHostHS[0].Pipes[0] = USBH_malloc(sizeof(uint32_t) * USBH_MAX_PIPES_NBR);

	USBH_Init(&hUSBHostHS[0], USBH_UserProcess_HS, ID_USB_HOST_HS);
	USBH_RegisterClass(&hUSBHostHS[0], USBH_HUB_CLASS);
	USBH_RegisterClass(&hUSBHostHS[0], USBH_MSC_CLASS);
	USBH_RegisterClass(&hUSBHostHS[0], USBH_HID_CLASS);

	USBH_Start(&hUSBHostHS[0]);
}

/*
 * Background task
 */
void MX_USB_HOST_Process(void) {
	/* USB Host Background task */
	hub_process(hUSBHostFS);
	hub_process(hUSBHostHS);
}
/*
 * user callback definition
 */
static void USBH_UserProcess_FS(USBH_HandleTypeDef *phost, uint8_t id) {
	/* USER CODE BEGIN CALL_BACK_1 */
	switch (id) {
	case HOST_USER_SELECT_CONFIGURATION:
		break;

	case HOST_USER_DISCONNECTION:
		Appli_state_FS = APPLICATION_DISCONNECT;
		break;

	case HOST_USER_CLASS_ACTIVE:
		if (USBDISKFatReady == USBH_OK) {
			hUSB_Host = *phost;
			/* Register the file system object to the FatFs module */
			if (FATFS_LinkDriver(&USBH_Driver, USBDISKPath) == 0) {
				if (f_mount(&USBDISKFatFs, (TCHAR const*) USBDISKPath, 0)
						!= FR_OK) {
					/* FatFs Initialization Error */
					LOG("FatFs Initialization Error");
					USBDISKFatReady = USBH_NOT_SUPPORTED;
					return;
				} else {
					LOG("FatFs Initialization Ready");
				}
			}
		}
		Appli_state_FS = APPLICATION_READY;
		break;

	case HOST_USER_CONNECTION:
		Appli_state_FS = APPLICATION_START;
		break;

	default:
		break;
	}
	/* USER CODE END CALL_BACK_1 */
}

static void USBH_UserProcess_HS(USBH_HandleTypeDef *phost, uint8_t id) {
	/* USER CODE BEGIN CALL_BACK_1 */
	switch (id) {
	case HOST_USER_SELECT_CONFIGURATION:
		break;

	case HOST_USER_DISCONNECTION:
		Appli_state_HS = APPLICATION_DISCONNECT;
		break;

	case HOST_USER_CLASS_ACTIVE:
		if (USBDISKFatReady == USBH_OK) {
			hUSB_Host = *phost;
			/* Register the file system object to the FatFs module */
			if (FATFS_LinkDriver(&USBH_Driver, USBDISKPath) == 0) {
				if (f_mount(&USBDISKFatFs, (TCHAR const*) USBDISKPath, 0)
						!= FR_OK) {
					/* FatFs Initialization Error */
					LOG("FatFs Initialization Error");
					USBDISKFatReady = USBH_NOT_SUPPORTED;
					return;
				} else {
					LOG("FatFs Initialization Ready");
				}
			}
		}
		Appli_state_HS = APPLICATION_READY;
		break;

	case HOST_USER_CONNECTION:
		Appli_state_HS = APPLICATION_START;
		break;

	default:
		break;
	}
	/* USER CODE END CALL_BACK_1 */
}

static USBH_HandleTypeDef *_phost = 0;

static void hub_process(USBH_HandleTypeDef *hUSBHost) {
	static uint8_t current_loop = -1;

	if (hUSBHost != NULL && hUSBHost->valid == 1) {
		//USBH_DbgLog("USBH_Process");
		hUSBHost->id = hUSBHost->id;
		USBH_Process(hUSBHost);

		if (hUSBHost->busy)
			return;
	}

	while (1) {
		current_loop++;

		if (current_loop > MAX_HUB_PORTS) {
			current_loop = 0;
		}

		if (hUSBHost[current_loop].valid) {
			_phost = &hUSBHost[current_loop];
			//USBH_DbgLog("USBH_LL_SetupEP0");
			USBH_LL_SetupEP0(_phost);

			if (_phost->valid == 3) {
				USBH_DbgLog("PROCESSING ATTACH %d", _phost->address);
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
			USBH_DbgLog("Btn %d%d%d %d%d%d%d%d %d%d%d %d%d%d; X %d; Y %d",
					minfo->buttons[0], minfo->buttons[1], minfo->buttons[2],
					minfo->buttons[3], minfo->buttons[4], minfo->buttons[5],
					minfo->buttons[6], minfo->buttons[7], minfo->buttons[8],
					minfo->buttons[9], minfo->buttons[10], minfo->buttons[11],
					minfo->buttons[12], minfo->buttons[13], minfo->x, minfo->y);
		} else {
			HID_KEYBD_Info_TypeDef *kinfo;
			kinfo = USBH_HID_GetKeybdInfo(_phost);
			if (kinfo != NULL) {
				uint8_t key = kinfo->keys[0];

				if (key == KEY_INSERT) {
					keyboard_insert = !keyboard_insert;
				} else {
					if((HAL_GetTick() - keyboard_led_timeout) > 300){
						keyboard_led_timeout = HAL_GetTick();

						if (key == KEY_KEYPAD_NUM_LOCK_AND_CLEAR) {
							if ((kbd_LED_status[0] & 1) == 0) {
								kbd_LED_status[0] |= 0B001;
							} else {
								kbd_LED_status[0] &= 0B110;
							}

							USBH_DbgLog("kbd_LED_status %d", kbd_LED_status[0]);

							//		USB_Set_Keyboard_LED_Status();
						} else if (key == KEY_CAPS_LOCK) {
							if (((kbd_LED_status[0] >> 1) & 1) == 0) {
								kbd_LED_status[0] |= 0B010;
							} else {
								kbd_LED_status[0] &= 0B101;
							}

							USBH_DbgLog("kbd_LED_status %d", kbd_LED_status[0]);
						} else if (key == KEY_SCROLL_LOCK) {
							if (((kbd_LED_status[0] >> 2) & 1) == 0) {
								kbd_LED_status[0] |= 0B100;
							} else {
								kbd_LED_status[0] &= 0B011;
							}

							USBH_DbgLog("kbd_LED_status %d", kbd_LED_status[0]);
						}
					} else {
						// keyboardMain(keybd_info1);
					}
				}

				USBH_DbgLog("KEYB %d", kinfo->keys[0]);
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

