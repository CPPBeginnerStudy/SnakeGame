#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
    : m_Shape(' ')
    , m_X(0)
    , m_Y(0)
    , m_IsRight(true)
    , m_IsBottom(true)
{
}

Object::~Object()
{
}

void Object::Init()
{
}

void Object::Release()
{
}

void Object::Update()
{
    RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
    if (m_IsRight)
    {
        ++m_X;
        if (m_X > boundaryBox.right)
        {
            m_X = boundaryBox.right;
            m_IsRight = false;
        }
    }
    else
    {
        --m_X;
        if (m_X < boundaryBox.left)
        {
            m_X = boundaryBox.left;
            m_IsRight = true;
        }
    }
    if (m_IsBottom)
    {
        ++m_Y;
        if (m_Y > boundaryBox.bottom)
        {
            m_Y = boundaryBox.bottom;
            m_IsBottom = false;
        }
    }
    else
    {
        --m_Y;
        if (m_Y < boundaryBox.top)
        {
            m_Y = boundaryBox.top;
            m_IsBottom = true;
        }
    }
}

void Object::Render()
{
    Console::GetInstance().Print(m_Shape, m_X, m_Y);
}
