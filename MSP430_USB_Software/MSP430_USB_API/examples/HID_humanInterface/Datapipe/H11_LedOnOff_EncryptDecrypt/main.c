/* --COPYRIGHT--,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*  
 * ======== main.c ========
 * H1 Example
 * LED Control Demo:
 *
 * This example implements a simple command-line interface, where the command 
 * is ended by pressing ?return?.  It accepts four "commands":
 * "LED ON!"
 * "LED OFF!"
 * "LED TOGGLE ? SLOW!"
 * "LED TOGGLE ? FAST!"
 * (Recall that when using the HID examples, a "!" character  serves the same 
 * purpose as a return character did in the CDC example, in terminating a 
 * string.)  
 * Be sure to select the appropriate board in hal.h; or if using a board not 
 * selectable in this file, manually configure an I/O on that board driving 
 * an LED.  
 *
 +----------------------------------------------------------------------------+
 * Please refer to the Examples Guide for more details.
 *----------------------------------------------------------------------------*/
#include <string.h>

#include "driverlib.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"                 // USB-specific functions
#include "USB_API/USB_HID_API/UsbHid.h"
#include "USB_app/usbConstructs.h"
#include "aes128lib/TI_aes.h"

/*
 * NOTE: Modify hal.h to select a specific evaluation board and customize for
 * your own board.
 */
#include "hal.h"


// Function declarations
uint8_t retInString (char* string);
void initTimer(void);
void setTimer_A_Parameters(void);

void decryptData(uint8_t* dataString, uint16_t dataSize);
void encryptData(uint8_t* dataString, uint16_t dataSize);

// Global flags set by events
volatile uint8_t bHIDDataReceived_event = FALSE; // Indicates data has been rx'ed
                                              // without an open rx operation

unsigned char key[]   = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                           0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

#define MAX_STR_LENGTH 64
char wholeString[MAX_STR_LENGTH] = ""; // Entire input str from last 'return'

// Set/declare toggle delays
uint16_t SlowToggle_Period = 20000 - 1;
uint16_t FastToggle_Period = 1000 - 1;
uint16_t strlength = 0;

Timer_A_initUpModeParam Timer_A_params = {0};
/*  
 * ======== main ========
 */
