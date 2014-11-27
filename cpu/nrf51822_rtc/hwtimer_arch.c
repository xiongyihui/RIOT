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
 * @file        hwtimer_arch.c
 * @brief       Implementation of the kernels hwtimer interface
 *
 * The hardware timer implementation uses a direct mapping to the low-level UART driver.
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include "arch/hwtimer_arch.h"
#include "board.h"
#include "thread.h"
#include "nrf51.h"


/**
 * Assign the rtc for  hwtimer
 */
#define RTC4HWTIMER_DEV      NRF_RTC1
#define RTC4HWTIMER_IRQ      RTC1_IRQn
#define RTC4HWTIMER_IRQ_PRIO 1
#define RTC4HWTIMER_ISR      isr_rtc1
#define RTC4HWTIMER_COMPARE_NUMOF   4
#define RTC4HWTIMER_MAX_VALUE       0xFFFFFF


static void (*timeout_handler)(int);

void hwtimer_arch_init(void (*handler)(int), uint32_t fcpu)
{
    timeout_handler = handler;

    /* configure interrupt */
    NVIC_SetPriority(RTC4HWTIMER_IRQ, RTC4HWTIMER_IRQ_PRIO);
    NVIC_EnableIRQ(RTC4HWTIMER_IRQ);

    /* prescaler: 0, resolution: 30.517us, overflow: 512s */
    RTC4HWTIMER_DEV->PRESCALER = 0;

    /* enable the low-frequency clock */
    NRF_CLOCK->TASKS_LFCLKSTART = 1;

    /* start the actual RTC4HWTIMER thing */
    RTC4HWTIMER_DEV->TASKS_START = 1;
}

void hwtimer_arch_enable_interrupt(void)
{
    NVIC_EnableIRQ(RTC4HWTIMER_IRQ);
}

void hwtimer_arch_disable_interrupt(void)
{
    NVIC_DisableIRQ(RTC4HWTIMER_IRQ);
}

void hwtimer_arch_set(unsigned long offset, short timer)
{
    hwtimer_arch_set_absolute(offset + RTC4HWTIMER_DEV->COUNTER, timer);
}

void hwtimer_arch_set_absolute(unsigned long value, short timer)
{
    unsigned int channel = timer;
    if (channel < RTC4HWTIMER_COMPARE_NUMOF) {
        unsigned int mask = (unsigned int)1 << (16 + channel);

        RTC4HWTIMER_DEV->CC[channel] = (value & RTC4HWTIMER_MAX_VALUE);
        RTC4HWTIMER_DEV->INTENSET = mask;
    }
}

void hwtimer_arch_unset(short timer)
{
    unsigned int channel = timer;
    if (channel < RTC4HWTIMER_COMPARE_NUMOF) {
        unsigned int mask = (unsigned int)1 << (16 + channel);
        RTC4HWTIMER_DEV->INTENCLR = mask;
    }
}

unsigned long hwtimer_arch_now(void)
{
    return RTC4HWTIMER_DEV->COUNTER;
}

void RTC4HWTIMER_ISR(void)
{
    unsigned int channel;
    for (channel = 0; channel < RTC4HWTIMER_COMPARE_NUMOF; channel++) {
        if (RTC4HWTIMER_DEV->EVENTS_COMPARE[channel] == 1) {
            unsigned int mask = (unsigned int)1 << (16 + channel);

            RTC4HWTIMER_DEV->EVENTS_COMPARE[channel] = 0;
            RTC4HWTIMER_DEV->INTENCLR = mask;

            timeout_handler((short)(channel));
        }
    }

    // if (RTC4HWTIMER_DEV->EVENTS_OVRFLW == 1) {
    //     RTC4HWTIMER_DEV->EVENTS_OVRFLW = 0;
    //     overflow_cb(overflow_arg);
    // }

    if (sched_context_switch_request) {
        thread_yield();
    }
}
