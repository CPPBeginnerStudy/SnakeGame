#pragma once
#include "Object.h"
class DeathZone : public Object
{
public:
    DeathZone();
    virtual ~DeathZone();

    virtual void        Update(float _dt) override;
    virtual void        Render() override;

    virtual bool        HitCheck(Object* _pOther) override;
    virtual void        OnHit(Object* _pHitter) override;

    void                GenerateLines();
    void                DestroyLines();

    bool                IsInDeathZone(Object* _pObject) const;

private:
    std::list<Object*>	m_DeathLines;
};
