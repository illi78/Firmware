/* (c) Sinelabore Software Tools GmbH - All rights reserved. Reproduction, modification,
   use or disclosure to third parties without express
   authority is forbidden. Generator running in demo mode!
   Please purchase a license if you want to use this software in projects.
 */

/* Command line options: -p ssc -E sm.xml   */
/* This file is generated from sm.xml - do not edit manually  */
/* Generated on: Sat Mar 20 21:42:40 CET 2021 / Version 5.0.6b3 */


#include <stdint.h>
#include <stdbool.h>
#include "sm_ext.h"
#include "user_defined_event.h"
#include "sm.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

extern TimerHandle_t timerHandle;



void  sm(SM_INSTANCEDATA_T *instanceVar, USER_EVENT_T *userData){
	
	/*execute entry code of default state once to init machine */
	if(instanceVar->saEntry==1U){
		printf("Entering SA\n");
		

		instanceVar->saEntry=0U;
	}


	switch (instanceVar->stateVar) {

		case SA:
			if(userData->msg==(SM_EVENT_T)evTimeout){
				/* Transition from SA to SB */
				/* OnExit code of state SA */
				printf("Leaving SA\n");

				/* Action code for transition  */
				printf("evTimeout with counter=%d\n",userData->counter);


				/* OnEntry code of state SB */
				printf("Entering SB\n");

				/* adjust state variables  */
				instanceVar->stateVar = SB;
			}else{
				/* Intentionally left blank */
			} /*end of event selection */
		break; /* end of case SA  */

		case SB:
			if(userData->msg==(SM_EVENT_T)evTimeout){
				/* Transition from SB to SA */
				/* OnExit code of state SB */
				printf("Leaving SB\n");

				/* Action code for transition  */
				printf("evTimeout with counter=%d\n",userData->counter);


				/* OnEntry code of state SA */
				printf("Entering SA\n");

				/* adjust state variables  */
				instanceVar->stateVar = SA;
			}else{
				/* Intentionally left blank */
			} /*end of event selection */
		break; /* end of case SB  */

		default:
			/* Intentionally left blank */
		break;
	} /* end switch stateVar_root */
}

/* Implementation of the reset machine function */
void smResetMachine(SM_INSTANCEDATA_T * const instanceVar){
	instanceVar->saEntry = 1U;
	instanceVar->stateVar = SA;
	
}

// Helper(s) to find out if the machine is in a certain state

uint8_t smIsInSA(const SM_INSTANCEDATA_T * const instanceVar){
	return(((instanceVar->stateVar== SA)) ? (1U) : (0U));
}

uint8_t smIsInSB(const SM_INSTANCEDATA_T * const instanceVar){
	return(((instanceVar->stateVar== SB)) ? (1U) : (0U));
}


// Helper to get id of innermost active state
SM_STATES_T smGetInnermostActiveState(const SM_INSTANCEDATA_T * const instanceVar){
	if(smIsInSB(instanceVar)){
		return SB;
	}else if(smIsInSA(instanceVar)){
		return SA;
	}else{
		return __SM_LAST_STATE__;
	}
}

