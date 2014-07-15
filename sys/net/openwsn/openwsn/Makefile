MODULE = openwsn_stack

INCLUDES += -I$(RIOTBASE) -I$(RIOTBASE)/sys/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/drivers/include -I$(RIOTBASE)/drivers/cc110x_ng/include -I$(RIOTBASE)/cpu/arm_common/include -I$(RIOTBASE)/cpu/msp430-common/include -I$(RIOTBASE)/sys/net/include/

INCLUDES += -I$(CURDIR)
INCLUDES += -I$(CURDIR)/02a-MAClow
INCLUDES += -I$(CURDIR)/02b-MAChigh
INCLUDES += -I$(CURDIR)/03a-IPHC
INCLUDES += -I$(CURDIR)/03b-IPv6
INCLUDES += -I$(CURDIR)/04-TRAN
INCLUDES += -I$(CURDIR)/cross-layers
INCLUDES += -I$(CURDIR)/07-App/rinfo
INCLUDES += -I$(CURDIR)/07-App/rwellknown
INCLUDES += -I$(CURDIR)/07-App/ohlone
INCLUDES += -I$(CURDIR)/07-App/tcpecho
INCLUDES += -I$(CURDIR)/07-App/tcpinject
INCLUDES += -I$(CURDIR)/07-App/tcpprint
INCLUDES += -I$(CURDIR)/07-App/udpecho
INCLUDES += -I$(CURDIR)/07-App/udpinject
INCLUDES += -I$(CURDIR)/07-App/udplatency
INCLUDES += -I$(CURDIR)/07-App/udpprint
INCLUDES += -I$(CURDIR)/07-App/udprand
INCLUDES += -I$(CURDIR)/07-App/udpstorm


DIRS =
DIRS += cross-layers
DIRS += 02a-MAClow
DIRS += 02b-MAChigh
DIRS += 03a-IPHC
DIRS += 03b-IPv6
DIRS += 04-TRAN
DIRS += 07-App

include $(RIOTBASE)/Makefile.base
