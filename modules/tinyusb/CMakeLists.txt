# SPDX-License-Identifier: Apache-2.0

if (CONFIG_TINYUSB)
  # Refer to https://docs.tinyusb.org/en/latest/integration.html

  # Create an interface library named "tinyusb"
  zephyr_interface_library_named(tinyusb)

  # 2. Add source files: Add every .c file from tinyusb/src/ to your project build system.
  zephyr_library()

  zephyr_library_sources(
    # TinyUSB common sources
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/tusb.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/common/tusb_fifo.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/device/usbd.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/host/hub.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/host/usbh.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/typec/usbc.c
    # TinyUSB class sources
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/audio/audio_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/bth/bth_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/cdc/cdc_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/cdc/cdc_host.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/dfu/dfu_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/dfu/dfu_rt_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/hid/hid_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/hid/hid_host.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/midi/midi2_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/midi/midi2_host.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/midi/midi_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/midi/midi_host.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/msc/msc_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/msc/msc_host.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/mtp/mtp_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/net/ecm_rndis_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/net/ncm_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/printer/printer_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/usbtmc/usbtmc_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/vendor/vendor_device.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/vendor/vendor_host.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/class/video/video_device.c
    # TinyUSB portable sources
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/analog/max3421/hcd_max3421.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/bridgetek/ft9xx/dcd_ft9xx.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/chipidea/ci_fs/dcd_ci_fs.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/chipidea/ci_hs/dcd_ci_hs.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/chipidea/ci_hs/hcd_ci_hs.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/dialog/da146xx/dcd_da146xx.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/ehci/ehci.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/mentor/musb/dcd_musb.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/mentor/musb/hcd_musb.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/microchip/pic/dcd_pic.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/microchip/pic32mz/dcd_pic32mz.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/microchip/samd/dcd_samd.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/microchip/samd/hcd_samd.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/microchip/samg/dcd_samg.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/microchip/samx7x/dcd_samx7x.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/mindmotion/mm32/dcd_mm32f327x_otg.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/nordic/nrf5x/dcd_nrf5x.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/nuvoton/nuc120/dcd_nuc120.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/nuvoton/nuc121/dcd_nuc121.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/nuvoton/nuc505/dcd_nuc505.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/nxp/khci/dcd_khci.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/nxp/khci/hcd_khci.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/nxp/lpc17_40/dcd_lpc17_40.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/nxp/lpc_ip3511/dcd_lpc_ip3511.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/nxp/lpc_ip3516/hcd_lpc_ip3516.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/ohci/ohci.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/raspberrypi/pio_usb/dcd_pio_usb.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/raspberrypi/pio_usb/hcd_pio_usb.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/raspberrypi/rp2040/dcd_rp2040.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/raspberrypi/rp2040/hcd_rp2040.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/raspberrypi/rp2040/rp2040_usb.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/renesas/rusb2/dcd_rusb2.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/renesas/rusb2/hcd_rusb2.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/renesas/rusb2/rusb2_common.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/sony/cxd56/dcd_cxd56.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/st/stm32_fsdev/dcd_stm32_fsdev.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/st/stm32_fsdev/fsdev_common.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/st/stm32_fsdev/hcd_stm32_fsdev.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/st/typec/typec_stm32.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/sunxi/dcd_sunxi_musb.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/synopsys/dwc2/dcd_dwc2.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/synopsys/dwc2/dwc2_common.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/synopsys/dwc2/hcd_dwc2.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/template/dcd_template.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/template/hcd_template.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/ti/msp430x5xx/dcd_msp430x5xx.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/valentyusb/eptri/dcd_eptri.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/wch/dcd_ch32_usbfs.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/wch/dcd_ch32_usbhs.c
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src/portable/wch/hcd_ch32_usbfs.c
  )

  # 4. Configure include paths: Add your_project/tinyusb/src (and the folder holding tusb_config.h)
  # to your include paths.
  target_include_directories(tinyusb INTERFACE
    ${ZEPHYR_TINYUSB_MODULE_DIR}/src
  )
endif() # CONFIG_TINYUSB
