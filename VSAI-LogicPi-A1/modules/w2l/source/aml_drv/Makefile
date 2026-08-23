AML_VERS_NUM=v1.2.0_2025-10.16-w2l driver:3c1fb1cfe fw:9e9a309b
# KERNELDIR ?= /usr/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)
ifeq ($(ARCH),)
ARCH ?= arm64
CROSS_COMPILE ?= aarch64-linux-gnu-
else ifeq ($(ARCH),arm)
SYSTEM_TYPE = SYSTEM32
CROSS_COMPILE ?= arm-linux-gnueabihf-
EXTRA_CFLAGS += -DSYSTEM32
else ifeq ($(ARCH),arm64)
SYSTEM_TYPE = SYSTEM64
CROSS_COMPILE ?= aarch64-linux-gnu-
EXTRA_CFLAGS += -DSYSTEM64
endif
ifeq ($(ROKU_PROJECT), y)
CUSTOM_LOG_PREFIX = wlan
-include $(BACKPORTS_VERSIONS)
ifneq ($(BACKPORTED_KERNEL_VERSION),)
export CFG_CFG80211_VERSION ?= $(BACKPORTED_KERNEL_VERSION)
endif

ifeq ($(ROKU_TV_PROJECT), y)
SDIO_MODE_ON = n
endif

ifneq ($(BACKPORTS_VERSIONS),)
LINUXINCLUDE := $(BACKPORTS_INCLUDE_DIR) $(LINUXINCLUDE)
include $(BACKPORTS_VERSIONS)
subdir-ccflags-y += -D__rcu=
subdir-ccflags-y += -DCOMPAT_KERNEL_RELEASE=1
subdir-ccflags-y += '-include' 'backport/backport.h'
subdir-ccflags-y += -DCPTCFG_VERSION=\"$(BACKPORTS_VERSION)\"
subdir-ccflags-y += -DCPTCFG_KERNEL_VERSION=\"$(BACKPORTED_KERNEL_VERSION)\"
subdir-ccflags-y += -DCPTCFG_KERNEL_NAME=\"$(BACKPORTED_KERNEL_NAME)\"
subdir-ccflags-y += -DBACKPORTED_KERNEL_NAME=\"$(BACKPORTED_KERNEL_NAME)\"
subdir-ccflags-y += -DBACKPORTS_VERSION=\"$(BACKPORTS_VERSION)\"
subdir-ccflags-y += -DBACKPORTED_KERNEL_VERSION=\"$(BACKPORTED_KERNEL_VERSION)\"
subdir-ccflags-y += -Wno-error=missing-attributes
subdir-ccflags-y += -Wno-error=stringop-truncation
subdir-ccflags-y += -Wno-error=unused-variable
endif
subdir-ccflags-y += -DCONFIG_ROKU
ifeq ($(BACKPORTS_3), y)
subdir-ccflags-y += -DCOMPAT_KERNEL_RELEASE_3_14=1
$(info set COMPAT_KERNEL_RELEASE_3_14)
else
# Assume all non_backport_3 is using backport_4_19
subdir-ccflags-y += -DCOMPAT_KERNEL_RELEASE_4_19=1
$(info set COMPAT_KERNEL_RELEASE_4_19)
endif
endif

