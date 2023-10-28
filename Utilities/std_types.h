



/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  -
 *	   	   File:  STD_TYPES.h
 *		  Layer:  LIB
 *       Module:  STD_TYPES
 *		Version:  1.00
 *	
 *  Description:  Standard types definitions      
 *  
 *********************************************************************************************************************/
#ifndef UTILITIES_STD_TYPES_H_
#define UTILITIES_STD_TYPES_H_


////////////////RAWAN

#define NULL_PTR    ((void*)0)

typedef unsigned char         uint8;          /*           0 .. 255              */
typedef signed char           sint8;          /*        -128 .. +127             */
typedef unsigned short        uint16;         /*           0 .. 65535            */
typedef signed short          sint16;         /*      -32768 .. +32767           */
typedef unsigned long         uint32;         /*           0 .. 4294967295       */
typedef signed long           sint32;         /* -2147483648 .. +2147483647      */
typedef unsigned long long    uint64;         /*       0 .. 18446744073709551615  */
typedef signed long long      sint64;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 float32;
typedef double                float64;

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
//#include <Utilities/Platform_Types.h>

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define NULL			0

#define ENABLE 1
#define DISABLE 0

#define SET 1
#define RESET 0

#define ON 1
#define OFF 0

//#define HIGH 1
//#define LOW 0

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
	IDLE=0,
	BUSY
}Peripheral_State;

typedef enum
{
	SEND_CHAR=0,
	SEND_STRING,
	SEND_BUFFER,
	RECEIVE_CHAR,
	RECEIVE_BUFFER,
	SINGLE_CONVERSION=0,
	CHAIN_CONVERSION
}ISR_Src;


typedef enum
{
	E_OK=0,
	E_NOK,
	E_NULL_POINTER,
	E_WRONG_OPTION,
    E_BUSY,
	E_BUSY_FUNC,
	E_TIME_OUT,
	E_NO_RESPOSE,
	E_CONNECTION_FAILED,
	E_DIV_BY_ZERO
}ErrorState_t;

typedef enum
{
	LOCKED=0,
	UNLOCKED
} Lock_t;

#endif /* UTILITIES_STD_TYPES_H_ */

/**********************************************************************************************************************
 *  END OF FILE: STD_TYPES.h
 *********************************************************************************************************************/



