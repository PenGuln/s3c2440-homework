#ifndef  __DCM_H__
#define __DCM_H__

void Delay(int t);
void* start_motor(void* data);

#endif

#ifndef CONFIG_H
#define CONFIG_H

#define DCM_IOCTRL_SETPWM (0x10)
#define DCM_TCNTB0 (16384)
static int dcm_fd = -1;
static char *DCM_DEV ="/dev/s3c2440-dc-motor0";
static char OVER = 0;

#endif // CONFIG_H
