/*
 * Copyright (C) 2014 Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; version 2.1 of the License, or (at your option) any
 * later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "stm32f10x.h"
#include "spi.h"
#include "periph_conf.h"

int spi_init_master(spi_t dev, spi_conf_t conf, uint32_t speed)
{
    SPI_TypeDef *SPIx;

    switch(dev) {
#ifdef SPI_0_EN
        case SPI_0:
            SPIx = SPI_0_DEV;
            SPI_0_CLKEN();
#endif
        case SPI_UNDEFINED:
        default:
            return -1;
    }

    uint16_t tmp = SPIx->CR1;
    tmp &= 0x3040;  /* reset value */

    tmp |= 0x0000;  /* SPI 2 lines full duplex */
    tmp |= 0x0104;  /* SPI master mode */
    tmp |= 0x0000;  /* Data size 8b */
    tmp |= 0x0000;  /* CPOL low */
    tmp |= 0x0000;  /* CPHA 1 edge */
    tmp |= 0x0200;  /* NSS soft */
    tmp |= 0x0018;  /* BR prescaler 16 */
    tmp |= 0x0000;  /* 1st Bit MSB */

    SPIx->CR1 = tmp;
    SPIx->I2SCFGR &= 0xF7FF;     /* select SPI mode */

    SPIx->CRCPR = 0x7;           /* reset CRC polynomial */

    return 0;
}

int spi_init_slave(spi_t dev, spi_conf_t conf, char (*cb)(char))
{
    /* TODO */
    return 0;
}

int spi_transfer_byte(spi_t dev, char out, char *in)
{
    SPI_TypeDef *SPI_dev;
    int transfered = 0;

    switch(dev) {
#ifdef SPI_0_EN
        case SPI_0:
            SPI_dev = SPI_0_DEV;
#endif
        case SPI_UNDEFINED:
        default:
            return -1;
    }

    if (out != 0) {
        /* wait for empty tx buffer */
        while ((SPI_dev->SR & 0x2) == 0);
        /* write out data to buffer */
        SPI_dev->DR = out;
        /* increase transfered bytes counter */
        transfered++;
    }

    if (in != 0) {
        /* wait for not empty rx buffer */
        while ((SPI_dev->SR & 0x1) == 0);
        /* read out data to in buffer */
        *in = SPI_dev->DR;
        /* increase transfered bytes counter */
        transfered++;
    }

    while ((SPI_dev->SR & 0x80) == SET);

    return transfered;
}

int spi_transfer_bytes(spi_t dev, char *out, char *in, int length)
{
    int transfered = 0;
    int ret = 0;

    if (out != 0) {
        while (length--) {
            ret += spi_transfer_byte(dev, *(out)++, 0);
            if (ret <  0) {
                return ret;
            }
            transfered += ret;
        }
    }
    if (in != 0) {
        while (length--) {
            ret += spi_transfer_byte(dev, 0, in++);
            if (ret <  0) {
                return ret;
            }
            transfered += ret;
        }
    }

    return transfered;
}

int spi_transfer_reg(spi_t dev, uint8_t reg, char *out, char *in)
{
    return -1;
}

int spi_transfer_regs(spi_t dev, uint8_t reg, char *out, char *in, int length)
{
    return -1;
}

int spi_poweron(spi_t dev)
{
    SPI_TypeDef *SPIx;

    switch(dev) {
#ifdef SPI_0_EN
        case SPI_0:
            SPIx = SPI_0_DEV;
#endif
        case SPI_UNDEFINED:
        default:
            return -1;
    }

    SPIx->CR1 |= 0x0001;
}

int spi_poweroff(spi_t dev)
{
    SPI_TypeDef *SPIx;

    switch(dev) {
#ifdef SPI_0_EN
        case SPI_0:
            SPIx = SPI_0_DEV;
#endif
        case SPI_UNDEFINED:
        default:
            return -1;
    }

    SPIx->CR1 &= ~(0x0001);
}
