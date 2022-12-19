/*
 * button.h
 *
 *  Created on: Nov 22, 2022
 *      Author: student
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"
class button
{
private:

	GPIO_TypeDef*  GPIOx;
	uint16_t GPIO_Pin;
public:
	button();
	virtual ~button();
};

#endif /* INC_BUTTON_H_ */
