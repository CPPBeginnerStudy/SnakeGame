#pragma once
#include "Object.h"
class SnakeBody : public Object
{
public:
    SnakeBody();
    virtual ~SnakeBody();

    virtual void    Init() override;
    virtual void    Release() override;
    virtual void    Update() override;
    virtual void    Render() override;

    float           GetSpeed() const { return m_Speed; }
    void            SetSpeed(float _speed) { m_Speed = _speed; }

    void            OnKeyPress(BYTE _key);

private:
    float           m_Speed;
};

