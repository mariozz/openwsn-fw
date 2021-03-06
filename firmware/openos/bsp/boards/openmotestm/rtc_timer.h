/**
\brief Cross-platform declaration "radiotimer" bsp module.

\author Thomas Watteyne <watteyne@eecs.berkeley.edu>, February 2012.
*/

#ifndef __RADIOTIMER_H
#define __RADIOTIMER_H

#include "stdint.h"
#include "board.h"

//=========================== define ==========================================

//=========================== typedef =========================================

typedef void (*radiotimer_compare_cbt)();
typedef void (*radiotimer_capture_cbt)(PORT_TIMER_WIDTH timestamp);

//=========================== variables =======================================

//=========================== prototypes ======================================

// admin
void     radiotimer_init();
void     radiotimer_setOverflowCb(radiotimer_compare_cbt cb);
void     radiotimer_setCompareCb(radiotimer_compare_cbt cb);
void     radiotimer_setStartFrameCb(radiotimer_capture_cbt cb);
void     radiotimer_setEndFrameCb(radiotimer_capture_cbt cb);
void     radiotimer_start(u32 period);
// direct access
u32 radiotimer_getValue();
void     radiotimer_setPeriod(u32 period);
u32 radiotimer_getPeriod();
// compare
void     radiotimer_schedule(u32 period,u32 offset);
void     radiotimer_cancel();
// capture
u32 radiotimer_getCapturedTime();


uint8_t  radiotimer_isr();

#endif
