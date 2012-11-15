/* 
 * File:   cst417.h
 * Author: Tyler
 *
 * Created on November 8, 2012, 12:43 PM
 */
#include "GenericTypeDefs.h"
#ifndef CST417_H
#define	CST417_H

#ifdef	__cplusplus
extern "C" {
#endif
// For a CST417_PACKET, the first two bytes are DST and SRC Node_IDs. They
// are followed by the Operation and the Data fields.
//
// Operation field (2 bytes) is defined as follows:
// 0 - Request MAC address from Node_ID (Sent to ff-ff-ff-ff-ff-ff)
// 1 - Reply from Node_ID with MAC Address (Sent to re-qu-es-te-rM-AC)
// 2 - Control LED at Node_ID (Sent to co-nt-ro-le-dM-AC)
//
// The 10 bytes of data will be populated based on Operation:
// 0 - 0 bytes = No data
// 1 - 6 bytes = Src MAC Address
// 2 - 3 bytes = LED control value: 1 -> ON, 0 -> OFF
typedef struct __attribute__((aligned(2), packed))
{
    WORD        Operation;   // operation code
    BYTE        Data[10];     // holds 10 bytes of data dependant on the opcode

} CST417_PACKET;

void CST417SendEth(CST417_PACKET * packet);
#ifdef	__cplusplus
}
#endif

#endif	/* CST417_H */

