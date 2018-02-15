/* 
 * File:        main.h
 * Author:      A.Smith
 * Comments:    
 */
 #ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #ifndef _XTAL_FREQ
    #define _XTAL_FREQ    4000000     // 8Mhz INTOSC internal osc
    #define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
    #endif
    
    #define LED0                     RA0                  // OUTPUT
    #define LED0_ON                  LED0             = 1
    #define LED0_OFF                 LED0             = 0
    
    #define LED1                     RA1                  // OUTPUT
    #define LED1_ON                  LED1             = 1
    #define LED1_OFF                 LED1             = 0
    
    #define LED2                     RA2                  // OUTPUT
    #define LED2_ON                  LED2             = 1
    #define LED2_OFF                 LED2             = 0

    #define LED4                     RA4                  // OUTPUT
    #define LED4_ON                  LED4             = 1
    #define LED4_OFF                 LED4             = 0

    #define STATUS_LED              RA3                  // OUTPUT
    #define STATUS_LED_ON           STATUS_LED      = 1
    #define STATUS_LED_OFF          STATUS_LED      = 0
    
    #define TEMP_OUT                RA5                  // OUTPUT
    #define TEMP_OUT_ON             TEMP_OUT        = 1
    #define TEMP_OUT_OFF            TEMP_OUT        = 0
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */