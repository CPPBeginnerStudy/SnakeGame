#pragma once
#include "Object.h"
// 어떤 클래스를 상속 받는 경우 아래처럼 : public 부모클래스 를 뒤에 붙여준다.
// 그리고 반드시 소멸자에 virtual가 붙어야 한다.
class RandomSpeedObj : public Object
{
public:
    RandomSpeedObj();
    virtual ~RandomSpeedObj();

    // 상속받는(오버라이딩) 함수들은 뒤에 override 키워드를 붙여준다.
    virtual void    Update() override;
    virtual void    Render() override;

private:
    float           m_XSpeed;
    float           m_YSpeed;

	// 현재 이동방향을 오른쪽/왼쪽 구분, 위/아래 구분 하기 위한 변수이다.
	bool            m_IsRight;
	bool            m_IsBottom;
};
