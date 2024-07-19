 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Marwan Medhat
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and PORT Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigPort * Port_PinNumber = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize the port driver module
************************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        /* reports the error E_PARAPM_CONFIG */
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_INIT_SID,
                        PORT_E_PARAM_CONFIG);
    }
    else
#endif
    {
        Port_PinType i; /* pin index */
        Port_Status = PORT_INITIALIZED;
        Port_PinNumber = ConfigPtr->Pins; /* Pointer to array of structures which holds the pins configurations */

        for( i = 0 ; i < PORT_NUMBER_OF_PORT_PINS ; i++) /* for loop for the array of config structure to initialize all pins in the MCU */
        {

            volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

            switch(Port_PinNumber[i].port_num)
            {
                case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                         break;
                case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                         break;
                case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                         break;
                case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                         break;
                case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                         break;
                case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                         break;
            }

            if( ((Port_PinNumber[i].port_num == PORT_D_ID) && (Port_PinNumber[i].pin_num == PIN_7_ID)) || ((Port_PinNumber[i].port_num == PORT_F_ID) && (Port_PinNumber[i].pin_num == PIN_0_ID)) ) /* PD7 or PF0 */
            {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_PinNumber[i].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else if( (Port_PinNumber[i].port_num == PORT_C_ID) && (Port_PinNumber[i].pin_num <= PIN_3_ID) ) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is the JTAG pins */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            if(Port_PinNumber[i].pin_mode == PORT_PIN_MODE_DIO)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinNumber[i].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinNumber[i].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinNumber[i].pin_num * 4));     /* Clear the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinNumber[i].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
            else if (Port_PinNumber[i].pin_mode == PORT_PIN_MODE_ADC)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinNumber[i].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinNumber[i].pin_num);           /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinNumber[i].pin_num);     /* Clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinNumber[i].pin_num);                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinNumber[i].pin_num);                         /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ( (Port_PinNumber[i].pin_mode & 0x0000000F) << (Port_PinNumber[i].pin_num * 4));      /* set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinNumber[i].pin_num);                   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }

            if(Port_PinNumber[i].direction == PORT_PIN_OUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PinNumber[i].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                if(Port_PinNumber[i].initial_value == STD_HIGH)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_PinNumber[i].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_PinNumber[i].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
            }
            else if(Port_PinNumber[i].direction == PORT_PIN_IN)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PinNumber[i].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                if(Port_PinNumber[i].resistor == PULL_UP)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_PinNumber[i].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if(Port_PinNumber[i].resistor == PULL_DOWN)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_PinNumber[i].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_PinNumber[i].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_PinNumber[i].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                }
            }
            else
            {
                /* Do Nothing */
            }
        }
    }
}
/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void)
{
    Port_PinType i;
    volatile uint32 *PortGpio_Ptr = NULL_PTR; /* points to the required Port Registers base address */
    boolean error = FALSE;

#if(PORT_DEV_ERROR_DETECT == STD_ON)
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_REFRESH_PORT_DIRECTION_SID,
                        PORT_E_UNINIT);
        error = TRUE;
    }

    else
    {
        /* Do Nothing */

    }
#endif
    if (error == FALSE)
    {
        for (i = 0; i < PORT_NUMBER_OF_PORT_PINS; i++)
        {
            /* PORT060: refresh the direction of the pins in all ports */
            if (Port_PinNumber[i].direction == PORT_PIN_OUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PinNumber[i].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            }

            else if (Port_PinNumber[i].direction == PORT_PIN_IN)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PinNumber[i].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            }
            else
            {
                /* Do Nothing */
            }

        }

    }

}
/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID Number / Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
************************************************************************************/
#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin,
                           Port_PinDirectionType Direction
                         )
{

    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* pointer to port gpio address */
    boolean error = FALSE; /* variable to check if there is error or no */

#if(PORT_DEV_ERROR_DETECT == STD_ON)/* check whether we want to check for development errors */
    if (PORT_NOT_INITIALIZED == Port_Status) /* Checks if the port module is initialized */
    {
            Det_ReportError(PORT_MODULE_ID,
                            PORT_INSTANCE_ID,
                            PORT_SET_PIN_DIRECTION_SID,
                            PORT_E_UNINIT
                            ); /* reports that the module is not initialized */
            error = TRUE;
    }
    else
    {
        /* do nothing */
    }

    if(Pin >= PORT_NUMBER_OF_PORT_PINS) /* checks if the number of pins is within the MC's pin range */
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_PARAM_PIN
                        ); /* reports that the input pin number is incorrect */
        error = TRUE;
    }
    else
    {
        /* do nothing */
    }

    if(PORT_PIN_DIRECTION_CHANGEABLE == STD_OFF) /* checks if the user allowed changes for the pin direction during run time */
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_DIRECTION_UNCHANGEABLE
                        ); /* reports that the pin direction is unchangeable as set by the user */
        error = TRUE;
    }
    else
    {
        /* do nothing */
    }
