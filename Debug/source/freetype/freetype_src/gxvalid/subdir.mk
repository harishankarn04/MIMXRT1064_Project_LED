################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/freetype/freetype_src/gxvalid/gxvalid.c \
../source/freetype/freetype_src/gxvalid/gxvbsln.c \
../source/freetype/freetype_src/gxvalid/gxvcommn.c \
../source/freetype/freetype_src/gxvalid/gxvfeat.c \
../source/freetype/freetype_src/gxvalid/gxvfgen.c \
../source/freetype/freetype_src/gxvalid/gxvjust.c \
../source/freetype/freetype_src/gxvalid/gxvkern.c \
../source/freetype/freetype_src/gxvalid/gxvlcar.c \
../source/freetype/freetype_src/gxvalid/gxvmod.c \
../source/freetype/freetype_src/gxvalid/gxvmort.c \
../source/freetype/freetype_src/gxvalid/gxvmort0.c \
../source/freetype/freetype_src/gxvalid/gxvmort1.c \
../source/freetype/freetype_src/gxvalid/gxvmort2.c \
../source/freetype/freetype_src/gxvalid/gxvmort4.c \
../source/freetype/freetype_src/gxvalid/gxvmort5.c \
../source/freetype/freetype_src/gxvalid/gxvmorx.c \
../source/freetype/freetype_src/gxvalid/gxvmorx0.c \
../source/freetype/freetype_src/gxvalid/gxvmorx1.c \
../source/freetype/freetype_src/gxvalid/gxvmorx2.c \
../source/freetype/freetype_src/gxvalid/gxvmorx4.c \
../source/freetype/freetype_src/gxvalid/gxvmorx5.c \
../source/freetype/freetype_src/gxvalid/gxvopbd.c \
../source/freetype/freetype_src/gxvalid/gxvprop.c \
../source/freetype/freetype_src/gxvalid/gxvtrak.c 

C_DEPS += \
./source/freetype/freetype_src/gxvalid/gxvalid.d \
./source/freetype/freetype_src/gxvalid/gxvbsln.d \
./source/freetype/freetype_src/gxvalid/gxvcommn.d \
./source/freetype/freetype_src/gxvalid/gxvfeat.d \
./source/freetype/freetype_src/gxvalid/gxvfgen.d \
./source/freetype/freetype_src/gxvalid/gxvjust.d \
./source/freetype/freetype_src/gxvalid/gxvkern.d \
./source/freetype/freetype_src/gxvalid/gxvlcar.d \
./source/freetype/freetype_src/gxvalid/gxvmod.d \
./source/freetype/freetype_src/gxvalid/gxvmort.d \
./source/freetype/freetype_src/gxvalid/gxvmort0.d \
./source/freetype/freetype_src/gxvalid/gxvmort1.d \
./source/freetype/freetype_src/gxvalid/gxvmort2.d \
./source/freetype/freetype_src/gxvalid/gxvmort4.d \
./source/freetype/freetype_src/gxvalid/gxvmort5.d \
./source/freetype/freetype_src/gxvalid/gxvmorx.d \
./source/freetype/freetype_src/gxvalid/gxvmorx0.d \
./source/freetype/freetype_src/gxvalid/gxvmorx1.d \
./source/freetype/freetype_src/gxvalid/gxvmorx2.d \
./source/freetype/freetype_src/gxvalid/gxvmorx4.d \
./source/freetype/freetype_src/gxvalid/gxvmorx5.d \
./source/freetype/freetype_src/gxvalid/gxvopbd.d \
./source/freetype/freetype_src/gxvalid/gxvprop.d \
./source/freetype/freetype_src/gxvalid/gxvtrak.d 

OBJS += \
./source/freetype/freetype_src/gxvalid/gxvalid.o \
./source/freetype/freetype_src/gxvalid/gxvbsln.o \
./source/freetype/freetype_src/gxvalid/gxvcommn.o \
./source/freetype/freetype_src/gxvalid/gxvfeat.o \
./source/freetype/freetype_src/gxvalid/gxvfgen.o \
./source/freetype/freetype_src/gxvalid/gxvjust.o \
./source/freetype/freetype_src/gxvalid/gxvkern.o \
./source/freetype/freetype_src/gxvalid/gxvlcar.o \
./source/freetype/freetype_src/gxvalid/gxvmod.o \
./source/freetype/freetype_src/gxvalid/gxvmort.o \
./source/freetype/freetype_src/gxvalid/gxvmort0.o \
./source/freetype/freetype_src/gxvalid/gxvmort1.o \
./source/freetype/freetype_src/gxvalid/gxvmort2.o \
./source/freetype/freetype_src/gxvalid/gxvmort4.o \
./source/freetype/freetype_src/gxvalid/gxvmort5.o \
./source/freetype/freetype_src/gxvalid/gxvmorx.o \
./source/freetype/freetype_src/gxvalid/gxvmorx0.o \
./source/freetype/freetype_src/gxvalid/gxvmorx1.o \
./source/freetype/freetype_src/gxvalid/gxvmorx2.o \
./source/freetype/freetype_src/gxvalid/gxvmorx4.o \
./source/freetype/freetype_src/gxvalid/gxvmorx5.o \
./source/freetype/freetype_src/gxvalid/gxvopbd.o \
./source/freetype/freetype_src/gxvalid/gxvprop.o \
./source/freetype/freetype_src/gxvalid/gxvtrak.o 


