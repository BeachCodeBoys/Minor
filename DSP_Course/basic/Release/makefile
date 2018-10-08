################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/user/bin/ticcs/ccsv6/tools/compiler/c5500_4.4.1

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./PLL.obj" \
"./aic3204.obj" \
"./aic3204_init.obj" \
"./hhs_setup_0.obj" \
"./main.obj" \
"./stereo.obj" \
"./usbstk5505.obj" \
"./usbstk5505_gpio.obj" \
"./usbstk5505_i2c.obj" \
"./usbstk5505_led.obj" \
"../55xdsph.lib" \
"../CSLc55x5h.lib" \
"../lnkx.cmd" \
$(GEN_CMDS__FLAG) \
-lrts55h.lib \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
project_0.out \

EXE_OUTPUTS__QUOTED += \
"project_0.out" \

BIN_OUTPUTS += \
project_0.hex \

BIN_OUTPUTS__QUOTED += \
"project_0.hex" \


# All Target
all: project_0.out

# Tool invocations
project_0.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C5500 Linker'
	"/home/user/bin/ticcs/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=huge -O2 --define=vc5505 --display_error_number --diag_warning=225 --ptrdiff_size=32 -z -m"project_0.map" --stack_size=0x200 --heap_size=0x400 -i"/home/user/bin/ticcs/ccsv6/tools/compiler/c5500_4.4.1/lib" -i"/home/user/bin/ticcs/ccsv6/tools/compiler/c5500_4.4.1/include" --reread_libs --display_error_number --warn_sections --xml_link_info="project_0_linkInfo.xml" --rom_model --sys_stacksize=0x200 -o "project_0.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

project_0.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C5500 Hex Utility'
	"/home/user/bin/ticcs/ccsv6/tools/compiler/c5500_4.4.1/bin/hex55"  -o "project_0.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "PLL.d" "aic3204.d" "aic3204_init.d" "hhs_setup_0.d" "main.d" "stereo.d" "usbstk5505.d" "usbstk5505_gpio.d" "usbstk5505_i2c.d" "usbstk5505_led.d" 
	-$(RM) "PLL.obj" "aic3204.obj" "aic3204_init.obj" "hhs_setup_0.obj" "main.obj" "stereo.obj" "usbstk5505.obj" "usbstk5505_gpio.obj" "usbstk5505_i2c.obj" "usbstk5505_led.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

