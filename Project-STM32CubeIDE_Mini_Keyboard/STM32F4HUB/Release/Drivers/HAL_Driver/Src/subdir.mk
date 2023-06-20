################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/HAL_Driver/Src/stm32f4xx_hal.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_cortex.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_dma.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_flash.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_gpio.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_hcd.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_tim.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_uart.c \
../Drivers/HAL_Driver/Src/stm32f4xx_hal_usart.c \
../Drivers/HAL_Driver/Src/stm32f4xx_ll_usb.c 

OBJS += \
./Drivers/HAL_Driver/Src/stm32f4xx_hal.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_cortex.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_dma.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_dma_ex.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ex.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_gpio.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_hcd.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_i2c_ex.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd_ex.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_tim.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_tim_ex.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_uart.o \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_usart.o \
./Drivers/HAL_Driver/Src/stm32f4xx_ll_usb.o 

C_DEPS += \
./Drivers/HAL_Driver/Src/stm32f4xx_hal.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_cortex.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_dma.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_dma_ex.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ex.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_gpio.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_hcd.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_i2c_ex.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd_ex.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr_ex.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc_ex.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_tim.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_tim_ex.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_uart.d \
./Drivers/HAL_Driver/Src/stm32f4xx_hal_usart.d \
./Drivers/HAL_Driver/Src/stm32f4xx_ll_usb.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/HAL_Driver/Src/%.o Drivers/HAL_Driver/Src/%.su: ../Drivers/HAL_Driver/Src/%.c Drivers/HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32F4DIYMORE -DSTM32 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Core/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Drivers/CMSIS/core" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Drivers/CMSIS/device" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Drivers/HAL_Driver/Inc/Legacy" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Drivers/HAL_Driver/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/HUB/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Class/Template/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/USB_HOST/App/" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/USB_HOST/Target/" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ampire480272" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ampire640480" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/Common" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/cs43l22" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/exc7200" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ft6x06" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ili9325" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ili9341" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/l3gd20" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/lis302dl" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/lis3dsh" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/lsm303dlhc" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/mfxstm32l152" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/n25q128a" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/n25q256a" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/n25q512a" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/otm8009a" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ov2640" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/s25fl512s" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/s5k5cag" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/st7735" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/stmpe1600" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/stmpe811" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/ts3510" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/Components/wm8994" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/STM32F4-Discovery" -I"/mnt/6AFEAF4BFEAF0E7F/Dados/STM32CubeIDE/workspace_1.11.0/STM32F4HUB/Utilities/STM32F4-Diymore" -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-HAL_Driver-2f-Src

clean-Drivers-2f-HAL_Driver-2f-Src:
	-$(RM) ./Drivers/HAL_Driver/Src/stm32f4xx_hal.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_cortex.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_cortex.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_cortex.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_dma.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_dma.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_dma.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_dma_ex.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_dma_ex.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_dma_ex.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ex.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ex.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ex.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_gpio.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_gpio.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_gpio.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_hcd.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_hcd.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_hcd.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_i2c_ex.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_i2c_ex.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_i2c_ex.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd_ex.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd_ex.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pcd_ex.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr_ex.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_pwr_ex.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc_ex.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_rcc_ex.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_tim.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_tim.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_tim.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_tim_ex.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_tim_ex.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_tim_ex.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_uart.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_uart.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_uart.su ./Drivers/HAL_Driver/Src/stm32f4xx_hal_usart.d ./Drivers/HAL_Driver/Src/stm32f4xx_hal_usart.o ./Drivers/HAL_Driver/Src/stm32f4xx_hal_usart.su ./Drivers/HAL_Driver/Src/stm32f4xx_ll_usb.d ./Drivers/HAL_Driver/Src/stm32f4xx_ll_usb.o ./Drivers/HAL_Driver/Src/stm32f4xx_ll_usb.su

.PHONY: clean-Drivers-2f-HAL_Driver-2f-Src

