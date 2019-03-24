#include "pch.h"
#include "Apple.h"
#include "Console.h"
#include "GameManager.h"


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
