#ifndef __ICMPv6RPL_H
#define __ICMPv6RPL_H

/**
\addtogroup IPv6
\{
\addtogroup ICMPv6RPL
\{
*/

//=========================== define ==========================================

#define TIMER_DIO_TIMEOUT         1700
#define TIMER_DAO_TIMEOUT         10000

#define MOP_DIO_A                 1<<5
#define MOP_DIO_B                 1<<4
#define MOP_DIO_C                 1<<3
#define PRF_DIO_A                 0<<2
#define PRF_DIO_B                 0<<1
#define PRF_DIO_C                 0<<0
#define G_DIO                     1<<7

#define FLAG_DAO_A                0<<0
#define FLAG_DAO_B                0<<1
#define FLAG_DAO_C                0<<2
#define FLAG_DAO_D                0<<3
#define FLAG_DAO_E                0<<4
#define FLAG_DAO_F                0<<5
#define D_DAO                     1<<6
#define K_DAO                     0<<7

#define E_DAO_Transit_Info        0<<7

#define PC1_A_DAO_Transit_Info    0<<7
#define PC1_B_DAO_Transit_Info    1<<6

#define PC2_A_DAO_Transit_Info    0<<5
#define PC2_B_DAO_Transit_Info    0<<4

#define PC3_A_DAO_Transit_Info    0<<3
#define PC3_B_DAO_Transit_Info    0<<2

#define PC4_A_DAO_Transit_Info    0<<1
#define PC4_B_DAO_Transit_Info    0<<0

#define Prf_A_dio_options         0<<4
#define Prf_B_dio_options         0<<3

enum{
  OPTION_ROUTE_INFORMATION_TYPE   = 0x03,
  OPTION_DODAG_CONFIGURATION_TYPE = 0x04,
  OPTION_TARGET_INFORMATION_TYPE  = 0x05,
  OPTION_TRANSIT_INFORMATION_TYPE = 0x06,
};

//=========================== static ==========================================

/**
\brief Well-known IPv6 multicast address for "all routers".
*/
static const uint8_t all_routers_multicast[] = {
   0xff, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02
};

//=========================== typedef =========================================

//===== DIO

/**
\brief Header format of a RPL DIO packet.
*/
PRAGMA(pack(1));
typedef struct {
   uint8_t         rplinstanceId;      ///< set by the DODAG root.
   uint8_t         verNumb;
   dagrank_t       rank;
   uint8_t         rplOptions;
   uint8_t         DTSN;
   uint8_t         flags;
   uint8_t         reserved;
   uint8_t         DODAGID[16];    
} icmpv6rpl_dio_ht;
PRAGMA(pack());

//===== DAO

/**
\brief Header format of a RPL DAO packet.
*/
PRAGMA(pack(1));
typedef struct {
   uint8_t         rplinstanceId;      ///< set by the DODAG root.
   uint8_t         K_D_flags;
   uint8_t         reserved;
   uint8_t         DAOSequance;
   uint8_t         DODAGID[16];
} icmpv6rpl_dao_ht;
PRAGMA(pack());

/**
\brief Header format of a RPL DAO "Transit Information" option.
*/
PRAGMA(pack(1));
typedef struct {
   uint8_t         type;               ///< set by the DODAG root.
   uint8_t         optionLength;
   uint8_t         E_flags;
   uint8_t         PathControl;
   uint8_t         PathSequence;   
   uint8_t         PathLifetime;   
} icmpv6rpl_dao_transit_ht;
PRAGMA(pack());

/**
\brief Header format of a RPL DAO "Target" option.
*/
PRAGMA(pack(1));
typedef struct {
   uint8_t         type;               ///< set by the DODAG root.
   uint8_t         optionLength;
   uint8_t         flags;
   uint8_t         prefixLength;  
} icmpv6rpl_dao_target_ht;
PRAGMA(pack());


//=========================== prototypes ======================================

void icmpv6rpl_init();
void icmpv6rpl_sendDone(OpenQueueEntry_t* msg, error_t error);
void icmpv6rpl_receive(OpenQueueEntry_t* msg);

/**
\}
\}
*/

#endif
