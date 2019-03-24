#include "pch.h"
#include "DeathZone.h"
#include "Console.h"


DeathZone::DeathZone()
{
}

DeathZone::~DeathZone()
{
    DestroyLines();
}

void DeathZone::Update(float _dt)
{
}

void DeathZone::Render()
{
    for (auto& pObject : m_DeathLines)
    {
        pObject->Render();
    }
}

bool DeathZone::HitCheck(Object* _pOther)
{
    // 상대가 없거나, 자신이라면 생략
    if (_pOther == nullptr || _pOther == this)
        return false;

    // 데스라인 객체 중 하나라도 상대객체와 부딪히면 나머지 데스라인과의 체크는 생략한다.
    for (auto& pObject : m_DeathLines)
    {
        if (pObject->GetX() == _pOther->GetX() &&
            pObject->GetY() == _pOther->GetY())
            return true;
    }
    return false;
}

void DeathZone::OnHit(Object* _pHitter)
{
    // 데스존은 누군가에게 맞지 않는다.
}

void DeathZone::GenerateLines()
{
    DestroyLines();

    // 왼쪽상단부터 시작해서 오른쪽->아래->왼쪽->위 순으로 이동하며 바운더리에 데스라인을 만든다.
    RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
    int x = boundaryBox.left;
    int y = boundaryBox.top;
    Direction dir = Direction::RIGHT;
    while (true)
    {
        switch (dir)
        {
        case Direction::UP:     --y;    break;
        case Direction::DOWN:   ++y;    break;
        case Direction::LEFT:   --x;    break;
        case Direction::RIGHT:  ++x;    break;
        }
        if (x > boundaryBox.right)
        {
            x = boundaryBox.right;
            dir = Direction::DOWN;
        }
        else if (y > boundaryBox.bottom)
        {
            y = boundaryBox.bottom;
            dir = Direction::LEFT;
        }
        else if (x < boundaryBox.left)
        {
            x = boundaryBox.left;
            dir = Direction::UP;
        }
        else if (y < boundaryBox.top)
        {
            // 위의 끝까지 도달하면 루프 종료
            break;
        }
        Object* pObject = new Object();
        pObject->SetX(x);
        pObject->SetY(y);
        pObject->SetShape(L'▨');
        pObject->SetColor(Color::DARK_YELLOW);
        m_DeathLines.push_back(pObject);
    }
}

void DeathZone::DestroyLines()
{
    for (auto& pObject : m_DeathLines)
    {
        delete pObject;
    }
}

bool DeathZone::IsInDeathZone(Object* _pObject) const
{
    if (_pObject == nullptr)
        return false;

    for (auto& pObject : m_DeathLines)
    {
        if (pObject->GetX() == _pObject->GetX() &&
            pObject->GetY() == _pObject->GetY())
            return true;
    }
    return false;
}
