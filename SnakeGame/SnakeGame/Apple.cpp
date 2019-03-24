#include "pch.h"
#include "Apple.h"
#include "Console.h"
#include "GameManager.h"
#include "SnakeBody.h"


Apple::Apple()
{
    m_Shape = L'◎';
    m_Color = Color::RED;
}

Apple::~Apple()
{
}

void Apple::Update(float _dt)
{
}

void Apple::Render()
{
    Object::Render();
}

bool Apple::HitCheck(Object* _pOther)
{
    // 사과는 누군가를 때리지 않는다.
    return false;
}

void Apple::OnHit(Object* _pHitter)
{
    // 히터가 뱀이 아니면 생략
    auto pSnake = dynamic_cast<SnakeBody*>(_pHitter);
    if (pSnake == nullptr)
        return;

    // 뱀이 사과를 먹었으면 뱀에 꼬리를 추가해주고, 사과를 다른 곳으로 옮긴다.
    pSnake->AddTail();
    RandomMovePosition();

    // 옮긴 곳에 뱀이 있으면 다시 옮긴다. (겹치지 않을 때까지)
    while (pSnake->HitCheck(this))
    {
        RandomMovePosition();
    }
    // 게임 매니저에게 사과가 먹혔다고 알려준다. (스코어 처리 등을 위해)
    GameManager::GetInstance().OnAppleEaten();
}

void Apple::RandomMovePosition()
{
    auto& gm = GameManager::GetInstance();

    // 난이도가 낮을 수록 사과의 랜덤이동 가능 범위를 좁혀준다.
    int rangeFactor = 12 - gm.GetGameLevel();
    if (rangeFactor < 1)
    {
        // 이 이상의 난이도에서는 바운더리에서 1칸씩 내의 범위로 이동하게 한다.
        rangeFactor = 1;
    }
    RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
    boundaryBox.left += rangeFactor;
    boundaryBox.top += rangeFactor;
    boundaryBox.right -= rangeFactor;
    boundaryBox.bottom -= rangeFactor;

    m_X = gm.GetRandom(boundaryBox.left, boundaryBox.right);
    m_Y = gm.GetRandom(boundaryBox.top, boundaryBox.bottom);
}
