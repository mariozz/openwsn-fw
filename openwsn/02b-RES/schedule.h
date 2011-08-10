/*
 * Manages the IEEE802.15.4e schedule
 *
 * Authors:
 * Thomas Watteyne <watteyne@eecs.berkeley.edu>, August 2011
 */

#ifndef __SCHEDULE_H
#define __SCHEDULE_H

#include "openwsn.h"

typedef uint8_t   cellType_t;
typedef uint8_t   channelOffset_t;

enum {
   CELLTYPE_OFF         = 0,
   CELLTYPE_ADV         = 1,
   CELLTYPE_TX          = 2,
   CELLTYPE_RX          = 3,
   CELLTYPE_RXSERIAL    = 4
};

typedef struct cellUsageInformation_t {
   uint8_t        type;
   uint8_t        channelOffset;
   open_addr_t    neighbor;
   uint8_t        numUsed;
   uint8_t        numTxACK;
   timervalue_t   timestamp;
} cellUsageInformation_t;

typedef struct debugCellUsageInformation_t {
   uint8_t                row;
   cellUsageInformation_t cellUsage;
} debugCellUsageInformation_t;

void            schedule_init();
cellType_t      schedule_getType(asn_t asn_param);
channelOffset_t schedule_getChannelOffset(asn_t asn_param);
void            schedule_getNeighbor(asn_t asn_param, open_addr_t* addrToWrite);
bool            schedule_debugPrint();

#endif
