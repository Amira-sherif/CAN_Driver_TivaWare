/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  -
 *         File:  CAN_MASTER.c
 *        Layer:  HAL
 *       Module:  CAN_MASTER
 *      Version:  1.00
 *
 *  Description:  CAN Master Message using CAN0
 *
 *********************************************************************************************************************/


/*******************************************************************************
 *                                includes                                     *
 *******************************************************************************/
#include <HAL/CAN_MASTER.h>
//#include"../app1_test.h"
//#include"../app2_test.h"
#include "app4_test_ledsInterrupt.h"
//#include "app3_test_sysInterrupt.h"



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DATA_LENGTH              (sizeof(app4_test_ledsInterrupt_image_0))
#define BIT_RATE                 500000 /* 500 kHz */
#define BLUE_LED                 0x04
#define RED_LED                  0x02
#define GREEN_LED                0x08
#define WHITE_LED                0x0E
#define RESET_REQUEST            1
#define FLASH_REQUEST            2
#define DATA_REQUEST             3
#define DONE_REQUEST             4
#define MESSAGE_LENGTH           1
#define MESSAGE_ID_MASK          0xFFFFFFFF
/***************************************************************************************************
*                                           Global variables                                       *
****************************************************************************************************/

volatile uint32 tx_intrrpt_msg_count = 0; /* counter to keep track of times tx interrupt occurred */
volatile uint8 tx_error_flag = 0; /* flag to indicate that some transmission error occurred */
volatile uint8 tx_status_flag = 1; /* flag to indicate that a reset request is sent */


uint32_t tx_clock_source = 0; /* clock source in Hz */

tCANMsgObject tx_msg_object1; /* CAN message object for reset */
tCANMsgObject tx_msg_object2; /* CAN message object for flash*/
tCANMsgObject tx_msg_object3; /* CAN message object for data*/
tCANMsgObject tx_msg_object4; /* CAN message object for done*/

uint8 tx_msg_obj_no1 = 1; /* CAN message using object number 1 */       //object ID not msg ID
uint8 tx_msg_obj_no2 = 2; /* CAN message using object number 2 */
uint8 tx_msg_obj_no3 = 3; /* CAN message using object number 3 */
uint8 tx_msg_obj_no4 = 4; /* CAN message using object number 4 */




uint8 tx_data_reset = 0x01; /* CAN message reset data -> 1 byte */
uint8 tx_data_flash = 0x02; /* CAN message flash data -> 1 byte */
uint8 tx_data_done = 0x04; /* CAN message done data -> 1 byte */
//uint8 tx_msg_data[] = {
//                            0x00,
//                            0x02,
//                            0x00,
//                            0x20,
//                            0x79,
//                            0x09,
//                            0x01,
//                            0x00,
//                            0x7f,
//                            0x09,
//}; /*Message data*/


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/***************************************************************************************************
* Function Name: Delay
* Parameters (in): uint32 milliseconds
* Return value: void
* Description: Delay in milliseconds according the the clock source
****************************************************************************************************/
void Delay(uint32 microSecond) {
    SysCtlDelay((tx_clock_source / 3) * (microSecond / 1000000.0f));
}


/***************************************************************************************************
* Function Name: MasterCANInit
* Parameters (in): void
* Return value: void
* Description: CAN initialization to initializes the message objects to a safe state prior to
*              enabling the controller on the CAN bus and bit timing values must be programmed
*              prior to enabling the CAN controller.
****************************************************************************************************/
void MasterCANInit(void){
    /* Systick and Clock Configuration */
//    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    tx_clock_source = SysCtlClockGet(); /* getting the actual configured system clock frequency in Hz*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {}
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    /* CAN Configuration */
    /* Set up CAN0 pins using PORTB */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB4_CAN0RX); /* CAN module 0 receive -> CAN0Rx on PB4 */
    GPIOPinConfigure(GPIO_PB5_CAN0TX); /* CAN module 0 transmit -> CAN0Tx on PB5 */

    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);  /* enable clock for CAN0 */
    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);/* Select the alternate (CAN) function for these pins */

    CANInit(CAN0_BASE); /* Initialize the CAN controller */
    CANBitRateSet(CAN0_BASE, tx_clock_source, BIT_RATE); /* Set up the bit rate for the CAN bus with 500 kHz */
    CANIntRegister(CAN0_BASE, MasterCANIntHandler); /* registers the interrupt handler in the interrupt vector table, and enables CAN interrupts on the interrupt controller*/
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS); /* Enables individual CAN controller interrupt sources */
    IntEnable(INT_CAN0); /* Enable the CAN interrupt on the processor (NVIC) */
    CANEnable(CAN0_BASE); /* Enable the CAN for operation */
    IntMasterEnable();

}


