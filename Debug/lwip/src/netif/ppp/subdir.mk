################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/netif/ppp/auth.c \
../lwip/src/netif/ppp/ccp.c \
../lwip/src/netif/ppp/chap-md5.c \
../lwip/src/netif/ppp/chap-new.c \
../lwip/src/netif/ppp/chap_ms.c \
../lwip/src/netif/ppp/demand.c \
../lwip/src/netif/ppp/eap.c \
../lwip/src/netif/ppp/ecp.c \
../lwip/src/netif/ppp/eui64.c \
../lwip/src/netif/ppp/fsm.c \
../lwip/src/netif/ppp/ipcp.c \
../lwip/src/netif/ppp/ipv6cp.c \
../lwip/src/netif/ppp/lcp.c \
../lwip/src/netif/ppp/magic.c \
../lwip/src/netif/ppp/mppe.c \
../lwip/src/netif/ppp/multilink.c \
../lwip/src/netif/ppp/ppp.c \
../lwip/src/netif/ppp/pppapi.c \
../lwip/src/netif/ppp/pppcrypt.c \
../lwip/src/netif/ppp/pppoe.c \
../lwip/src/netif/ppp/pppol2tp.c \
../lwip/src/netif/ppp/pppos.c \
../lwip/src/netif/ppp/upap.c \
../lwip/src/netif/ppp/utils.c \
../lwip/src/netif/ppp/vj.c 

C_DEPS += \
./lwip/src/netif/ppp/auth.d \
./lwip/src/netif/ppp/ccp.d \
./lwip/src/netif/ppp/chap-md5.d \
./lwip/src/netif/ppp/chap-new.d \
./lwip/src/netif/ppp/chap_ms.d \
./lwip/src/netif/ppp/demand.d \
./lwip/src/netif/ppp/eap.d \
./lwip/src/netif/ppp/ecp.d \
./lwip/src/netif/ppp/eui64.d \
./lwip/src/netif/ppp/fsm.d \
./lwip/src/netif/ppp/ipcp.d \
./lwip/src/netif/ppp/ipv6cp.d \
./lwip/src/netif/ppp/lcp.d \
./lwip/src/netif/ppp/magic.d \
./lwip/src/netif/ppp/mppe.d \
./lwip/src/netif/ppp/multilink.d \
./lwip/src/netif/ppp/ppp.d \
./lwip/src/netif/ppp/pppapi.d \
./lwip/src/netif/ppp/pppcrypt.d \
./lwip/src/netif/ppp/pppoe.d \
./lwip/src/netif/ppp/pppol2tp.d \
./lwip/src/netif/ppp/pppos.d \
./lwip/src/netif/ppp/upap.d \
./lwip/src/netif/ppp/utils.d \
./lwip/src/netif/ppp/vj.d 

