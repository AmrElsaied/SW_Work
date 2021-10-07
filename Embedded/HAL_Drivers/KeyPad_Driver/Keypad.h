/*
 * Keypad.h
 *
 *  Created on: Sep 6, 2019
 *      Author: Amr Elsaied
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*
 * Initialize the pins for the keyPad
 * Port --> from port0 to port3
 * return Status:
 * 1: Success
 * 0: Failed
 */
U8 KeyPad_Initialize(U8 Port);

/*
 * Detect which button has been Pressed
 * it returns from 1 to 16
 * it returns (111) if no button is being pressed
 */
U8 KeyPad_Scan(U8 Port);

#endif /* KEYPAD_H_ */
