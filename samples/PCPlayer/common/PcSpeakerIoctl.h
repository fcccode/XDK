/*
 * Copyright (c) 2008-2016, Integrity Project Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of the Integrity Project nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE
 */

#ifndef __PCSPEAKER_IOCTL_H
#define __PCSPEAKER_IOCTL_H


/*
 * PcSpeakerIoctl.h
 *
 * This file is auto-generated by the IDL compiler with the IOCTL template
 * file. This file contains the IOCTL codes for the device.
 *
 * Note:
 *   This file is compile for both ring3 application and ring0 applications.
 *
 * Author: Elad Raz <e@eladraz.com>
 */
#include "xStl/types.h"

// Ring3 applications include files
#ifdef XSTL_WINDOWS
#include <winioctl.h>
#endif

// Ring0 applications include files
#ifdef XSTL_NTDDK
#include "XDK/kernel.h"
#endif


/*
 * The interface for the devices for both ring3 and ring0 applications.
 * The interface PcSpeaker is responsible for: Basic speaker device class.
 * Handles the features of the PC-Speaker
 *
 *
 * All the methods in this class are protected since only the
 * cPcSpeakerClient and the cPcSpeakerServer implements
 * the IOCTL private protocol.
 *
 * These class should be accessable for programmers. To use the protocol
 * instance one of the server/client class and channel your requests.
 */
class cPcSpeakerIoctl
{
public:
    /*
     * Destructor. This is an interface class.
     */
    virtual ~cPcSpeakerIoctl() {};

protected:
    // Codes 0x000...0x7FF reserved for Microsoft.
    // Codes 0x800...0xFFF free for private use.
    enum { BASE = 0x0900 };

    // The functions IOCTL codes
    enum
    {

        /*
         * See soundOn.
         * Marshal index (OXID) for function soundOn
         */
        IOCTL_PLAYER_SOUNDON =
            CTL_CODE(FILE_DEVICE_UNKNOWN, BASE + 0, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS),

        /*
         * See soundOff.
         * Marshal index (OXID) for function soundOff
         */
        IOCTL_PLAYER_SOUNDOFF =
            CTL_CODE(FILE_DEVICE_UNKNOWN, BASE + 1, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS),

        /*
         * See setFrequency.
         * Marshal index (OXID) for function setFrequency
         */
        IOCTL_PLAYER_SETFREQUENCY =
            CTL_CODE(FILE_DEVICE_UNKNOWN, BASE + 2, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS),

        /*
         * See makeImpulse.
         * Marshal index (OXID) for function makeImpulse
         */
        IOCTL_PLAYER_MAKEIMPULSE =
            CTL_CODE(FILE_DEVICE_UNKNOWN, BASE + 3, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS),

        /*
         * The last IOCTL code. Used for security
         */
        IOCTL_PLAYER_END_CODE
    };

    // The abstract function declaration.


    // Activate the sound signal.
    virtual void soundOn() = 0;

    // Stop the sound signal.
    virtual void soundOff() = 0;

    // Change the frequency of the timer chip 8254 The timer connected
    // to the speaker and transfer a sinus wave to the speaker.
    // The frequency is from 10Hz to 119250Hz.
    //
    // frequency - The number of times when 1 puls will be heard.
    virtual void setFrequency(uint32 frequency) = 0;

    // This method change the 8254 channel 2 counter to generate a
    // single impulse for a short prioed of time.
    //
    // counter - Number of counts to pass over them. The frequency
    //           of the chip is 119250Hz. This number is the length
    //           of the out signal. The counter is limited to the
    //           low 16bit.
    virtual void makeImpulse(uint32 counter) = 0;

};

#endif // __PCSPEAKER_IOCTL_H