/***************************************************************************************************
* Function Name: MasterCANMessage
* Parameters (in): void
* Return value: void
* Description: CAN Message to configure a message object to send data where each message
*              object can be configured to generate interrupts on transmission.
****************************************************************************************************/
void MasterCANMessage(void){

    tx_msg_object1.ui32MsgID = RESET_REQUEST; /* The CAN message identifier used for 11 or 29 bit identifiers.*/
    tx_msg_object1.ui32MsgIDMask = MESSAGE_ID_MASK; /* The message identifier mask used when identifier filtering is enabled.*/
    tx_msg_object1.ui32MsgLen = MESSAGE_LENGTH; /* This value is the number of bytes of data in the message object.*/
    tx_msg_object1.ui32Flags = MSG_OBJ_TX_INT_ENABLE; /* This value holds various status flags and settings specified by tCANObjFlags. -> receive and transmit interrupts are enabled*/


    tx_msg_object2.ui32MsgID = FLASH_REQUEST; /* The CAN message identifier used for 11 or 29 bit identifiers.*/
    tx_msg_object2.ui32MsgIDMask = MESSAGE_ID_MASK; /* The message identifier mask used when identifier filtering is enabled.*/
    tx_msg_object2.ui32MsgLen = MESSAGE_LENGTH; /* This value is the number of bytes of data in the message object.*/
    tx_msg_object2.ui32Flags = MSG_OBJ_TX_INT_ENABLE; /* This value holds various status flags and settings specified by tCANObjFlags. -> receive and transmit interrupts are enabled*/


    tx_msg_object3.ui32MsgID = DATA_REQUEST; /* The CAN message identifier used for 11 or 29 bit identifiers.*/
    tx_msg_object3.ui32MsgIDMask = MESSAGE_ID_MASK; /* The message identifier mask used when identifier filtering is enabled.*/
    tx_msg_object3.ui32MsgLen = MESSAGE_LENGTH; /* This value is the number of bytes of data in the message object.*/
    tx_msg_object3.ui32Flags = MSG_OBJ_TX_INT_ENABLE; /* This value holds various status flags and settings specified by tCANObjFlags. -> receive and transmit interrupts are enabled*/


    tx_msg_object4.ui32MsgID = DONE_REQUEST; /* The CAN message identifier used for 11 or 29 bit identifiers.*/
    tx_msg_object4.ui32MsgIDMask = MESSAGE_ID_MASK; /* The message identifier mask used when identifier filtering is enabled.*/
    tx_msg_object4.ui32MsgLen = MESSAGE_LENGTH; /* This value is the number of bytes of data in the message object.*/
    tx_msg_object4.ui32Flags = MSG_OBJ_TX_INT_ENABLE; /* This value holds various status flags and settings specified by tCANObjFlags. -> receive and transmit interrupts are enabled*/



    if (tx_status_flag == RESET_REQUEST){

        tx_msg_object1.pui8MsgData = &tx_data_reset;
        CANMessageSet(CAN0_BASE, tx_msg_obj_no1, &tx_msg_object1, MSG_OBJ_TYPE_TX); /*Send the CAN message using object number 1*/


        if(tx_error_flag) /* Check the error flag to see if errors occurred */
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, RED_LED);
        }
        else /* If no errors */
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GREEN_LED);
        }
    }
    else if (tx_status_flag == FLASH_REQUEST){

        tx_msg_object2.pui8MsgData = &tx_data_flash;
        CANMessageSet(CAN0_BASE, tx_msg_obj_no2, &tx_msg_object2, MSG_OBJ_TYPE_TX); /*Send the CAN message using object number 1*/


        if(tx_error_flag) /* Check the error flag to see if errors occurred */
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, RED_LED);
        }
        else /* If no errors */
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GREEN_LED);
        }
    }
    else if (tx_status_flag == DATA_REQUEST)
    {
        uint32 msg_count = 0;
        while(msg_count < DATA_LENGTH) /* loop to send messages. A new message will be sent once per second*/
        {
            tx_msg_object3.pui8MsgData = (uint8 *) &app4_test_ledsInterrupt_image_0[msg_count];

            CANMessageSet(CAN0_BASE, tx_msg_obj_no3, &tx_msg_object3, MSG_OBJ_TYPE_TX); /*Send the CAN message using object number 1*/

            Delay(1000); /*delay 1 ms before continuing*/

            if(tx_error_flag) /* Check the error flag to see if errors occurred */
            {
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, RED_LED);
            }
            else /* If no errors */
            {
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GREEN_LED);
            }
            msg_count++;
        }
    }
    else if (tx_status_flag == DONE_REQUEST){

        tx_msg_object4.pui8MsgData = &tx_data_done;
        CANMessageSet(CAN0_BASE, tx_msg_obj_no4, &tx_msg_object4, MSG_OBJ_TYPE_TX); /*Send the CAN message using object number 1*/


        if(tx_error_flag) /* Check the error flag to see if errors occurred */
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, RED_LED);
        }
        else /* If no errors */
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GREEN_LED);
        }
    }


}



