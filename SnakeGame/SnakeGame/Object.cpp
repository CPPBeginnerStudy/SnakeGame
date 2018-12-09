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
    RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
    if (m_IsRight)
    {
        m_X += 2.f;
        if (m_X > boundaryBox.right)
        {
            m_X = boundaryBox.right;
            m_IsRight = false;
        }
    }
    else
    {
        m_X -= 2.f;
        if (m_X < boundaryBox.left)
        {
            m_X = boundaryBox.left;
            m_IsRight = true;
        }
    }
    if (m_IsBottom)
    {
        m_Y += 1.f;
        if (m_Y > boundaryBox.bottom)
        {
            m_Y = boundaryBox.bottom;
            m_IsBottom = false;
        }
    }
    else
    {
        m_Y -= 1.f;
        if (m_Y < boundaryBox.top)
        {
            m_Y = boundaryBox.top;
            m_IsBottom = true;
        }
    }
}

void Object::Render()
{
    // 현재 내 위치(m_X, m_Y)에 내 모습(m_Shape)을 콘솔이 그리도록 한다.
    Console::GetInstance().Print(m_Shape, (short)m_X, (short)m_Y);
}
