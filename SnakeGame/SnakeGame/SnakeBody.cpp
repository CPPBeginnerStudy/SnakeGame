#include "pch.h"
#include "SnakeBody.h"
#include "Console.h"
#include "GameManager.h"
#include "DeathZone.h"


SnakeBody::SnakeBody()
    : m_Speed(1)    // 1번 업데이트 될 때에 몇 칸을 움직일지 정하는 수치이다.
    , m_Direction(Direction::UP)
{
    m_Shape = L'▣';
    m_Color = Color::GREEN;
}

SnakeBody::~SnakeBody()
{
    // 만약에 꼬리가 있으면 함께 할당해제 해준다.
    ClearTails();
}

void SnakeBody::Update(float _dt)
{
    // 원래 뱀꼬리잡기 게임의 뱀은 자동으로 이동합니다..
    // 기존의 각각 직접 작성했던 이동 로직을 Move()라는 함수로 만들어놓으니
    // 여기서도 이렇게 코드를 간결하게 짤 수 있게 됩니다.

    // 움직이기 전에 먼저 원래 위치를 보관해놓는다.
    // 다음 꼬리가 이 보관된 위치로 이동한다.
    int prevX = m_X;
    int prevY = m_Y;
    Move(m_Direction, m_Speed);

    // 각 꼬리는 이전 꼬리의 위치로 셋팅된다. (즉, 따라가는 형태가 된다.)
    for (auto& pTail : m_TailList)
    {
        int tempX = pTail->GetX();
        int tempY = pTail->GetY();
        pTail->SetX(prevX);
        pTail->SetY(prevY);
        prevX = tempX;
        prevY = tempY;
    }
}

void SnakeBody::Render()
{
    Object::Render();

    // 나에게 붙은 꼬리들도 렌더링
    for (auto& pTail : m_TailList)
    {
        pTail->Render();
    }
}

bool SnakeBody::HitCheck(Object* _pOther)
{
    // 상대가 없다면 생략 (자기 자신의 체크는 허용(몸통과 꼬리의 충돌체크를 위해))
    if (_pOther == nullptr)
        return false;

    // 자기 자신이 아닌 경우에는 몸통의 좌표와 먼저 충돌체크를 해준다.
    if (_pOther != this)
    {
        if (m_X == _pOther->GetX() &&
            m_Y == _pOther->GetY())
            return true;
    }
    // 꼬리 객체 중 하나라도 상대객체와 부딪히면 나머지 꼬리와의 체크는 생략한다.
    for (auto& pTail : m_TailList)
    {
        if (pTail->GetX() == _pOther->GetX() &&
            pTail->GetY() == _pOther->GetY())
            return true;
    }
    return false;
}

void SnakeBody::OnHit(Object* _pHitter)
{
    // 히터가 자신이거나(꼬리와의 충돌시) 데스존인 경우 게임 오버 처리한다.
    if (_pHitter == this || dynamic_cast<DeathZone*>(_pHitter) != nullptr)
    {
        GameManager::GetInstance().GameOver();
    }
}

void SnakeBody::OnKeyPress(int _key)
{
    // 유저는 방향만 바꿔줄 수 있다.
    switch (_key)
    {
    case VK_UP:
        {
            if (m_Direction != Direction::DOWN)
            {
                m_Direction = Direction::UP;
            }
        }
        break;
    case VK_DOWN:
        {
            if (m_Direction != Direction::UP)
            {
                m_Direction = Direction::DOWN;
            }
        }
        break;
    case VK_LEFT:
        {
            if (m_Direction != Direction::RIGHT)
            {
                m_Direction = Direction::LEFT;
            }
        }
        break;
    case VK_RIGHT:
        {
            if (m_Direction != Direction::LEFT)
            {
                m_Direction = Direction::RIGHT;
            }
        }
        break;
    }
}

void SnakeBody::AddTail()
{
    Object* pTail = new Object();
    pTail->SetShape(L'□');
    pTail->SetColor(Color::GREEN);
    m_TailList.push_back(pTail);
}

void SnakeBody::ClearTails()
{
    for (auto& pTail : m_TailList)
    {
        delete pTail;
    }
    m_TailList.clear();
}
