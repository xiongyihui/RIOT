MODULE =$(shell basename $(CURDIR))

INCLUDES += -I$(RIOTBASE) -I$(RIOTBASE)/sys/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/drivers/include -I$(RIOTBASE)/drivers/cc110x_ng/include -I$(RIOTBASE)/cpu/arm_common/include -I$(RIOTBASE)/sys/net/include/
INCLUDES += -I$(CURDIR)/02a-MAClow
INCLUDES += -I$(CURDIR)/02b-MAChigh
INCLUDES += -I$(CURDIR)/03a-IPHC
INCLUDES += -I$(CURDIR)/03b-IPv6
INCLUDES += -I$(CURDIR)/04-TRAN
INCLUDES += -I$(CURDIR)/cross-layers

include $(RIOTBASE)/Makefile.base
