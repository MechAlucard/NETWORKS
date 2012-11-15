#include "cst417.h"
#include "TCPIP Stack/TCPIP.h"
#define TYLER_CODE 0x65
void CST417SendEth(CST417_PACKET * packet)
{
    while(!MACIsTxReady());
	MACSetWritePtr(BASE_TX_ADDR);
        //packet->Operation;
        //set to broadcast
        MAC_ADDR TargetMACAddr ={0x00,0xff,0xff,0xff,0xff,0xff,0xff};// {0xff,0xff,0xff,0xff,0xff,0xff,0xff};
    CST417PutHeader(&TargetMACAddr, MAC_ARP, sizeof(*packet));
    MACPutArray((BYTE*)packet, sizeof(*packet));
    MACFlush();
}
