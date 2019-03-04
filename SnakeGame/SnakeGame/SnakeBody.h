#pragma once
#include "Object.h"
class SnakeBody : public Object
{
public:
    SnakeBody();
    virtual ~SnakeBody();

    virtual void        Update(float _dt) override;
    virtual void        Render() override;

public:
    int                 GetSpeed() const { return m_Speed; }
    void                SetSpeed(int _speed) { m_Speed = _speed; }

    void                OnKeyPress(BYTE _key);
    void                AddTail();

private:
    int                 m_Speed;
    Direction           m_Direction;
    std::list<Object*>  m_TailList;
};
