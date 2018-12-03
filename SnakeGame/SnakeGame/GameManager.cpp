#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"


GameManager::GameManager()
    : m_IsOn(false)
{
}

GameManager::~GameManager()
{
}

void GameManager::Run()
{
    Init();
    MainLoop();
    Release();
}

void GameManager::Shutdown()
{
    // 게임의 상태를 off로 변경함으로써 다음 프레임에 메인루프에서 빠져나오게 한다.
    m_IsOn = false;
}

void GameManager::Init()
{
    // 랜덤값 사용을 위해 랜덤시드를 초기화한다.
    srand((unsigned int)time(nullptr));

    // Console객체의 인스턴스를 가져와서 console이라는 참조변수에 저장하여 사용.
    // 매번 Console::GetInstance()를 써주기보단 이렇게 참조변수를 이용하는 것이
    // 가독성 측면에서도 좋고.. 여러모로 좋다.
    // auto 키워드는 대입되는 타입과 동일한 타입으로 자동으로 받아주는 역할이다.
    // 즉, 아래의 줄은 Console& console = Console::GetInstance(); 과 완전히 동일하다.
    auto& console = Console::GetInstance();
    console.Init();

    // 5개의 Object를 생성하면서 x, y 좌표를 매번 랜덤하게 지정한다. (바운더리 내에서)
    RECT boundaryBox = console.GetBoundaryBox();
    for (int i = 0; i < 5; ++i)
    {
        Object* pObject = new Object();
        pObject->Init();
        pObject->SetShape('O');
        pObject->SetX(rand() % boundaryBox.right);
        pObject->SetY(rand() % boundaryBox.bottom);
        m_ObjectList.push_back(pObject);
    }

    // 모든 초기화가 완료되었으므로, 게임의 상태를 on으로 설정한다.
    m_IsOn = true;
}

void GameManager::Release()
{
    // 현재 게임과 관련된 모든 객체들을 Release한다.
    // 보통은 위의 Init()에서 Init한 객체들을 여기서 Release해주면 된다.
    Console::GetInstance().Release();

    // m_ObjectList라는 자료구조에서 그 저장된 데이터들을 하나씩 가져오는 반복문이다.
    // 즉, m_ObjectList의 보관개수만큼 반복문이 실행된다. (5개 보관중이면 5번)
    for (auto& pObject : m_ObjectList)
    {
        // 현재 가져온 데이터(pObejct)에 대해 Release()를 호출해주고,
        // 해당 인스턴스를 delete하여 메모리 할당 해제해준다.
        pObject->Release();
        delete pObject;
    }
    // 보관중이던 모든 포인터들이 그 가리키던 인스턴스들을 다 할당해제했으니,
    // m_ObjectList를 비워주도록 한다. 이렇게 안하면 주인없는 포인터들을 가지고 있게 된다.
    m_ObjectList.clear();
}

void GameManager::MainLoop()
{
    while (m_IsOn)
    {
        Update();
        Render();

        // Sleep()함수는 인자로 받은 수치만큼(밀리세컨드 단위) 프로그램을 정지시킨다.
        // 메인루프가 너무 빨리 돌면 화면을 알아보기 힘드니,
        // 0.03초마다 한 프레임씩 수행되도록 이러한 처리를 추가하였다.
        // 즉, 1초에 33번 프레임이 돌게되니 33프레임의 게임이라고 보면 된다.
        // (참고로 보통 상용 게임은 Update와 Render의 프레임을 분리하여,
        //  렌더는 60프레임 고정, 업데이트는 수백~수천 프레임으로 돌게 해놓는다.)
        Sleep(30);
    }
}

void GameManager::Update()
{
    // 게임이 가지고 있는 모든 객체들에게
    // 각자 자신을 업데이트 하도록 Update를 호출시켜 준다.
    for (auto& pObject : m_ObjectList)
    {
        pObject->Update();
    }
}

void GameManager::Render()
{
    // 이번 프레임의 렌더링을 시작하기에 앞서 먼저 백버퍼를 깨끗히 지워준다.
    auto& console = Console::GetInstance();
    console.Clear();

    // 빈 도화지 상태의 백버퍼에 각 객체들의 렌더링을 수행시킨다.
    for (auto& pObject : m_ObjectList)
    {
        pObject->Render();
    }

    // 모든 객체의 렌더링이 끝나면, 백버퍼와 스크린버퍼를 교체하여
    // 화면에 한번에 이번 프레임에 바뀐 렌더링 내용이 표시되도록 한다.
    console.SwapBuffer();
}
