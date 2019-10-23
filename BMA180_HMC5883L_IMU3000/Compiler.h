#ifndef __COMPILER_H
#define __COMPILER_H

#if defined(__dsPIC33F__) && defined(__C30__)	// Microchip C30 compiler
	// dsPIC33F processor
    #define COMPILER_MPLAB_C30
	#include <p33Fxxxx.h>
	#if !defined(Nop)
		#define Nop()    __builtin_nop()
		#define ClrWdt() {__asm__ volatile ("clrwdt");}
		#define Sleep()  {__asm__ volatile ("pwrsav #0");}
		#define Idle()   {__asm__ volatile ("pwrsav #1");}
	#endif
#elif defined(__PIC32MX__)	// Microchip C32 compiler
	#if !defined(__C32__)
		#define __C32__
	#endif
    #define COMPILER_MPLAB_C32
	#include <p32xxxx.h>
	#include <plib.h>
#else
	#error Unknown processor or compiler.  See Compiler.h
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Base RAM and ROM pointer types for given architecture
#if defined(__PIC32MX__)
	#define PTR_BASE		unsigned long
	#define ROM_PTR_BASE	unsigned long
#elif defined(__C30__)
	#define PTR_BASE		unsigned short
	#define ROM_PTR_BASE	unsigned short
#endif
#define	ROM						const
// 16-bit specific defines (PIC24F, PIC24H, dsPIC30F, dsPIC33F)
	#if defined(__C30__)
		#define Reset()				asm("reset")
        #define FAR                 __attribute__((far))
	#endif

	// 32-bit specific defines (PIC32)
	#if defined(__PIC32MX__)
		#define persistent
		#define far
        #define FAR
		#define Reset()				SoftReset()
		#define ClrWdt()			(WDTCONSET = _WDTCON_WDTCLR_MASK)

		// MPLAB C Compiler for PIC32 MCUs version 1.04 and below don't have a 
		// Nop() function. However, version 1.05 has Nop() declared as _nop().
		#if !defined(Nop) && (__C32_VERSION__ <= 104)
			#define Nop()				asm("nop")
		#endif
	#endif
#endif
