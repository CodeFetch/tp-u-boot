#
# (C) Copyright 2000-2004
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

ifndef CROSS_COMPILE
  $(error "CROSS_COMPILE is not defined!")
endif
export CROSS_COMPILE

TOPDIR	:= $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)
export	TOPDIR

ifeq ($(TP_BOARD_FILE),)
include $(BUILD_TOPDIR)/boards/$(TP_BOARD_FILE).config
endif


ifeq ($(FACTORY_UBOOT), y)
export FACTORY_UBOOT=y
endif

ifeq (include/config.mk,$(wildcard include/config.mk))
# load ARCH, BOARD, and CPU configuration
include include/config.mk
export	ARCH CPU BOARD VENDOR SOC
# load other configuration
include $(TOPDIR)/config.mk

ifeq ($(ON_BOARD_DDR1),y)
DRAM_TYPE=DDR1
endif
ifeq ($(ON_BOARD_DDR2),y)
DRAM_TYPE=DDR2
endif
ifeq ($(ON_BOARD_DDR3),y)
DRAM_TYPE=DDR3
endif
ifeq ($(ON_BOARD_SDR),y)
DRAM_TYPE=SDR
endif

DRAM_SIZE=2
ifeq ($(ON_BOARD_64M_DRAM_COMPONENT),y)
DRAM_SIZE=8
endif
ifeq ($(ON_BOARD_128M_DRAM_COMPONENT),y)
DRAM_SIZE=16
endif
ifeq ($(ON_BOARD_256M_DRAM_COMPONENT),y)
DRAM_SIZE=32
endif
ifeq ($(ON_BOARD_512M_DRAM_COMPONENT),y)
DRAM_SIZE=64
endif
ifeq ($(ON_BOARD_1024M_DRAM_COMPONENT),y)
DRAM_SIZE=128
endif
ifeq ($(ON_BOARD_2048M_DRAM_COMPONENT),y)
DRAM_SIZE=256
endif
ifeq ($(ON_BOARD_4096M_DRAM_COMPONENT),y)
DRAM_SIZE=448
endif

# DRAM_WIDTH: SDR(DDR2)
# 0:16(8)
# 1:32(16)
ifeq ($(ON_BOARD_DDR_WIDTH_16),y)
DRAM_WIDTH=32
else
DRAM_WIDTH=16
endif

ifeq ($(ON_BOARD_32BIT_DRAM_BUS),y)
DRAM_TOTAL_WIDTH=32
else
DRAM_TOTAL_WIDTH=16
endif

#default value for syscfg0/syscfg1
ifeq ($(DRAM_CFG0),)
DRAM_SYSCFG0=0xFF
else
DRAM_SYSCFG0=$(DRAM_CFG0)
endif

ifeq ($(DRAM_CFG1),)
DRAM_SYSCFG1=0xFF
else
DRAM_SYSCFG1=$(DRAM_CFG1)
endif

ifeq ($(CPUPLLCFG),)
CPU_PLL_CFG=0xFF
else
CPU_PLL_CFG=$(CPUPLLCFG)
endif
export	CROSS_COMPILE

#########################################################################
# U-Boot objects....order is important (i.e. start must be first)

ifeq ($(MT7621_MP), y)
OBJS  = cpu/$(CPU)/start_1004k.o
else
OBJS  = cpu/$(CPU)/start.o
endif

LIBS  = lib_generic/libgeneric.a
LIBS += board/$(BOARDDIR)/lib$(BOARD).a
LIBS += cpu/$(CPU)/lib$(CPU).a
ifdef SOC
LIBS += cpu/$(CPU)/$(SOC)/lib$(SOC).a
endif
LIBS += lib_$(ARCH)/lib$(ARCH).a

ifeq ($(MINI_WEB_SERVER_SUPPORT), y)
LIBS += httpd/libhttpd.a
endif

LIBS += net/libnet.a

#LIBS += rtc/librtc.a
LIBS += drivers/libdrivers.a

ifeq ($(RALINK_USB),ON)
LIBS += fs/fat/libfat.a
LIBS += disk/libdisk.a
endif

ifeq ($(MTK_USB),ON)
LIBS += fs/fat/libfat.a
LIBS += disk/libdisk.a
endif

#LIBS += post/libpost.a post/cpu/libcpu.a
LIBS += common/libcommon.a
.PHONY : $(LIBS)

# Add GCC lib
PLATFORM_LIBS += -L $(shell dirname `$(CC) $(CFLAGS)  -print-libgcc-file-name`)

