/*******************************************************************************
* File Name: SW0.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SW0_H) /* Pins SW0_H */
#define CY_PINS_SW0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SW0_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} SW0_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SW0_Read(void);
void    SW0_Write(uint8 value);
uint8   SW0_ReadDataReg(void);
#if defined(SW0__PC) || (CY_PSOC4_4200L) 
    void    SW0_SetDriveMode(uint8 mode);
#endif
void    SW0_SetInterruptMode(uint16 position, uint16 mode);
uint8   SW0_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SW0_Sleep(void); 
void SW0_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SW0__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SW0_DRIVE_MODE_BITS        (3)
    #define SW0_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SW0_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SW0_SetDriveMode() function.
         *  @{
         */
        #define SW0_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SW0_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SW0_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SW0_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SW0_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SW0_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SW0_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SW0_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SW0_MASK               SW0__MASK
#define SW0_SHIFT              SW0__SHIFT
#define SW0_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SW0_SetInterruptMode() function.
     *  @{
     */
        #define SW0_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SW0_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SW0_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SW0_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SW0__SIO)
    #define SW0_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SW0__PC) && (CY_PSOC4_4200L)
    #define SW0_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SW0_USBIO_DISABLE              ((uint32)(~SW0_USBIO_ENABLE))
    #define SW0_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SW0_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SW0_USBIO_ENTER_SLEEP          ((uint32)((1u << SW0_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SW0_USBIO_SUSPEND_DEL_SHIFT)))
    #define SW0_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SW0_USBIO_SUSPEND_SHIFT)))
    #define SW0_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SW0_USBIO_SUSPEND_DEL_SHIFT)))
    #define SW0_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SW0__PC)
    /* Port Configuration */
    #define SW0_PC                 (* (reg32 *) SW0__PC)
#endif
/* Pin State */
#define SW0_PS                     (* (reg32 *) SW0__PS)
/* Data Register */
#define SW0_DR                     (* (reg32 *) SW0__DR)
/* Input Buffer Disable Override */
#define SW0_INP_DIS                (* (reg32 *) SW0__PC2)

/* Interrupt configuration Registers */
#define SW0_INTCFG                 (* (reg32 *) SW0__INTCFG)
#define SW0_INTSTAT                (* (reg32 *) SW0__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SW0_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SW0__SIO)
    #define SW0_SIO_REG            (* (reg32 *) SW0__SIO)
#endif /* (SW0__SIO_CFG) */

/* USBIO registers */
#if !defined(SW0__PC) && (CY_PSOC4_4200L)
    #define SW0_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SW0_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SW0_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SW0_DRIVE_MODE_SHIFT       (0x00u)
#define SW0_DRIVE_MODE_MASK        (0x07u << SW0_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SW0_H */


/* [] END OF FILE */
