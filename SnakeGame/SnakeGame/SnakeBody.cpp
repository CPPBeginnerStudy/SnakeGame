#include "pch.h"
#include "SnakeBody.h"
#include "Console.h"
#include "GameManager.h"


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

	// 움직인 뒤에 머리가 꼬리에 닿았는지 체크하여 게임오버 처리
	for (auto& pTail : m_TailList)
	{
		// 각 오브젝트의 크기는 1로 고정이기 때문에
		// 두 오브젝트의 x, y 거리가 모두 1이내 이면 겹쳐져 있는 것이다.
		if (m_X > pTail->GetX() - 0.5f &&
			m_X < pTail->GetX() + 0.5f &&
			m_Y > pTail->GetY() - 0.5f &&
			m_Y < pTail->GetY() + 0.5f)
		{
			// 일단은 충돌시 바로 게임 종료되도록 구현
			GameManager::GetInstance().Shutdown();
			return;
		}
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
