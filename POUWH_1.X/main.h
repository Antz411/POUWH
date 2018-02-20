/* 
 * File:        MAIN.H
 * Author:      A.SMITH
 * Comments:    --
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

/********************************************************************************/
/*     TIMING CONSTANT TIMING CONSTANT TIMING CONSTANT TIMING CONSTANT          */
/********************************************************************************/
    #ifndef _XTAL_FREQ
    #define _XTAL_FREQ    4000000     // 8Mhz INTOSC internal osc
    #define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
    #endif

/********************************************************************************/
/*        PIN DEFINITIONS PIN DEFINITIONS PIN DEFINITIONS PIN DEFINITIONS       */
/********************************************************************************/
    #define Tmp_Var             RA1     // INPUT 
    #define Tmp_In              RA4     // INPUT
    #define STATUS              RA2     // OUTPUT
    #define POWER               RA5     // OUTPUT
    
    #define POWER_ON            POWER   = 1
    #define POWER_OFF           POWER   = 0
    #define STATUS_ON           STATUS  = 1
    #define STATUS_OFF          STATUS  = 0
    
/********************************************************************************/
/*     PUBLIC CONSTANTS PUBLIC CONSTANTS PUBLIC CONSTANTS PUBLIC CONSTANTS      */
/********************************************************************************/

    typedef unsigned char           u8;         // 0 -> 255
    typedef signed char             s8;         // -128 -> +128
    typedef unsigned short          u4;         // 0 -> 65 535
    typedef unsigned int            u16;		// 0 -> 4 294 967 295
    typedef signed int              s16;		// -half -> +half
    typedef unsigned long           u32;		// 0 -> VERY_BIG
    typedef signed long             s32;		// -BIG -> +BIG
    typedef u16                     FLADDR;     // Used for flash W/R

    #define CLEAR                   0x00
    #define SET                     0x01
    #define ON                      0x01
    #define OFF                     0x00
    #define TRUE                    0x01
    #define FALSE                   0x00
    #define MATCH                   0x00
    
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

