################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL_Driver/Src/stm32f4xx_hal.c \
../HAL_Driver/Src/stm32f4xx_hal_cortex.c \
../HAL_Driver/Src/stm32f4xx_hal_dma.c \
../HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
../HAL_Driver/Src/stm32f4xx_hal_flash.c \
../HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
../HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
../HAL_Driver/Src/stm32f4xx_hal_gpio.c \
../HAL_Driver/Src/stm32f4xx_hal_hcd.c \
../HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
../HAL_Driver/Src/stm32f4xx_hal_pcd.c \
../HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c \
../HAL_Driver/Src/stm32f4xx_hal_pwr.c \
../HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
../HAL_Driver/Src/stm32f4xx_hal_rcc.c \
../HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
../HAL_Driver/Src/stm32f4xx_hal_tim.c \
../HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
../HAL_Driver/Src/stm32f4xx_hal_uart.c \
../HAL_Driver/Src/stm32f4xx_hal_usart.c \
../HAL_Driver/Src/stm32f4xx_ll_usb.c 

OBJS += \
./HAL_Driver/Src/stm32f4xx_hal.o \
./HAL_Driver/Src/stm32f4xx_hal_cortex.o \
./HAL_Driver/Src/stm32f4xx_hal_dma.o \
./HAL_Driver/Src/stm32f4xx_hal_dma_ex.o \
./HAL_Driver/Src/stm32f4xx_hal_flash.o \
./HAL_Driver/Src/stm32f4xx_hal_flash_ex.o \
./HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o \
./HAL_Driver/Src/stm32f4xx_hal_gpio.o \
./HAL_Driver/Src/stm32f4xx_hal_hcd.o \
./HAL_Driver/Src/stm32f4xx_hal_i2c_ex.o \
./HAL_Driver/Src/stm32f4xx_hal_pcd.o \
./HAL_Driver/Src/stm32f4xx_hal_pcd_ex.o \
./HAL_Driver/Src/stm32f4xx_hal_pwr.o \
./HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o \
./HAL_Driver/Src/stm32f4xx_hal_rcc.o \
./HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o \
./HAL_Driver/Src/stm32f4xx_hal_tim.o \
./HAL_Driver/Src/stm32f4xx_hal_tim_ex.o \
./HAL_Driver/Src/stm32f4xx_hal_uart.o \
./HAL_Driver/Src/stm32f4xx_hal_usart.o \
./HAL_Driver/Src/stm32f4xx_ll_usb.o 

C_DEPS += \
./HAL_Driver/Src/stm32f4xx_hal.d \
./HAL_Driver/Src/stm32f4xx_hal_cortex.d \
./HAL_Driver/Src/stm32f4xx_hal_dma.d \
./HAL_Driver/Src/stm32f4xx_hal_dma_ex.d \
./HAL_Driver/Src/stm32f4xx_hal_flash.d \
./HAL_Driver/Src/stm32f4xx_hal_flash_ex.d \
./HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.d \
./HAL_Driver/Src/stm32f4xx_hal_gpio.d \
./HAL_Driver/Src/stm32f4xx_hal_hcd.d \
./HAL_Driver/Src/stm32f4xx_hal_i2c_ex.d \
./HAL_Driver/Src/stm32f4xx_hal_pcd.d \
./HAL_Driver/Src/stm32f4xx_hal_pcd_ex.d \
./HAL_Driver/Src/stm32f4xx_hal_pwr.d \
./HAL_Driver/Src/stm32f4xx_hal_pwr_ex.d \
./HAL_Driver/Src/stm32f4xx_hal_rcc.d \
./HAL_Driver/Src/stm32f4xx_hal_rcc_ex.d \
./HAL_Driver/Src/stm32f4xx_hal_tim.d \
./HAL_Driver/Src/stm32f4xx_hal_tim_ex.d \
./HAL_Driver/Src/stm32f4xx_hal_uart.d \
./HAL_Driver/Src/stm32f4xx_hal_usart.d \
./HAL_Driver/Src/stm32f4xx_ll_usb.d 


# Each subdirectory must supply rules for building sources it contributes
HAL_Driver/Src/%.o HAL_Driver/Src/%.su: ../HAL_Driver/Src/%.c HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/CMSIS/core" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/CMSIS/device" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/HAL_Driver/Inc/Legacy" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/HAL_Driver/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/HUB/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/Template/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ampire480272" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ampire640480" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/Common" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/cs43l22" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/exc7200" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ft6x06" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ili9325" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ili9341" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/l3gd20" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/lis302dl" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/lis3dsh" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/lsm303dlhc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/mfxstm32l152" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/n25q128a" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/n25q256a" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/n25q512a" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/otm8009a" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ov2640" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/s25fl512s" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/s5k5cag" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/st7735" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/stmpe1600" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/stmpe811" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ts3510" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/wm8994" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/STM32F4-Discovery" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/STM32F4-Diymore" -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL_Driver-2f-Src

