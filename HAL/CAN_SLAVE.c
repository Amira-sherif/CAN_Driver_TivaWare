///**********************************************************************************************************************
// *  FILE DESCRIPTION
// *  -------------------------------------------------------------------------------------------------------------------
// *       Author:  -
// *         File:  CAN_SLAVE.c
// *        Layer:  HAL
// *       Module:  CAN_SLAVE
// *      Version:  1.00
// *
// *  Description:  CAN Salve Message using CAN0
// *
// *********************************************************************************************************************/
//
//
///*******************************************************************************
// *                                includes                                     *
// *******************************************************************************/
//
//#include <HAL/CAN_SLAVE.h>
//
///*******************************************************************************
// *                                Definitions                                  *
// *******************************************************************************/
//#define BIT_RATE                 500000 /* 500 kHz */
//#define BLUE_LED                 0x04
//#define RED_LED                  0x02
//#define GREEN_LED                0x08
//#define WHITE_LED                0x0E
//#define RESET_REQUEST            1
//#define FLASH_REQUEST            2
//#define DATA_REQUEST             3
//#define DONE_REQUEST             4
//#define MESSAGE_LENGTH           1
//#define MESSAGE_ID_MASK          0xFFFFFFFF
//
///***************************************************************************************************
//*                                           Global variables                                       *
//****************************************************************************************************/
//
////volatile uint32 rx_intrrpt_msg_count = 0; /* counter to keep track of times rx interrupt occurred */
//volatile uint8 rx_msg_flag = 0; /* flag to indicate that a message was received */
//volatile uint8 rx_error_flag = 0; /* flag to indicate that some reception error occurred */
//volatile uint8 rx_status_flag = 1; /* flag to indicate which status from the four is received */
//volatile uint8 rx_reset_flag = 0; /* flag to indicate that a reset request is sent */
//volatile uint8 rx_flash_flag = 0; /* flag to indicate that a flash request is sent */
//volatile uint8 rx_data_flag = 0; /* flag to indicate that a data request is sent */
//volatile uint8 rx_done_flag = 0; /* flag to indicate that a done request is sent */
//
//uint32 rx_clock_source; /* clock source in Hz */
//
//tCANMsgObject rx_msg_object1; /* CAN message object for reset */
//tCANMsgObject rx_msg_object2; /* CAN message object for flash*/
//tCANMsgObject rx_msg_object3; /* CAN message object for data*/
//tCANMsgObject rx_msg_object4; /* CAN message object for done*/
//
//uint8 rx_msg_obj_no1 = 1; /* CAN message using object number 1 */
//uint8 rx_msg_obj_no2 = 2; /* CAN message using object number 2 */
//uint8 rx_msg_obj_no3 = 3; /* CAN message using object number 3 */
//uint8 rx_msg_obj_no4 = 4; /* CAN message using object number 4 */
//
//uint8 rx_data_reset; /* CAN message reset data -> 1 byte */
//uint8 rx_data_flash; /* CAN message flash data -> 1 byte */
//uint8 rx_data_done; /* CAN message done data -> 1 byte */
//uint8 rx_msg_data[10*1024];  /* CAN message data -> 10 bytes */
//
///*******************************************************************************
// *                              Functions Prototypes                           *
// *******************************************************************************/
//
//
///***************************************************************************************************
//* Function Name: SlaveCANInit
//* Parameters (in): void
//* Return value: void
//* Description: CAN initialization to initializes the message objects to a safe state prior to
//*              enabling the controller on the CAN bus and bit timing values must be programmed
//*              prior to enabling the CAN controller.
//****************************************************************************************************/
//void SlaveCANInit(void){
//    /* Systick and Clock Configuration */
//    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
//    rx_clock_source = SysCtlClockGet(); /* getting the actual configured system clock frequency in Hz*/
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
//    {}
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
//
//    /* CAN Configuration */
//    /* Set up CAN0 pins using PORTB */
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//
//    GPIOPinConfigure(GPIO_PB4_CAN0RX); /* CAN module 0 receive -> CAN0Rx on PB4 */
//    GPIOPinConfigure(GPIO_PB5_CAN0TX); /* CAN module 0 transmit -> CAN0Tx on PB5 */
//
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);  /* enable clock for CAN0 */
//    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);/* Select the alternate (CAN) function for these pins */
//
//    CANInit(CAN0_BASE); /* Initialize the CAN controller */
//    CANBitRateSet(CAN0_BASE, rx_clock_source, BIT_RATE); /* Set up the bit rate for the CAN bus with 500 kHz */
//    CANIntRegister(CAN0_BASE, SlaveCANIntHandler); /* registers the interrupt handler in the interrupt vector table, and enables CAN interrupts on the interrupt controller*/
//    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS); /* Enables individual CAN controller interrupt sources */
//    IntEnable(INT_CAN0); /* Enable the CAN interrupt on the processor (NVIC) */
//    CANEnable(CAN0_BASE); /* Enable the CAN for operation */
//    IntMasterEnable();
//
//
//    /*Object creations*/
//    rx_msg_object1.ui32MsgID = RESET_REQUEST; /* The CAN message identifier used for 11 or 29 bit identifiers. -> receiving CAN messages with any CAN ID*/
//    rx_msg_object1.ui32MsgIDMask = MESSAGE_ID_MASK; /* The message identifier mask used when identifier filtering is enabled.*/
//    rx_msg_object1.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER; /* This value holds various status flags and settings specified by tCANObjFlags. -> receive and transmit interrupts are enabled*/
//    rx_msg_object1.ui32MsgLen = MESSAGE_LENGTH; /* This value is the number of bytes of data in the message object.*/
//
//    rx_msg_object2.ui32MsgID = FLASH_REQUEST; /* The CAN message identifier used for 11 or 29 bit identifiers. -> receiving CAN messages with any CAN ID*/
//    rx_msg_object2.ui32MsgIDMask = MESSAGE_ID_MASK; /* The message identifier mask used when identifier filtering is enabled.*/
//    rx_msg_object2.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER; /* This value holds various status flags and settings specified by tCANObjFlags. -> receive and transmit interrupts are enabled*/
//    rx_msg_object2.ui32MsgLen = MESSAGE_LENGTH; /* This value is the number of bytes of data in the message object.*/
//
//    rx_msg_object3.ui32MsgID = DATA_REQUEST; /* The CAN message identifier used for 11 or 29 bit identifiers. -> receiving CAN messages with any CAN ID*/
//    rx_msg_object3.ui32MsgIDMask = MESSAGE_ID_MASK; /* The message identifier mask used when identifier filtering is enabled.*/
//    rx_msg_object3.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER; /* This value holds various status flags and settings specified by tCANObjFlags. -> receive and transmit interrupts are enabled*/
//    rx_msg_object3.ui32MsgLen = MESSAGE_LENGTH; /* This value is the number of bytes of data in the message object.*/
//
//    rx_msg_object4.ui32MsgID = DONE_REQUEST; /* The CAN message identifier used for 11 or 29 bit identifiers. -> receiving CAN messages with any CAN ID*/
//    rx_msg_object4.ui32MsgIDMask = MESSAGE_ID_MASK; /* The message identifier mask used when identifier filtering is enabled.*/
//    rx_msg_object4.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER; /* This value holds various status flags and settings specified by tCANObjFlags. -> receive and transmit interrupts are enabled*/
//    rx_msg_object4.ui32MsgLen = MESSAGE_LENGTH; /* This value is the number of bytes of data in the message object.*/
//
//    CANMessageSet(CAN0_BASE, rx_msg_obj_no1, &rx_msg_object1, MSG_OBJ_TYPE_RX); /*load the message object number 1 into the CAN peripheral */
//    CANMessageSet(CAN0_BASE, rx_msg_obj_no2, &rx_msg_object2, MSG_OBJ_TYPE_RX); /*load the message object object number 1 into the CAN peripheral */
//    CANMessageSet(CAN0_BASE, rx_msg_obj_no3, &rx_msg_object3, MSG_OBJ_TYPE_RX); /*load the message object object number 1 into the CAN peripheral */
//    CANMessageSet(CAN0_BASE, rx_msg_obj_no4, &rx_msg_object4, MSG_OBJ_TYPE_RX); /*load the message object object number 1 into the CAN peripheral */
//}
//
//
///***************************************************************************************************
//* Function Name: SlaveCANMessage
//* Parameters (in): void
//* Return value: void
//* Description: CAN Message to configure a message object to send data where each message
//*              object can be configured to generate interrupts on transmission.
//****************************************************************************************************/
//void SlaveCANMessage(void){
//
//    static uint8_t i = 0;
//    if(rx_status_flag == RESET_REQUEST)
//    {
//        if(rx_msg_flag) /* check if a message is received when the RX interrupt occurred*/
//        {
//            rx_msg_object1.pui8MsgData = &rx_data_reset; /* set pointer to rx_msg_data buffer */
//
//            CANMessageGet(CAN0_BASE, rx_msg_obj_no1, &rx_msg_object1, 0); /* Read the message from the CAN and the interrupt flag is already cleared in the handler*/
//            rx_msg_flag = 0; /* clear the received flag so the interrupt can set it again for new messages*/
//
//            if(rx_msg_object1.ui32Flags & MSG_OBJ_DATA_LOST) /* if there is a data loss*/
//            {
//                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, RED_LED);
//            }
//            else /* otherwise */
//            {
//                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GREEN_LED);
//                // TODO: /* write code here */
//
//            }
//        }
//        else
//        {
//            /*For MISRA*/
//        }
//
//    }
//    else if(rx_status_flag == FLASH_REQUEST)
//    {
//        if(rx_msg_flag) /* check if a message is received when the RX interrupt occurred*/
//        {
//            rx_msg_object2.pui8MsgData = &rx_data_flash; /* set pointer to rx_msg_data buffer */
//
//            CANMessageGet(CAN0_BASE, rx_msg_obj_no2, &rx_msg_object2, 0); /* Read the message from the CAN and the interrupt flag is already cleared in the handler*/
//            rx_msg_flag = 0; /* clear the received flag so the interrupt can set it again for new messages*/
//
//            if(rx_msg_object2.ui32Flags & MSG_OBJ_DATA_LOST) /* if there is a data loss*/
//            {
//                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, RED_LED);
//            }
//            else /* otherwise */
//            {
//                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GREEN_LED);
//                // TODO: /* write code here */
//            }
//        }
//        else
//        {
//            /*For MISRA*/
//        }
//    }
//    else if(rx_status_flag == DATA_REQUEST)
//    {
////        while(1)
////        {
//
//            if(rx_msg_flag) /* check if a message is received when the RX interrupt occurred*/
//            {
//                rx_msg_object3.pui8MsgData = &rx_msg_data[i++]; /* set pointer to rx_msg_data buffer */
//
//                CANMessageGet(CAN0_BASE, rx_msg_obj_no3, &rx_msg_object3, 0); /* Read the message from the CAN and the interrupt flag is already cleared in the handler*/
//                rx_msg_flag = 0; /* clear the received flag so the interrupt can set it again for new messages*/
//
//                if(rx_msg_object3.ui32Flags & MSG_OBJ_DATA_LOST) /* if there is a data loss*/
//                {
//                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, RED_LED);
//                }
//                else /* otherwise */
//                {
//                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GREEN_LED);
//                }
//            }
//            else
//            {
//                /*For MISRA*/
//            }
////        }
//    }
//    else if(rx_status_flag == DONE_REQUEST)
//    {
//        if(rx_msg_flag) /* check if a message is received when the RX interrupt occurred*/
//        {
//            i = 0;
//            rx_msg_object4.pui8MsgData = &rx_data_done; /* set pointer to rx_msg_data buffer */
//
//            CANMessageGet(CAN0_BASE, rx_msg_obj_no4, &rx_msg_object4, 0); /* Read the message from the CAN and the interrupt flag is already cleared in the handler*/
//            rx_msg_flag = 0; /* clear the received flag so the interrupt can set it again for new messages*/
//
//            if(rx_msg_object4.ui32Flags & MSG_OBJ_DATA_LOST) /* if there is a data loss*/
//            {
//                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, RED_LED);
//            }
//            else /* otherwise */
//            {
//                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GREEN_LED);
//                // TODO: /* write code here */
//
//            }
//        }
//        else
//        {
//            /*For MISRA*/
//        }
//    }
//    else
//    {
//        /*For MISRA*/
//    }
//}
//
//
//
///***************************************************************************************************
//* Function Name: SlaveCANIntHandler
//* Parameters (in): void
//* Return value: void
//* Description: CAN Interrupt Handler to process CAN interrupts
//****************************************************************************************************/
//void SlaveCANIntHandler(void){
//
//    uint32 interrupt_status =  CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE); /* to determine which condition caused the interrupt*/
//    if(interrupt_status == CAN_INT_INTID_STATUS) /* If the cause is a controller status interrupt */
//    {
//        interrupt_status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL); /* to read the error block then clear the status interrupt */
//        rx_error_flag = 1; /* raising the error flag */
//    }
//    else if(interrupt_status == rx_msg_obj_no1) /* If the cause is a is message object no. 1 (interrupt register is in the range 1-32 for message objects), which what we are using for receiving message and the message RX is complete */
//    {
//        CANIntClear(CAN0_BASE, rx_msg_obj_no1); /* Clear the message object interrupt. */
////        rx_intrrpt_msg_count++; /* incrementing the interrupt counter to identify the number of received messages*/
//        rx_msg_flag = 1; /* raising the receive flag for pending messages */
//        rx_error_flag = 0; /* no error occurred */
//        rx_status_flag = RESET_REQUEST;
////        rx_reset_flag = 1;
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, WHITE_LED);
//    }
//    else if(interrupt_status == rx_msg_obj_no2) /* If the cause is a is message object no. 1 (interrupt register is in the range 1-32 for message objects), which what we are using for receiving message and the message RX is complete */
//    {
//        CANIntClear(CAN0_BASE, rx_msg_obj_no2); /* Clear the message object interrupt. */
////        rx_intrrpt_msg_count++; /* incrementing the interrupt counter to identify the number of received messages*/
//        rx_msg_flag = 1; /* raising the receive flag for pending messages */
//        rx_error_flag = 0; /* no error occurred */
////        rx_flash_flag = 1;
//        rx_status_flag = FLASH_REQUEST;
//
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, WHITE_LED);
//    }
//    else if(interrupt_status == rx_msg_obj_no3) /* If the cause is a is message object no. 1 (interrupt register is in the range 1-32 for message objects), which what we are using for receiving message and the message RX is complete */
//    {
//        CANIntClear(CAN0_BASE, rx_msg_obj_no3); /* Clear the message object interrupt. */
////        rx_intrrpt_msg_count++; /* incrementing the interrupt counter to identify the number of received messages*/
//        rx_msg_flag = 1; /* raising the receive flag for pending messages */
//        rx_error_flag = 0; /* no error occurred */
//        rx_status_flag = DATA_REQUEST;
////        rx_data_flag = 1;
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, WHITE_LED);
//    }
//    else if(interrupt_status == rx_msg_obj_no4) /* If the cause is a is message object no. 1 (interrupt register is in the range 1-32 for message objects), which what we are using for receiving message and the message RX is complete */
//    {
//        CANIntClear(CAN0_BASE, rx_msg_obj_no4); /* Clear the message object interrupt. */
////        rx_intrrpt_msg_count++; /* incrementing the interrupt counter to identify the number of received messages*/
//        rx_msg_flag = 1; /* raising the receive flag for pending messages */
//        rx_error_flag = 0; /* no error occurred */
//        rx_status_flag = DONE_REQUEST;
////        rx_done_flag = 1;
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, WHITE_LED);
//    }
//    else /* Otherwise, something unexpected caused the interrupt. This should never happen*/
//    {
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, BLUE_LED);
//    }
//
//
//}
