/*
 *	Copyright 1994, 1995, 2000 Neil Russell.
 *	(See License)
 *	Copyright 2000, 2001 DENX Software Engineering, Wolfgang Denk, wd@denx.de
 */

#include <common.h>
#include <command.h>
#include <net.h>
#include <asm/byteorder.h>
#include <tpLinuxTag.h>
#include "httpd.h"

#include "../httpd/uipopt.h"
#include "../httpd/uip.h"
#include "../httpd/uip_arp.h"

static int arptimer = 0;
#define TAG_LEN         512

int upgrade_filecheck(unsigned char * ptr, int size){

	if (size > 0x800000 || size < 0x20000)
	{
		printf("size 0x%X is illegal!\n", size);
		return -1;
	}
	
	return(0);
}

void HttpdHandler(void){
	int i;

	for(i = 0; i < UIP_CONNS; i++){
		uip_periodic(i);

		if(uip_len > 0){
			uip_arp_out();
			NetSendHttpd();
		}
	}

	if(++arptimer == 20){
		uip_arp_timer();
		arptimer = 0;
	}
}

// start http daemon
void HttpdStart(void){
	uip_init();
	httpd_init(upgrade_filecheck);
}

static int existSupportList(LINUX_FILE_TAG *pImageTag)
{
    if ((pImageTag->supportListAddress != 0xFFFFFFFF) && (pImageTag->supportListLen != 0xFFFFFFFF))
    {
        return 1;
    }
    return 0;
}


int tpFirmwareRecovery(unsigned char *ptr,int bufsize)
{
	unsigned int len = 0;
	LINUX_FILE_TAG * pImageTag = ptr;

	if (existSupportList(ptr))
	{
		bufsize -= ntohl(pImageTag->supportListLen);
	}

	ptr += TAG_LEN;
	bufsize -= TAG_LEN;

	len = raspi_erase(FACTORY_UBOOT_SIZE, bufsize);
	if (len < 0)
	{
		printf("erase flash error!.\n");
		return -1;
	}
	len = raspi_write(ptr, FACTORY_UBOOT_SIZE, bufsize);

	printf("bufsize %x, len %x\n", bufsize, len);
	if (len != bufsize)
		return -1;
	ubootArgs * pargs = ptr;
	memset(pargs, 0, sizeof(ubootArgs));
	if (raspi_erase_write(pargs, DUAL_UBOOT_ARGS_ADDR, sizeof(ubootArgs)))
	{
		return -1;
	}
	
	return 0;
}


int do_http_upgrade(const ulong size, const int upgrade_type){
	int ret;
	printf("do http upgrade\n");
	if(upgrade_type == WEBFAILSAFE_UPGRADE_TYPE_FIRMWARE){
		
		ret = tpFirmwareRecovery((unsigned char *)WEBFAILSAFE_UPLOAD_RAM_ADDRESS, (int)size);
		if (ret == 0)
		{
			return(0);
		}
	}

	printf("Web recovery failed type %d.\n", upgrade_type);

	return(-1);
}

// info about current progress of failsafe mode
int do_http_progress(const int state){
	/* toggle LED's here */
	switch(state){
		case WEBFAILSAFE_PROGRESS_START:
			printf("HTTP server is ready!\n\n");
			break;

		case WEBFAILSAFE_PROGRESS_TIMEOUT:
			//printf("Waiting for request...\n");
			break;

		case WEBFAILSAFE_PROGRESS_UPLOAD_READY:
			printf("HTTP upload is done! Upgrading...\n");
			break;

		case WEBFAILSAFE_PROGRESS_UPGRADE_READY:
			printf("HTTP ugrade is done! Rebooting...\n\n");
			break;

		case WEBFAILSAFE_PROGRESS_UPGRADE_FAILED:
			printf("## Error: HTTP ugrade failed!\n\n");
			break;

		case WEBFAILSAFE_PROGRESS_CHECK_FAILED:
			printf("## Error: HTTP upgrade file check failed!\n\n");
			break;
			
		default:
			printf("## Error: Wrong state!\n\n");
			break;
	}

	return(0);
}
