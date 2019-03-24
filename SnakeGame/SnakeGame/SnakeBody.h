#pragma once
#include "Object.h"
class SnakeBody : public Object
{
public:
    SnakeBody();
    virtual ~SnakeBody();

    virtual void        Update(float _dt) override;
    virtual void        Render() override;

    virtual bool        HitCheck(Object* _pOther) override;
    virtual void        OnHit(Object* _pHitter) override;

public:
    int                 GetSpeed() const { return m_Speed; }
    void                SetSpeed(int _speed) { m_Speed = _speed; }

    void                OnKeyPress(int _key);

    void                AddTail();
    void                ClearTails();

private:
    int                 m_Speed;
    Direction           m_Direction;
    std::list<Object*>  m_TailList;
};
