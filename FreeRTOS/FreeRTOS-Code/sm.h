/* (c) Sinelabore Software Tools GmbH - All rights reserved. Reproduction, modification,
   use or disclosure to third parties without express
   authority is forbidden. Generator running in demo mode!
   Please purchase a license if you want to use this software in projects.
 */

/* Command line options: -p ssc -E sm.xml   */
/* This file is generated from sm.xml - do not edit manually*/
/* Generated on: Sat Mar 20 21:42:40 CET 2021 / Version 5.0.6b3 */


#ifndef __SM_H__
#define __SM_H__


/* Header to define simple data types */
#include <stdint.h>

/* State definitions */
typedef enum{
	SA,
	SB,
	__SM_LAST_STATE__} SM_STATES_T;






/* Predefined types required by the codegen. You can provide your own  */
/* definitions by setting the following define somewhere in your built env. */
#ifndef __PROVIDE_OWN_SM_STATEMACHINE_TYPES__
	typedef uint8_t SM_ENTRY_FLAG_T;
	typedef SM_STATES_T SM_STATEVAR_T;
	typedef uint8_t SM_INST_ID_T;
	typedef uint8_t SM_EV_CONSUMED_FLAG_T ;
#endif




/* Instance data definition of state machine */
typedef struct{
	SM_ENTRY_FLAG_T saEntry;
	SM_STATEVAR_T stateVar;
		SM_INST_ID_T inst_id;
} SM_INSTANCEDATA_T;

/* Helper to initialize the machine's instance data */
#define SM_INSTANCEDATA_INIT {\
	1,\
	(SM_STATEVAR_T) SA /* set init state of top state */,\
	0 /* instance id */ } 


/*Prototype of the state machine function */
void  sm(SM_INSTANCEDATA_T *instanceVar, USER_EVENT_T *userData);


/*Prototoye of the reset machine function */
void smResetMachine(SM_INSTANCEDATA_T * const instanceVar);

// Helper(s) to find out if the machine is in a certain state
uint8_t smIsInSA(const SM_INSTANCEDATA_T * const instanceVar);
uint8_t smIsInSB(const SM_INSTANCEDATA_T * const instanceVar);


/* Macros to test if the machine is in a certain state. */
#define SM_IS_IN_SA(instance)((((&instance)->stateVar==SA)) ? (1U) : (0U))
#define SM_IS_IN_SB(instance)((((&instance)->stateVar==SB)) ? (1U) : (0U))


/* Helper returning the innermost active state.*/
SM_STATES_T smGetInnermostActiveState(const SM_INSTANCEDATA_T * const instanceVar);

#endif
