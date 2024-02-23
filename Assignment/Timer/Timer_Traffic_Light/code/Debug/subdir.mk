################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_prog.c \
../EXTI_prog.c \
../GIE_prog.c \
../LED_prog.c \
../PORT_prog.c \
../SWITCH_prog.c \
../TIMER_prog.c \
../main.c 

OBJS += \
./DIO_prog.o \
./EXTI_prog.o \
./GIE_prog.o \
./LED_prog.o \
./PORT_prog.o \
./SWITCH_prog.o \
./TIMER_prog.o \
./main.o 

C_DEPS += \
./DIO_prog.d \
./EXTI_prog.d \
./GIE_prog.d \
./LED_prog.d \
./PORT_prog.d \
./SWITCH_prog.d \
./TIMER_prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