void main (void)
{
    setTimer_A_Parameters(); 

    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    // Minumum Vcore setting required for the USB API is PMM_CORE_LEVEL_2 .
    PMM_setVCore(PMM_CORE_LEVEL_2);
    USBHAL_initPorts();           // Config GPIOS for low-power (output low)
    USBHAL_initClocks(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz
    initTimer();           // Prepare timer for LED toggling
    USB_setup(TRUE, TRUE); // Init USB & events; if a host is present, connect

    __enable_interrupt();  // Enable interrupts globally
    
    while (1)
    {
        uint8_t i;
        
        // Check the USB state and directly main loop accordingly
        switch (USB_getConnectionState())
        {
            // This case is executed while your device is enumerated on the
            // USB host
            case ST_ENUM_ACTIVE:
            
                // Enter LPM0 (can't do LPM3 when active)
                __bis_SR_register(LPM0_bits + GIE);
                _NOP(); 
                // Exit LPM on USB receive and perform a receive operation
                
                // If true, some data is in the buffer; begin receiving a cmd
                if (bHIDDataReceived_event){
 
                    // Holds the new addition to the string
                    char pieceOfString[MAX_STR_LENGTH] = "";
                    
                    // Holds the outgoing string
                    char outString[MAX_STR_LENGTH] = "";

                    // Add bytes in USB buffer to the string
                    USBHID_receiveDataInBuffer((uint8_t*)pieceOfString,
                        MAX_STR_LENGTH,
                        HID0_INTFNUM); // Get the next piece of the string

                    decryptData((uint8_t*)pieceOfString, strlen(pieceOfString));

                    // Append new piece to the whole
                    strcat(wholeString,pieceOfString);


                    // Echo back the characters received
                    encryptData((uint8_t*)pieceOfString, strlen(pieceOfString));

                    // Echo back the characters received
                    USBHID_sendDataInBackground((uint8_t*)pieceOfString,
                        strlength,HID0_INTFNUM,0);


                    // Has the user pressed return yet?
                    if (retInString(wholeString)){
                    
                        // Compare to string #1, and respond
                        if (!(strcmp(wholeString, "LED ON"))){
                        
                            // Turn off timer; no longer toggling LED
                            Timer_A_stop(TIMER_A0_BASE);
                            
                            // Turn on LED P1.0
                            GPIO_setOutputHighOnPin(LED_PORT, LED_PIN);
                            
                            // Prepare the outgoing string
                            strcpy(outString,"\r\nLED is ON\r\n\r\n");

                            encryptData((uint8_t*)outString, strlen(outString));

                            // Send the response over USB
                            USBHID_sendDataInBackground((uint8_t*)outString,
                                strlength,HID0_INTFNUM,0);
                                

                        // Compare to string #2, and respond
                        } else if (!(strcmp(wholeString, "LED OFF"))){
                        
                            // Turn off timer; no longer toggling LED
                            Timer_A_stop(TIMER_A0_BASE);
                            
                            // Turn off LED P1.0
                            GPIO_setOutputLowOnPin(LED_PORT, LED_PIN);
                            
                            // Prepare the outgoing string
                            strcpy(outString,"\r\nLED is OFF\r\n\r\n");

                            encryptData((uint8_t*)outString, strlen(outString));

                            // Send the response over USB
                            USBHID_sendDataInBackground((uint8_t*)outString,
                                strlength,HID0_INTFNUM,0);
                                

                        // Compare to string #3, and respond
                       } else if (!(strcmp(wholeString, "LED TOGGLE - SLOW"))){
                        
                            // Turn off timer while changing toggle period
                            Timer_A_stop(TIMER_A0_BASE);
                            
                            // Set timer period for slow LED toggle
                            Timer_A_params.timerPeriod = SlowToggle_Period;

                            Timer_A_initUpMode(TIMER_A0_BASE, &Timer_A_params);
                                
                            // Start timer for toggling
                            Timer_A_startCounter(TIMER_A0_BASE,
                                TIMER_A_UP_MODE);
                                
                            // Prepare the outgoing string
                            strcpy(outString,
                                "\r\nLED is toggling slowly\r\n\r\n");

                            encryptData((uint8_t*)outString, strlen(outString));
                                
                            // Send the response over USB
                           USBHID_sendDataInBackground((uint8_t*)outString,
                                strlength,HID0_INTFNUM,0);

                                
                        // Compare to string #4, and respond
                        } else if (!(strcmp(wholeString,"LED TOGGLE - FAST"))){
                        
                            // Turn off timer while changing toggle period
                            Timer_A_stop(TIMER_A0_BASE);
                            
                              // Set timer period for fast LED toggle
                            Timer_A_params.timerPeriod = FastToggle_Period;

                            Timer_A_initUpMode(TIMER_A0_BASE, &Timer_A_params);
                                
                            // Start timer for toggling
                            Timer_A_startCounter(TIMER_A0_BASE,
                                TIMER_A_UP_MODE);
                                
                            // Prepare the outgoing string
                            strcpy(outString,
                                "\r\nLED is toggling fast\r\n\r\n");

                            encryptData((uint8_t*)outString, strlen(outString));
                                
                            // Send the response over USB
                            USBHID_sendDataInBackground((uint8_t*)outString,
                            		strlength,HID0_INTFNUM,0);
                                

                        // Handle other
                        } else {
                            // Prepare the outgoing string
                            strcpy(outString,"\r\nNo such command!\r\n\r\n");
                            
                            encryptData((uint8_t*)outString, strlen(outString));

                            // Send the response over USB
                            USBHID_sendDataInBackground((uint8_t*)outString,
                            		strlength,HID0_INTFNUM,0);
                        }
                        // Clear the string in preparation for the next one
                        for (i = 0; i < MAX_STR_LENGTH; i++){
                            wholeString[i] = 0x00;
                        }
                    }
                    bHIDDataReceived_event = FALSE;
                }
                break;

            // These cases are executed while your device is disconnected from
            // the host (meaning, not enumerated); enumerated but suspended
            // by the host, or connected to a powered hub without a USB host
            // present.
            case ST_PHYS_DISCONNECTED:
            case ST_ENUM_SUSPENDED:
            case ST_PHYS_CONNECTED_NOENUM_SUSP:
                // Turn off LED P1.0
                GPIO_setOutputLowOnPin(LED_PORT, LED_PIN);
                __bis_SR_register(LPM3_bits + GIE);
                _NOP();
                break;

            // The default is executed for the momentary state
            // ST_ENUM_IN_PROGRESS.  Usually, this state only last a few
            // seconds.  Be sure not to enter LPM3 in this state; USB
            // communication is taking place here, and therefore the mode must
            // be LPM0 or active-CPU.
            case ST_ENUM_IN_PROGRESS:
            default:;
        }

    }  //while(1)
} //main()

/*  
 * ======== UNMI_ISR ========
 */
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(UNMI_VECTOR))) UNMI_ISR (void)
#else
#error Compiler not found!
#endif
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG))
    {
        case SYSUNIV_NONE:
            __no_operation();
            break;
        case SYSUNIV_NMIIFG:
            __no_operation();
            break;
        case SYSUNIV_OFIFG:
            UCS_clearFaultFlag(UCS_XT2OFFG);
            UCS_clearFaultFlag(UCS_DCOFFG);
            SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
            break;
        case SYSUNIV_ACCVIFG:
            __no_operation();
            break;
        case SYSUNIV_BUSIFG:
            // If the CPU accesses USB memory while the USB module is
            // suspended, a "bus error" can occur.  This generates an NMI.  If
            // USB is automatically disconnecting in your software, set a
            // breakpoint here and see if execution hits it.  See the
            // Programmer's Guide for more information.
            SYSBERRIV = 0; //clear bus error flag
            USB_disable(); //Disable
    }
}

