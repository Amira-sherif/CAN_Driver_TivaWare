///**********************************************************************************************************************
// *  FILE DESCRIPTION
// *  -------------------------------------------------------------------------------------------------------------------
// *       Author:  -
// *         File:  CAN_SLAVE.h
// *        Layer:  HAL
// *       Module:  CAN_SLAVE
// *      Version:  1.00
// *
// *  Description:  CAN Salve Message using CAN0
// *
// *********************************************************************************************************************/
//
//
//
//#ifndef HAL_CAN_CAN_SLAVE_H_
//#define HAL_CAN_CAN_SLAVE_H_
//
///*******************************************************************************
// *                                includes                                     *
// *******************************************************************************/
//
//#include <Utilities/std_types.h>
//#include <stdbool.h>
//#include <stdint.h>
//#include "inc/hw_can.h"
//#include "inc/hw_ints.h"
//#include "inc/hw_memmap.h"
//#include "driverlib/gpio.h"
//#include "driverlib/interrupt.h"
//#include "driverlib/pin_map.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/can.h"
//
///***************************************************************************************************
//*                                           Global variables                                       *
//****************************************************************************************************/
//
//
//extern volatile uint32 rx_intrrpt_msg_count; /* counter to keep track of times rx interrupt occurred */
//extern volatile uint8 rx_msg_flag; /* flag to indicate that a message was received */
//extern volatile uint8 rx_error_flag; /* flag to indicate that some reception error occurred */
//extern volatile uint8 rx_status_flag; /* flag to indicate which status from the four is received */
//extern volatile uint8 rx_reset_flag; /* flag to indicate that a reset request is sent */
//extern volatile uint8 rx_flash_flag; /* flag to indicate that a flash request is sent */
//extern volatile uint8 rx_data_flag; /* flag to indicate that a data request is sent */
//extern volatile uint8 rx_done_flag; /* flag to indicate that a done request is sent */
//
//extern uint32 rx_clock_source; /* clock source in Hz */
//
//extern tCANMsgObject rx_msg_object1; /* CAN message object for reset */
//extern tCANMsgObject rx_msg_object2; /* CAN message object for flash*/
//extern tCANMsgObject rx_msg_object3; /* CAN message object for data*/
//extern tCANMsgObject rx_msg_object4; /* CAN message object for done*/
//
//extern uint8 rx_msg_obj_no1; /* CAN message using object number 1 */
//extern uint8 rx_msg_obj_no2; /* CAN message using object number 2 */
//extern uint8 rx_msg_obj_no3; /* CAN message using object number 3 */
//extern uint8 rx_msg_obj_no4; /* CAN message using object number 4 */
//
//extern uint8 rx_data_reset; /* CAN message reset data -> 1 byte */
//extern uint8 rx_data_flash; /* CAN message flash data -> 1 byte */
//extern uint8 rx_data_done; /* CAN message done data -> 1 byte */
//extern uint8 rx_msg_data[10];  /* CAN message data -> 10 bytes */
//
///*******************************************************************************
// *                              Functions Prototypes                           *
// *******************************************************************************/
//
///***************************************************************************************************
//* Function Name: SlaveCANInit
//* Parameters (in): void
//* Return value: void
//* Description: CAN initialization to initializes the message objects to a safe state prior to
//*              enabling the controller on the CAN bus and bit timing values must be programmed
//*              prior to enabling the CAN controller.
//****************************************************************************************************/
//void SlaveCANInit(void);
//
///***************************************************************************************************
//* Function Name: SlaveCANMessage
//* Parameters (in): void
//* Return value: void
//* Description: CAN Message to configure a message object to send data where each message
//*              object can be configured to generate interrupts on transmission.
//****************************************************************************************************/
//void SlaveCANMessage(void);
//
//
///***************************************************************************************************
//* Function Name: SlaveCANIntHandler
//* Parameters (in): void
//* Return value: void
//* Description: CAN Interrupt Handler to process CAN interrupts
//****************************************************************************************************/
//void SlaveCANIntHandler(void);
//
//
//
//#endif /* HAL_CAN_CAN_SLAVE_H_ */
