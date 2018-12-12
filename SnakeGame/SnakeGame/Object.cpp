#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
    : m_Shape(L' ') // ' '이 아닌 L' '인 이유는, char가 아닌 wchar_t이기 때문.
    , m_X(0.f)
    , m_Y(0.f)
    , m_IsRight(false)
    , m_IsBottom(false)
{
}

Object::~Object()
{
}

void Object::Update()
{
    // 화면의 바운더리를 벗어나려 하면 반대 방향으로 전환하여 계속 움직이도록 하는 코드
    // [삼항연산자]
    //   - 간단하게 if문과 같은 분기처리를 하고 싶을 때 사용.
    //   - 아래와 같이 3개의 항이 존재해서 삼항연산자라고 부르며,
    //   - 첫항에서의 true/false여부의 따라 true인 경우 둘째항, false인 경우 셋째항이 수행된다.
    //     (평가식) ? (true인 경우) : (false인 경우)
    //   - 즉, 아래의 코드는 m_IsRight의 값이 true인 경우 Move()함수의 인자로 RIGHT를 넘기게 되고,
    //     false인 경우 LEFT를 넘기게 하는 코드이다.
    if (!Move(m_IsRight ? Direction::RIGHT : Direction::LEFT, 1.f))
    {
        // 이동이 실패하면(바운더리에 걸리면) 반대 방향으로 전환
        // 아래의 코드는 bool값 변수가 자신의 값을 반전시키는 코드이다. (true->false, false->true)
        m_IsRight = !m_IsRight;
    }
    if (!Move(m_IsBottom ? Direction::DOWN : Direction::UP, 1.f))
    {
        m_IsBottom = !m_IsBottom;
    }
}

void Object::Render()
{
    // 현재 내 위치(m_X, m_Y)에 내 모습(m_Shape)을 콘솔이 그리도록 한다.
    Console::GetInstance().Print(m_Shape, (short)m_X, (short)m_Y);
}

bool Object::Move(Direction _dir, float _distance)
{
    RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
    switch (_dir)
    {
    case Direction::UP:
        {
            // 현재 y좌표가 위쪽 경계선보다 크면(아래쪽이면) 위쪽으로 이동이 가능하다.
            if (m_Y > boundaryBox.top)
            {
                // 요청된 거리만큼 이동을 시도하며, 바운더리를 넘어서지 않도록 처리한다.
                // std::max는 두개의 인자중 더 큰것을 반환하는 함수이다.
                // 즉, m_Y - _distance 가 바운더리보다 작으면, 바운더리값을 반환하여 그 이하값이 나오지 않게한다.
                m_Y = std::max<float>(m_Y - _distance, boundaryBox.top);

                // 여기에 왔다는건 어찌됐든 어느정도 이동은 한다는 뜻이다.
                return true;
            }
        }
        break;
    case Direction::DOWN:
        {
            // 현재 y좌표가 아래쪽 경계선보다 작으면(위쪽이면) 아래쪽으로 이동이 가능하다.
            if (m_Y < boundaryBox.bottom)
            {
                m_Y = std::min<float>(m_Y + _distance, boundaryBox.bottom);
                return true;
            }
        }
        break;
    case Direction::LEFT:
        {
            // 현재 x좌표가 왼쪽 경계선보다 크면(오른쪽이면) 왼쪽으로 이동이 가능하다.
            if (m_X > boundaryBox.left)
            {
                // 거리를 2배 곱하는 이유는 x좌표가 y좌표의 절반이기 때문.
                m_X = std::max<float>(m_X - _distance * 2, boundaryBox.left);
                return true;
            }
        }
        break;
    case Direction::RIGHT:
        {
            // 현재 x좌표가 오른쪽 경계선보다 작으면(왼쪽이면) 오른쪽으로 이동이 가능하다.
            if (m_X < boundaryBox.right)
            {
                m_X = std::min<float>(m_X + _distance * 2, boundaryBox.right);
                return true;
            }
        }
        break;
    }
    // 여기에 왔다는건 아무 이동도 하지 않았다는 뜻이다.
    return false;
}
