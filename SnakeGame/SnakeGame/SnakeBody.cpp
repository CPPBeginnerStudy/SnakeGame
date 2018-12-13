#include "pch.h"
#include "SnakeBody.h"
#include "Console.h"


SnakeBody::SnakeBody()
    : m_Speed(1.f)
    , m_Direction(Direction::UP)
{
}

SnakeBody::~SnakeBody()
{
}

void SnakeBody::Update()
{
    // 원래 뱀꼬리잡기 게임의 뱀은 자동으로 이동합니다..
    // 기존의 각각 직접 작성했던 이동 로직을 Move()라는 함수로 만들어놓으니
    // 여기서도 이렇게 코드를 간결하게 짤 수 있게 됩니다.
    Move(m_Direction, m_Speed);
}

void SnakeBody::Render()
{
    Object::Render();
}

void SnakeBody::OnKeyPress(BYTE _key)
{
    // 유저는 방향만 바꿔줄 수 있다.
    switch (_key)
    {
    case VK_UP:
        {
            m_Direction = Direction::UP;
        }
        break;
    case VK_DOWN:
        {
            m_Direction = Direction::DOWN;
        }
        break;
    case VK_LEFT:
        {
            m_Direction = Direction::LEFT;
        }
        break;
    case VK_RIGHT:
        {
            m_Direction = Direction::RIGHT;
        }
        break;
    case 'Z':
        {
            // 이속 줄이기 (최소 0.1배)
            m_Speed = std::max<float>(m_Speed - 0.1f, 0.1f);
        }
        break;
    case 'X':
        {
            // 이속 늘리기 (최대 3배)
            m_Speed = std::min<float>(m_Speed + 0.1f, 3.0f);
        }
        break;
    }
}
