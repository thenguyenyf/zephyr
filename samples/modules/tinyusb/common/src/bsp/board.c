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

#define LED0_NODE DT_ALIAS(led0)

/* Pick the RUSB2 controller matching BOARD_TUH_RHPORT (0 = USBFS / full-speed,
 * 1 = USBHS / high-speed). Each port has its own DT node, pinctrl, NVIC slot
 * and FSP event code.
 */
#if BOARD_TUH_RHPORT == 0
#define USB_NODE      DT_NODELABEL(usbfs)
#define USB_IRQ       DT_IRQ_BY_NAME(USB_NODE, usbfs_i, irq)
#define USB_IRQ_PRIO  DT_IRQ_BY_NAME(USB_NODE, usbfs_i, priority)
#define USB_FSP_EVENT EVENT_USBFS_INT
#elif BOARD_TUH_RHPORT == 1
#define USB_NODE      DT_NODELABEL(usbhs)
#define USB_IRQ       DT_IRQ_BY_NAME(USB_NODE, usbhs_ir, irq)
#define USB_IRQ_PRIO  DT_IRQ_BY_NAME(USB_NODE, usbhs_ir, priority)
#define USB_FSP_EVENT EVENT_USBHS_USB_INT_RESUME
#else
#error "BOARD_TUH_RHPORT must be 0 (usbfs) or 1 (usbhs)"
#endif

#if !DT_NODE_HAS_STATUS(USB_NODE, okay)
#error "Selected USB controller DT node must be enabled for this sample"
#endif

PINCTRL_DT_DEFINE(USB_NODE);

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec board_led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#endif

static void usb_isr(const void *arg)
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

	(void)pinctrl_apply_state(PINCTRL_DT_DEV_CONFIG_GET(USB_NODE), PINCTRL_STATE_DEFAULT);

	R_ICU->IELSR[USB_IRQ] = BSP_PRV_IELS_ENUM(USB_FSP_EVENT);
	BSP_ASSIGN_EVENT_TO_CURRENT_CORE(BSP_PRV_IELS_ENUM(USB_FSP_EVENT));

	IRQ_CONNECT(USB_IRQ, USB_IRQ_PRIO, usb_isr, NULL, 0);

	tusb_rusb2_set_irqnum(BOARD_TUH_RHPORT, USB_IRQ);
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