# The "tools" are needed early, so put this first
# Don't include stuff already done in $(LIBS)
ifneq ($(CFG_ENV_IS), IN_FLASH)
SUBDIRS	= tools
else
SUBDIRS	=
endif
.PHONY : $(SUBDIRS)

#########################################################################
#########################################################################

ALL = u-boot.srec uboot.bin System.map
ifneq ($(CFG_ENV_IS), IN_FLASH)
ALL += uboot.img
endif
ifeq ($(MT7621_MP), y)
ALL += uboot_a.bin
endif

all:		clean $(ALL)

u-boot.hex:	u-boot
		$(OBJCOPY) ${OBJCFLAGS} -O ihex $< $@


u-boot.srec:	u-boot
		$(OBJCOPY) ${OBJCFLAGS} -O srec $< $@

ifeq ($(MT7621_MP), y)
ifeq ($(CFG_ENV_IS), IN_NAND)
uboot_a.bin:	uboot.bin mt7621_stage_L2.bin
		cp mt7621_stage_L2.bin uboot_a.bin
ifeq ($(MT7621_CPU_800MHZ), y)
		echo "0 725a00c0"|xxd -r|dd bs=1 seek=32 of=uboot_a.bin conv=notrunc
endif
ifeq ($(MT7621_CPU_900MHZ), y)
		echo "0 c25a00c0"|xxd -r|dd bs=1 seek=32 of=uboot_a.bin conv=notrunc
endif
ifeq ($(MT7621_CPU_875MHZ), y)
		echo "0 224a00c0"|xxd -r|dd bs=1 seek=32 of=uboot_a.bin conv=notrunc
endif
ifeq ($(DDR_ACT_SETTING), y)		
		./mt7621_ddr.sh uboot_a.bin uboot_a.bin mt7621_ddr_param.txt $(DDR_CHIP) $(CFG_ENV_IS)
		echo "0 10"|xxd -r|dd bs=1 count=1 seek=38 of=uboot_a.bin conv=notrunc
endif
		echo "0 $(MT7621_DDR_SPEED)"|xxd -r|dd bs=1 count=1 seek=39 of=uboot_a.bin conv=notrunc
#SLT baudrate echo "0 00c20100"|xxd -r|dd bs=1 seek=304 of=uboot_a.bin conv=notrunc
		chmod 777 uboot_a.bin
		dd if=uboot.bin of=uboot_a.bin bs=1 count=$(shell stat -c %s uboot.bin) \
		seek=$(shell echo "(($(shell stat -c %s mt7621_stage_L2.bin)+4095)/4096)*4096-64" |bc) conv=notrunc
		cp uboot_a.bin uboot.bin
else
uboot_a.bin:	uboot.bin mt7621_stage_sram.bin
		cp uboot.bin uboot_a.bin
		chmod 777 uboot_a.bin
		dd if=mt7621_stage_sram.bin of=uboot_a.bin bs=1 count=$(shell stat -c %s mt7621_stage_sram.bin) \
		seek=$(shell stat -c %s uboot.bin)
ifeq ($(MT7621_CPU_800MHZ), y)
		echo "0 725a00c0"|xxd -r|dd bs=1 of=uboot_a.bin seek=$(shell echo "(($(shell stat -c %s uboot.bin)+32))" |bc)  conv=notrunc
endif
ifeq ($(MT7621_CPU_900MHZ), y)
		echo "0 c25a00c0"|xxd -r|dd bs=1 of=uboot_a.bin seek=$(shell echo "(($(shell stat -c %s uboot.bin)+32))" |bc)  conv=notrunc
endif
ifeq ($(MT7621_CPU_875MHZ), y)
		echo "0 224a00c0"|xxd -r|dd bs=1 of=uboot_a.bin seek=$(shell echo "(($(shell stat -c %s uboot.bin)+32))" |bc)  conv=notrunc

endif
		echo "0 $(MT7621_DDR_SPEED)"|xxd -r|dd bs=1 count=1 of=uboot_a.bin seek=$(shell echo "(($(shell stat -c %s uboot.bin)+39))" |bc) conv=notrunc	
ifeq ($(DDR_ACT_SETTING), y)	
		./mt7621_ddr.sh uboot_a.bin uboot_a.bin mt7621_ddr_param.txt $(DDR_CHIP) $(CFG_ENV_IS)
		echo "0 10"|xxd -r|dd bs=1 count=1 of=uboot_a.bin seek=$(shell echo "(($(shell stat -c %s uboot.bin)+38))" |bc) conv=notrunc
