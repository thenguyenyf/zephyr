/*
 * Copyright (c) 2026 Renesas Electronics Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BOARD_API_H_
#define BOARD_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <tusb.h>

void board_init(void);
void board_init_after_tusb(void);
void board_led_write(bool state);

/* Using Zephyr's console for stdio */
int board_getchar(void);
int board_putchar(int c);

/* Blocking millisecond delay backed by Zephyr's k_msleep(). */
void board_delay(uint32_t ms);

static inline void board_led_on(void)
{
	board_led_write(true);
}

static inline void board_led_off(void)
{
	board_led_write(false);
}

#ifdef __cplusplus
}
#endif

#endif