OBJS += \
./lwip/src/netif/ppp/auth.o \
./lwip/src/netif/ppp/ccp.o \
./lwip/src/netif/ppp/chap-md5.o \
./lwip/src/netif/ppp/chap-new.o \
./lwip/src/netif/ppp/chap_ms.o \
./lwip/src/netif/ppp/demand.o \
./lwip/src/netif/ppp/eap.o \
./lwip/src/netif/ppp/ecp.o \
./lwip/src/netif/ppp/eui64.o \
./lwip/src/netif/ppp/fsm.o \
./lwip/src/netif/ppp/ipcp.o \
./lwip/src/netif/ppp/ipv6cp.o \
./lwip/src/netif/ppp/lcp.o \
./lwip/src/netif/ppp/magic.o \
./lwip/src/netif/ppp/mppe.o \
./lwip/src/netif/ppp/multilink.o \
./lwip/src/netif/ppp/ppp.o \
./lwip/src/netif/ppp/pppapi.o \
./lwip/src/netif/ppp/pppcrypt.o \
./lwip/src/netif/ppp/pppoe.o \
./lwip/src/netif/ppp/pppol2tp.o \
./lwip/src/netif/ppp/pppos.o \
./lwip/src/netif/ppp/upap.o \
./lwip/src/netif/ppp/utils.o \
./lwip/src/netif/ppp/vj.o 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/netif/ppp/%.o: ../lwip/src/netif/ppp/%.c lwip/src/netif/ppp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DSDK_DELAY_USE_DWT=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DCPU_MIMXRT1064DVL6A -DCPU_MIMXRT1064DVL6A_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DUSE_RTOS=0 -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DLWIP_SUPPORT_CUSTOM_PBUF=1 -DCHECKSUM_GEN_UDP=1 -DCHECKSUM_GEN_TCP=1 -DCHECKSUM_GEN_ICMP=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_UDP=1 -DCHECKSUM_CHECK_TCP=1 -DCHECKSUM_CHECK_ICMP=1 -DCHECKSUM_CHECK_ICMP6=1 -D__NEWLIB__ -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/device" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/device/periph" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities/debug_console_lite" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/uart" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/drivers" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities/str" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/CMSIS" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/CMSIS/m-profile" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/xip" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/ping" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lvgl" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lvgl/src" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/tcpecho" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/tcpecho_raw" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/udpecho" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/udpecho_raw" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/host" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/include" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/host/class" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/osa" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/osa/config" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/lists" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/port" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src/include" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src/include/lwip" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/port/sys_arch/dynamic" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/gpio" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/phy" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/silicon_id" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/phy" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/board" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source/config/host/ehci" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source/application/DisplayController" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/wifi_bt_module/Murata/tx_pwr_limits" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lwip-2f-src-2f-netif-2f-ppp

clean-lwip-2f-src-2f-netif-2f-ppp:
	-$(RM) ./lwip/src/netif/ppp/auth.d ./lwip/src/netif/ppp/auth.o ./lwip/src/netif/ppp/ccp.d ./lwip/src/netif/ppp/ccp.o ./lwip/src/netif/ppp/chap-md5.d ./lwip/src/netif/ppp/chap-md5.o ./lwip/src/netif/ppp/chap-new.d ./lwip/src/netif/ppp/chap-new.o ./lwip/src/netif/ppp/chap_ms.d ./lwip/src/netif/ppp/chap_ms.o ./lwip/src/netif/ppp/demand.d ./lwip/src/netif/ppp/demand.o ./lwip/src/netif/ppp/eap.d ./lwip/src/netif/ppp/eap.o ./lwip/src/netif/ppp/ecp.d ./lwip/src/netif/ppp/ecp.o ./lwip/src/netif/ppp/eui64.d ./lwip/src/netif/ppp/eui64.o ./lwip/src/netif/ppp/fsm.d ./lwip/src/netif/ppp/fsm.o ./lwip/src/netif/ppp/ipcp.d ./lwip/src/netif/ppp/ipcp.o ./lwip/src/netif/ppp/ipv6cp.d ./lwip/src/netif/ppp/ipv6cp.o ./lwip/src/netif/ppp/lcp.d ./lwip/src/netif/ppp/lcp.o ./lwip/src/netif/ppp/magic.d ./lwip/src/netif/ppp/magic.o ./lwip/src/netif/ppp/mppe.d ./lwip/src/netif/ppp/mppe.o ./lwip/src/netif/ppp/multilink.d ./lwip/src/netif/ppp/multilink.o ./lwip/src/netif/ppp/ppp.d ./lwip/src/netif/ppp/ppp.o ./lwip/src/netif/ppp/pppapi.d ./lwip/src/netif/ppp/pppapi.o ./lwip/src/netif/ppp/pppcrypt.d ./lwip/src/netif/ppp/pppcrypt.o ./lwip/src/netif/ppp/pppoe.d ./lwip/src/netif/ppp/pppoe.o ./lwip/src/netif/ppp/pppol2tp.d ./lwip/src/netif/ppp/pppol2tp.o ./lwip/src/netif/ppp/pppos.d ./lwip/src/netif/ppp/pppos.o ./lwip/src/netif/ppp/upap.d ./lwip/src/netif/ppp/upap.o ./lwip/src/netif/ppp/utils.d ./lwip/src/netif/ppp/utils.o ./lwip/src/netif/ppp/vj.d ./lwip/src/netif/ppp/vj.o

.PHONY: clean-lwip-2f-src-2f-netif-2f-ppp

