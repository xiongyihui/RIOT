/**
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 *
 * @file   at86rf231_spi1.c
 * @author Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 */

#include <stdio.h>
#include <stddef.h>

#include "cpu.h"
#include "periph/gpio.h"
#include "spi.h"
#include "periph_conf.h"
#include "at86rf231_spi1.h"

/*
SPI1
  SCLK : PA5
  MISO : PA6
  MOSI : PA7
  CS : PA4

GPIO
  IRQ0 : PC4 : Frame buff empty indicator
  DIG2 : ? : RX Frame Time stamping XXX : NOT USED
  Reset : PC1 : active low, enable chip
  SLEEP : PA2 : control sleep, tx & rx state
*/


void at86rf231_spi1_init(void)
{
    spi_init_master(SPI_0, SPI_CONF_FIRST_RISING, 4500000);
}

uint8_t at86rf231_spi_transfer_byte(uint8_t byte)
{
    char ret;
    spi_transfer_byte(SPI_0, byte, &ret);
    return ret;
}

void at86rf231_spi_transfer(const uint8_t *data_out, uint8_t *data_in, uint16_t length)
{
    spi_transfer_bytes(SPI_0, (char*)data_out, (char*)data_in, length);
}
