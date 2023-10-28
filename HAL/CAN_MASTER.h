/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  -
 *         File:  CAN_MASTER.h
 *        Layer:  HAL
 *       Module:  CAN_MASTER
 *      Version:  1.00
 *
 *  Description:  CAN Master Message using CAN0
 *
 *********************************************************************************************************************/


#ifndef HAL_CAN_CAN_MASTER_H_
#define HAL_CAN_CAN_MASTER_H_


/*******************************************************************************
 *                                includes                                     *
 *******************************************************************************/

#include <Utilities/std_types.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/can.h"



/***************************************************************************************************
*                                           Global variables                                       *
****************************************************************************************************/
extern volatile uint32 tx_intrrpt_msg_count; /* counter to keep track of times tx interrupt occurred */
extern volatile uint8 tx_error_flag; /* flag to indicate that some transmission error occurred */
extern volatile uint8 tx_status_flag; /* flag to indicate that a reset request is sent */

extern uint32_t tx_clock_source; /* clock source in Hz */

extern tCANMsgObject tx_msg_object1; /* CAN message object for reset */
extern tCANMsgObject tx_msg_object2; /* CAN message object for flash*/
extern tCANMsgObject tx_msg_object3; /* CAN message object for data*/
extern tCANMsgObject tx_msg_object4; /* CAN message object for done*/

extern uint8 tx_msg_obj_no1; /* CAN message using object number 1 */
extern uint8 tx_msg_obj_no2; /* CAN message using object number 2 */
extern uint8 tx_msg_obj_no3; /* CAN message using object number 3 */
extern uint8 tx_msg_obj_no4; /* CAN message using object number 4 */




extern uint8 tx_data_reset; /* CAN message reset data -> 1 byte */
extern uint8 tx_data_flash; /* CAN message flash data -> 1 byte */
extern uint8 tx_data_done; /* CAN message done data -> 1 byte */
extern uint8 tx_msg_data[]; /*Message data*/


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/***************************************************************************************************
* Function Name: Delay
* Parameters (in): uint32 milliseconds
* Return value: void
* Description: Delay in milliseconds according the the clock source
****************************************************************************************************/
void Delay(uint32 milliseconds);

/***************************************************************************************************
* Function Name: MasterCANInit
* Parameters (in): void
* Return value: void
* Description: CAN initialization to initializes the message objects to a safe state prior to
*              enabling the controller on the CAN bus and bit timing values must be programmed
*              prior to enabling the CAN controller.
****************************************************************************************************/
void MasterCANInit(void);

/***************************************************************************************************
* Function Name: MasterCANMessage
* Parameters (in): void
* Return value: void
* Description: CAN Message to configure a message object to send data where each message
*              object can be configured to generate interrupts on transmission.
****************************************************************************************************/
void MasterCANMessage(void);


/***************************************************************************************************
* Function Name: MasterCANIntHandler
* Parameters (in): void
* Return value: void
* Description: CAN Interrupt Handler to process CAN interrupts
****************************************************************************************************/
void MasterCANIntHandler(void);



#endif /* HAL_CAN_CAN_MASTER_H_ */
