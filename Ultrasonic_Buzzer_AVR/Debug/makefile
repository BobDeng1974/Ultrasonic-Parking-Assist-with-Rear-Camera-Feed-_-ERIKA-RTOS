### Setting Erika's variables:
# ERIKA_FILES= ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1278



############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += __ARDUINO_SDK__
EEOPT += __ARDUINO_UNO_328__
EEOPT += __ADD_LIBS__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_LINUX__
EEOPT += __ATMEGA__
EEOPT += __AVR8__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __DISABLE_EEOPT_DEFINES__


############################################################################
#
# Erika base directory
#
############################################################################
ifdef ERIKA_FILES
ifdef EEBASE
    $(warning EEBASE is set, but it has been overridden by ERIKA_FILES)
endif
EEBASE := ${ERIKA_FILES}

else # ERIKA_FILES

ifndef EEBASE
        EEBASE := /home/evidence/Erika_SVN/
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=
$(info Using erika files in $(EEBASE))


############################################################################
#
# AVR8 (atmega328p)
#
############################################################################
-include $(EEBASE)/pkg/cfg/path_helper.mk
APPBASE := ..
OUTBASE := Debug

AVR8_MCU := atmega328p

$(eval $(call check_and_set_linux_compiler_path,AVR_TOOLS,))


############################################################################
#
# Flags
#
############################################################################
CFLAGS  += 
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 

LIB_OPT  += __LIB_ARDUINO_SDK__


############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c code.cpp task.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
