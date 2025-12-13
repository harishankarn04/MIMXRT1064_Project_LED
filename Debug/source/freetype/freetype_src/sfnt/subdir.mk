################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/freetype/freetype_src/sfnt/pngshim.c \
../source/freetype/freetype_src/sfnt/sfdriver.c \
../source/freetype/freetype_src/sfnt/sfnt.c \
../source/freetype/freetype_src/sfnt/sfobjs.c \
../source/freetype/freetype_src/sfnt/sfwoff.c \
../source/freetype/freetype_src/sfnt/sfwoff2.c \
../source/freetype/freetype_src/sfnt/ttbdf.c \
../source/freetype/freetype_src/sfnt/ttcmap.c \
../source/freetype/freetype_src/sfnt/ttcolr.c \
../source/freetype/freetype_src/sfnt/ttcpal.c \
../source/freetype/freetype_src/sfnt/ttgpos.c \
../source/freetype/freetype_src/sfnt/ttkern.c \
../source/freetype/freetype_src/sfnt/ttload.c \
../source/freetype/freetype_src/sfnt/ttmtx.c \
../source/freetype/freetype_src/sfnt/ttpost.c \
../source/freetype/freetype_src/sfnt/ttsbit.c \
../source/freetype/freetype_src/sfnt/ttsvg.c \
../source/freetype/freetype_src/sfnt/woff2tags.c 

C_DEPS += \
./source/freetype/freetype_src/sfnt/pngshim.d \
./source/freetype/freetype_src/sfnt/sfdriver.d \
./source/freetype/freetype_src/sfnt/sfnt.d \
./source/freetype/freetype_src/sfnt/sfobjs.d \
./source/freetype/freetype_src/sfnt/sfwoff.d \
./source/freetype/freetype_src/sfnt/sfwoff2.d \
./source/freetype/freetype_src/sfnt/ttbdf.d \
./source/freetype/freetype_src/sfnt/ttcmap.d \
./source/freetype/freetype_src/sfnt/ttcolr.d \
./source/freetype/freetype_src/sfnt/ttcpal.d \
./source/freetype/freetype_src/sfnt/ttgpos.d \
./source/freetype/freetype_src/sfnt/ttkern.d \
./source/freetype/freetype_src/sfnt/ttload.d \
./source/freetype/freetype_src/sfnt/ttmtx.d \
./source/freetype/freetype_src/sfnt/ttpost.d \
./source/freetype/freetype_src/sfnt/ttsbit.d \
./source/freetype/freetype_src/sfnt/ttsvg.d \
./source/freetype/freetype_src/sfnt/woff2tags.d 

OBJS += \
./source/freetype/freetype_src/sfnt/pngshim.o \
./source/freetype/freetype_src/sfnt/sfdriver.o \
./source/freetype/freetype_src/sfnt/sfnt.o \
./source/freetype/freetype_src/sfnt/sfobjs.o \
./source/freetype/freetype_src/sfnt/sfwoff.o \
./source/freetype/freetype_src/sfnt/sfwoff2.o \
./source/freetype/freetype_src/sfnt/ttbdf.o \
./source/freetype/freetype_src/sfnt/ttcmap.o \
./source/freetype/freetype_src/sfnt/ttcolr.o \
./source/freetype/freetype_src/sfnt/ttcpal.o \
./source/freetype/freetype_src/sfnt/ttgpos.o \
./source/freetype/freetype_src/sfnt/ttkern.o \
./source/freetype/freetype_src/sfnt/ttload.o \
./source/freetype/freetype_src/sfnt/ttmtx.o \
./source/freetype/freetype_src/sfnt/ttpost.o \
./source/freetype/freetype_src/sfnt/ttsbit.o \
./source/freetype/freetype_src/sfnt/ttsvg.o \
./source/freetype/freetype_src/sfnt/woff2tags.o 


