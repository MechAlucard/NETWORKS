#include "cst417.h"
#include "TCPIP Stack/TCPIP.h"
#define B
#ifdef A
#define TYLER_CODE 0x65
#endif
#ifdef B
#define TYLER_CODE 0x67
#endif
#define REQUEST 0
#define REPLY 1
#define CONTROL 2
#define TABLE_SIZE 15
CST417Node AddressTable[TABLE_SIZE];
int table_end = 0;
void CST417SendEth(CST417_PACKET * packet)
{
    while(!MACIsTxReady());
	MACSetWritePtr(BASE_TX_ADDR);
    MAC_ADDR TargetMACAddr;
   // memset(TargetMACAddr.v,0xff,6);
   GetAddress(&TargetMACAddr, packet->Destination);

    CST417PutHeader(&TargetMACAddr, MAC_ARP, sizeof(*packet));
    MACPutArray((BYTE*)packet, sizeof(*packet));
    MACFlush();
}
void CST417Process()
{
    MAC_ADDR source;
    BYTE type;
    CST417_PACKET packet;
    //MACGetHeader(&source,&type);
    MACGetArray((BYTE*)&packet, sizeof(packet));
    MACDiscardRx();
  
    
    //see if packet was sent to the device
    if(packet.Destination == TYLER_CODE)
    // request mac address from Node_ID
    {
        if(packet.Operation == REQUEST)
        {
            dbg("request recived\n");
            CST417_PACKET send;
            send.Operation = REPLY;
            send.Destination = packet.Source;
            send.Source = TYLER_CODE;
            memcpy(send.Data,AppConfig.MyMACAddr.v,sizeof(MAC_ADDR));
            CST417SendEth(&send);
        }
        //Reply from Node_ID with mac
        else if(packet.Operation == REPLY)
        {
            dbg("reply recived\n");
            AddAddress(packet.Data,packet.Source);
        }
        //control LED at Node_ID
        else if(packet.Operation == CONTROL)
        {
            dbg("control recived\n");
            //if(packet. == TYLER_CODE)
            {
             
                    LED0_IO = packet.Data[0];
                    LED1_IO = packet.Data[1];
                    LED2_IO = packet.Data[2];
            }
        }
    }
}
//if MAC is found based on node id it is returned If not, it is set to broadcast
void GetAddress(MAC_ADDR * address, BYTE node)
{
    int i = 0;
    while (i <= table_end)
    {
        if (AddressTable[i].Node_id == node)
        {
            memcpy(address->v,&AddressTable[i].Address,sizeof(MAC_ADDR));
            return;
        }
        i++;
    }
    memset(address->v,0xff,6);
    return;
}
//adds and address and node_id pair if node_id does not exist
//returns true if found, false if not
BOOL AddAddress(BYTE * address, BYTE node)
{
    int i = 0;
    while( i <= table_end)
    {
        if(node == AddressTable[i].Node_id)
        {
            return TRUE;
        }
        i++;
    }
    if(table_end < TABLE_SIZE)
    {
        AddressTable[table_end].Node_id = node;
        memcpy(AddressTable[table_end].Address.v,address,sizeof(MAC_ADDR));
        table_end++;
    }
    return FALSE;
}