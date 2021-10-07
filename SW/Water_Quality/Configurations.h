#ifndef _CONFIGURATIONS_H
#define _CONFIGURATIONS_H

/* Moods of solonid */
#define TimerMode        0
#define WithouTimerMode  1

/* PINS of BUMP and Solonid */
#define BUMP_PIN_EN      17
#define BUMP_PIN_DIR1    4
#define BUMP_PIN_DIR2    16
#define Solonid1_PIN     2
#define Solonid2_PIN     15

#define RelayHigh  LOW
#define RelayLow   HIGH
/* Danger values of PH and Turbidity Sensors */

#define PH_MinDangerVal  7
#define PH_MaxDangerVal  8
#define TURB_DangerVal  5
#define NTU_CLEAR     4.15
#define NTU_HALFCLEAR 4.10
 /* Choose Mode */
#define SolonidMode  WithouTimerMode

/* Time select*/
#define ON_Time  2000
#define OFF_Time  2000

#define PHNeg 32
#define PHPos 33
#define TempNegFan 25 
#define TempPosHeat 5
#define LVLPos 12
#define LVLNeg 23

#endif