#endif
    if (error == FALSE) /* if no error detected */
    {
        /* Point to the correct PORT register according to the Port Id stored in the port_num member */
        switch(Port_PinNumber[Pin].port_num)
        {
            case 0:
                PortGpio_Ptr = &PORT_PORTA_DIR_REG; /*  Pointer points to PORTA Directions Register */
                break;
            case 1:
                PortGpio_Ptr = &PORT_PORTB_DIR_REG; /*  Pointer points to PORTB Directions Register */
                break;
            case 2:
                PortGpio_Ptr = &PORT_PORTC_DIR_REG; /*  Pointer points to PORTC Directions Register */
                break;
            case 3:
                PortGpio_Ptr = &PORT_PORTD_DIR_REG; /*  Pointer points to PORTD Directions Register */
                break;
            case 4:
                PortGpio_Ptr = &PORT_PORTE_DIR_REG; /*  Pointer points to PORTE Directions Register */
                break;
            case 5:
                PortGpio_Ptr = &PORT_PORTF_DIR_REG; /*  Pointer points to PORTF Directions Register */
                break;
        }
        if( (Port_PinNumber[Pin].port_num == PORT_C_ID) && (Port_PinNumber[Pin].pin_num <= PIN_3_ID) ) /* PC0 to PC3 */
        {
                /* Do Nothing ...  this is the JTAG pins */
        }
        else
        {
            /* sets the direction of the pin according to the value of Pin_DirectionType parameter */
            if(Direction == PORT_PIN_OUT)
            {
                SET_BIT(*PortGpio_Ptr,Port_PinNumber[Pin].pin_num); /* sets the corresponding port direction register */
            }
            else if(Direction == PORT_PIN_IN)
            {
                CLEAR_BIT(*PortGpio_Ptr,Port_PinNumber[Pin].pin_num); /* clears the corresponding port direction register */
            }
        }

    }

    else
    {
        /* do nothing */
    }
}
#endif
/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module
* Return value: None
* Description: Returns the version information of this module
************************************************************************************/
#if(PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID,
                        PORT_E_PARAM_POINTER);
    }
    else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif
/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID Number / Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
#if(PORT_SET_PIN_Mode_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin,
                     Port_PinModeType Mode
                     )
{
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* pointer to port gpio address */
    boolean error = FALSE; /* variable to check if there is error or no */

#if(PORT_DEV_ERROR_DETECT == STD_ON)/* check whether we want to check for development errors */
    if (PORT_NOT_INITIALIZED == Port_Status) /* Checks if the port module is initialized */
    {
            Det_ReportError(PORT_MODULE_ID,
                            PORT_INSTANCE_ID,
                            PORT_SET_PIN_MODE_SID,
                            PORT_E_UNINIT
                            ); /* reports that the module is not initialized */
            error = TRUE;
    }
    else
    {
        /* do nothing */
    }
    /* TIVA C will only support 4 numbers of modes according to AUTOSAR 0,2,7,8, and ADC */
    if(Mode == PORT_PIN_MODE_DIO || Mode == PORT_PIN_MODE_DIO_GPT || Mode == PORT_PIN_MODE_CAN || Mode == PORT_PIN_MODE_LIN || Mode == PORT_PIN_MODE_ADC)/* checks if the number of input mode is within the mode range */
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_SET_PIN_MODE_SID,
                        PORT_E_PARAM_INVALID_MODE
                        ); /* reports that the input pin number is incorrect */
        error = TRUE;
    }
    else
    {
        /* do nothing */
    }


    if(Pin >= PORT_NUMBER_OF_PORT_PINS) /* checks if the number of pins is within the MC's pin range */
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_SET_PIN_MODE_SID,
                        PORT_E_PARAM_PIN
                        ); /* reports that the input pin number is incorrect */
        error = TRUE;
    }
    else
    {
        /* do nothing */
    }

    if(PORT_PIN_MODE_CHANGEABLE == STD_OFF) /* checks if the user allowed changes for the pin mode during run time */
        {
            Det_ReportError(PORT_MODULE_ID,
                            PORT_INSTANCE_ID,
                            PORT_SET_PIN_MODE_SID,
                            PORT_E_MODE_UNCHANGEABLE
                            ); /* reports that the pin mode is unchangeable as set by the user */
            error = TRUE;
        }
        else
        {
            /* do nothing */
        }

#endif
    if (error == FALSE)
    {
        switch(Port_PinNumber[Pin].port_num)
        {
            case 0:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* Points to PORTA base address */
                break;
            case 1:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* Points to PORTB base address */
                break;
            case 2:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* Points to PORTC base address */
                break;
            case 3:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* Points to PORTD base address */
                break;
            case 4:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* Points to PORTE base address */
                break;
            case 5:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* Points to PORTF base address */
                break;
        }

        if( (Port_PinNumber[Pin].port_num == PORT_C_ID) && (Port_PinNumber[Pin].pin_num <= PIN_3_ID) ) /* PC0 to PC3 */
        {
                /* Do Nothing ...  this is the JTAG pins */
        }
        else
        {

            if(Mode == PORT_PIN_MODE_DIO)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinNumber[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinNumber[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinNumber[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinNumber[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
            else if (Mode == PORT_PIN_MODE_ADC)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinNumber[Pin].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinNumber[Pin].pin_num);           /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinNumber[Pin].pin_num);     /* Clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinNumber[Pin].pin_num);                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinNumber[Pin].pin_num);                         /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ( (Mode & 0x0000000F) << (Port_PinNumber[Pin].pin_num * 4));      /* set the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinNumber[Pin].pin_num);                   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
        }
    }
    else
    {
        /* do nothing */
    }

}
#endif
