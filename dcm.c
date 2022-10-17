#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include "dcm.h"
void Delay(int t)
{
    int i;
    for(;t>0;t--)
        for(i=0;i<400;i++);
}

void* start_motor(void*data){
    int i = 0;
    int status = 1;
    int setpwm = 0;
    int factor = DCM_TCNTB0/1024;
    
    if((dcm_fd=open(DCM_DEV, O_WRONLY))<0){
        printf("Error opening %s device\n", DCM_DEV);

    }
    int tim = 0;
        for (i=-30; i<=30; i++) {
            if(status == 1)
                setpwm = i;
            else
                setpwm = -i;
            ioctl(dcm_fd, DCM_IOCTRL_SETPWM, (setpwm * factor));
            Delay(500);
            //printf("setpwm = %d \n", setpwm);
        }
        status = -status;

    close(dcm_fd);
}
