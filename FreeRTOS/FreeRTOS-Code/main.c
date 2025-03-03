/* Standard includes. */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

// state machine includes
#include "sm_ext.h"
#include "user_defined_event.h"
#include "sm.h"

void tA(void* pvParameters);
void  prvInitialiseHeap(void);
void timerCallback(TimerHandle_t xTimerHandle);

QueueHandle_t queueHandle = NULL;
TimerHandle_t timerHandle = NULL;

SM_INSTANCEDATA_T instDataSM = SM_INSTANCEDATA_INIT;

int main( void ){
	prvInitialiseHeap();
	vTraceEnable( TRC_START );

    xTaskCreate(tA, "TA", 1000 /*Bytes stack*/, NULL /* no parameters */,
        tskIDLE_PRIORITY + 1, NULL);

    
    /* Create the queue. */
    queueHandle = xQueueCreate(32, sizeof(USER_EVENT_T));
    
    timerHandle = xTimerCreate("Timer",				/* The text name assigned to the software timer - for debug only as it is not used by the kernel. */
        1000,		        /* ticks -> 1s */
        true,			    /* true = repetitive */
        NULL,				/* The timer's ID is not used. */
        timerCallback);/* The function executed when the timer expires. */

    xTimerStart(timerHandle, 0); /* The scheduler has not started so use a block time of 0. */

    vTaskStartScheduler();


}

/* This is the software timer callback function.  The software timer has a
    period of two seconds and is reset each time a key is pressed.  This
    callback function will execute if the timer expires */
void timerCallback(TimerHandle_t xTimerHandle){
    static uint8_t cnt = 0;
    cnt++;

    USER_EVENT_T data = {evTimeout, cnt};

    /* Avoid compiler warnings resulting from the unused parameter. */
    (void)xTimerHandle;

    /* Send to the queue. This function is called from the timer/daemon task, so
    must not block.  Hence the block time is set to 0. */
    xQueueSend(queueHandle, &data, 0U);
}


static void tA(void* xTimerHandle){
    /* Avoid compiler warnings resulting from the unused parameter. */
    (void)xTimerHandle;
    USER_EVENT_T data = { SM_NO_MSG , 0 };
    
    while(true){
        printf("TA task.\r\n");

        /* Wait until something arrives in the queue - this task will block
        indefinitely. */

        // call once to init
        sm(&instDataSM, &data);

        while (true) {
            xQueueReceive(queueHandle, &data, portMAX_DELAY);        
            sm(&instDataSM, &data);
            // stop after n times
            if (data.counter == 10) {
                xTimerStop(timerHandle, 0);
            }
        }
    }
}