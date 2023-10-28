/*
 * Bitwise_Operations.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Shrook
 */

#ifndef MCAL_BITWISE_OPERATIONS_H_
#define MCAL_BITWISE_OPERATIONS_H_

#define SET_BIT(REG, BIT) (REG |= 1 << BIT)
#define CLEAR_BIT(REG, BIT) (REG &= ~(1 << BIT))
#define GET_BIT(REG, BIT) (REG & 1 << BIT)
#define TOGGLE_BIT(REG, BIT) (REG ^= 1 << BIT)

#define GET_VALUE(REG,Offset,count)         ((REG>>Offset)&((1<<count)-1))
#define INSERT_BIT(REG,BIT_NO,VALUE)        (REG =(REG&(~(1<<BIT_NO))|(VALUE<<BIT_NO)))
#define INSERT_VALUE(REG,Offset,count,VALUE)(REG =(REG&(~((1<<count)-1)<<Offset))|(VALUE<<Offset))



#endif /* MCAL_BITWISE_OPERATIONS_H_ */
