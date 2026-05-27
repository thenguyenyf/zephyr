# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(tinyusb_hid_controller)

# Path to common code shared by all our TinyUSB samples (e.g. board and IRQ initialization).
set(TINYUSB_SAMPLE_COMMON_DIR ${ZEPHYR_BASE}/samples/modules/tinyusb/common)

# Path to upstream TinyUSB sample sources (unmodified, referenced in place).
set(TUSB_SAMPLE_DIR ${ZEPHYR_TINYUSB_MODULE_DIR}/examples/host/hid_controller)

include(${TINYUSB_SAMPLE_COMMON_DIR}/common.cmake)

# Link with the TinyUSB library, which provides the core USB host stack and
# class drivers (including HID).
zephyr_link_libraries(tinyusb)

# Target: ek_ra8p1 (cm85 core) — Renesas RA8P1, RUSB2 full-speed controller (usbfs)
# The board overlay enables `usbfs`, which maps to TinyUSB RA RHPORT 0 / FS.
zephyr_compile_definitions(
  CFG_TUSB_MCU=OPT_MCU_RAXXX
  CFG_TUSB_OS=OPT_OS_ZEPHYR
  BOARD_TUH_RHPORT=0
  BOARD_TUH_MAX_SPEED=OPT_MODE_FULL_SPEED
  # FSP-generated NVIC slot symbols don't exist under Zephyr — stub them so
  # rusb2_common.c compiles; the real slot is set at runtime via
  # tusb_rusb2_set_irqnum() inside board_init() (see src/bsp/board.c).
  USBFS_INT_IRQn=0
  USBHS_USB_INT_RESUME_IRQn=0
)

zephyr_include_directories(
  ${TUSB_SAMPLE_DIR}/src
)

# The sample's own source files, which implement board initialization and the
# HID host application logic, respectively.
target_sources(app PRIVATE
  ${TUSB_SAMPLE_DIR}/src/main.c
  ${TUSB_SAMPLE_DIR}/src/hid_app.c
)
