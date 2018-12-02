#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
    : m_Shape(' ')
    , m_X(0)
    , m_Y(0)
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
}

void Object::Render()
{
    Console::GetInstance().Print(m_Shape, m_X, m_Y);
}
