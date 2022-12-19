

#pragma once


#ifndef INC_MAINTIMER_H_
#define INC_MAINTIMER_H_

typedef void (*HandlerTime)(void* obj);

void MainTimer_unregisterCallbck(HandlerTime func , void * obj);

void MainTimer_registerCallbck(HandlerTime func , void * obj);
#endif /* INC_MAINTIMER_H_ */
