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
#include <stdint.h>
#include "Event.h"
#include "State.h"


#pragma once

namespace Edf
{
constexpr uint32_t defPrioity = (MAX_PRIORITIES - 5);

class CActive
{
public:
	CActive(char *Name);

	void Start();

	void Start(uint8_t prio, uint32_t queueLen, uint32_t itemSize);

	void Post(Event const *const e);

	static void EventLoop(void *pvParameters) ;

	virtual void Dispatcher(Event const * const e);

	virtual void Initial() = 0;

public:
	Q_HANDLE Q() const
	{
		return queue;
	}

	//State m_State;

private:
    T_HANDLE thread;     /* private thread */
    Q_HANDLE queue;     /* private message queue */


    enum {EQ_SIZE = 10};

    char *m_Name;

public:
	DEF_STATE(CActive);
};
    
} // namespace Edf

#include "Time.h"
#include "publish.h"
