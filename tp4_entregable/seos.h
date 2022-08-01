/*
 * seos.h
 *
 * Created: 29/07/2022 03:25:13 p. m.
 *  Author: Alejandro Mejía
 */ 


#ifndef SEOS_H_
#define SEOS_H_
  #include "menu.h"
  #include <avr/io.h>
	#include <avr/interrupt.h>

  void SEOS_Schedule_Tasks(void);
  void SEOS_Dispatch_Tasks (void);
#endif /* SEOS_H_ */