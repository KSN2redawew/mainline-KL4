# SPDX-License-Identifier: GPL-2.0-or-later

ccflags-y += -I$(src)
ccflags-y += -I$(src)/tcm
ccflags-y += -Wno-error
ccflags-y += -DCONFIG_TOUCHSCREEN_SYNA_TCM2_TOUCHCOMM_VERSION_1
ccflags-y += -DCONFIG_TOUCHSCREEN_SYNA_TCM2_SPI
ccflags-y += -DCONFIG_OF

obj-y += synaptics_tcm2.o

synaptics_tcm2-y := syna_tcm2.o \
	syna_tcm2_cdev.o \
	tcm/synaptics_touchcom_func_base.o \
	tcm/synaptics_touchcom_func_touch.o \
	tcm/synaptics_touchcom_func_reflash.o \
	tcm/synaptics_touchcom_image_parsing.o \
	tcm/synaptics_touchcom_core_v1.o \
	syna_tcm2_platform_spi.o
