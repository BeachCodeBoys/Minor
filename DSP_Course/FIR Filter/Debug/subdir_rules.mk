################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
PLL.obj: ../PLL.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --include_path="/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/include" --define=c5505 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="PLL.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

aic3204.obj: ../aic3204.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --include_path="/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/include" --define=c5505 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="aic3204.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

aic3204_init.obj: ../aic3204_init.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --include_path="/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/include" --define=c5505 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="aic3204_init.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

hhs_setup_0.obj: ../hhs_setup_0.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --include_path="/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/include" --define=c5505 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="hhs_setup_0.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --include_path="/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/include" --define=c5505 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

stereo.obj: ../stereo.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --include_path="/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/include" --define=c5505 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="stereo.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

usbstk5505.obj: ../usbstk5505.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --include_path="/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/include" --define=c5505 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="usbstk5505.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

usbstk5505_gpio.obj: ../usbstk5505_gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --include_path="/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/include" --define=c5505 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="usbstk5505_gpio.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

usbstk5505_i2c.obj: ../usbstk5505_i2c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --include_path="/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/include" --define=c5505 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="usbstk5505_i2c.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

usbstk5505_led.obj: ../usbstk5505_led.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -g --include_path="/home/user/bin/ticcs/ccsv7/tools/compiler/c5500_4.4.1/include" --define=c5505 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="usbstk5505_led.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