/***************************************************************************************************
* Function Name: MasterCANIntHandler
* Parameters (in): void
* Return value: void
* Description: CAN Interrupt Handler to process CAN interrupts
****************************************************************************************************/
void MasterCANIntHandler(void){

    uint32 interrupt_status =  CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE); /* to determine which condition caused the interrupt*/
    if(interrupt_status == CAN_INT_INTID_STATUS) /* If the cause is a controller status interrupt */
    {
        interrupt_status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL); /* to read the error block then clear the status interrupt */
        tx_error_flag = 1; /* raising the error flag */
    }
    else if(interrupt_status == tx_msg_obj_no1) /* If the cause is a is message object no. 1 (interrupt register is in the range 1-32 for message objects), which what we are using for sending message and the message TX is complete */
    {
        CANIntClear(CAN0_BASE, tx_msg_obj_no1); /* Clear the message object interrupt. */
        tx_intrrpt_msg_count++; /* incrementing the interrupt counter to identify the number of sent messages*/
        tx_error_flag = 0; /* no error occurred */
        tx_status_flag = RESET_REQUEST;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, WHITE_LED);

    }
    else if(interrupt_status == tx_msg_obj_no2) /* If the cause is a is message object no. 1 (interrupt register is in the range 1-32 for message objects), which what we are using for sending message and the message TX is complete */
    {
        CANIntClear(CAN0_BASE, tx_msg_obj_no2); /* Clear the message object interrupt. */
        tx_intrrpt_msg_count++; /* incrementing the interrupt counter to identify the number of sent messages*/
        tx_error_flag = 0; /* no error occurred */
        tx_status_flag = FLASH_REQUEST;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, WHITE_LED);

    }
    else if(interrupt_status == tx_msg_obj_no3) /* If the cause is a is message object no. 1 (interrupt register is in the range 1-32 for message objects), which what we are using for sending message and the message TX is complete */
    {
        CANIntClear(CAN0_BASE, tx_msg_obj_no3); /* Clear the message object interrupt. */
        tx_intrrpt_msg_count++; /* incrementing the interrupt counter to identify the number of sent messages*/
        tx_error_flag = 0; /* no error occurred */
        tx_status_flag = DATA_REQUEST;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, WHITE_LED);

    }
    else if(interrupt_status == tx_msg_obj_no4) /* If the cause is a is message object no. 1 (interrupt register is in the range 1-32 for message objects), which what we are using for sending message and the message TX is complete */
    {
        CANIntClear(CAN0_BASE, tx_msg_obj_no4); /* Clear the message object interrupt. */
        tx_intrrpt_msg_count++; /* incrementing the interrupt counter to identify the number of sent messages*/
        tx_error_flag = 0; /* no error occurred */
        tx_status_flag = DONE_REQUEST;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, WHITE_LED);

    }
    else /* Otherwise, something unexpected caused the interrupt. This should never happen*/
    {
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, BLUE_LED);
    }


}
