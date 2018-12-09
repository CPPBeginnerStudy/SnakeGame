#include "pch.h"
#include "SnakeBody.h"
#include "Console.h"


SnakeBody::SnakeBody()
    : m_Speed(0.f)
{
}

SnakeBody::~SnakeBody()
{
}

void SnakeBody::Init()
{
    Object::Init();
    m_Speed = 1.f;
}

void SnakeBody::Release()
{
    Object::Release();
}

void SnakeBody::Update()
{
}

void SnakeBody::Render()
{
    Object::Render();
}

void SnakeBody::OnKeyPress(BYTE _key)
{
    RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
    switch (_key)
    {
    case VK_UP:
        {
            m_Y -= 1 * m_Speed;
            if (m_Y < boundaryBox.top)
            {
                m_Y = boundaryBox.top;
            }
        }
        break;
    case VK_DOWN:
        {
            m_Y += 1 * m_Speed;
            if (m_Y > boundaryBox.bottom)
            {
                m_Y = boundaryBox.bottom;
            }
        }
        break;
    case VK_LEFT:
        {
            // x좌표는 y좌표의 절반 간격이기 때문에 동일한 비율로 움직이려면
            // y좌표보다 2배씩 움직여야 한다.
            m_X -= 2 * m_Speed;
            if (m_X < boundaryBox.left)
            {
                m_X = boundaryBox.left;
            }
        }
        break;
    case VK_RIGHT:
        {
            m_X += 2 * m_Speed;
            if (m_X > boundaryBox.right)
            {
                m_X = boundaryBox.right;
            }
        }
        break;
    case 'Z':
        {
            // 이속 줄이기
            m_Speed -= 0.1f;
            if (m_Speed < 0.1f)
            {
                m_Speed = 0.1f;
            }
        }
        break;
    case 'X':
        {
            // 이속 늘리기
            m_Speed += 0.1f;
            if (m_Speed > 3.f)
            {
                m_Speed = 3.f;
            }
        }
        break;
    }
}
