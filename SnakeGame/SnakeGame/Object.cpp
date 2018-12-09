#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
    : m_Shape(L' ') // ' '�� �ƴ� L' '�� ������, char�� �ƴ� wchar_t�̱� ����.
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
    // ȭ���� �ٿ������ ����� �ϸ� �ݴ� �������� ��ȯ�Ͽ� ��� �����̵��� �ϴ� �ڵ�
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
    // ���� �� ��ġ(m_X, m_Y)�� �� ���(m_Shape)�� �ܼ��� �׸����� �Ѵ�.
    Console::GetInstance().Print(m_Shape, (short)m_X, (short)m_Y);
}
