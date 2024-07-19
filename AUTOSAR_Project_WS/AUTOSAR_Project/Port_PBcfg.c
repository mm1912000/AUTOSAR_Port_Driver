/*
 * Port_PBcfg.c
 *
 *  Created on: Jun 25, 2024
 *      Author: m1912000
 */

#ifndef PORT_PBCFG_C_
#define PORT_PBCFG_C_

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */
const Port_ConfigType Port_Configuration = {
                                             /* PORT A PBcfg */
                                             PORT_A_ID, PIN_0_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_A_ID, PIN_1_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_A_ID, PIN_2_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_A_ID, PIN_3_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_A_ID, PIN_4_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_A_ID, PIN_5_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_A_ID, PIN_6_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_A_ID, PIN_7_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,

                                             /* PORT B PBcfg */
                                             PORT_B_ID, PIN_0_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_B_ID, PIN_1_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_B_ID, PIN_2_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_B_ID, PIN_3_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_B_ID, PIN_4_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_B_ID, PIN_5_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_B_ID, PIN_6_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_B_ID, PIN_7_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,

                                             /* PORT C PBcfg */
                                             PORT_C_ID, PIN_0_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_C_ID, PIN_1_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_C_ID, PIN_2_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_C_ID, PIN_3_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_C_ID, PIN_4_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_C_ID, PIN_5_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_C_ID, PIN_6_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_C_ID, PIN_7_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,

                                             /* PORT D PBcfg */
                                             PORT_D_ID, PIN_0_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_D_ID, PIN_1_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_D_ID, PIN_2_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_D_ID, PIN_3_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_D_ID, PIN_4_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_D_ID, PIN_5_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_D_ID, PIN_6_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_D_ID, PIN_7_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,

                                             /* PORT E PBcfg */
                                             PORT_E_ID, PIN_0_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_E_ID, PIN_1_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_E_ID, PIN_2_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_E_ID, PIN_3_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_E_ID, PIN_4_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_E_ID, PIN_5_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,

                                             /* PORT F PBcfg */
                                             PORT_F_ID, PIN_0_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PortConf_LED1_PORT_NUM, PortConf_LED1_PIN_ID, PORT_PIN_MODE_DIO, PortConf_LED1_PIN_DIRECTION, OFF, PortConf_LED1_PIN_LEVEL_VALUE,
                                             PORT_F_ID, PIN_2_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PORT_F_ID, PIN_3_ID, PORT_PIN_MODE_DIO, PortConf_PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW,
                                             PortConf_SW1_PORT_NUM, PortConf_SW1_PIN_ID, PORT_PIN_MODE_DIO, PortConf_SW1_PIN_DIRECTION, PULL_UP, PortConf_SW1_PIN_LEVEL_VALUE
                                         };
/* violation of Misra-C rule for exceeding 80 characters per line for better
 * readability as each line represents the config parameters for the
 * corresponding HW.
 */



#endif /* PORT_PBCFG_C_ */