# Each subdirectory must supply rules for building sources it contributes
source/freetype/freetype_src/sfnt/%.o: ../source/freetype/freetype_src/sfnt/%.c source/freetype/freetype_src/sfnt/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DSDK_DELAY_USE_DWT=1 -DFT2_BUILD_LIBRARY=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DCPU_MIMXRT1064DVL6A -DCPU_MIMXRT1064DVL6A_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DUSE_RTOS=0 -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DLWIP_SUPPORT_CUSTOM_PBUF=1 -DCHECKSUM_GEN_UDP=1 -DCHECKSUM_GEN_TCP=1 -DCHECKSUM_GEN_ICMP=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_UDP=1 -DCHECKSUM_CHECK_TCP=1 -DCHECKSUM_CHECK_ICMP=1 -DCHECKSUM_CHECK_ICMP6=1 -D__NEWLIB__ -UPRINTF_ADVANCED_ENABLE=1 -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\device" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\device\periph" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\utilities\debug_console_lite" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\uart" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\drivers" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\utilities\str" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\CMSIS" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\CMSIS\m-profile" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\xip" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\utilities" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\ping" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\tcpecho" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\tcpecho_raw" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\udpecho" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\udpecho_raw" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\mbedtls\include" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\mbedtls\library" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\usb\host" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\usb\include" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\usb\host\class" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\osa" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\mbedtls\port\ksdk" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\osa\config" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\lists" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\port" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\src" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\src\include" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\src\include\lwip" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\port\sys_arch\dynamic" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\common" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\sdio" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\host\usdhc" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\incl" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\AzureWave\tx_pwr_limits" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\Murata\tx_pwr_limits" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\u-blox\tx_pwr_limits" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\osa" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\gpio" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\phy" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\silicon_id" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\board" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\template\usdhc" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-freetype-2f-freetype_src-2f-sfnt

clean-source-2f-freetype-2f-freetype_src-2f-sfnt:
	-$(RM) ./source/freetype/freetype_src/sfnt/pngshim.d ./source/freetype/freetype_src/sfnt/pngshim.o ./source/freetype/freetype_src/sfnt/sfdriver.d ./source/freetype/freetype_src/sfnt/sfdriver.o ./source/freetype/freetype_src/sfnt/sfnt.d ./source/freetype/freetype_src/sfnt/sfnt.o ./source/freetype/freetype_src/sfnt/sfobjs.d ./source/freetype/freetype_src/sfnt/sfobjs.o ./source/freetype/freetype_src/sfnt/sfwoff.d ./source/freetype/freetype_src/sfnt/sfwoff.o ./source/freetype/freetype_src/sfnt/sfwoff2.d ./source/freetype/freetype_src/sfnt/sfwoff2.o ./source/freetype/freetype_src/sfnt/ttbdf.d ./source/freetype/freetype_src/sfnt/ttbdf.o ./source/freetype/freetype_src/sfnt/ttcmap.d ./source/freetype/freetype_src/sfnt/ttcmap.o ./source/freetype/freetype_src/sfnt/ttcolr.d ./source/freetype/freetype_src/sfnt/ttcolr.o ./source/freetype/freetype_src/sfnt/ttcpal.d ./source/freetype/freetype_src/sfnt/ttcpal.o ./source/freetype/freetype_src/sfnt/ttgpos.d ./source/freetype/freetype_src/sfnt/ttgpos.o ./source/freetype/freetype_src/sfnt/ttkern.d ./source/freetype/freetype_src/sfnt/ttkern.o ./source/freetype/freetype_src/sfnt/ttload.d ./source/freetype/freetype_src/sfnt/ttload.o ./source/freetype/freetype_src/sfnt/ttmtx.d ./source/freetype/freetype_src/sfnt/ttmtx.o ./source/freetype/freetype_src/sfnt/ttpost.d ./source/freetype/freetype_src/sfnt/ttpost.o ./source/freetype/freetype_src/sfnt/ttsbit.d ./source/freetype/freetype_src/sfnt/ttsbit.o ./source/freetype/freetype_src/sfnt/ttsvg.d ./source/freetype/freetype_src/sfnt/ttsvg.o ./source/freetype/freetype_src/sfnt/woff2tags.d ./source/freetype/freetype_src/sfnt/woff2tags.o

.PHONY: clean-source-2f-freetype-2f-freetype_src-2f-sfnt

