/* 
 * File:    main.c
 * Author:  A.Smith
 * Created: 14-02-2018, 12:17 PM
 */
// CONFIG1
#pragma config FOSC = INTOSC    // (INTOSC oscillator; I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOREN = OFF    // Low Power Brown-out Reset enable bit (LPBOR is disabled)
#pragma config LVP = OFF         // Low-Voltage Programming Enable (Low-voltage programming enabled)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include "main.h"

/*****************************
            PROTOTYPES
******************************/
void initializers(void);
void ADC_Init(void);
u16 ADC_Read(unsigned char channel);
void blink_LED(void);
void blink_Power(void);
void Delay_Sec(unsigned char sec);

/*****************************
            GLOBALS
******************************/
u16 a = 0;                          // Temperature value

/*****************************
            MAIN
******************************/
void main(void) 
{
    initializers();
    ADC_Init();
    
    while(1)
    {
        a = ADC_Read(0);            //Read Analog Channel 0
        blink_LED();
        //blink_Power();
    }
    return;
}

/* Initialize */
void initializers(void)
{
    /*** set corresponding tris bits to inputs and outputs ***/
	TRISA = 0x03;               // (MCLR/ICSP = Inputs) 0000 0011
	// Clear all Ports
	PORTA = 0X00;
    /* OSC SET UP */
    OSCCON = 0x6A;              // IRCF Bits for 4MHz (pg 42)
}

/* Initialize the ADC */
void ADC_Init(void)
{
    ADCON0 = 0x81;               //Turn ON ADC and Clock Selection
    ADCON1 = 0x00;               //All pins as Analog Input and setting Reference Voltages
}

/* Read the Temperature Input value */
u16 ADC_Read(u8 channel)
{
    if(channel > 7)              // Channel range is 0 ~ 7
        return 0;

    ADCON0 &= 0xC5;              // Clearing channel selection bits
    ADCON0 |= channel<<3;        // Setting channel selection bits
    __delay_ms(2);               // Acquisition time to charge hold capacitor
    
    GO_nDONE = 1;                // Initializes A/D conversion
    while(GO_nDONE);             // Waiting for conversion to complete
    return ((ADRESH<<8)+ADRESL); // Return result
}

/* Delay for X seconds */
void Delay_Sec(u8 sec)
{
    unsigned char x, y;
    
    for(y = 0; y < sec; y++){
        for(x = 0; x < 100; x++){
            __delay_ms(10);
        }
    }
}

/* Switch Power On/Off */
void blink_Power(void)
{
    POWER_ON;
    Delay_Sec(5);       //__delay_ms(250);
    POWER_OFF;
    Delay_Sec(5);       //__delay_ms(250);
}

/* Status LED */
void blink_LED(void)
{
    STATUS_ON;
    __delay_ms(250);
    STATUS_OFF;
    __delay_ms(250);
}
