/*
 * cppCli.h
 *
 *  Created on: 6 Nov 2022
 *      Author: student
 */

#ifndef INC_CPPCLI_H_
#define INC_CPPCLI_H_

class cppCli {
public:
	virtual void execute(char * data) = 0;
	void cliInit();
	cppCli();
	virtual ~cppCli();
};

typedef enum State {
	NORMAL, CRITICAL, WARNING
} SystemState;

class threshold
{
private:
	uint8_t crit;
	SystemState thresholdState = NORMAL;
	uint8_t warning;
	const char *massage;
	const char * Mcritical = " is critical**";
	const char * Mnormal = "is normal";
	const char * Mwarning = " is above normal!!!";
public:
	threshold(uint8_t _crit , uint8_t _warning):
			crit(_crit) ,warning(_warning) {}
	void setcrit(uint32_t newcrit)
	{
		crit = newcrit;
	}
	void setwarning(uint32_t newwarninng)
	{
		warning = newwarninng;

	}
	uint32_t getcrit()
	{
		return crit;
	}
	uint32_t getwarninng()
	{
		return warning;
	}
	const char * getmassage(double temp)
	{
		if(temp > crit)
		{
			massage = Mcritical;
		}
		else if(temp > warning)
		{
			massage = Mwarning;
		}
		else
		{
			massage = Mnormal;
		}
		return massage;
	}
	void setState(double temp)
	{
		if(temp > crit)
		{
			thresholdState = CRITICAL;
		}
		else if(temp > warning)
		{
			thresholdState = WARNING;
		}
		else
		{
			thresholdState = NORMAL;
		}
	}
	SystemState getState()
	{
		return thresholdState;
	}


};
#endif /* INC_CPPCLI_H_ */
