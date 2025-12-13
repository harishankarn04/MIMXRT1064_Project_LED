################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/AnjaliOldLipi_ttf.c \
../source/MIMXRT1064_Project.c \
../source/MTCORSVA_TTF.c \
../source/NotoSerif_ttf.c \
../source/hb_shaper.c \
../source/lv_hb_canvas_label.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/AnjaliOldLipi_ttf.d \
./source/MIMXRT1064_Project.d \
./source/MTCORSVA_TTF.d \
./source/NotoSerif_ttf.d \
./source/hb_shaper.d \
./source/lv_hb_canvas_label.d \
./source/semihost_hardfault.d 

OBJS += \
./source/AnjaliOldLipi_ttf.o \
./source/MIMXRT1064_Project.o \
./source/MTCORSVA_TTF.o \
./source/NotoSerif_ttf.o \
./source/hb_shaper.o \
./source/lv_hb_canvas_label.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DSDK_DELAY_USE_DWT=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DCPU_MIMXRT1064DVL6A -DCPU_MIMXRT1064DVL6A_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DUSE_RTOS=0 -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DLWIP_SUPPORT_CUSTOM_PBUF=1 -DCHECKSUM_GEN_UDP=1 -DCHECKSUM_GEN_TCP=1 -DCHECKSUM_GEN_ICMP=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_UDP=1 -DCHECKSUM_CHECK_TCP=1 -DCHECKSUM_CHECK_ICMP=1 -DCHECKSUM_CHECK_ICMP6=1 -D__NEWLIB__ -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/device" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/device/periph" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/utilities/debug_console_lite" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component/uart" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/drivers" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/utilities/str" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/CMSIS" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/CMSIS/m-profile" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/xip" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/utilities" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/lwip/contrib/apps/ping" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/lwip/contrib/apps/tcpecho" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/lwip/contrib/apps/tcpecho_raw" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/lwip/contrib/apps/udpecho" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/lwip/contrib/apps/udpecho_raw" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/mbedtls/include" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/mbedtls/library" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/usb/host" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/usb/include" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/usb/host/class" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component/osa" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/mbedtls/port/ksdk" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component/osa/config" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component/lists" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/lwip/port" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/lwip/src" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/lwip/src/include" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/lwip/src/include/lwip" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/lwip/port/sys_arch/dynamic" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/sdmmc/common" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/sdmmc/sdio" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/sdmmc/host/usdhc" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component/wifi_bt_module/incl" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component/wifi_bt_module/AzureWave/tx_pwr_limits" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component/wifi_bt_module/Murata/tx_pwr_limits" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component/wifi_bt_module/u-blox/tx_pwr_limits" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/sdmmc/osa" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component/gpio" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component/phy" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component/silicon_id" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/component" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/board" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/sdmmc/template/usdhc" -I"/Users/harishankar/Documents/gitClone/MIMXRT1064_Project_LED/source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/AnjaliOldLipi_ttf.d ./source/AnjaliOldLipi_ttf.o ./source/MIMXRT1064_Project.d ./source/MIMXRT1064_Project.o ./source/MTCORSVA_TTF.d ./source/MTCORSVA_TTF.o ./source/NotoSerif_ttf.d ./source/NotoSerif_ttf.o ./source/hb_shaper.d ./source/hb_shaper.o ./source/lv_hb_canvas_label.d ./source/lv_hb_canvas_label.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

