#pragma once
#include "Object.h"
class Apple : public Object
{
public:
	Apple();
	virtual ~Apple();

	virtual void    Update();
	virtual void    Render();
};
