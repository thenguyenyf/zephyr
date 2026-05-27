# SPDX-License-Identifier: Apache-2.0

# Path to common code shared by all our TinyUSB samples (e.g. board and IRQ initialization).
set(TINYUSB_SAMPLE_COMMON_DIR ${ZEPHYR_BASE}/samples/modules/tinyusb/common)

zephyr_include_directories(
  ${TINYUSB_SAMPLE_COMMON_DIR}/src
)

target_sources(app PRIVATE
  ${TINYUSB_SAMPLE_COMMON_DIR}/src/bsp/board.c
)
