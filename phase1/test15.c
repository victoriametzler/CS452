#include <stdio.h>	
#include "phase1.h"
#include <malloc.h>

/*  Test Case to test Basic Interrupt Handling, Disk interrupt Handler, Disk Device Semaphore using Disk Write

Output:

---------Starting Test 15 ----------
status from WaitDevice is 0
Request Completed Succesfully 
 ---------Ending Test 15 ----------

*/ 

	
int P2_Startup(void *arg) {
	
	USLOSS_Console(" \n---------Starting Test 15 ----------\n");
	
	int status;
	USLOSS_DeviceRequest *req = (USLOSS_DeviceRequest *)malloc(sizeof(USLOSS_DeviceRequest)); //Needed to pass to USLOSS_DeviceOutput
	req = (USLOSS_DeviceRequest *)malloc(sizeof(USLOSS_DeviceRequest)); //Needed to pass to USLOSS_DeviceOutput
	req->opr = USLOSS_DISK_WRITE; // Fill the request indicating the operation to be done on the disk
	req->reg1 = 1; // Sector to be written 
	char *buf = (char *)malloc(512); // Buffer that holds the characters to be written
	buf[0] = 'a';
	buf[1] = '\0';
	req->reg2 = buf; //Set the buffer in the request
	USLOSS_DeviceOutput(USLOSS_DISK_DEV, 1, req); // Write to Disk, unit 1, Request obj..that contains all the information needed to be done on the Disk.
	P1_WaitDevice(USLOSS_DISK_DEV, 1, &status); // Wait for the interrupt to occur
	USLOSS_Console("status from WaitDevice is %d \n", status);// Retrieve the status
	if(status == USLOSS_DEV_READY) // For Disk device, this implies the request completed
		USLOSS_Console("Request Completed Succesfully \n");
	
	USLOSS_Console(" ---------Ending Test 15 ----------\n");
	P1_Quit(0);
}