ifneq ($(CFG_CFG80211_VERSION),)
VERSION_STR = $(subst $\",,$(subst ., , $(subst -, ,$(subst v,,$(CFG_CFG80211_VERSION)))))
$(info VERSION_STR=$(VERSION_STR))
X = $(firstword $(VERSION_STR))
Y = $(word 2 ,$(VERSION_STR))
Z = $(word 3 ,$(VERSION_STR))
VERSION := $(shell echo "$$(( $(X) * 65536 + $(Y) * 256 + $(Z)))" )
subdir-ccflags-y += -DCFG_CFG80211_VERSION=$(VERSION)
$(info DCFG_CFG80211_VERSION=$(VERSION))
endif

ifeq ($(PROJ_NAME),p-amlogic)
SRCTOP ?= /proj/vlsi.wifi/p-amlogic
KERNELDIR ?= $(SRCTOP)/out/target/product/newton/obj/KERNEL_OBJ
EXTRA_CFLAGS += -DSYSTEM64
else ifeq ($(PROJ_NAME),yeke)
SRCTOP ?= /proj/vlsi.wifi/yeke_64bit
KERNELDIR ?= $(SRCTOP)/out/target/product/p281/obj/KERNEL_OBJ
EXTRA_CFLAGS += -DSYSTEM64
else ifeq ($(PROJ_NAME),9-xiaomi)
SRCTOP ?= /proj/vlsi.wifi/9-xiaomi
KERNELDIR ?= $(SRCTOP)/out/target/product/aquaman/obj/KERNEL_OBJ
EXTRA_CFLAGS += -DSYSTEM64
else ifeq ($(PROJ_NAME),gva)
SRCTOP ?= /proj/vlsi.wifi/gva
KERNELDIR ?= $(SRCTOP)/kernel-4.9/common
EXTRA_CFLAGS += -DSYSTEM64
else
ifeq ($(SYSTEM_TYPE),)
ARCH = arm
CROSS_COMPILE = arm-linux-gnueabihf-
EXTRA_CFLAGS += -DSYSTEM32
endif
SRCTOP ?= /proj/vlsi.wifi/p212_32bit
KERNELDIR ?= $(SRCTOP)/out/target/product/ampere/obj/KERNEL_OBJ
endif

CC        ?= $(CROSS_COMPILE)gcc
STRIP     ?= $(CROSS_COMPILE)strip

M ?= $(shell pwd)
ifneq ($(KERNEL_SRC),)
CUR_DIR  := $(KERNEL_SRC)/$(M)
else
CUR_DIR  := $(M)
endif
EXT_INCS := $(CUR_DIR)/../common
INCS     := -I$(CUR_DIR) -I$(EXT_INCS)
KERNEL_SRC ?= $(KERNELDIR)
TARGET = vlsicomm

#
# WAITING FOR KCONFIG {
#
CONFIG_AML_SOFTMAC ?= n
CONFIG_AML_FULLMAC ?= m
CONFIG_AML_FHOST ?= n

#
# DEBUG OPTIONS
CONFIG_AML_UM_HELPER_DFLT ?= "/usr/bin/aml_umh.sh"

#
# FW ARCH:
CONFIG_AML_SDM ?= n
CONFIG_AML_TL4 ?= n

# IPC version
CONFIG_AML_OLD_IPC ?= n

# Support of P2P DebugFS for enabling/disabling NoA and OppPS
CONFIG_AML_P2P_DEBUGFS ?= y

# Need open it when use FPGA pcie version
CONFIG_AML_FPGA_PCIE ?= n

# Product test mode
CONFIG_PT_MODE ?= n

# Amlogic specified android(/w Kernel) platform depends
CONFIG_AML_PLATFORM_ANDROID ?= y

CONFIG_AML_SDIO_IRQ_VIA_GPIO ?= y

# Use platform random mac
CONFIG_AML_PLATFORM_RANDOM_MAC ?= n

# Support to use preallocing static buffer for wlan driver reloadable
CONFIG_AML_PREALLOC_BUF_STATIC ?= y

# Support to use preallocing buffer for debug SKB alloc failed
CONFIG_AML_PREALLOC_BUF_SKB ?= n

# Config to enable WFA certification mode
CONFIG_AML_WFA_CERT_MODE ?= n

# Config to enable Power_Save mode
CONFIG_AML_POWER_SAVE_MODE ?= n

# Config to enable GOOGLE_CAST wake host
CONFIG_AML_WOW_GOOGLE_CAST_EN ?= n

# Config to enable MAGIC_PKT wake host
CONFIG_AML_WOW_MAGIC_PACKET_EN ?= n

# Support to use tasks to process IRQ Handlers
CONFIG_AML_USE_TASK ?= y

# Support recovery function
CONFIG_AML_RECOVERY ?= y
# } // WAITING FOR KCONFIG
#

# Support rx minisize function
CONFIG_AML_RX_MINISIZE ?= y

# Support RX BIGSIZE function
CONFIG_AML_RX_BIGSIZE ?= n

# Support ND_RANDOM_MAC_ADDR
CONFIG_ND_RANDOM_MAC_ADDR ?= n

#support NAPI
CONFIG_AML_NAPI ?= y

# support MDNS_OFFLOAD feature
CONFIG_MDNS_OFFLOAD_FEATURE ?= y

# support rf low power feature
CONFIG_RF_POWER_OPTI ?= n

# Support 4.9 ax
ifeq ($(CONFIG_AML_KERNEL_4_9),y)
CONFIG_KERNEL_AX_PATCH ?= y
endif
# } // NEED 4.9 PATCH

# compile sdio in driver
SDIO_MODE_ON ?= y
export SDIO_MODE_ON
CUSTOM_LOG_PREFIX ?= n
export CUSTOM_LOG_PREFIX
#CONFIG_SDIO_TX_ENH ?= y

ifeq ($(CONFIG_GOOGLE_CAST_EN),y)
CONFIG_AML_WOW_GOOGLE_CAST_EN = y
endif

ifeq ($(CONFIG_MAGIC_PACKET_EN),y)
CONFIG_AML_WOW_MAGIC_PACKET_EN = y
endif

# Support sdio rx atuo interrupt function
#CONFIG_SDIO_RX_AUTO_INT ?= y

CONFIG_CUSTOMER_11D_FORBIDDEN ?= y

# optimize the debug mem if driver donot need it
CONFIG_LIGHT_WEIGHT_MEM ?=y

# active powersave mode on
CONFIG_AML_ACTIVE_PS ?=y

# usb hotplug on
ifeq ($(ROKU_PROJECT), y)
CONFIG_AML_USB_HOTPLUG ?= y
endif

subdir-ccflags-$(CONFIG_PT_MODE) += -DCONFIG_PT_MODE
subdir-ccflags-$(CONFIG_AML_PLATFORM_ANDROID) += -DCONFIG_AML_PLATFORM_ANDROID
subdir-ccflags-$(CONFIG_DEBUG_FS) += -DCONFIG_AML_DEBUGFS
subdir-ccflags-$(CONFIG_DEBUG_FS) += -DCONFIG_AML_UM_HELPER_DFLT=\"$(CONFIG_AML_UM_HELPER_DFLT)\"
subdir-ccflags-$(CONFIG_AML_P2P_DEBUGFS) += -DCONFIG_AML_P2P_DEBUGFS
subdir-ccflags-$(CONFIG_AML_FPGA_PCIE) += -DCONFIG_AML_FPGA_PCIE
subdir-ccflags-$(CONFIG_AML_PREALLOC_BUF_STATIC) += -DCONFIG_AML_PREALLOC_BUF_STATIC
subdir-ccflags-$(CONFIG_AML_PREALLOC_BUF_SKB) += -DCONFIG_AML_PREALLOC_BUF_SKB
subdir-ccflags-$(CONFIG_AML_WFA_CERT_MODE) += -DCONFIG_AML_WFA_CERT_MODE
subdir-ccflags-$(CONFIG_AML_POWER_SAVE_MODE) += -DCONFIG_AML_POWER_SAVE_MODE
subdir-ccflags-$(CONFIG_AML_USE_TASK) += -DCONFIG_AML_USE_TASK
subdir-ccflags-$(CONFIG_AML_RECOVERY) += -DCONFIG_AML_RECOVERY
subdir-ccflags-$(CONFIG_AML_RX_MINISIZE) += -DCONFIG_AML_W2L_RX_MINISIZE
subdir-ccflags-$(CONFIG_AML_RX_BIGSIZE) += -DCONFIG_AML_W2_RX_MINISIZE
subdir-ccflags-$(CONFIG_AML_NAPI) += -DCONFIG_AML_NAPI
subdir-ccflags-$(CONFIG_KERNEL_AX_PATCH) += -DCONFIG_KERNEL_AX_PATCH
subdir-ccflags-$(CONFIG_SDIO_RX_AUTO_INT) += -DCONFIG_SDIO_RX_AUTO_INT
#subdir-ccflags-$(CONFIG_SDIO_TX_ENH) += -DCONFIG_SDIO_TX_ENH
subdir-ccflags-$(CONFIG_MDNS_OFFLOAD_FEATURE) += -DMDNS_OFFLOAD_FEATURE
subdir-ccflags-$(CONFIG_RF_POWER_OPTI) += -DRF_POWER_OPTI
subdir-ccflags-$(ROKU_TV_PROJECT) += -DROKU_TV_PROJECT
subdir-ccflags-$(SDIO_MODE_ON) += -DSDIO_MODE_ON
subdir-ccflags-$(CONFIG_AML_WOW_GOOGLE_CAST_EN) += -DAML_WOW_GOOGLE_CAST_EN
subdir-ccflags-$(CONFIG_AML_WOW_MAGIC_PACKET_EN) += -DAML_WOW_MAGIC_PACKET_EN
subdir-ccflags-$(LINUX_UPSTREAM) += -DCONFIG_LINUX_UPSTREAM
subdir-ccflags-$(CONFIG_LIGHT_WEIGHT_MEM) += -DLIGHT_WEIGHT_MEM
subdir-ccflags-$(CONFIG_AML_ACTIVE_PS) += -DCONFIG_ACTIVE_PS
subdir-ccflags-$(CONFIG_AML_USB_HOTPLUG) += -DCONFIG_USB_HOTPLUG
subdir-ccflags-$(CONFIG_ND_RANDOM_MAC_ADDR) += -DCONFIG_ND_RANDOM_MAC_ADDR

# FW VARS
subdir-ccflags-y += -DNX_VIRT_DEV_MAX=4
subdir-ccflags-y += -DNX_REMOTE_STA_MAX=16
subdir-ccflags-y += -DNX_MU_GROUP_MAX=62
subdir-ccflags-y += -DNX_TX_MAX_RATES=4
subdir-ccflags-y += -DNX_CHAN_CTXT_CNT=3

# FW ARCH:
subdir-ccflags-$(CONFIG_AML_SDM) += -DCONFIG_AML_SDM
subdir-ccflags-$(CONFIG_AML_TL4) += -DCONFIG_AML_TL4
subdir-ccflags-$(CONFIG_AML_OLD_IPC) += -DCONFIG_AML_OLD_IPC

ifeq ($(CONFIG_AML_PLATFORM_ANDROID),y)
subdir-ccflags-$(CONFIG_AML_SDIO_IRQ_VIA_GPIO) += -DCONFIG_AML_SDIO_IRQ_VIA_GPIO
subdir-ccflags-$(CONFIG_ANDROID_GKI) += -DCONFIG_ANDROID_GKI

ifneq ($(CONFIG_AML_ANDROID),)
subdir-ccflags-y += -DCONFIG_AML_ANDROID=$(CONFIG_AML_ANDROID)
endif
endif

ifeq ($(CONFIG_CUSTOMER_11D_FORBIDDEN),y)
subdir-ccflags-y += -DCONFIG_CUSTOMER_11D_FORBIDDEN
endif

obj-$(CONFIG_AML_FULLMAC) += fullmac/

all: modules

modules clean:
	@$(PWD)/mklink.sh
	$(MAKE) CUR_DIR=$(CUR_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_SRC) M=$(M) $@
	@$(PWD)/mklink.sh clean
#ifneq (${OUT_DIR},)
#	$(CROSS_COMPILE)strip --strip-unneeded ${OUT_DIR}/$(M)/$(TARGET).ko
#else
#	$(STRIP) -S $(TARGET).ko
#endif

modules_install:
	@$(MAKE) INSTALL_MOD_STRIP=1 M=$(M) -C $(KERNEL_SRC) modules_install
	mkdir -p ${OUT_DIR}/../vendor_lib/modules
	cd ${OUT_DIR}/$(M)/; find -name "*.ko" -exec cp {} ${OUT_DIR}/../vendor_lib/modules/ \;

clean-files := aml_version_gen.h

