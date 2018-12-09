#include "pch.h"
#include "RandomSpeedObj.h"
#include "Console.h"


// 상속받은 클래스의 생성자는 부모클래스의 생성자가 먼저 호출된 이후에 이 생성자가 호출된다.
// 이는 따로 코드를 추가하지 않아도 자동으로 수행되는 작업이다.
// 따라서 자식클래스들은 부모클래스의 멤버변수 초기화를 신경쓰지 않아도 된다. (부모생성자가 해주므로)
// 예제코드)
// class A { virtual ~A(){} }
// class B : public A { virtual ~B(){} }
// class C : public B { virtual ~C(){} }
// int main()
// {
//     C* pC = new C(); // A생성자->B생성자->C생성자 순으로 호출됨.
// }
RandomSpeedObj::RandomSpeedObj()
    : m_XSpeed(0.f)
    , m_YSpeed(0.f)
{
}

// 상속받은 클래스의 소멸자는 자신이 먼저 호출된 후 부모클래스의 소멸자를 호출한다.
// 이는 따로 코드를 추가하지 않아도 자동으로 수행되는 작업이다.
// 생성자와 호출순서가 반대인 이유는 여러가지가..있는데 간단히 요약하면,
// 할당해제는 할당된 순서의 반대로 진행되는 것이 안전하고 효율적이기 때문
// 예제코드)
// class A { virtual ~A(){} }
// class B : public A { virtual ~B(){} }
// class C : public B { virtual ~C(){} }
// int main()
// {
//     A* pC = new C(); // A생성자->B생성자->C생성자 순으로 호출됨.
//     delete pC;       // C소멸자->B소멸자->A소멸자 순으로 호출됨.
//     // 그리고 여기서 눈치챘을 수도 있겠지만,
//     // 생성자는 항상 실제 자신을 아는 상태이기 때문에 virtual 키워드가 필요없지만
//     // 소멸자는 소멸시점에 부모클래스 포인터타입에 저장된 변수를 통해 delete할 가능성이 있기 때문에
//     // virtual 키워드가 없다면 실제 자신의 소멸자를 찾을 수가 없어서 반드시 키워드를 추가해야 하는 것이다.
//     // 위 코드에서 만약 virtual 키워드가 없었다면, A소멸자만 호출되어 메모리 릭이 발생한다.
// }
RandomSpeedObj::~RandomSpeedObj()
{
}

void RandomSpeedObj::Init()
{
    // 오버라이딩한 함수는 기본적으로 부모함수를 호출하지 않는다.
    // 따라서 부모함수도 호출할 필요가 있을 경우 아래와 같이 부모클래스::함수명 으로 호출해준다.
    // Init()의 경우는 부모의 Init()을 먼저 호출하고, 추가로 나(자식)가 초기화할 것을 해준다.
    Object::Init();
    m_XSpeed = 1.f;
    m_YSpeed = 1.f;
}

void RandomSpeedObj::Release()
{
    // 부모 클래스의 구현과 다르게 처리할 게 없다면, 그냥 부모꺼를 여기서 다시 호출해주면 된다.
    Object::Release();
}

void RandomSpeedObj::Update()
{
    // Update()의 경우는 부모의 구현을 아예 쓰지 않고, 새롭게 구현을 재정의하기 위해
    // 부모의 Update()를 호출하지 않은 점 참고.
    RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
    if (m_IsRight)
    {
        m_X += 2 * m_XSpeed;
        if (m_X > boundaryBox.right)
        {
            m_X = boundaryBox.right;
            m_IsRight = false;
            m_XSpeed = (rand() % 5 + 1) * 0.5f; // 0.5배 ~ 3배
        }
    }
    else
    {
        m_X -= 2 * m_XSpeed;
        if (m_X < boundaryBox.left)
        {
            m_X = boundaryBox.left;
            m_IsRight = true;
            m_XSpeed = (rand() % 6 + 1) * 0.5f;
        }
    }
    if (m_IsBottom)
    {
        m_Y += 1 * m_YSpeed;
        if (m_Y > boundaryBox.bottom)
        {
            m_Y = boundaryBox.bottom;
            m_IsBottom = false;
            m_YSpeed = (rand() % 6 + 1) * 0.5f;
        }
    }
    else
    {
        m_Y -= 1 * m_YSpeed;
        if (m_Y < boundaryBox.top)
        {
            m_Y = boundaryBox.top;
            m_IsBottom = true;
            m_YSpeed = (rand() % 6 + 1) * 0.5f;
        }
    }
}

void RandomSpeedObj::Render()
{
    Object::Render();
}
