#pragma once
#include "Object.h"
class Apple : public Object
{
public:
	Apple();
	virtual ~Apple();

	virtual void    Update(float _dt);
	virtual void    Render();
};
