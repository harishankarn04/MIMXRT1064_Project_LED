################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_cache.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dcdc.c \
../drivers/fsl_dcp.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_edma.c \
../drivers/fsl_enet.c \
../drivers/fsl_gpc.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpspi.c \
../drivers/fsl_lpspi_edma.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_pit.c \
../drivers/fsl_pmu.c \
../drivers/fsl_semc.c \
../drivers/fsl_snvs_lp.c \
../drivers/fsl_src.c \
../drivers/fsl_trng.c \
../drivers/fsl_usdhc.c 

C_DEPS += \
./drivers/fsl_cache.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dcdc.d \
./drivers/fsl_dcp.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_edma.d \
./drivers/fsl_enet.d \
./drivers/fsl_gpc.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpspi.d \
./drivers/fsl_lpspi_edma.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_pit.d \
./drivers/fsl_pmu.d \
./drivers/fsl_semc.d \
./drivers/fsl_snvs_lp.d \
./drivers/fsl_src.d \
./drivers/fsl_trng.d \
./drivers/fsl_usdhc.d 

OBJS += \
./drivers/fsl_cache.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dcdc.o \
./drivers/fsl_dcp.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_edma.o \
./drivers/fsl_enet.o \
./drivers/fsl_gpc.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpspi.o \
./drivers/fsl_lpspi_edma.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_pit.o \
./drivers/fsl_pmu.o \
./drivers/fsl_semc.o \
./drivers/fsl_snvs_lp.o \
./drivers/fsl_src.o \
./drivers/fsl_trng.o \
./drivers/fsl_usdhc.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DSDK_DELAY_USE_DWT=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DCPU_MIMXRT1064DVL6A -DCPU_MIMXRT1064DVL6A_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DUSE_RTOS=0 -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DLWIP_SUPPORT_CUSTOM_PBUF=1 -DCHECKSUM_GEN_UDP=1 -DCHECKSUM_GEN_TCP=1 -DCHECKSUM_GEN_ICMP=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_UDP=1 -DCHECKSUM_CHECK_TCP=1 -DCHECKSUM_CHECK_ICMP=1 -DCHECKSUM_CHECK_ICMP6=1 -D__NEWLIB__ -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/device" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/device/periph" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities/debug_console_lite" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/uart" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/drivers" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities/str" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/CMSIS" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/CMSIS/m-profile" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/xip" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/ping" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lvgl" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lvgl/src" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/tcpecho" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/tcpecho_raw" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/udpecho" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/udpecho_raw" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/host" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/include" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/host/class" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/osa" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/osa/config" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/lists" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/port" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src/include" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src/include/lwip" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/port/sys_arch/dynamic" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/gpio" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/phy" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/silicon_id" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/phy" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/board" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source/config/host/ehci" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source/application/DisplayController" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/wifi_bt_module/Murata/tx_pwr_limits" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_cache.d ./drivers/fsl_cache.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dcdc.d ./drivers/fsl_dcdc.o ./drivers/fsl_dcp.d ./drivers/fsl_dcp.o ./drivers/fsl_dmamux.d ./drivers/fsl_dmamux.o ./drivers/fsl_edma.d ./drivers/fsl_edma.o ./drivers/fsl_enet.d ./drivers/fsl_enet.o ./drivers/fsl_gpc.d ./drivers/fsl_gpc.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpspi.d ./drivers/fsl_lpspi.o ./drivers/fsl_lpspi_edma.d ./drivers/fsl_lpspi_edma.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_pit.d ./drivers/fsl_pit.o ./drivers/fsl_pmu.d ./drivers/fsl_pmu.o ./drivers/fsl_semc.d ./drivers/fsl_semc.o ./drivers/fsl_snvs_lp.d ./drivers/fsl_snvs_lp.o ./drivers/fsl_src.d ./drivers/fsl_src.o ./drivers/fsl_trng.d ./drivers/fsl_trng.o ./drivers/fsl_usdhc.d ./drivers/fsl_usdhc.o

.PHONY: clean-drivers

