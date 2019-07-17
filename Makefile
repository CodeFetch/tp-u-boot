#
# Copyright (C) 2019 Vincent Wiemann <vincent.wiemann@ironai.com>
#
# SPDX-License-Identifier: GPL-2.0
#

export BUILD_TOPDIR=$(PWD)
export STAGING_DIR=$(BUILD_TOPDIR)/tmp

export MAKECMD=make --silent ARCH=mips CROSS_COMPILE=mipsel-openwrt-linux-musl-
export PATH:=$(BUILD_TOPDIR)/toolchain/bin/:$(PATH)

SHELL = bash

HOSTARCH := $(shell uname -m |        \
	      sed -e s/i.86/x86_32/   \
		  -e s/sun4u/sparc64/ \
		  -e s/arm.*/arm/     \
		  -e s/sa110/arm/     \
		  -e s/powerpc/ppc/   \
		  -e s/macppc/ppc/)

HOSTOS := $(shell uname -s | tr '[:upper:]' '[:lower:]' | \
	    sed -e 's/\(cygwin\).*/cygwin/')

ifneq ($(HOSTOS), darwin)
  ifneq ($(HOSTOS), linux)
    $(error Error! Unsupported host operating system/arch: "$(HOSTOS)-$(HOSTARCH)")
  endif
endif

export HOSTOS
export HOSTARCH
export STAGING_DIR  = $(BUILD_TOPDIR)/tmp
export SOURCE_DIR   = $(BUILD_TOPDIR)/u-boot
export BIN_DIR      = $(BUILD_TOPDIR)/bin
export SUB_MAKE_CMD = $(MAKE) --silent --no-print-directory \
                      ARCH=mips V=1 SHELL=$(SHELL)

ifndef CROSS_COMPILE
  CROSS_COMPILE = mipsel-openwrt-linux-musl-
endif
export CROSS_COMPILE

# =======================
# CUSTOM HELPER FUNCTIONS
# =======================

define echo_green
  echo -e "\e[92m$(1)\e[0m"
endef

define echo_red
  echo -e "\e[91m$(1)\e[0m"
endef

define echo_blue
  echo -e "\e[96m$(1)\e[0m"
endef

# $(1): size
define img_size
$(if $(IMG_SIZE),$(strip $(IMG_SIZE)),$(strip $(1)))
endef

define git_branch
$(shell git symbolic-ref --short -q HEAD 2>/dev/null || echo "unknown")
endef

define git_hash
$(shell git rev-parse --short=8 -q HEAD 2>/dev/null || echo "unknown")
endef

define git_branch_hash
git_$(call git_branch)-$(call git_hash)
endef

# $(1): file extension
define img_name
tp-u-boot__$@__$(shell date +"%Y%m%d")__$(call git_branch_hash)
endef

define md5_sum
  $(call echo_green,Calculating MD5 sum for the final image...)

  md5sum $(BIN_DIR)/$(call img_name,bin) | \
         awk '{print $$1}' | \
         tr -d '\n' > $(BIN_DIR)/$(call img_name).md5

  echo ' *'$(call img_name,bin) >> $(BIN_DIR)/$(call img_name,md5)
endef

# $(1): size
define padded_img
  $(call echo_green,Preparing $(1) KB image padded with 0xFF...)
  tr "\000" "\377" < /dev/zero | dd ibs=1k count=$(1) \
     of=$(BIN_DIR)/$(call img_name,bin) 2> /dev/null
endef

define final_img
  $(call echo_green,Preparing final image...)
  dd if=$(BIN_DIR)/temp.bin of=$(BIN_DIR)/$(call img_name,bin) \
     conv=notrunc 2> /dev/null

  rm -f $(BIN_DIR)/temp.bin
endef

# $(1): path to image
# $(2): size limit in KB
define size_chk
  $(call echo_green,Checking size of the image...)

  if [ `wc -c < $(1)` -gt $$(($(2) * 1024)) ]; then \
    echo; \
    $(call echo_red,  ======================); \
    $(call echo_red,  IMAGE SIZE IS TOO BIG!); \
    $(call echo_red,  ======================); \
    echo; \
    rm -f $(1); \
    exit 1; \
  fi;
endef

# $(1): filename of image to copy
# $(2): image size limit (check if set)
define copy_img
  echo;
  $(call echo_green,Copying compiled image...)

  cp $(SOURCE_DIR)/$(strip $(1)).bin $(BIN_DIR)/temp.bin
  $(if $(2),$(call size_chk,$(BIN_DIR)/temp.bin,$(2)))
endef

# $(1): size limit in KB
# $(2): other parameters passed to subdir make
define build
  args="IMG_SIZE=$$((1024*$(call img_size,$(1)))) \
        TP_BOARD_FILE=$(strip $(2))"; \
  cd $(SOURCE_DIR) && \
     $(SUB_MAKE_CMD) $$args && \
     $(SUB_MAKE_CMD) all $$args

  $(call final_img)
  $(call md5_sum)
  echo;
  $(call echo_green,DONE!)
  $(call echo_green,Image 'bin/$(call img_name,bin)' is ready!)

endef

# ===========================================
# TARGETS IN ALPHABETICAL ORDER, SHARED FIRST
# ===========================================

tp-link_archer_c50_v4:
	@$(call build,128,tp_archer_c50_v4)

# =============
# CLEAN TARGETS
# =============

clean:
	@cd $(SOURCE_DIR) && $(SUB_MAKE_CMD) distclean

clean_all: clean
	@$(call echo_green,Removing all binary images...)
	@rm -f $(BIN_DIR)/*.bin
	@rm -f $(BIN_DIR)/*.md5
