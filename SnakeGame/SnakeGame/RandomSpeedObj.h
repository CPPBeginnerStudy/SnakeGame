#pragma once
#include "Object.h"
// � Ŭ������ ��� �޴� ��� �Ʒ�ó�� : public �θ�Ŭ���� �� �ڿ� �ٿ��ش�.
// �׸��� �ݵ�� �Ҹ��ڿ� virtual�� �پ�� �Ѵ�.
class RandomSpeedObj : public Object
{
public:
    RandomSpeedObj();
    virtual ~RandomSpeedObj();

    // ��ӹ޴�(�������̵�) �Լ����� �ڿ� override Ű���带 �ٿ��ش�.
    virtual void    Init() override;
    virtual void    Release() override;
    virtual void    Update() override;
    virtual void    Render() override;

private:
    float           m_XSpeed;
    float           m_YSpeed;
};

