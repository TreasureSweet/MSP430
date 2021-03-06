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
 */
#include <string.h>

#include "driverlib.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"
#include "USB_API/USB_MSC_API/UsbMscScsi.h"
#include "USB_API/USB_MSC_API/UsbMsc.h"
#include "USB_API/USB_MSC_API/UsbMscStateMachine.h"
#include "USB_API/USB_HID_API/UsbHid.h"

/*
 * NOTE: Modify hal.h to select a specific evaluation board and customize for
 * your own board.
 */
#include "hal.h"

void main (void)
{
    // Set up clocks/IOs.  USBHAL_initPorts()/USBHAL_initClocks() will need to be customized
    // for your application, but MCLK should be between 4-25MHz.  Using the
    // DCO/FLL for MCLK is recommended, instead of the crystal.  For examples 
    // of these functions, see the complete USB code examples.  Also see the 
    // Programmer's Guide for discussion on clocks/power.
    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer
    
    // Minimum Vcore setting required for the USB API is PMM_CORE_LEVEL_2 .
    PMM_setVCore(PMM_CORE_LEVEL_2);
    USBHAL_initPorts();             // Configure all GPIOs
    USBHAL_initClocks(8000000);     // Configure clocks
    USB_setup(TRUE,TRUE);    // Init USB & events; if a host is present, connect

    __enable_interrupt();    // Enable interrupts globally

    while (1)
    {
        // This switch() creates separate main loops, depending on whether USB 
        // is enumerated and active on the host, or disconnected/suspended.  If
        // you prefer, you can eliminate the switch, and just call
        // USB_getConnectionState() prior to sending data (to ensure the state is
        // ST_ENUM_ACTIVE). 
        switch(USB_getConnectionState())
        {
            // This case is executed while your device is connected to the USB
            // host, enumerated, and communication is active.  Never enter 
            // LPM3/4/5 in this mode; the MCU must be active or LPM0 during USB
            // communication.
            case ST_ENUM_ACTIVE:

            // These cases are executed while your device is:
            case ST_USB_DISCONNECTED: // physically disconnected from the host
            case ST_ENUM_SUSPENDED:   // connected/enumerated, but suspended
            case ST_NOENUM_SUSPENDED: // connected, enum started, but the host is unresponsive
            
                // In this example, for all of these states we enter LPM3.  If 
                // the host performs a "USB resume" from suspend, the CPU will
                // automatically wake.  Other events can also wake the
                // CPU, if their event handlers in eventHandlers.c are 
                // configured to return TRUE.
                __bis_SR_register(LPM3_bits + GIE);  
                break;

            // The default is executed for the momentary state
            // ST_ENUM_IN_PROGRESS.  Almost always, this state lasts no more than a 
            // few seconds.  Be sure not to enter LPM3 in this state; USB 
            // communication is taking place, so mode must be LPM0 or active.
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
            UCS_clearAllOscFlagsWithTimeout(0);
            SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
            break;
        case SYSUNIV_ACCVIFG:
            __no_operation();
            break;
        case SYSUNIV_BUSIFG:
            // If the CPU accesses USB memory while the USB module is 
            // suspended, a "bus error" can occur.  This generates an NMI, and
            // execution enters this case.  This should never occur.  If USB is
            // automatically disconnecting in your software, set a breakpoint
            // here and see if execution hits it.  See the Programmer's
            // Guide for more information. 
            SYSBERRIV = 0; // Clear bus error flag
            USB_disable(); // Disable USB -- USB must be reset after a bus error
    }
}
//Released_Version_5_20_06_02
