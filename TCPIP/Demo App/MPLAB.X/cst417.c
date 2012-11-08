#include "cst417.h"
#include "TCPIP Stack/TCPIP.h"
static BOOL CST417SendEth(CST417_PACKET * packet)
{
    while(!MACIsTxReady());
	MACSetWritePtr(BASE_TX_ADDR);
        //packet->Operation;

    //memcpy(&packet->SenderMACAddr, (void*)&AppConfig.MyMACAddr, sizeof(packet->SenderMACAddr));
#ifdef STACK_USE_ZEROCONF_LINK_LOCAL
    //packet->SenderIPAddr  = AppConfig.MyIPAddr; /* Removed for ZCLL, SenderIPAddr should be filled in */
#else
   // packet->SenderIPAddr  = AppConfig.MyIPAddr;
#endif

    //SwapARPPacket(packet);

    //MACPutHeader(&packet->TargetMACAddr, MAC_ARP, sizeof(*packet));
    MACPutArray((BYTE*)packet, sizeof(*packet));
    MACFlush();

	return TRUE;
}
