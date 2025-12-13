################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/core/altcp.c \
../lwip/src/core/altcp_alloc.c \
../lwip/src/core/altcp_tcp.c \
../lwip/src/core/def.c \
../lwip/src/core/dns.c \
../lwip/src/core/inet_chksum.c \
../lwip/src/core/init.c \
../lwip/src/core/ip.c \
../lwip/src/core/mem.c \
../lwip/src/core/memp.c \
../lwip/src/core/netif.c \
../lwip/src/core/pbuf.c \
../lwip/src/core/raw.c \
../lwip/src/core/stats.c \
../lwip/src/core/sys.c \
../lwip/src/core/tcp.c \
../lwip/src/core/tcp_in.c \
../lwip/src/core/tcp_out.c \
../lwip/src/core/timeouts.c \
../lwip/src/core/udp.c 

C_DEPS += \
./lwip/src/core/altcp.d \
./lwip/src/core/altcp_alloc.d \
./lwip/src/core/altcp_tcp.d \
./lwip/src/core/def.d \
./lwip/src/core/dns.d \
./lwip/src/core/inet_chksum.d \
./lwip/src/core/init.d \
./lwip/src/core/ip.d \
./lwip/src/core/mem.d \
./lwip/src/core/memp.d \
./lwip/src/core/netif.d \
./lwip/src/core/pbuf.d \
./lwip/src/core/raw.d \
./lwip/src/core/stats.d \
./lwip/src/core/sys.d \
./lwip/src/core/tcp.d \
./lwip/src/core/tcp_in.d \
./lwip/src/core/tcp_out.d \
./lwip/src/core/timeouts.d \
./lwip/src/core/udp.d 

OBJS += \
./lwip/src/core/altcp.o \
./lwip/src/core/altcp_alloc.o \
./lwip/src/core/altcp_tcp.o \
./lwip/src/core/def.o \
./lwip/src/core/dns.o \
./lwip/src/core/inet_chksum.o \
./lwip/src/core/init.o \
./lwip/src/core/ip.o \
./lwip/src/core/mem.o \
./lwip/src/core/memp.o \
./lwip/src/core/netif.o \
./lwip/src/core/pbuf.o \
./lwip/src/core/raw.o \
./lwip/src/core/stats.o \
./lwip/src/core/sys.o \
./lwip/src/core/tcp.o \
./lwip/src/core/tcp_in.o \
./lwip/src/core/tcp_out.o \
./lwip/src/core/timeouts.o \
./lwip/src/core/udp.o 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/core/%.o: ../lwip/src/core/%.c lwip/src/core/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DSDK_DELAY_USE_DWT=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DCPU_MIMXRT1064DVL6A -DCPU_MIMXRT1064DVL6A_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DUSE_RTOS=0 -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DLWIP_SUPPORT_CUSTOM_PBUF=1 -DCHECKSUM_GEN_UDP=1 -DCHECKSUM_GEN_TCP=1 -DCHECKSUM_GEN_ICMP=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_UDP=1 -DCHECKSUM_CHECK_TCP=1 -DCHECKSUM_CHECK_ICMP=1 -DCHECKSUM_CHECK_ICMP6=1 -D__NEWLIB__ -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/device" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/device/periph" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities/debug_console_lite" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/uart" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/drivers" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities/str" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/CMSIS" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/CMSIS/m-profile" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/xip" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/ping" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lvgl" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lvgl/src" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/tcpecho" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/tcpecho_raw" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/udpecho" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/udpecho_raw" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/host" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/include" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/host/class" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/osa" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/osa/config" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/lists" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/port" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src/include" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src/include/lwip" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/port/sys_arch/dynamic" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/gpio" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/phy" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/silicon_id" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/phy" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/board" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source/config/host/ehci" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source/application/DisplayController" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/wifi_bt_module/Murata/tx_pwr_limits" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lwip-2f-src-2f-core

clean-lwip-2f-src-2f-core:
	-$(RM) ./lwip/src/core/altcp.d ./lwip/src/core/altcp.o ./lwip/src/core/altcp_alloc.d ./lwip/src/core/altcp_alloc.o ./lwip/src/core/altcp_tcp.d ./lwip/src/core/altcp_tcp.o ./lwip/src/core/def.d ./lwip/src/core/def.o ./lwip/src/core/dns.d ./lwip/src/core/dns.o ./lwip/src/core/inet_chksum.d ./lwip/src/core/inet_chksum.o ./lwip/src/core/init.d ./lwip/src/core/init.o ./lwip/src/core/ip.d ./lwip/src/core/ip.o ./lwip/src/core/mem.d ./lwip/src/core/mem.o ./lwip/src/core/memp.d ./lwip/src/core/memp.o ./lwip/src/core/netif.d ./lwip/src/core/netif.o ./lwip/src/core/pbuf.d ./lwip/src/core/pbuf.o ./lwip/src/core/raw.d ./lwip/src/core/raw.o ./lwip/src/core/stats.d ./lwip/src/core/stats.o ./lwip/src/core/sys.d ./lwip/src/core/sys.o ./lwip/src/core/tcp.d ./lwip/src/core/tcp.o ./lwip/src/core/tcp_in.d ./lwip/src/core/tcp_in.o ./lwip/src/core/tcp_out.d ./lwip/src/core/tcp_out.o ./lwip/src/core/timeouts.d ./lwip/src/core/timeouts.o ./lwip/src/core/udp.d ./lwip/src/core/udp.o

.PHONY: clean-lwip-2f-src-2f-core

