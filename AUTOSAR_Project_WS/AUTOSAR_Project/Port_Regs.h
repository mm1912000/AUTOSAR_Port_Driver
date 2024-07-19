/*
 * Port_Regs.h
 *
 *  Created on: Jun 25, 2024
 *      Author: m1912000
 */

#ifndef PORT_REGS_H_
#define PORT_REGS_H_

#include"Std_Types.h"

/*****************************************************************************
GPIO registers (PORTA)
*****************************************************************************/
#define PORT_PORTA_DATA_REG       (*((volatile uint32 *)0x400043FC))
#define PORT_PORTA_DIR_REG        (*((volatile uint32 *)0x40004400))
#define PORT_PORTA_AFSEL_REG      (*((volatile uint32 *)0x40004420))
#define PORT_PORTA_PUR_REG        (*((volatile uint32 *)0x40004510))
#define PORT_PORTA_PDR_REG        (*((volatile uint32 *)0x40004514))
#define PORT_PORTA_DEN_REG        (*((volatile uint32 *)0x4000451C))
#define PORT_PORTA_LOCK_REG       (*((volatile uint32 *)0x40004520))
#define PORT_PORTA_CR_REG         (*((volatile uint32 *)0x40004524))
#define PORT_PORTA_AMSEL_REG      (*((volatile uint32 *)0x40004528))
#define PORT_PORTA_PCTL_REG       (*((volatile uint32 *)0x4000452C))
/*****************************************************************************
GPIO registers (PORTB)
*****************************************************************************/
#define PORT_PORTB_DATA_REG       (*((volatile uint32 *)0x400053FC))
#define PORT_PORTB_DIR_REG        (*((volatile uint32 *)0x40005400))
#define PORT_PORTB_AFSEL_REG      (*((volatile uint32 *)0x40005420))
#define PORT_PORTB_PUR_REG        (*((volatile uint32 *)0x40005510))
#define PORT_PORTB_PDR_REG        (*((volatile uint32 *)0x40005514))
#define PORT_PORTB_DEN_REG        (*((volatile uint32 *)0x4000551C))
#define PORT_PORTB_LOCK_REG       (*((volatile uint32 *)0x40005520))
#define PORT_PORTB_CR_REG         (*((volatile uint32 *)0x40005524))
#define PORT_PORTB_AMSEL_REG      (*((volatile uint32 *)0x40005528))
#define PORT_PORTB_PCTL_REG       (*((volatile uint32 *)0x4000552C))
/*****************************************************************************
GPIO registers (PORTC)
*****************************************************************************/
#define PORT_PORTC_DATA_REG       (*((volatile uint32 *)0x400063FC))
#define PORT_PORTC_DIR_REG        (*((volatile uint32 *)0x40006400))
#define PORT_PORTC_AFSEL_REG      (*((volatile uint32 *)0x40006420))
#define PORT_PORTC_PUR_REG        (*((volatile uint32 *)0x40006510))
#define PORT_PORTC_PDR_REG        (*((volatile uint32 *)0x40006514))
#define PORT_PORTC_DEN_REG        (*((volatile uint32 *)0x4000651C))
#define PORT_PORTC_LOCK_REG       (*((volatile uint32 *)0x40006520))
#define PORT_PORTC_CR_REG         (*((volatile uint32 *)0x40006524))
#define PORT_PORTC_AMSEL_REG      (*((volatile uint32 *)0x40006528))
#define PORT_PORTC_PCTL_REG       (*((volatile uint32 *)0x4000652C))
/*****************************************************************************
GPIO registers (PORTD)
*****************************************************************************/
#define PORT_PORTD_DATA_REG       (*((volatile uint32 *)0x400073FC))
#define PORT_PORTD_DIR_REG        (*((volatile uint32 *)0x40007400))
#define PORT_PORTD_AFSEL_REG      (*((volatile uint32 *)0x40007420))
#define PORT_PORTD_PUR_REG        (*((volatile uint32 *)0x40007510))
#define PORT_PORTD_PDR_REG        (*((volatile uint32 *)0x40007514))
#define PORT_PORTD_DEN_REG        (*((volatile uint32 *)0x4000751C))
#define PORT_PORTD_LOCK_REG       (*((volatile uint32 *)0x40007520))
#define PORT_PORTD_CR_REG         (*((volatile uint32 *)0x40007524))
#define PORT_PORTD_AMSEL_REG      (*((volatile uint32 *)0x40007528))
#define PORT_PORTD_PCTL_REG       (*((volatile uint32 *)0x4000752C))
/*****************************************************************************
GPIO registers (PORTE)
*****************************************************************************/
#define PORT_PORTE_DATA_REG       (*((volatile uint32 *)0x400243FC))
#define PORT_PORTE_DIR_REG        (*((volatile uint32 *)0x40024400))
#define PORT_PORTE_AFSEL_REG      (*((volatile uint32 *)0x40024420))
#define PORT_PORTE_PUR_REG        (*((volatile uint32 *)0x40024510))
#define PORT_PORTE_PDR_REG        (*((volatile uint32 *)0x40024514))
#define PORT_PORTE_DEN_REG        (*((volatile uint32 *)0x4002451C))
#define PORT_PORTE_LOCK_REG       (*((volatile uint32 *)0x40024520))
#define PORT_PORTE_CR_REG         (*((volatile uint32 *)0x40024524))
#define PORT_PORTE_AMSEL_REG      (*((volatile uint32 *)0x40024528))
#define PORT_PORTE_PCTL_REG       (*((volatile uint32 *)0x4002452C))
/*****************************************************************************
GPIO registers (PORTF)
*****************************************************************************/
#define PORT_PORTF_DATA_REG       (*((volatile uint32 *)0x400253FC))
#define PORT_PORTF_DIR_REG        (*((volatile uint32 *)0x40025400))
#define PORT_PORTF_AFSEL_REG      (*((volatile uint32 *)0x40025420))
#define PORT_PORTF_PUR_REG        (*((volatile uint32 *)0x40025510))
#define PORT_PORTF_PDR_REG        (*((volatile uint32 *)0x40025514))
#define PORT_PORTF_DEN_REG        (*((volatile uint32 *)0x4002551C))
#define PORT_PORTF_LOCK_REG       (*((volatile uint32 *)0x40025520))
#define PORT_PORTF_CR_REG         (*((volatile uint32 *)0x40025524))
#define PORT_PORTF_AMSEL_REG      (*((volatile uint32 *)0x40025528))
#define PORT_PORTF_PCTL_REG       (*((volatile uint32 *)0x4002552C))

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C


#endif /* PORT_REGS_H_ */
