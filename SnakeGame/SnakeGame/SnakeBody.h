#pragma once
#include "Object.h"
class SnakeBody : public Object
{
public:
    SnakeBody();
    virtual ~SnakeBody();

    virtual void    Update() override;
    virtual void    Render() override;

public:
    float           GetSpeed() const { return m_Speed; }
    void            SetSpeed(float _speed) { m_Speed = _speed; }

    void            OnKeyPress(BYTE _key);

private:
    float           m_Speed;
};