endif
#SLT baudrate echo "0 00c20100"|xxd -r|dd bs=1 of=uboot_a.bin seek=$(shell echo "(($(shell stat -c %s uboot.bin)+304))" |bc) conv=notrunc
		
		mv uboot_a.bin uboot.bin
endif		
endif

uboot.bin:	u-boot
		$(OBJCOPY) ${OBJCFLAGS} -O binary $< $@

ifneq ($(MT7621_MP), y)
uboot.img:	uboot.bin
ifeq ($(CFG_ENV_IS), IN_SPI)
		./tools/mkimage -A $(ARCH) -T standalone -C none \
		-a $(TEXT_BASE) -e $(shell readelf -h u-boot | grep "Entry" | awk '{print $$4}') \
		-n "$(shell echo $(CFG_ENV_IS) | sed -e 's/IN_//') Flash Image" \
		-r $(DRAM_TYPE) -s $(DRAM_TOTAL_WIDTH) -t $(DRAM_SIZE) -u $(DRAM_WIDTH) \
		-y $(DRAM_SYSCFG0) -z $(DRAM_SYSCFG1) -w $(CPU_PLL_CFG) -d $< $@
endif
else
uboot.img:	uboot_a.bin
endif
#ifeq ($(CFG_ENV_IS), IN_NAND)
#		$(MAKE) -C stage1
#endif
ifeq ($(CFG_ENV_IS), IN_NAND)
ifneq ($(MT7621_MP), y)
		./tools/mkimage -A $(ARCH) -T standalone -C none \
		-a $(TEXT_BASE) -e $(shell readelf -h u-boot | grep "Entry" | awk '{print $$4}') \
		-n "$(shell echo $(CFG_ENV_IS) | sed -e 's/IN_//') Flash Image" \
		-r $(DRAM_TYPE) -s $(DRAM_TOTAL_WIDTH) -t $(DRAM_SIZE) -u $(DRAM_WIDTH) \
		-y $(DRAM_SYSCFG0) -z $(DRAM_SYSCFG1) -d $< $@
else
		./tools/mkimage -A $(ARCH) -T standalone -C none \
		-a $(TEXT_BASE) -e $(shell readelf -h u-boot | grep "Entry" | awk '{print $$4}') \
		-n "$(shell echo $(CFG_ENV_IS) | sed -e 's/IN_//') Flash Image" \
		-r $(DRAM_TYPE) -s $(DRAM_TOTAL_WIDTH) -t $(DRAM_SIZE) -u $(DRAM_WIDTH) \
		-y $(shell echo "40") \
		-z $(shell echo "obase=16;(($(shell stat -c %s mt7621_stage_L2.bin)+64+4095)/4096)*4096" |bc) -d $< $@
		@rm -fr uboot_a.bin
endif
endif

		@echo ""
		@echo "===============<<IMPORTANT>>=================="
ifeq ($(ON_BOARD_NAND_FLASH_COMPONENT),y)
		@echo "Notes:Uboot firmware is uboot.img NOT uboot.bin"
		@rm -f uboot.bin
endif
ifeq ($(ON_BOARD_NOR_FLASH_COMPONENT),y)
		@echo "Notes:Uboot firmware is uboot.bin NOT uboot.img"
		@rm -f uboot.img
endif
ifeq ($(ON_BOARD_SPI_FLASH_COMPONENT),y)
ifeq ($(UBOOT_ROM),y)
		@echo "Notes:Uboot firmware is uboot.bin NOT uboot.img"
		@rm -f uboot.img
else
ifeq ($(UBOOT_RAM),y)
		@echo "Notes:Uboot firmware in flash is uboot.img NOT uboot.bin"
		@rm -f uboot.bin
endif
endif
endif
		@echo "================================================"
		@echo ""

u-boot.dis:	u-boot
		$(OBJDUMP) -d $< > $@

#u-boot:		depend $(SUBDIRS) $(OBJS) $(LIBS) $(LDSCRIPT)
#		UNDEF_SYM=`$(OBJDUMP) -x $(LIBS) |sed  -n -e 's/.*\(__u_boot_cmd_.*\)/-u\1/p'|sort|uniq`;\
#		$(LD) $(LDFLAGS) $$UNDEF_SYM $(OBJS) \
#			--start-group $(LIBS) --end-group -L $(shell dirname) $(CC) $(CFLAGS) -print-libgcc-file-name -lgcc \
#			-Map u-boot.map -o u-boot 
			