void decryptData(uint8_t* dataString, uint16_t dataSize)
{
    uint8_t i, j;
    uint8_t aes128Len=16;  //AES-128 data array length
    uint8_t numWords = 0;
    uint8_t bufPtr = 1;
    uint8_t ptr = 0;
    uint8_t actualSize = 0;
    uint8_t padBytes = 0;
    uint8_t tempBuf[16];  //temporary buffer used to do decryption
    uint8_t bytesLeft;


    unsigned char tempStr[MAX_STR_LENGTH] = "";

    // Make a copy of the string
    strncpy((char*)tempStr,(char*)dataString,dataSize);

    //get the actual data size sent by user.  This size is not padded.
    actualSize = tempStr[0];

    numWords = actualSize / aes128Len;

    bytesLeft = actualSize - (numWords * aes128Len);

    if (bytesLeft > 0)
    {
    	//Any bytes not divisible by 16 are padded as sent by user's GUI
    	numWords = numWords + 1;
    }

    for (i = 0; i < numWords; i++)
    {
    	for (j = 0; j < aes128Len; j++)
		{
    		//copy up to 16 bytes of encrypted data to temporary array
    		tempBuf[j] = tempStr[bufPtr + j];
		}
    	//decrypt the data
		aes_decrypt(tempBuf, key);

		//copy back the decrypted data into temporary array
		for (j = 0; j < aes128Len; j++)
		{
			tempStr[ptr + j] = tempBuf[j];

		}
        bufPtr += 16;
        ptr += 16;

    }
    //calculate the number of bytes used for padding the data string
	padBytes = aes128Len - bytesLeft;

    //copy back the decrypted data into original array
   	for (i = 0; i < actualSize; i++)
   	{
   		dataString[i] = tempStr[i];
   	}
	if (padBytes < 16)
	{
	   	for (i = 0; i < padBytes + 1; i++)
	   	{
	   		dataString[actualSize + i] = 0;
	   	}
	}

}


