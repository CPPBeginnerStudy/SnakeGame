#pragma once
// [virtual 키워드의 의미]
// 어떤 클래스들을 서로 상속관계에 놓을 때 virtual 키워드가 어떤 역할을 하는지 간략히 설명하면,
// 1. 클래스 정의에서 virtual 키워드가 하나라도 존재하면 그 클래스에 대해 virtual 테이블이 생성된다.
// 2. 이 테이블에는 virtual 키워드로 선언된 멤버 함수들의 주소가 저장된다.
// 3. 이 테이블을 가리키는 포인터값이 해당 클래스를 생성할 때 숨겨진 멤버변수로 추가된다.
// 4. 생성된 인스턴스가 현재 부모클래스의 포인터타입으로 저장되어 있다고 하더라도,
//    그 숨겨진 멤버변수의 포인터값은 생성시의 클래스(원래 자신의 클래스)에 대한 virtual 테이블을 가리키고 있기 때문에
//    virtual 키워드가 있는 함수를 호출하는 경우 그 테이블을 참조하여 원래 자신의 함수를 찾아서 호출할 수 있게 된다.
// 참고 이미지: https://candide-guevara.github.io/diagram/cpp/2015/07/07/cpp-virtual-table.html
// 위 이미지에서 Object1은 new BaseClass()로 생성됐고, Object2는 new DerivedClass()로 생성됐다고 보면 된다.
class Object
{
public:
    Object();
    virtual ~Object();

    virtual void    Update();
    virtual void    Render();

public:
    wchar_t         GetShape() const { return m_Shape; }
    float           GetX() const { return m_X; }
    float           GetY() const { return m_Y; }

    void            SetShape(wchar_t _shape) { m_Shape = _shape; }
    void            SetX(float _x) { m_X = _x; }
    void            SetY(float _y) { m_Y = _y; }

    // private: 범위는 온전히 본 클래스 내에서만 접근이 가능하기 때문에
    // protected: 범위로 변경하였다. 이 범위는 자식 클래스에서도 접근이 가능한 범위이다.
protected:
    // 렌더링될 객체는 자신의 모양을 하나의 문자(wchar_t)로 나타내며,
    // x, y 좌표를 통해 현재 위치를 알 수 있게 한다.
    // cmd관련 라이브러리 함수에서 좌표값들을 short타입으로 다루기 때문에
    // 여기서도 short타입으로 좌표변수를 지정한다.
    wchar_t         m_Shape;
    float           m_X;
    float           m_Y;

    // 현재 이동방향을 오른쪽/왼쪽 구분, 위/아래 구분 하기 위한 변수이다.
    bool            m_IsRight;
    bool            m_IsBottom;
};
