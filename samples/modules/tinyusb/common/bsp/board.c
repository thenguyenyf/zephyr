/*
 * Copyright (c) 2026 Renesas Electronics Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/console/console.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/irq.h>

#include "tusb.h"
#include "host/hcd.h"
#include "bsp/board_api.h"

#include <stdio.h>
/* FSP register/macro access (R_ICU, ELC_*, BSP_PRV_IELS_ENUM, ...) */
#include "bsp_api.h"

extern void tusb_rusb2_set_irqnum(uint8_t rhport, int32_t irqnum);

#define LED0_NODE  DT_ALIAS(led0)
#define USBHS_NODE DT_NODELABEL(usbhs)

#if !DT_NODE_HAS_STATUS(USBHS_NODE, okay)
#error "usbhs DT node must be enabled for this sample"
#endif

#define USBHS_IRQ  DT_IRQ_BY_NAME(USBHS_NODE, usbhs_ir, irq)
#define USBHS_PRIO DT_IRQ_BY_NAME(USBHS_NODE, usbhs_ir, priority)

PINCTRL_DT_DEFINE(USBHS_NODE);

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec board_led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#endif

static void usbhs_isr(const void *arg)
{
	ARG_UNUSED(arg);
	R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());
	tusb_int_handler(BOARD_TUH_RHPORT, true);
}

void board_init(void)
{
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
	if (gpio_is_ready_dt(&board_led)) {
		(void)gpio_pin_configure_dt(&board_led, GPIO_OUTPUT_INACTIVE);
	}
#endif

	(void)pinctrl_apply_state(PINCTRL_DT_DEV_CONFIG_GET(USBHS_NODE), PINCTRL_STATE_DEFAULT);

	R_ICU->IELSR[USBHS_IRQ] = BSP_PRV_IELS_ENUM(EVENT_USBHS_USB_INT_RESUME);
	BSP_ASSIGN_EVENT_TO_CURRENT_CORE(BSP_PRV_IELS_ENUM(EVENT_USBHS_USB_INT_RESUME));

	IRQ_CONNECT(USBHS_IRQ, USBHS_PRIO, usbhs_isr, NULL, 0);

	tusb_rusb2_set_irqnum(BOARD_TUH_RHPORT, USBHS_IRQ);
}

void board_init_after_tusb(void)
{
}

void board_led_write(bool state)
{
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
	if (gpio_is_ready_dt(&board_led)) {
		(void)gpio_pin_set_dt(&board_led, state ? 1 : 0);
	}
#else
	ARG_UNUSED(state);
#endif
}

void board_delay(uint32_t ms)
{
	k_msleep(ms);
}

/* Using Zephyr's console for stdio */
int board_getchar(void)
{
	return getchar();
}

int board_putchar(int c)
{
	return putchar((char)c);
}
