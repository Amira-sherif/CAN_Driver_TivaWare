#include "HAL/CAN_SLAVE.h"
#include "HAL/CAN_MASTER.h"
int main(void)
{
    /*Master*/
     MasterCANInit();    /*CAN FOR THE MASTER NODE*/
     int i = 0;
//     tx_status_flag++;
     for (i = 0; i < 4; ++i) {
         MasterCANMessage();
         tx_status_flag++;
    }

//     SlaveCANInit();
//     while(1)
//     {
//         SlaveCANMessage();
//
//     }

     while(1);

}
