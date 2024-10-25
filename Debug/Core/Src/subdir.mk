################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/blink_control.c \
../Core/Src/debouncer.c \
../Core/Src/edge_detector.c \
../Core/Src/fsm.c \
../Core/Src/main.c \
../Core/Src/modulo_semaforo.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/timer.c \
../Core/Src/timer_period_manager.c 

OBJS += \
./Core/Src/blink_control.o \
./Core/Src/debouncer.o \
./Core/Src/edge_detector.o \
./Core/Src/fsm.o \
./Core/Src/main.o \
./Core/Src/modulo_semaforo.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/timer.o \
./Core/Src/timer_period_manager.o 

C_DEPS += \
./Core/Src/blink_control.d \
./Core/Src/debouncer.d \
./Core/Src/edge_detector.d \
./Core/Src/fsm.d \
./Core/Src/main.d \
./Core/Src/modulo_semaforo.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/timer.d \
./Core/Src/timer_period_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/blink_control.cyclo ./Core/Src/blink_control.d ./Core/Src/blink_control.o ./Core/Src/blink_control.su ./Core/Src/debouncer.cyclo ./Core/Src/debouncer.d ./Core/Src/debouncer.o ./Core/Src/debouncer.su ./Core/Src/edge_detector.cyclo ./Core/Src/edge_detector.d ./Core/Src/edge_detector.o ./Core/Src/edge_detector.su ./Core/Src/fsm.cyclo ./Core/Src/fsm.d ./Core/Src/fsm.o ./Core/Src/fsm.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/modulo_semaforo.cyclo ./Core/Src/modulo_semaforo.d ./Core/Src/modulo_semaforo.o ./Core/Src/modulo_semaforo.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/timer.cyclo ./Core/Src/timer.d ./Core/Src/timer.o ./Core/Src/timer.su ./Core/Src/timer_period_manager.cyclo ./Core/Src/timer_period_manager.d ./Core/Src/timer_period_manager.o ./Core/Src/timer_period_manager.su

.PHONY: clean-Core-2f-Src

