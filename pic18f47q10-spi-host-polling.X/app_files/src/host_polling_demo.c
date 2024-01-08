/**
 * Polling Demo Application Source File
 * 
 * @file host_polling_demo.c
 * 
 * @ingroup hostpollingdemo
 * 
 * @brief SPI polling mode demonstration implementation.
 * 
 * @version Polling Demo Application Version v1.0.0
 * 
 */

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS "AS IS". 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

// Included files
#include <stdint.h>

#include "../../mcc_generated_files/system/pins.h"
#include "../../mcc_generated_files/spi/spi_interface.h"
#include "../host_polling_demo.h"


// Functions
void DemoInitialize()
{
    SPI_Host.Initialize();
    SPI_Host.Open(SEVENSEG);
}

void DisplayCustomCharacter(uint8_t input)
{
    uint8_t recVal = 0X00;
    CS1_SetLow();    
    recVal = SPI_Host.ByteExchange(input);
    CS1_SetHigh();
    NOP();
}

void DisplayNumber(uint8_t numberInput)
{
    uint8_t displayNumber[2], digit;
    digit = numberInput%10;
    displayNumber[0] = sevenSegNumbers[digit];
    digit = numberInput/10;
    displayNumber[1] = sevenSegNumbers[digit];
    CS1_SetLow();
    SPI_Host.BufferExchange(displayNumber, 2);
    CS1_SetHigh();
}

bool ButtonPress(void)
{   
    static int8_t debounce = 10;
    static unsigned int buttonState = 0;
    static char buttonPressEnabled = 1;

    if(SW0_GetValue() == 0)
    {       
        if(buttonState < debounce)
        {
            buttonState++;
        }
        else if(buttonPressEnabled)
        {
            buttonPressEnabled = 0;
            return true;
        }
    }
    else if(buttonState > 0 )
    {
        buttonState--;
    }
    else
    {
        buttonPressEnabled = 1;
    }
    return false;
}