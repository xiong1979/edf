/*****************************************************************************
* MIT License:
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*
* Contact information:
* <9183399@qq.com>
*****************************************************************************/
#include <osal.h>


T_HANDLE TaskCreate(	TaskExec pxTaskCode,
                        const char * const pcName,
                        const uint16_t usStackDepth,
                        void * const pvParameters,
                        uint32_t uxPriority )
{
    T_HANDLE CreatedTask;

    xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, &CreatedTask);

    return CreatedTask;
}


Q_HANDLE QueueCreate( const uint32_t uxQueueLength, const uint32_t uxItemSize)
{
    return xQueueCreate(uxQueueLength, uxItemSize);
}

uint32_t QueueReceive(Q_HANDLE Q, void * const pvBuffer, uint32_t TimeOut)
{
    return xQueueReceive(Q, pvBuffer, TimeOut);
}



/*..........................................................................*/
/*..........................................................................*/
void QueueSend(Q_HANDLE q, void const * const p, bool FromISR)
{
	BaseType_t status;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if (FromISR)
	{
		status = xQueueSendFromISR(q, (void *)&p, &xHigherPriorityTaskWoken);
	}
	else
	{
		status = xQueueSend(q, (void *)&p, (TickType_t)0);
	}
    configASSERT(status == pdTRUE);
}


/*..........................................................................*/




extern void TimeEvent_tickFromISR();
/* Application hooks used in this project ==================================*/
/* NOTE: only the "FromISR" API variants are allowed in vApplicationTickHook*/
extern "C"
{

void vApplicationTickHook(void) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;


    /* perform clock tick processing */
    TimeEvent_tickFromISR();

    /* notify FreeRTOS to perform context switch from ISR, if needed */
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
}
