#pragma once
#include "Object.h"
class Apple : public Object
{
public:
    Apple();
    virtual ~Apple();

    virtual void    Update(float _dt) override;
    virtual void    Render() override;

    virtual bool    HitCheck(Object* _pOther) override;
    virtual void    OnHit(Object* _pHitter) override;

    void            RandomMovePosition();
};
