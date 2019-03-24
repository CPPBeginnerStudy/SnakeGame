#pragma once
#include "Color.hpp"
class Timer;

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
    // 클래스 내부에 또다른 클래스나 enum 등을 정의할 수 있다.
    // 이렇게 내부에 정의한 타입은 그 상위타입의 이름공간 내에 들어간다.
    // 즉, 아래의 Direction이라는 enum은 Object 내에서는 Direction:: 으로 사용 가능하고,
    // Object 외부에서는 Object::Direction:: 으로 사용해야 한다.
    // 이렇게 하는 것의 이점은, 만약에 이런 기능이 없다면 이름을 지을 때마다 매번 같은 의미여도
    // 이름이 중복되지 않도록 이름을 지어야해서 길어지게 될텐데 굳이 그럴필요가 없게 해주는 것이다.
    // 예를들어, class A와 class B에서 각각 Type이라는 enum을 정의하고자 한다면,
    // 내부에서는 간단하게 Type으로 쓰고 외부에서 접근할 때에만 A::Type 처럼 범위를 지정해주면 되는 것.
    // 이러한 기능이 없다면 TypeForA, TypeForB 등 항상 겹치지 않는 이름을 지어야만 한다.
    
    // 그리고 아래의 타입이 그냥 enum이 아니라 enum class 타입인데 이 둘의 차이를 간략히 설명하면,
    // enum은 이름공간이 없고(전역적이고), enum class는 이름공간이 부여된다는 차이가 있다.
    // 예를들어, 아래코드를 그냥 enum으로 정의했으면, 사용할 때 Direction::을 안붙히고 사용하게 되며,
    // 그러면 위에서 설명한 것과 같이 이름 짓기가 까다로워진다. (모든 다른 enum들과도 겹치지 않게해야하기 때문(UP, DOWN 등이))
    enum class Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };
public:
    Object();
    virtual ~Object();

    virtual void    Update(float _dt);
    virtual void    Render();

    virtual bool    HitCheck(Object* _pOther);
    virtual void    OnHit(Object* _pHitter);

public:
    wchar_t         GetShape() const { return m_Shape; }
    Color           GetColor() const { return m_Color; }
    int             GetX() const { return m_X; }
    int             GetY() const { return m_Y; }

    void            SetShape(wchar_t _shape) { m_Shape = _shape; }
    void            SetColor(Color _color) { m_Color = _color; }
    void            SetX(int _x) { m_X = _x; }
    void            SetY(int _y) { m_Y = _y; }

    // 방향과 거리를 인자로 받아서 이동을 수행하고,
    // 실제로 이동을 했는지 여부를 bool값으로 반환하는 함수
    bool            Move(Direction _dir, int _distance);

    // private: 범위는 온전히 본 클래스 내에서만 접근이 가능하기 때문에
    // protected: 범위로 변경하였다. 이 범위는 자식 클래스에서도 접근이 가능한 범위이다.
protected:
    // 렌더링될 객체는 자신의 모양을 하나의 문자(wchar_t)로 나타내며,
    // x, y 좌표를 통해 현재 위치를 알 수 있게 한다.
    wchar_t         m_Shape;
    Color           m_Color;

    // 뱀꼬리잡기 게임 특성상 1칸씩 도트좌표를 움직이도록 구현하는 것이
    // 여러모로 좋기 때문에 실수형 좌표가 아니라 정수형 좌표를 사용한다.
    int             m_X;
    int             m_Y;
};