void encryptData(uint8_t* dataString, uint16_t dataSize)
{
	 uint8_t bytesForPad = 0, i, j;
	 uint8_t numWords=0;
	 uint8_t bufPtr = 0;
	 uint8_t tempBuf[16];
	 uint8_t bytesLeft = 0;
	 uint8_t ptr = 1;
	 uint8_t aes128DataSize = 16;

	 unsigned char tempStr[MAX_STR_LENGTH] = "";


    //calculate number of 16byte words in data string
	numWords = dataSize / aes128DataSize;
	//calculate the extra bytes
	bytesLeft = dataSize - (numWords * aes128DataSize);

    if (numWords > 0)
    {
		for (i = 0; i < numWords; i++)
		{
			for (j = 0; j < aes128DataSize; j++)
			{
			//copy data into temporary buffer array
			   tempBuf[j] = dataString[bufPtr + j];

			}
			//encrypt data in 16 byte increments
			aes_encrypt(tempBuf, key);
			for (j = 0; j< aes128DataSize; j++)
			{
				//copy encrypted data into temporary array
				tempStr[ptr + j] = tempBuf[j];

			}
			bufPtr += 16;
			ptr += 16;
		}

    }
    //add bytes for padding data
	if (bytesLeft > 0)
	{
		//increment number of 16 byte word by 1
        numWords = numWords + 1;
        //number of bytes used for padding data
		bytesForPad = aes128DataSize - bytesLeft;

		for (i = 0; i < bytesLeft; i++)
	    {
			//copy un-padded data to temporary buffer array
		   	tempBuf[i] = dataString[bufPtr + i];
	    }
		for (j = 0; j < bytesForPad; j++)
		{
			//add the pads for a total data length of 16 bytes
            tempBuf[bytesLeft + j] = 0;

		}
		//encrypt the data
	    aes_encrypt(tempBuf, key);
	    for (i = 0; i < aes128DataSize; i++)
	    {
	    	//copy the encrypted data into temporary array
	    	tempStr[ptr + i] = tempBuf[i];
	    }
	}
	//include actual data length
	tempStr[0] = dataSize;
	//padded data length
	strlength = aes128DataSize * numWords + 1;
	//copy the entire encrypted data with padding to original data string
	for (i = 0; i < strlength; i++)
	{
		dataString[i] = tempStr[i];
	}

}
/*  
 * ======== retInString ========
 */
// This function returns true if there's an 0x21('!') character in the string;
// and if so, it trims the 0x0D and anything that had followed it.
uint8_t retInString (char* string)
{
    uint8_t retPos = 0,i,len;
    char tempStr[MAX_STR_LENGTH] = "";

    // Make a copy of the string
    strncpy(tempStr,string,strlen(string));
    len = strlen(tempStr);
    
    // Find 0x21 "!"; if not found, retPos ends up at len
    while ((tempStr[retPos] != 0x21) && (retPos++ < len)) ;

    // If 0x21 was actually found...
    if (retPos < len){
        for (i = 0; i < MAX_STR_LENGTH; i++){  // Empty the buffer
            string[i] = 0x00;
        }
        
        //...trim the input string to just before 0x0D
        strncpy(string,tempStr,retPos);
        
        //...and tell the calling function that we did so
        return ( TRUE) ;
    }

    return ( FALSE) ; // Otherwise, it wasn't found
}

/*
 * ======== setTimer_A_Parameters ========
 */
// This function sets the timer A parameters
void setTimer_A_Parameters()
{
	Timer_A_params.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
	Timer_A_params.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
	Timer_A_params.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
	Timer_A_params.captureCompareInterruptEnable_CCR0_CCIE =
		       TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
	Timer_A_params.timerClear = TIMER_A_DO_CLEAR;
	Timer_A_params.startTimer = false;
}

/*
 * ======== initTimer ========
 */
void initTimer (void)
{
    // Start timer
    Timer_A_clearTimerInterrupt(TIMER_A0_BASE);
    
    // Set timer period to zero 
    Timer_A_params.timerPeriod = 0;

    Timer_A_initUpMode(TIMER_A0_BASE, &Timer_A_params);
}

/*
 * ======== TIMER1_A0_ISR ========
 */
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) TIMER0_A0_ISR (void)
#else
#error Compiler not found!
#endif
{
    GPIO_toggleOutputOnPin(LED_PORT, LED_PIN);
}
//Released_Version_5_10_00_17
//Released_Version_5_20_06_02
