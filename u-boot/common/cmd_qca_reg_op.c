/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <net.h>

#define PRT(format, args...) printf("""[====%s: %d======]"format"\n",__FUNCTION__, __LINE__,  ##args);


/* -------------------------------------------------------------------- */
int do_qca_reg_op (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	u32	reg = 0; 
	u32 value = 0;
	
	if (argc < 2) {
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	reg = simple_strtoul(argv[2], NULL, 16);

	if(strncmp(argv[1], "get", 3))
	{
		/* Set register. */
		value = simple_strtoul(argv[3], NULL, 16);
		qca8337_write_register(reg, value);
	}
	else
	{
		/* Get register. */
		qca8337_read_register(reg, &value);
		printf("reg %x	value %x\n", reg, value);
	}
	return 0;
}

/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	regop, CFG_MAXARGS, 1,	do_qca_reg_op,
	"regop      - set or get register's value of switch(qca8337)\n",
	"regoff [arg...]\n    - set or get the register value of 'regoff'.\n"
	"      passing 'arg' as argument for set.\n"
);
