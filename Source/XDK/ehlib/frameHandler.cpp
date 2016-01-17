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

/*
 * frameHandler.cpp
 *
 * A thunk to EHLib::internalFrameHandler. The code which generated by the
 * compiler uses EAX register. In order to avoid compiler dependency to
 * reservce the EAX register we created a thunk which clear the direction
 * flag, translates the EAX register into a function argument and invoke
 * a call to EHLib::internalFrameHandler.
 *
 * Author: Elad Raz <e@eladraz.com>
 */
#include "xStl/types.h"
#include "XDK/EHLib/ehlib.h"
#include "xdk/utils/bugcheck.h"


EXTERNC EXCEPTION_DISPOSITION __cdecl internalFrameHandler(
        EHLib::ExceptionRecord*  exceptionRecord,
        EHLib::MSCPPEstablisher* establisherFrame,
        struct _CONTEXT*         contextRecord,
        struct _CONTEXT**        dispatcherContext,
        EHLib::FunctionEHData*   eh)
{
    return EHLib::internalFrameHandler(exceptionRecord,
        establisherFrame,
        contextRecord,
        dispatcherContext,
        eh, EHLib::FRAME_HANDLER_TYPE_0);
}

EXTERNC EXCEPTION_DISPOSITION __cdecl internalFrameHandler3(
        EHLib::ExceptionRecord*  exceptionRecord,
        EHLib::MSCPPEstablisher* establisherFrame,
        struct _CONTEXT*         contextRecord,
        struct _CONTEXT**        dispatcherContext,
        EHLib::FunctionEHData*   eh)
{
    return EHLib::internalFrameHandler(exceptionRecord,
        establisherFrame,
        contextRecord,
        dispatcherContext,
        eh, EHLib::FRAME_HANDLER_TYPE_3);
}


// Visual Studio 2005 exception handling frames
EXTERNC _declspec(naked) EXCEPTION_DISPOSITION __cdecl __CxxFrameHandler(
    EHLib::ExceptionRecord* exceptionRecord,
    EHLib::MSCPPEstablisher* establisherFrame,
    struct _CONTEXT* contextRecord,
    struct _CONTEXT** dispatcherContext)
{
    _asm {
        ; // Enter
        push ebp
        mov ebp, esp

        cld
        push eax
        push dispatcherContext
        push contextRecord
        push establisherFrame
        push exceptionRecord
        call internalFrameHandler
        add esp, 0x14

        ; // Leave
        pop ebp
        retn
    }
}

EXTERNC _declspec(naked) void __cdecl __CxxFrameHandler3(EHLib::ExceptionRecord* exceptionRecord,
    EHLib::MSCPPEstablisher* establisherFrame,
    struct _CONTEXT* contextRecord,
    struct _CONTEXT** dispatcherContext)
{
    // New frame format. Throw exception
    _asm {
        ; // Enter
        push ebp
        mov ebp, esp

        cld
        push eax
        push dispatcherContext
        push contextRecord
        push establisherFrame
        push exceptionRecord
        call internalFrameHandler3
        add esp, 0x14

        ; // Leave
        pop ebp
        retn
    }
}
