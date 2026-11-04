# chipone_tddi — ChipOne ICNL9922C TDDI touchscreen driver

[![Build](https://github.com/kevinkreiser/chipone_tddi/actions/workflows/build.yml/badge.svg)](https://github.com/kevinkreiser/chipone_tddi/actions/workflows/build.yml)

Out-of-tree Linux kernel module for the **ChipOne ICNL9922C** TDDI touch
controller, as used in the **KONKR Pocket FIT** (Qualcomm SM8650) handheld.
Built for use with [ROCKNIX](https://github.com/ROCKNIX/distribution) on its
mainline-based kernel (7.0.x).

## Provenance

This is a port of ChipOne's `cts_*` vendor driver, taken from
`MotorolaMobilityLLC/motorola-kernel-modules`, path
`drivers/input/touchscreen/chipone_tddi_mmi_v2`
(tag `android-14-release-u4ui34.8-28-1`). You can brows the original source
[here](https://github.com/MotorolaMobilityLLC/motorola-kernel-modules/tree/df9767e77a5450c421538e323dccb1d5213aa50a/drivers/input/touchscreen/chipone_tddi_mmi_v2). The original copyright and
`SPDX-License-Identifier` headers are retained in each source file.

It was written against a downstream Android kernel (~5.10/6.1 GKI); this fork
makes it build and load as an out-of-tree module on **mainline Linux 7.0.x**.

## Changes from upstream

- API drift fixes for mainline 7.0: `<linux/unaligned.h>`; dropped
  `linux/mmi_wake_lock.h`; single-arg i2c `.probe` and `void` `.remove`;
  `class_create()` (1-arg); `PDE_DATA()` -> `pde_data()`; `no_llseek` ->
  `noop_llseek`; `MODULE_IMPORT_NS("...")` string form; removed the
  module-unexported `irq_to_desc()` debug use; dropped the driver's private
  `get/put_unaligned_le24/be24` (now provided by the kernel).
- Disabled charger-detect and earjack-detect (not wired on this hardware).

## Build

Configuration is set via the `Kbuild` ccflags:

- `CONFIG_CTS_I2C_HOST` — I²C transport
- `CONFIG_CTS_IC_NAME_ICNL9922C` — target IC
- `CFG_CTS_WRAP_X` — invert the X axis (the KONKR panel is mounted rotated 90°)

Out-of-tree against an installed kernel:

```sh
make KDIR=/path/to/kernel/build
```

## Devicetree

The controller sits on `&i2c4` (`i2c@a90000`) at address `0x48`, IRQ on TLMM
gpio 162, reset on TLMM gpio 161:

```dts
&i2c4 {
    touchscreen@48 {
        compatible = "chipone-tddi";
        reg = <0x48>;
        interrupt-parent = <&tlmm>;
        interrupts = <162 IRQ_TYPE_EDGE_FALLING>;
        chipone,irq-gpio = <&tlmm 162 GPIO_ACTIVE_HIGH>;
        chipone,rst-gpio = <&tlmm 161 GPIO_ACTIVE_HIGH>;
        chipone,x-res = <1080>;
        chipone,y-res = <1920>;
        pinctrl-names = "default";
        pinctrl-0 = <&ts_irq_default>, <&ts_reset_default>;
        status = "okay";
    };
};
```

## License

GPL-2.0 (see `LICENSE`). Derivative of GPL-2.0 vendor source; license retained.
