################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/freetype/freetype_src/psaux/afmparse.c \
../source/freetype/freetype_src/psaux/cffdecode.c \
../source/freetype/freetype_src/psaux/psarrst.c \
../source/freetype/freetype_src/psaux/psaux.c \
../source/freetype/freetype_src/psaux/psauxmod.c \
../source/freetype/freetype_src/psaux/psblues.c \
../source/freetype/freetype_src/psaux/psconv.c \
../source/freetype/freetype_src/psaux/pserror.c \
../source/freetype/freetype_src/psaux/psfont.c \
../source/freetype/freetype_src/psaux/psft.c \
../source/freetype/freetype_src/psaux/pshints.c \
../source/freetype/freetype_src/psaux/psintrp.c \
../source/freetype/freetype_src/psaux/psobjs.c \
../source/freetype/freetype_src/psaux/psread.c \
../source/freetype/freetype_src/psaux/psstack.c \
../source/freetype/freetype_src/psaux/t1cmap.c \
../source/freetype/freetype_src/psaux/t1decode.c 

C_DEPS += \
./source/freetype/freetype_src/psaux/afmparse.d \
./source/freetype/freetype_src/psaux/cffdecode.d \
./source/freetype/freetype_src/psaux/psarrst.d \
./source/freetype/freetype_src/psaux/psaux.d \
./source/freetype/freetype_src/psaux/psauxmod.d \
./source/freetype/freetype_src/psaux/psblues.d \
./source/freetype/freetype_src/psaux/psconv.d \
./source/freetype/freetype_src/psaux/pserror.d \
./source/freetype/freetype_src/psaux/psfont.d \
./source/freetype/freetype_src/psaux/psft.d \
./source/freetype/freetype_src/psaux/pshints.d \
./source/freetype/freetype_src/psaux/psintrp.d \
./source/freetype/freetype_src/psaux/psobjs.d \
./source/freetype/freetype_src/psaux/psread.d \
./source/freetype/freetype_src/psaux/psstack.d \
./source/freetype/freetype_src/psaux/t1cmap.d \
./source/freetype/freetype_src/psaux/t1decode.d 

OBJS += \
./source/freetype/freetype_src/psaux/afmparse.o \
./source/freetype/freetype_src/psaux/cffdecode.o \
./source/freetype/freetype_src/psaux/psarrst.o \
./source/freetype/freetype_src/psaux/psaux.o \
./source/freetype/freetype_src/psaux/psauxmod.o \
./source/freetype/freetype_src/psaux/psblues.o \
./source/freetype/freetype_src/psaux/psconv.o \
./source/freetype/freetype_src/psaux/pserror.o \
./source/freetype/freetype_src/psaux/psfont.o \
./source/freetype/freetype_src/psaux/psft.o \
./source/freetype/freetype_src/psaux/pshints.o \
./source/freetype/freetype_src/psaux/psintrp.o \
./source/freetype/freetype_src/psaux/psobjs.o \
./source/freetype/freetype_src/psaux/psread.o \
./source/freetype/freetype_src/psaux/psstack.o \
./source/freetype/freetype_src/psaux/t1cmap.o \
./source/freetype/freetype_src/psaux/t1decode.o 


# Each subdirectory must supply rules for building sources it contributes
source/freetype/freetype_src/psaux/%.o: ../source/freetype/freetype_src/psaux/%.c source/freetype/freetype_src/psaux/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DSDK_DELAY_USE_DWT=1 -DFT2_BUILD_LIBRARY=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DCPU_MIMXRT1064DVL6A -DCPU_MIMXRT1064DVL6A_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DUSE_RTOS=0 -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DLWIP_SUPPORT_CUSTOM_PBUF=1 -DCHECKSUM_GEN_UDP=1 -DCHECKSUM_GEN_TCP=1 -DCHECKSUM_GEN_ICMP=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_UDP=1 -DCHECKSUM_CHECK_TCP=1 -DCHECKSUM_CHECK_ICMP=1 -DCHECKSUM_CHECK_ICMP6=1 -D__NEWLIB__ -UPRINTF_ADVANCED_ENABLE=1 -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\device" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\device\periph" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\utilities\debug_console_lite" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\uart" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\drivers" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\utilities\str" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\CMSIS" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\CMSIS\m-profile" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\xip" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\utilities" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\ping" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\tcpecho" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\tcpecho_raw" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\udpecho" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\udpecho_raw" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\mbedtls\include" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\mbedtls\library" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\usb\host" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\usb\include" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\usb\host\class" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\osa" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\mbedtls\port\ksdk" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\osa\config" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\lists" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\port" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\src" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\src\include" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\src\include\lwip" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\port\sys_arch\dynamic" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\common" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\sdio" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\host\usdhc" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\incl" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\AzureWave\tx_pwr_limits" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\Murata\tx_pwr_limits" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\u-blox\tx_pwr_limits" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\osa" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\gpio" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\phy" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\silicon_id" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\board" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\template\usdhc" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-freetype-2f-freetype_src-2f-psaux

clean-source-2f-freetype-2f-freetype_src-2f-psaux:
	-$(RM) ./source/freetype/freetype_src/psaux/afmparse.d ./source/freetype/freetype_src/psaux/afmparse.o ./source/freetype/freetype_src/psaux/cffdecode.d ./source/freetype/freetype_src/psaux/cffdecode.o ./source/freetype/freetype_src/psaux/psarrst.d ./source/freetype/freetype_src/psaux/psarrst.o ./source/freetype/freetype_src/psaux/psaux.d ./source/freetype/freetype_src/psaux/psaux.o ./source/freetype/freetype_src/psaux/psauxmod.d ./source/freetype/freetype_src/psaux/psauxmod.o ./source/freetype/freetype_src/psaux/psblues.d ./source/freetype/freetype_src/psaux/psblues.o ./source/freetype/freetype_src/psaux/psconv.d ./source/freetype/freetype_src/psaux/psconv.o ./source/freetype/freetype_src/psaux/pserror.d ./source/freetype/freetype_src/psaux/pserror.o ./source/freetype/freetype_src/psaux/psfont.d ./source/freetype/freetype_src/psaux/psfont.o ./source/freetype/freetype_src/psaux/psft.d ./source/freetype/freetype_src/psaux/psft.o ./source/freetype/freetype_src/psaux/pshints.d ./source/freetype/freetype_src/psaux/pshints.o ./source/freetype/freetype_src/psaux/psintrp.d ./source/freetype/freetype_src/psaux/psintrp.o ./source/freetype/freetype_src/psaux/psobjs.d ./source/freetype/freetype_src/psaux/psobjs.o ./source/freetype/freetype_src/psaux/psread.d ./source/freetype/freetype_src/psaux/psread.o ./source/freetype/freetype_src/psaux/psstack.d ./source/freetype/freetype_src/psaux/psstack.o ./source/freetype/freetype_src/psaux/t1cmap.d ./source/freetype/freetype_src/psaux/t1cmap.o ./source/freetype/freetype_src/psaux/t1decode.d ./source/freetype/freetype_src/psaux/t1decode.o

.PHONY: clean-source-2f-freetype-2f-freetype_src-2f-psaux

