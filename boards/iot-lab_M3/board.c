/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; version 2.1 of the License.
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

/**
 * @ingroup     board_iot-lab_M3
 * @{
 *
 * @file        board.c
 * @brief       Board specific implementations for the iot-lab_M3 board
 *
 * @author      Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * @}
 */

#include "cmsis_system.h"
#include "board.h"
#include "cpu.h"


static void leds_init(void);


void board_init(void)
{
    /* initialize core clocks via CMSIS function provided by ST */
    SystemInit();

    /* initialize the CPU */
    cpu_init();

    /* initialize the boards LEDs */
    leds_init();
}

/**
 * @brief Initialize the boards on-board LEDs
 *
 * The LEDs initialization is hard-coded in this function. As the LED is soldered
 * onto the board it is fixed to its CPU pins.
 *
 * The LEDs are connected to the following pin:
 * - Green:     PB5
 * - Orange:    PC10
 * - Red:       PD2
 */
static void leds_init(void)
{
    /* green pin */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIOB->CRL = (0x3 << (5*4));

    /* orange pin */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH = (0x3 << ((10-8)*4));

    /* red pin */
    RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
    GPIOD->CRL = (0x3 << (2*4));
}
