 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Marwan Medhat
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION           (1U)
#define PORT_CFG_SW_MINOR_VERSION           (0U)
#define PORT_CFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION   (3U)

/* Pre-compile option for number of pins */
#define PORT_NUMBER_OF_PORT_PINS             (43U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* PORT Configurations whether Pin direction is changeable or not */
#define PORT_PIN_DIRECTION_CHANGEABLE        (STD_OFF)

/* PORT Configurations whether Pin mode is changeable or not */
#define PORT_PIN_MODE_CHANGEABLE             (STD_OFF)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)

/* Pre-compile option for SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API           (STD_OFF)

/* Pre-compile option for SetPinMode API */
#define PORT_SET_PIN_Mode_API                (STD_OFF)

/* PORT Configured Port's number */
#define PortConf_LED1_PORT_NUM                (5U)/* PORTF */
#define PortConf_SW1_PORT_NUM                 (5U)/* PORTF */

/* PORT Configured Pin's Direction */
#define PortConf_LED1_PIN_DIRECTION           (Port_PinDirectionType)PORT_PIN_OUT /* LED as Output pin */
#define PortConf_SW1_PIN_DIRECTION            (Port_PinDirectionType)PORT_PIN_IN /* Button as Input Pin */

/* definitions for PORT_PIN_LEVEL */
#define PORT_PIN_LEVEL_LOW                    (STD_LOW)
#define PORT_PIN_LEVEL_HIGH                   (STD_HIGH)

/* PORT Configured Pin's Level Value */
#define PortConf_LED1_PIN_LEVEL_VALUE         PORT_PIN_LEVEL_LOW
#define PortConf_SW1_PIN_LEVEL_VALUE          PORT_PIN_LEVEL_HIGH

/* definitions for PORT_PIN_MODE
 * 0 for DIO
 * 2 for Serial communications like SPI,I2C, and LIN
 * 7 for Timer0 and its modes like ICU and PWM
 * 8 for Can
 * */
#define PORT_PIN_MODE_DIO                    (uint8)0x00 /* clear all bits in the PCTL register to set it as DIO port */
#define PORT_PIN_MODE_ADC                    (uint8)0x0A /* we dont need to set PCTL when using ADC so i chose a value 10 which corresponds to nothing in the modes */
#define PORT_PIN_MODE_CAN                    (uint8)0x08
#define PORT_PIN_MODE_DIO_GPT                (uint8)0x07
#define PORT_PIN_MODE_DIO_WDG                (uint8)0x20 /* Not in the requirements of the assignment however we will need to configure the registers in the System Control Block related to watchdog */
#define PORT_PIN_MODE_DIO_ICU                (uint8)0x07
#define PORT_PIN_MODE_LIN                    (uint8)0x02
#define PORT_PIN_MODE_MEM                    (uint8)0x21 /* Not in the requirements of the assignment however we will need to configure the registers in the System Control Block related to MPU */
#define PORT_PIN_MODE_PWM                    (uint8)0x07
#define PORT_PIN_MODE_SPI                    (uint8)0x02
#define PORT_PIN_MODE_FLEXRAY                (uint8)0x22 /* Not in the requirements of the assignment and not supported by TIVAC */

/*PORT Configured Pin's initial mode */
#define PortConf_LED1_PIN_INITIAL_MODE        PORT_PIN_MODE_DIO
#define PortConf_SW1_PIN_INITIAL_MODE         PORT_PIN_MODE_DIO

/* Port Configured Pin's ID */
#define PortConf_LED1_PIN_ID                  (Port_PinType)1 /* Pin 1  */
#define PortConf_SW1_PIN_ID                   (Port_PinType)4 /* Pin 4  */

/* PORTS Direction */
#define PortConf_PORT_PIN_IN                  (Port_PinDirectionType)PORT_PIN_IN
#define PortConf_PORT_PIN_OUT                 (Port_PinDirectionType)PORT_PIN_OUT

#endif /* PORT_CFG_H_ */
