################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/core/lv_group.c \
../lvgl/src/core/lv_obj.c \
../lvgl/src/core/lv_obj_class.c \
../lvgl/src/core/lv_obj_draw.c \
../lvgl/src/core/lv_obj_event.c \
../lvgl/src/core/lv_obj_id_builtin.c \
../lvgl/src/core/lv_obj_pos.c \
../lvgl/src/core/lv_obj_property.c \
../lvgl/src/core/lv_obj_scroll.c \
../lvgl/src/core/lv_obj_style.c \
../lvgl/src/core/lv_obj_style_gen.c \
../lvgl/src/core/lv_obj_tree.c \
../lvgl/src/core/lv_refr.c 

C_DEPS += \
./lvgl/src/core/lv_group.d \
./lvgl/src/core/lv_obj.d \
./lvgl/src/core/lv_obj_class.d \
./lvgl/src/core/lv_obj_draw.d \
./lvgl/src/core/lv_obj_event.d \
./lvgl/src/core/lv_obj_id_builtin.d \
./lvgl/src/core/lv_obj_pos.d \
./lvgl/src/core/lv_obj_property.d \
./lvgl/src/core/lv_obj_scroll.d \
./lvgl/src/core/lv_obj_style.d \
./lvgl/src/core/lv_obj_style_gen.d \
./lvgl/src/core/lv_obj_tree.d \
./lvgl/src/core/lv_refr.d 

OBJS += \
./lvgl/src/core/lv_group.o \
./lvgl/src/core/lv_obj.o \
./lvgl/src/core/lv_obj_class.o \
./lvgl/src/core/lv_obj_draw.o \
./lvgl/src/core/lv_obj_event.o \
./lvgl/src/core/lv_obj_id_builtin.o \
./lvgl/src/core/lv_obj_pos.o \
./lvgl/src/core/lv_obj_property.o \
./lvgl/src/core/lv_obj_scroll.o \
./lvgl/src/core/lv_obj_style.o \
./lvgl/src/core/lv_obj_style_gen.o \
./lvgl/src/core/lv_obj_tree.o \
./lvgl/src/core/lv_refr.o 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/core/%.o: ../lvgl/src/core/%.c lvgl/src/core/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DSDK_DELAY_USE_DWT=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DCPU_MIMXRT1064DVL6A -DCPU_MIMXRT1064DVL6A_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DUSE_RTOS=0 -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DLWIP_SUPPORT_CUSTOM_PBUF=1 -DCHECKSUM_GEN_UDP=1 -DCHECKSUM_GEN_TCP=1 -DCHECKSUM_GEN_ICMP=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_UDP=1 -DCHECKSUM_CHECK_TCP=1 -DCHECKSUM_CHECK_ICMP=1 -DCHECKSUM_CHECK_ICMP6=1 -D__NEWLIB__ -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/device" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/device/periph" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities/debug_console_lite" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/uart" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/drivers" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities/str" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/CMSIS" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/CMSIS/m-profile" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/xip" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/utilities" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/ping" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lvgl" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lvgl/src" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/tcpecho" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/tcpecho_raw" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/udpecho" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/contrib/apps/udpecho_raw" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/host" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/include" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/host/class" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/osa" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/osa/config" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/lists" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/port" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src/include" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/src/include/lwip" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/lwip/port/sys_arch/dynamic" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/gpio" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/phy" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/silicon_id" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/usb/phy" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/board" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source/config/host/ehci" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source/application/DisplayController" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/component/wifi_bt_module/Murata/tx_pwr_limits" -I"/Users/harishankar/Documents/MCUXpressoIDE_25.6.136/MIMXRT1064_Project_LED/source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lvgl-2f-src-2f-core

clean-lvgl-2f-src-2f-core:
	-$(RM) ./lvgl/src/core/lv_group.d ./lvgl/src/core/lv_group.o ./lvgl/src/core/lv_obj.d ./lvgl/src/core/lv_obj.o ./lvgl/src/core/lv_obj_class.d ./lvgl/src/core/lv_obj_class.o ./lvgl/src/core/lv_obj_draw.d ./lvgl/src/core/lv_obj_draw.o ./lvgl/src/core/lv_obj_event.d ./lvgl/src/core/lv_obj_event.o ./lvgl/src/core/lv_obj_id_builtin.d ./lvgl/src/core/lv_obj_id_builtin.o ./lvgl/src/core/lv_obj_pos.d ./lvgl/src/core/lv_obj_pos.o ./lvgl/src/core/lv_obj_property.d ./lvgl/src/core/lv_obj_property.o ./lvgl/src/core/lv_obj_scroll.d ./lvgl/src/core/lv_obj_scroll.o ./lvgl/src/core/lv_obj_style.d ./lvgl/src/core/lv_obj_style.o ./lvgl/src/core/lv_obj_style_gen.d ./lvgl/src/core/lv_obj_style_gen.o ./lvgl/src/core/lv_obj_tree.d ./lvgl/src/core/lv_obj_tree.o ./lvgl/src/core/lv_refr.d ./lvgl/src/core/lv_refr.o

.PHONY: clean-lvgl-2f-src-2f-core

