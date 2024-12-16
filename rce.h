#ifndef RCE_H
#define RCE_H
#include <time.h>

#define MAX_TOUCHSCREEN_NUM 32 // Let's assume no one has 32 touchscreens

extern struct timespec LONG_CLICK_INTERVAL;
extern int LONG_CLICK_FUZZ;
extern int TOUCH_DEVICE_GRAB;
#endif