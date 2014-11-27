/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     cpu_nrf51822
 * @{
 *
 * @file        lpm_arch.c
 * @brief       Implementation of the kernels power management interface
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include "arch/lpm_arch.h"
#include "cpu.h"
#include "debug.h"

void lpm_arch_init(void)
{
}

enum lpm_mode lpm_arch_set(enum lpm_mode target)
{
    switch (target)
    {
    case LPM_ON:
        break;
    case LPM_IDLE:
    case LPM_SLEEP:
        // Enter System ON sleep mode
        __WFE();
        // Make sure any pending events are cleared
        __SEV();
        __WFE();
        break;
    case LPM_POWERDOWN:
    case LPM_OFF:

        break;
    default:
        DEBUG("ERROR: trying to set an invalid low-power mode!\n");
        DEBUG("       Operation aborted.\n\n");
    }

    return LPM_ON;
}

enum lpm_mode lpm_arch_get(void)
{
    return LPM_ON;
}

void lpm_arch_awake(void)
{
}

void lpm_arch_begin_awake(void)
{
}

void lpm_arch_end_awake(void)
{
}
