#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
    : m_Shape(L' ') // ' '이 아닌 L' '인 이유는, char가 아닌 wchar_t이기 때문.
    , m_X(0.f)
    , m_Y(0.f)
{
}

Object::~Object()
{
}

void Object::Update(float _dt)
{
}

void Object::Render()
{
    // 현재 내 위치(m_X, m_Y)에 내 모습(m_Shape)을 콘솔이 그리도록 한다.
	// m_X를 2배 곱하는 이유는 cmd에서 x좌표 길이가 y좌표 길이의 절반이기 때문.
	Console::GetInstance().Print(m_Shape, (short)(m_X * 2), (short)m_Y);
}

bool Object::Move(Direction _dir, float _distance)
{
    RECT boundaryBox = Console::GetInstance().GetBoundaryBox();

	// cmd 좌표계인 boundartBox를 인게임 좌표계로 변환하여 계산하도록 한다.
	// cmd 좌표계에선 x가 y의 길이가 다르기 때문에 인게임 좌표계산 과정에 바로 쓰기에 부적절하다.
	float minX = (float)boundaryBox.left / 2;
	float maxX = (float)boundaryBox.right / 2;
	float minY = (float)boundaryBox.top;
	float maxY = (float)boundaryBox.bottom;

    switch (_dir)
    {
    case Direction::UP:
        {
            // 현재 y좌표가 위쪽 경계선보다 크면(아래쪽이면) 위쪽으로 이동이 가능하다.
            if (m_Y > minY)
            {
                // 요청된 거리만큼 이동을 시도하며, 바운더리를 넘어서지 않도록 처리한다.
                // std::max는 두개의 인자중 더 큰것을 반환하는 함수이다.
                // 즉, m_Y - _distance 가 바운더리보다 작으면, 바운더리값을 반환하여 그 이하값이 나오지 않게한다.
                m_Y = std::max<float>(m_Y - _distance, minY);

                // 여기에 왔다는건 어찌됐든 어느정도 이동은 한다는 뜻이다.
                return true;
            }
        }
        break;
    case Direction::DOWN:
        {
            // 현재 y좌표가 아래쪽 경계선보다 작으면(위쪽이면) 아래쪽으로 이동이 가능하다.
            if (m_Y < maxY)
            {
                m_Y = std::min<float>(m_Y + _distance, maxY);
                return true;
            }
        }
        break;
    case Direction::LEFT:
        {
            // 현재 x좌표가 왼쪽 경계선보다 크면(오른쪽이면) 왼쪽으로 이동이 가능하다.
            if (m_X > minX)
            {
                m_X = std::max<float>(m_X - _distance, minX);
                return true;
            }
        }
        break;
    case Direction::RIGHT:
        {
            // 현재 x좌표가 오른쪽 경계선보다 작으면(왼쪽이면) 오른쪽으로 이동이 가능하다.
            if (m_X < maxX)
            {
                m_X = std::min<float>(m_X + _distance, maxX);
                return true;
            }
        }
        break;
    }
    // 여기에 왔다는건 아무 이동도 하지 않았다는 뜻이다.
    return false;
}
