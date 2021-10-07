#ifndef _INTERFACE_
#define _INTERFACE_
#include "SYS_private.h"

/*
 * 
 * call this function to get the current state of the timming system
 */
byte byteSysGetState(unsigned long copySysTimer);
/*
 * After getting the state pass it to this function to apply changes according to the state
 */
void voidSysApplyState(byte copyState);

/*
 * to fetch the data of EEPROM & call this function in void setup
 */
void voidGetSavedData(void);
/*
 * To init pins as i/o in void setup
 */
void voidSystemInit();
#endif
