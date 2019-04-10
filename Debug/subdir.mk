################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../._main.c \
../LWIPServer.c \
../adc.c \
../gpio.c \
../main.c \
../pwm.c \
../wifi.c \
../wifiClient.c 

OBJS += \
./._main.o \
./LWIPServer.o \
./adc.o \
./gpio.o \
./main.o \
./pwm.o \
./wifi.o \
./wifiClient.o 

C_DEPS += \
./._main.d \
./LWIPServer.d \
./adc.d \
./gpio.d \
./main.d \
./pwm.d \
./wifi.d \
./wifiClient.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARTIK GCC C Compiler'
	arm-none-eabi-gcc  -D__TINYARA__ -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/include -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/include/apps -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/framework_include -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/apps_include -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/apps_include/netutils -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/artik-sdk_include -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/artik-sdk_include/base -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/artik-sdk_include/connectivity -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/artik-sdk_include/systemio -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/artik-sdk_include/wifi -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/artik-sdk_include/lwm2m -IC:/ARTIK/SDK/A05x/v1.7.1/libsdk/A053/extra/artik-sdk_include/mqtt -O0 -ffunction-sections -fdata-sections -fno-builtin -fno-strict-aliasing -fno-strength-reduce -fomit-frame-pointer -Wstrict-prototypes -Wshadow -Wno-implicit-function-declaration -Wno-unused-function -Wno-unused-but-set-variable -DAPP_STACKSIZE=18432 -DAPP_PRIORITY=100 -g -DCONFIG_ARTIK_IDE_INTERGRATE -mcpu=cortex-r4 -mfpu=vfpv3 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


