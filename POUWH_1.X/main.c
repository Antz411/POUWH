/*
 * File:    main.c
 * Author:  A.Smith
 * Created: 14-02-2018, 12:17 PM
 */
// CONFIG1
#pragma config FOSC = INTOSC    //  (INTOSC oscillator; I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOREN = OFF    // Low Power Brown-out Reset enable bit (LPBOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

#include <xc.h>
#include "main.h"

/**********************************
            GLOBALS
**********************************/
void initializers(void);
void Delay_Sec(unsigned char sec);
void blink_LED(void);

/**********************************
        INITIALISE MCU
**********************************/
void initializers(void)
{
    /*** set corresponding tris bits to inputs and outputs ***/
	TRISA = 0x03;                   // (MCLR/ICSP = Inputs) 0000 0011
	PORTA = 0X00;                   // Clear all Ports
    /* OSC SET UP */
    //OSCCON = 0x60;                // IRCF Bits for 4MHz (pg 42)
}

/* Delay for X seconds */
void Delay_Sec(unsigned char sec)
{
    unsigned char x, y;
    
    for(y = 0; y < sec; y++){
        for(x = 0; x < 100; x++){
            __delay_ms(10);
        }
    }
}

void blink_LED(void)
{
    STATUS_LED_ON;
    LED0_ON;
    LED1_ON;
    LED2_ON;
    LED4_ON;
    TEMP_OUT_ON;
    Delay_Sec(1);
    
    STATUS_LED_OFF;
    LED0_OFF;
    LED1_OFF;
    LED2_OFF;
    LED4_OFF;
    TEMP_OUT_OFF;
    Delay_Sec(1);
}

/**********************************
            MIAN FINCTION
**********************************/
void main(void) 
{
    initializers();
    
    blink_LED();
    
    while(1) {
        blink_LED();
    }
    return;
}