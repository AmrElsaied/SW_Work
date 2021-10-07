/*
 * keypad.c
 *
 *  Created on: Sep 6, 2019
 *      Author: Amr Elsaied
 */

#include "Std_types.h"
#include "DIO.h"
#include "Keypad.h"
#include "Keybad_Priv.h"

/*
 * Initialize the Port Pins
 *  4 PINS as OUTPUT for ROW (from 0 to 3)
 *  4 PINS as INPUT for Columns (from 4 to 7)
 */
U8 KeyPad_Initialize(U8 Port) {

	if (Port > Invalid_Port_Min && Port < Invalid_Port_Max) {
		for (int i = 0; i <= 7; i++) {
			if (i < 4) {
				DIO_SetPinDirection(Port, i, OUTPUT);

			} else {
				DIO_SetPinDirection(Port, i, INPUT);
				DIO_SetPinPullUp(Port, i);
			}
		}
		return Success;
	}

	else {
		return Failed;
	}

}

/*
 * This function to determine which key is pressed
 * it takes two argument the ROW Number and the Column number
 * and then determine which button is being pressed
 * by applying these equations
 */
U8 Get_Key(U8 ROWCounter, U8 COlCounter) {
	U8 Ret_Val = 0;
	switch (ROWCounter) {
	case 0:
		Ret_Val = ROWCounter + (COlCounter - 4) + 1;
		break;
	case 1:
		Ret_Val = 4 * ROWCounter + (COlCounter - 4) + 1;
		break;
	case 2:
		Ret_Val = 4 * ROWCounter + (COlCounter - 4) + 1;
		break;
	case 3:
		Ret_Val = 4 * ROWCounter + (COlCounter - 4) + 1;
		break;
	}
	return Ret_Val;
}

U8 KeyPad_Scan(U8 Port) {
	U8 Ret_Val = 0;
	U8 Last_RowCounter = 0;
	U8 check = 0;
	U8 flag = 0;

	for (int RowCounter = 0; RowCounter < 4; RowCounter++) {
		if (RowCounter == Last_RowCounter) {
			DIO_SetPinValue(Port, RowCounter, LOW);
			DIO_SetPinValue(Port, RowMaxPinNumber, HIGH);
		} else {
			DIO_SetPinValue(Port, RowCounter, LOW);
			DIO_SetPinValue(Port, Last_RowCounter, HIGH);
		}
		for (int ColCounter = 4; ColCounter <= 7; ColCounter++) {
			check = GetPinValue(Port, ColCounter);
			if (check == Pressed) {
				Ret_Val = Get_Key(RowCounter, ColCounter);
				flag = 1;
				break;
			}
		}

		Last_RowCounter = RowCounter;
	}
	if (flag == 1) {
		flag = 0;
		return Ret_Val;
	} else {
		return 111;
	}

}
