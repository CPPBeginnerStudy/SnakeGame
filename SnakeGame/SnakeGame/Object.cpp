#include "pch.h"
#include "Object.h"
#include "Console.h"
#include "Timer.h"


Object::Object()
    : m_Shape(L' ') // ' '이 아닌 L' '인 이유는, char가 아닌 wchar_t이기 때문.
    , m_Color(Color::WHITE)
    , m_X(0)
    , m_Y(0)
{
    // 업데이트 주기를 다르게 갖기 위한 타이머
    m_pUpdateTimer = new Timer();
}

Object::~Object()
{
    delete m_pUpdateTimer;
}

void Object::Update(float _dt)
{
}

void Object::Render()
{
    // 현재 내 위치(m_X, m_Y)에 내 모습(m_Shape)을 콘솔이 그리도록 한다.
    // m_X를 2배 곱하는 이유는 cmd에서 x좌표 길이가 y좌표 길이의 절반이기 때문.
    Console::GetInstance().Print(m_Shape, m_Color, (short)(m_X * 2), (short)m_Y);
}

bool Object::Move(Direction _dir, int _distance)
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
                m_Y = std::max<int>(m_Y - _distance, boundaryBox.top);

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
                m_Y = std::min<int>(m_Y + _distance, boundaryBox.bottom);
                return true;
            }
        }
        break;
    case Direction::LEFT:
        {
            // 현재 x좌표가 왼쪽 경계선보다 크면(오른쪽이면) 왼쪽으로 이동이 가능하다.
            if (m_X > boundaryBox.left)
            {
                m_X = std::max<int>(m_X - _distance, boundaryBox.left);
                return true;
            }
        }
        break;
    case Direction::RIGHT:
        {
            // 현재 x좌표가 오른쪽 경계선보다 작으면(왼쪽이면) 오른쪽으로 이동이 가능하다.
            if (m_X < boundaryBox.right)
            {
                m_X = std::min<int>(m_X + _distance, boundaryBox.right);
                return true;
            }
        }
        break;
    }
    // 여기에 왔다는건 아무 이동도 하지 않았다는 뜻이다.
    return false;
}