# Each subdirectory must supply rules for building sources it contributes
source/freetype/freetype_src/gxvalid/%.o: ../source/freetype/freetype_src/gxvalid/%.c source/freetype/freetype_src/gxvalid/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DSDK_DELAY_USE_DWT=1 -DFT2_BUILD_LIBRARY=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DCPU_MIMXRT1064DVL6A -DCPU_MIMXRT1064DVL6A_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DUSE_RTOS=0 -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DLWIP_SUPPORT_CUSTOM_PBUF=1 -DCHECKSUM_GEN_UDP=1 -DCHECKSUM_GEN_TCP=1 -DCHECKSUM_GEN_ICMP=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_UDP=1 -DCHECKSUM_CHECK_TCP=1 -DCHECKSUM_CHECK_ICMP=1 -DCHECKSUM_CHECK_ICMP6=1 -D__NEWLIB__ -UPRINTF_ADVANCED_ENABLE=1 -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\device" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\device\periph" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\utilities\debug_console_lite" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\uart" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\drivers" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\utilities\str" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\CMSIS" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\CMSIS\m-profile" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\xip" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\utilities" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\ping" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\tcpecho" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\tcpecho_raw" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\udpecho" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\contrib\apps\udpecho_raw" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\mbedtls\include" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\mbedtls\library" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\usb\host" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\usb\include" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\usb\host\class" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\osa" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\mbedtls\port\ksdk" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\osa\config" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\lists" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\port" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\src" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\src\include" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\src\include\lwip" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\lwip\port\sys_arch\dynamic" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\common" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\sdio" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\host\usdhc" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\incl" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\AzureWave\tx_pwr_limits" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\Murata\tx_pwr_limits" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\wifi_bt_module\u-blox\tx_pwr_limits" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\osa" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\gpio" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\phy" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component\silicon_id" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\component" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\board" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\sdmmc\template\usdhc" -I"C:\Users\AL HAD\Documents\MCUXpressoIDE_25.6.136\work_space\MIMXRT1064_Project_LED\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-freetype-2f-freetype_src-2f-gxvalid

clean-source-2f-freetype-2f-freetype_src-2f-gxvalid:
	-$(RM) ./source/freetype/freetype_src/gxvalid/gxvalid.d ./source/freetype/freetype_src/gxvalid/gxvalid.o ./source/freetype/freetype_src/gxvalid/gxvbsln.d ./source/freetype/freetype_src/gxvalid/gxvbsln.o ./source/freetype/freetype_src/gxvalid/gxvcommn.d ./source/freetype/freetype_src/gxvalid/gxvcommn.o ./source/freetype/freetype_src/gxvalid/gxvfeat.d ./source/freetype/freetype_src/gxvalid/gxvfeat.o ./source/freetype/freetype_src/gxvalid/gxvfgen.d ./source/freetype/freetype_src/gxvalid/gxvfgen.o ./source/freetype/freetype_src/gxvalid/gxvjust.d ./source/freetype/freetype_src/gxvalid/gxvjust.o ./source/freetype/freetype_src/gxvalid/gxvkern.d ./source/freetype/freetype_src/gxvalid/gxvkern.o ./source/freetype/freetype_src/gxvalid/gxvlcar.d ./source/freetype/freetype_src/gxvalid/gxvlcar.o ./source/freetype/freetype_src/gxvalid/gxvmod.d ./source/freetype/freetype_src/gxvalid/gxvmod.o ./source/freetype/freetype_src/gxvalid/gxvmort.d ./source/freetype/freetype_src/gxvalid/gxvmort.o ./source/freetype/freetype_src/gxvalid/gxvmort0.d ./source/freetype/freetype_src/gxvalid/gxvmort0.o ./source/freetype/freetype_src/gxvalid/gxvmort1.d ./source/freetype/freetype_src/gxvalid/gxvmort1.o ./source/freetype/freetype_src/gxvalid/gxvmort2.d ./source/freetype/freetype_src/gxvalid/gxvmort2.o ./source/freetype/freetype_src/gxvalid/gxvmort4.d ./source/freetype/freetype_src/gxvalid/gxvmort4.o ./source/freetype/freetype_src/gxvalid/gxvmort5.d ./source/freetype/freetype_src/gxvalid/gxvmort5.o ./source/freetype/freetype_src/gxvalid/gxvmorx.d ./source/freetype/freetype_src/gxvalid/gxvmorx.o ./source/freetype/freetype_src/gxvalid/gxvmorx0.d ./source/freetype/freetype_src/gxvalid/gxvmorx0.o ./source/freetype/freetype_src/gxvalid/gxvmorx1.d ./source/freetype/freetype_src/gxvalid/gxvmorx1.o ./source/freetype/freetype_src/gxvalid/gxvmorx2.d ./source/freetype/freetype_src/gxvalid/gxvmorx2.o ./source/freetype/freetype_src/gxvalid/gxvmorx4.d ./source/freetype/freetype_src/gxvalid/gxvmorx4.o ./source/freetype/freetype_src/gxvalid/gxvmorx5.d ./source/freetype/freetype_src/gxvalid/gxvmorx5.o ./source/freetype/freetype_src/gxvalid/gxvopbd.d ./source/freetype/freetype_src/gxvalid/gxvopbd.o ./source/freetype/freetype_src/gxvalid/gxvprop.d ./source/freetype/freetype_src/gxvalid/gxvprop.o ./source/freetype/freetype_src/gxvalid/gxvtrak.d ./source/freetype/freetype_src/gxvalid/gxvtrak.o

.PHONY: clean-source-2f-freetype-2f-freetype_src-2f-gxvalid

