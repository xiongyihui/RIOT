#!/bin/sh

# This flash script dynamically generates a file with a set of commands which
# have to be handed to the flashing script of SEGGER (JLinkExe >4.84).
# After that, JLinkExe will be executed with that set of commands to flash the
# latest .bin file to the board.

# @author Timo Ziegler <timo.ziegler@fu-berlin.de>
# @author Hauke Petersen <hauke.petersen@fu-berlin.de>

BINDIR=$1
HEXFILE=$2

cp $2 /media/$USER/MBED
