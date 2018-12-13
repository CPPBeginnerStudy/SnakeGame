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
    // 만약에 꼬리가 있으면 함께 할당해제 해준다.
    for (auto& pTail : m_TailList)
    {
        delete pTail;
    }
}

void SnakeBody::Update()
{
    // 일단 임시로 10% 확률로 꼬리 추가
    if (rand() % 100 < 10)
    {
        AddTail();
    }
    // 원래 뱀꼬리잡기 게임의 뱀은 자동으로 이동합니다..
    // 기존의 각각 직접 작성했던 이동 로직을 Move()라는 함수로 만들어놓으니
    // 여기서도 이렇게 코드를 간결하게 짤 수 있게 됩니다.

    // 움직이기 전에 먼저 원래 위치를 보관해놓는다.
    // 다음 꼬리가 이 보관된 위치로 이동한다.
    float prevX = m_X;
    float prevY = m_Y;
    Move(m_Direction, m_Speed);

    // 각 꼬리는 이전 꼬리의 위치로 셋팅된다. (즉, 따라가는 형태가 된다.)
    for (auto& pTail : m_TailList)
    {
        float tempX = pTail->GetX();
        float tempY = pTail->GetY();
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

void SnakeBody::AddTail()
{
    Object* pTail = new Object();
    pTail->SetShape(L'※');
    m_TailList.push_back(pTail);
}