u-boot:		depend $(SUBDIRS) $(OBJS) $(LIBS) $(LDSCRIPT)
		UNDEF_SYM=`$(OBJDUMP) -x $(LIBS) |sed  -n -e 's/.*\(__u_boot_cmd_.*\)/-u\1/p'|sort|uniq`;\
		$(LD) $(LDFLAGS) $$UNDEF_SYM $(OBJS) \
			--start-group $(LIBS) --end-group $(PLATFORM_LIBS) \
			-Map u-boot.map -o u-boot
			
show_path:
	echo $(OBJDUMP)

$(LIBS):
		$(MAKE) -C `dirname $@`
		echo $(MAKE) -C `dirname $@`

$(SUBDIRS):
		$(MAKE) -C $@ all
		echo $(MAKE) -C $@ all

gdbtools:
		$(MAKE) -C tools/gdb || exit 1

depend dep:
		@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir .depend ; done

tags:
		ctags -w `find $(SUBDIRS) include \
				lib_generic board/$(BOARDDIR) cpu/$(CPU) lib_$(ARCH) \
				fs/cramfs fs/fat fs/fdos fs/jffs2 \
				net disk rtc dtt drivers drivers/sk98lin common \
			\( -name CVS -prune \) -o \( -name '*.[ch]' -print \)`

etags:
		etags -a `find $(SUBDIRS) include \
				lib_generic board/$(BOARDDIR) cpu/$(CPU) lib_$(ARCH) \
				fs/cramfs fs/fat fs/fdos fs/jffs2 \
				net disk rtc dtt drivers drivers/sk98lin common \
			\( -name CVS -prune \) -o \( -name '*.[ch]' -print \)`

System.map:	u-boot
		@$(NM) $< | \
		grep -v '\(compiled\)\|\(\.o$$\)\|\( [aUw] \)\|\(\.\.ng$$\)\|\(LASH[RL]DI\)' | \
		sort > System.map

#########################################################################
else
all install u-boot u-boot.srec depend dep:
	@echo "System not configured - see README" >&2
	@ exit 1
endif

#########################################################################

unconfig:
	@rm -f board/*/config.tmp .config .tmp_config System.map autoconf.h

rt2880_config: unconfig
	@./mkconfig $(@:_config=) mips ralink_soc rt2880



clean:
	find . -type f \
		\( -name 'core' -o -name '*.bak' -o -name '*~' \
		-o -name '*.o'  -o -name '*.a'  \) -print \
		| xargs rm -f
	find ./ -name '.depend' -print | xargs rm -f

	rm -f examples/hello_world examples/timer \
	      examples/eepro100_eeprom examples/sched \
	      examples/mem_to_mem_idma2intr examples/82559_eeprom
	rm -f tools/img2srec tools/mkimage tools/envcrc tools/gen_eth_addr
	rm -f tools/mpc86x_clk tools/ncb
	rm -f tools/easylogo/easylogo tools/bmp_logo
	rm -f tools/gdb/astest tools/gdb/gdbcont tools/gdb/gdbsend
	rm -f tools/env/fw_printenv tools/env/fw_setenv
	rm -f board/cray/L1/bootscript.c board/cray/L1/bootscript.image
	rm -f board/trab/trab_fkt
	rm -f stage1/stage2.bin stage1/stage1n2.elf stage1/stage1n2.map
	rm -f ./uboot.bin ./uboot.img ./u-boot ./u-boot.* ./uboot_a.bin ./System.map
	rm -f scripts/lxdialog/lxdialog
	rm -f httpd/fsdata.c

clobber:	clean
	find . -type f \( -name .depend \
		-o -name '*.srec' -o -name 'uboot.bin' -o -name u-boot.img \) \
		-print0 \
		| xargs -0 rm -f
	rm -f $(OBJS) *.bak tags TAGS
	rm -fr *.*~
	rm -f u-boot u-boot.map u-boot.hex $(ALL)

mrproper \
distclean:	clobber unconfig

backup:
	F=`basename $(TOPDIR)` ; cd .. ; \
	gtar --force-local -zcvf `date "+$$F-%Y-%m-%d-%T.tar.gz"` $$F

menuconfig: clean config.in
	$(MAKE) -C scripts/lxdialog all
	$(CONFIG_SHELL) scripts/Menuconfig config.in

silentconfig: clean config.in
	$(MAKE) -C scripts/lxdialog all
	$(CONFIG_SHELL) scripts/Menuconfig config.in quiet

#########################################################################
