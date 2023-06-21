# STM32F4HUB_modified

- Support to all HID interfaces (if not recognized, skip handling)
- - To recognize the Mini Keyboard with built-in touchpad
- - - This project can serve as a basis for other devices with multiple interfaces
- - - - To do: Update HID project from ASC project (it stopped recognizing the multimedia keyboard)
- - - - To do: Check if keyboard accepts LED control, Mini Keyboard crashes when sending control data.

Note: Original STM32F4HUB description at the [bottom of this page](https://github.com/rtek1000/STM32F4HUB_modified/tree/main#stm32f4hub---original-info)

----

- Date: Jun, 20, 2023
- - Modification:
- - - Adaptation of [Project-STM32CubeIDE_USBH_HID](https://github.com/rtek1000/STM32F4HUB/tree/master/Project-STM32CubeIDE_USBH_HID)
- - - Project "All Supported Classes" automatically generated by STM32CubeIDE version: 1.12.1 (FW_F4 1.27.1)
- - - - Modifications to USB port RESET timers to not block code for many milliseconds
- - - - Added automatic recovery, "de-initialize" the USB port and "re-initialize"
- - - - Port timeout modifications for automatic recovery
- - - - Adaptation to recognize more HID interfaces
- - - - - Mini Wireless Keyboard Built-in Touchpad  (VID: 0x0513, PID: 0x0318) supported, multimedia buttons and touchpad supported
- - - - - Regular keyboard multimedia interface was not implemented, only the keyboard part works
- - - - Keyboard LED control supported
- - - - Wireless Mouse Logitech M220 (and M185) (VID: 0x046D, PID: 0xC534) supported
- - - - HUB class not implemented
- - - - Folder: [Project-STM32CubeIDE_USBH_ASC](https://github.com/rtek1000/STM32F4HUB_modified/tree/main/Project-STM32CubeIDE_USBH_ASC)
- - By: RTEK1000
-
- Date: Jun, 15, 2023
- - Modification:
- - - Adaptation to recognize more HID interfaces
- - - Project automatically generated by STM32CubeIDE version: 1.12.1 (Current version)
- - - - The main issue is the use of arrays to save initializations and perform processing
- - - - HUB class not implemented
- - - - Folder: [Project-STM32CubeIDE_USBH_HID](https://github.com/rtek1000/STM32F4HUB/tree/master/Project-STM32CubeIDE_USBH_HID)
- - - Ref.: [BTstack Port for STM32 USB](https://bluekitchen-gmbh.com/btstack-stm32-usb-port/)
- - By: RTEK1000
 -
- Date: Jun, 13, 2023
- - Debug info for Mini Keyboard Wireless with built-in touchpad
- - - Debug messages obtained on serial port UART1 (PA9: TX, PA10: RX)
- - - Board: [STM32F407VGT6-diymore](https://stm32-base.org/boards/STM32F407VGT6-diymore.html)
- - By: RTEK1000
-
- Date: Dez, 31, 2022
- - Modification:
- - - Added support for two USB ports
- - - Added MSC class support
- - - Modified HUB Class
- - By: RTEK1000
-
- Date: Dez, 27, 2022
- - Modification:
- - - Added Alternative support for Mini Keyboard (built-in touchpad)
- - - - Note: The HID class must support multiple interfaces for this keyboard to work.
- - - - (See https://www.amazon.com/Wireless-Keyboard-BIFANS-Portable-Touchpad/dp/B075SBX1CX)
- - - - Click to open image: [Mini Keyboard Wireless with built-in touchpad](https://raw.githubusercontent.com/rtek1000/STM32F4HUB/master/Project-STM32CubeIDE_Mini_Keyboard/Mini_Keyboard1.jpg)
- - By: RTEK1000
-
- Date: Dez, 26, 2022
- - Modification:
- - - Converted from 'System Workbench for STM32' to 'STM32CubeIDE v1.11.0'
- - - - (See UM2579 - Migration guide from System Workbench to STM32CubeIDE)
- - - Added DiyMore board (selected in main.h file)
- - - - (See https://stm32-base.org/boards/STM32F407VGT6-diymore.html)
- - By: RTEK1000

-----

## STM32F4HUB - Original info

[STM32F4HUB](https://github.com/mori-br/STM32F4HUB) 

Add USB Hub support to your STM32F4 project. Based on STM32Cube Library

* Support to Full speed and low speed usb devices through a hub. 
* Support to all hid interfaces.
* Easilly portable to others STM32Fx microcontrollers

* Ready to be opened and compiled with AC6 IDE

It's ready to run on a STM32F4DISCOVERY development board. You just need a Micro-AB to Type A usb cable.
