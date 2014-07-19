####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../../RIOT 
#### ../../boards   for board definitions (if you have one or more)
#### 

# name of your application
export APPLICATION = openwsn

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD = native
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE = $(CURDIR)/../../../RIOT

# uncomment this to enable scheduler statistics for ps
#CFLAGS += -DSCHEDSTATISTICS

# If you want to use valgrind, you should recompile native with either
# HAVE_VALGRIND_H or HAVE_VALGRIND_VALGRIND_H depending on the location
# of the valgrind header (i.e. <valgrind.h> or <valgrind/valgrind.h>)
# For more information about the valgrind support of RIOT read:
# RIOT/cpu/native/README
#CFLAGS += -DHAVE_VALGRIND_VALGRIND_H
#CFLAGS += -DHAVE_VALGRIND_H

## Modules to include. 

#USEMODULE += config
#USEMODULE += shell
#USEMODULE += shell_commands
#USEMODULE += uart0
#USEMODULE += posix
#USEMODULE += ps
#USEMODULE += auto_init

#USEMODULE += transceiver
ifeq ($(BOARD),msba2)
	USEMODULE += cc110x_ng
else ifeq ($(BOARD),native)
	USEMODULE += nativenet
else ifeq ($(BOARD),telosb)
#	USEMODULE += cc2420
else ifeq ($(BOARD),iot-lab_M3)
	#include Makefile.iot-lab_M3
	#USEMODULE += at86rf231
endif

USEMODULE += openwsn_stack

export INCLUDES += -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTCPU)/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/ -I$(RIOTBASE)/drivers/cc110x_ng/include/ -I$(RIOTBASE)/drivers/cc2420/include/ -I$(RIOTBASE)/drivers/at86rf231/include -I$(RIOTBASE)/sys/net/include -I$(RIOTBASE)/sys/net/openwsn_stack/ -I$(RIOTBASE)/sys/net/openwsn_stack/kernel -I$(RIOTBASE)/sys/net/openwsn_stack/bsp -I$(RIOTBASE)/sys/net/openwsn_stack/bsp/riot

include $(RIOTBASE)/Makefile.include
