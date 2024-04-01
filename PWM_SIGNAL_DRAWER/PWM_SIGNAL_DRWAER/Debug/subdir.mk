################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GLcd.c \
../Gpio.c \
../Main.c \
../PWM_Signal_img.c \
../icu.c 

OBJS += \
./GLcd.o \
./Gpio.o \
./Main.o \
./PWM_Signal_img.o \
./icu.o 

C_DEPS += \
./GLcd.d \
./Gpio.d \
./Main.d \
./PWM_Signal_img.d \
./icu.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


