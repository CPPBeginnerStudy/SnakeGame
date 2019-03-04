#include "pch.h"
#include "RandomSpeedObj.h"
#include "Console.h"
#include "Timer.h"


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
    : m_XSpeed(1)
    , m_YSpeed(1)
    , m_IsRight(false)
    , m_IsBottom(false)
{
    m_Shape = L'★';
    m_Color = Color::YELLOW;

    // 0.1초마다 한번 Update()가 실행되도록 한다. (즉, 스피드가 1이면 1초에 10칸 움직이게 한다.)
    m_pUpdateTimer->SetDelay(0.1f);
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

void RandomSpeedObj::Update(float _dt)
{
    // 자신의 주기에 맞춰 시행되도록 한다.
    if (!m_pUpdateTimer->CheckDelay(_dt))
        return;

    // Move()의 리턴값이 false일 때(즉, 바운더리에 닿았을때)
    // 방향을 반전시키고, 속도를 랜덤으로 변경하는 코드.
    // 이렇게 기존의 공통된 로직(이동 로직)을 Move()라는 함수로 추출하니
    // 중복코드가 줄어들고 좀 더 차이점을 파악하기 쉬워졌습니다.
    // [삼항연산자]
    //   - 간단하게 if문과 같은 분기처리를 하고 싶을 때 사용.
    //   - 아래와 같이 3개의 항이 존재해서 삼항연산자라고 부르며,
    //   - 첫항에서의 true/false여부의 따라 true인 경우 둘째항, false인 경우 셋째항이 수행된다.
    //     (평가식) ? (true인 경우) : (false인 경우)
    //   - 즉, 아래의 코드는 m_IsRight의 값이 true인 경우 Move()함수의 인자로 RIGHT를 넘기게 되고,
    //     false인 경우 LEFT를 넘기게 하는 코드이다.
    if (!Move(m_IsRight ? Direction::RIGHT : Direction::LEFT, m_XSpeed))
    {
        // 이동이 실패하면(바운더리에 걸리면) 반대 방향으로 전환
        // 아래의 코드는 bool값 변수가 자신의 값을 반전시키는 코드이다. (true->false, false->true)
        m_IsRight = !m_IsRight;

        // 1 ~ 3으로 이동속도 랜덤조정
        m_XSpeed = rand() % 3 + 1;
    }
    if (!Move(m_IsBottom ? Direction::DOWN : Direction::UP, m_YSpeed))
    {
        m_IsBottom = !m_IsBottom;
        m_YSpeed = rand() % 3 + 1;
    }
}

void RandomSpeedObj::Render()
{
    // 오버라이딩한 함수는 기본적으로 부모함수를 호출하지 않는다.
    // 따라서 부모함수도 호출할 필요가 있을 경우 아래와 같이 부모클래스::함수명 으로 호출해준다.
    // 부모 클래스의 구현과 다르게 처리할 게 없다면, 그냥 부모꺼를 여기서 다시 호출해주면 된다.
    Object::Render();
}
