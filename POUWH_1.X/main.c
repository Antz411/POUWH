/* 
 * File:    main.c
 * Author:  A.Smith
 * Created: 14-02-2018, 12:17 PM
 * 
 * NOTES:
 * ADC3 = RA4 - Temperature Sensor
 * ADC2 = RA2 - Temperature Control
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
u16 ADC1_Read(void);
u16 ADC3_Read(void);
void blink_LED_S(void);
void blink_LED_F(void);
void Heat_Up(void);
void Delay_Sec(unsigned char sec);

/*****************************
            GLOBALS
******************************/
u16 adc = 0;                            // Temperature value
u16 ADCH = 0x0000;                      // ADC High value
u16 ADCL = 0x0000;                      // ADC Low value

/*****************************
            MAIN
******************************/
void main(void) 
{
    //unsigned char once = 0x0050;
    initializers();
    ADC_Init();
        
    while(1)
    {        
        //adc = ADC3_Read();                          // Read Analog Channel 3 [RA4]
        adc = ADC1_Read();                          // Read Analog Channel 2 [RA2]
        /***********************************/
        /* To find a temperature threshold */
        /***********************************/
        if(adc <= 255){//if(adc <= 0xFF){
            //Heat_Up();                            // Heat the elements for 25 seconds
            blink_LED_F();                          // blink fast
        }
        else{
            //Heat_Up();                            // start heating for 25 seconds
            blink_LED_S();                          // blink slow
        }
        
    }
    return;
}

/*****************************
         FUNCTIONS
******************************/
/* Initialize */
void initializers(void)
{
    /* TRIS BITS TO IO's ***/
	//TRISA = 0x1F;                 // (MCLR/ICSP = Inputs) 0001 1111 - No Status LED
    TRISA = 0x1B;                   // (MCLR/ICSP = Inputs) 0001 1011 - Status LED
	/* PORTS */
	PORTA = 0X00;                   // Clear all I/O's
    /* OSC SET UP */
    OSCCON = 0x6A;                  // IRCF Bits for 4MHz (pg 42)
}

/* Initialize the ADC */
void ADC_Init(void)
{
    /* Using ADC Channel 1 &  */
    //ADCON0 = 0x81;             // Channel specifically enabled at each read?
    
    /* Vrpos = Vdd + Fosc/2
     * Right Justified (6 MSB = 0) - Read as [xxxx xx11 1111 1111 ]*/
    ADCON1 = 0x80;               // Reference Voltages, frequency & bit justification
}

/* Read the Temperature Sensor value  [RA1 - AN1] */
u16 ADC1_Read(void)
{
    ADCON0 = 0x05;               // 0000 0101   -> ADC Enable + AN1 select
    __delay_ms(2);               // Acquisition time to charge hold capacitor
    
    GO_nDONE = 1;                // Initializes A/D conversion
    while(GO_nDONE);             // Waiting for conversion to complete
    //return ((ADCH<<8)+ADRESL);
    
    /* Right Justified */
    ADCH = ADRESH;
    ADCL = ADRESL;
    ADCH = ADRESH && 0x03;          // AND 0000 0011
    ADCH = (ADCH<<8);               // shift to top 8 bits
    ADCH = ADCH + ADCL;             // Add results
    return ADCH;                    // Return result
}

/* Read the Temperature Control value [RA4 - AN3] */
u16 ADC3_Read(void)
{
    ADCON0 = 0x0B;               // 0000 1101   -> ADC Enable + AN3 select
    __delay_ms(2);               // Acquisition time to charge hold capacitor
    
    GO_nDONE = 1;                // Initializes A/D conversion
    while(GO_nDONE);             // Waiting for conversion to complete
    //return ((ADCH<<8)+ADRESL);   // Top 6 bits of ADRESH are ignored [Pg 122]
    
    /* Right Justified */
    ADCH = ADRESH;
    ADCL = ADRESL;
    ADCH = ADRESH && 0x03;          // AND 0000 0011
    ADCH = (ADCH<<8);               // shift to top 8 bits
    ADCH = ADCH + ADCL;             // Add results
    return ADCH;                    // Return result
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
void Heat_Up(void)
{
    POWER_ON;
    Delay_Sec(25);          //__delay_ms(250);
    POWER_OFF;
    Delay_Sec(10);        //__delay_ms(250);
}

/* Status LED */
void blink_LED_F(void)
{
    STATUS_ON;
    __delay_ms(100);
    STATUS_OFF;
    __delay_ms(100);
}
/* Status LED */
void blink_LED_S(void)
{
    STATUS_ON;
    __delay_ms(500);
    STATUS_OFF;
    __delay_ms(500);
}