clean-HAL_Driver-2f-Src:
	-$(RM) ./HAL_Driver/Src/stm32f4xx_hal.d ./HAL_Driver/Src/stm32f4xx_hal.o ./HAL_Driver/Src/stm32f4xx_hal.su ./HAL_Driver/Src/stm32f4xx_hal_cortex.d ./HAL_Driver/Src/stm32f4xx_hal_cortex.o ./HAL_Driver/Src/stm32f4xx_hal_cortex.su ./HAL_Driver/Src/stm32f4xx_hal_dma.d ./HAL_Driver/Src/stm32f4xx_hal_dma.o ./HAL_Driver/Src/stm32f4xx_hal_dma.su ./HAL_Driver/Src/stm32f4xx_hal_dma_ex.d ./HAL_Driver/Src/stm32f4xx_hal_dma_ex.o ./HAL_Driver/Src/stm32f4xx_hal_dma_ex.su ./HAL_Driver/Src/stm32f4xx_hal_flash.d ./HAL_Driver/Src/stm32f4xx_hal_flash.o ./HAL_Driver/Src/stm32f4xx_hal_flash.su ./HAL_Driver/Src/stm32f4xx_hal_flash_ex.d ./HAL_Driver/Src/stm32f4xx_hal_flash_ex.o ./HAL_Driver/Src/stm32f4xx_hal_flash_ex.su ./HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.d ./HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o ./HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.su ./HAL_Driver/Src/stm32f4xx_hal_gpio.d ./HAL_Driver/Src/stm32f4xx_hal_gpio.o ./HAL_Driver/Src/stm32f4xx_hal_gpio.su ./HAL_Driver/Src/stm32f4xx_hal_hcd.d ./HAL_Driver/Src/stm32f4xx_hal_hcd.o ./HAL_Driver/Src/stm32f4xx_hal_hcd.su ./HAL_Driver/Src/stm32f4xx_hal_i2c_ex.d ./HAL_Driver/Src/stm32f4xx_hal_i2c_ex.o ./HAL_Driver/Src/stm32f4xx_hal_i2c_ex.su ./HAL_Driver/Src/stm32f4xx_hal_pcd.d ./HAL_Driver/Src/stm32f4xx_hal_pcd.o ./HAL_Driver/Src/stm32f4xx_hal_pcd.su ./HAL_Driver/Src/stm32f4xx_hal_pcd_ex.d ./HAL_Driver/Src/stm32f4xx_hal_pcd_ex.o ./HAL_Driver/Src/stm32f4xx_hal_pcd_ex.su ./HAL_Driver/Src/stm32f4xx_hal_pwr.d ./HAL_Driver/Src/stm32f4xx_hal_pwr.o ./HAL_Driver/Src/stm32f4xx_hal_pwr.su ./HAL_Driver/Src/stm32f4xx_hal_pwr_ex.d ./HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o ./HAL_Driver/Src/stm32f4xx_hal_pwr_ex.su ./HAL_Driver/Src/stm32f4xx_hal_rcc.d ./HAL_Driver/Src/stm32f4xx_hal_rcc.o ./HAL_Driver/Src/stm32f4xx_hal_rcc.su ./HAL_Driver/Src/stm32f4xx_hal_rcc_ex.d ./HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o ./HAL_Driver/Src/stm32f4xx_hal_rcc_ex.su ./HAL_Driver/Src/stm32f4xx_hal_tim.d ./HAL_Driver/Src/stm32f4xx_hal_tim.o ./HAL_Driver/Src/stm32f4xx_hal_tim.su ./HAL_Driver/Src/stm32f4xx_hal_tim_ex.d ./HAL_Driver/Src/stm32f4xx_hal_tim_ex.o ./HAL_Driver/Src/stm32f4xx_hal_tim_ex.su ./HAL_Driver/Src/stm32f4xx_hal_uart.d ./HAL_Driver/Src/stm32f4xx_hal_uart.o ./HAL_Driver/Src/stm32f4xx_hal_uart.su ./HAL_Driver/Src/stm32f4xx_hal_usart.d ./HAL_Driver/Src/stm32f4xx_hal_usart.o ./HAL_Driver/Src/stm32f4xx_hal_usart.su ./HAL_Driver/Src/stm32f4xx_ll_usb.d ./HAL_Driver/Src/stm32f4xx_ll_usb.o ./HAL_Driver/Src/stm32f4xx_ll_usb.su

.PHONY: clean-HAL_Driver-2f-Src

