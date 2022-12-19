



#ifndef INC_TIMERTASK_H_
#define INC_TIMERTASK_H_

class TimerTask
{
public:
	virtual void timerFunc() = 0;
	virtual ~TimerTask() {}
};



#endif /* INC_TIMERTASK_H_ */
