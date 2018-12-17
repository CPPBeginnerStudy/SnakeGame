#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"
#include "RandomSpeedObj.h"
#include "SnakeBody.h"
#include "Apple.h"


GameManager::GameManager()
    : m_IsOn(false)
	, m_pSnakeBody(nullptr)
	, m_pApple(nullptr)
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
    // 랜덤 시드 초기화는 게임 시작시 단 한번만 수행해야 한다.
    // (이를 기반으로 앞으로 랜덤값을 산출하게 된다.)
    srand((unsigned int)time(nullptr));

    // Console객체의 인스턴스를 가져와서 console이라는 참조변수에 저장하여 사용.
    // 매번 Console::GetInstance()를 써주기보단 이렇게 참조변수를 이용하는 것이
    // 가독성 측면에서도 좋고.. 여러모로 좋다.
    // auto 키워드는 대입되는 타입과 동일한 타입으로 자동으로 받아주는 역할이다.
    // 즉, 아래의 줄은 Console& console = Console::GetInstance(); 과 완전히 동일하다.
    auto& console = Console::GetInstance();
    console.Init();

	// 동일한 길이에 대해 인게임 좌표보다 cmd좌표가 x값이 2배이기 때문에 2로 나눠준다.
    RECT boundaryBox = console.GetBoundaryBox();
	boundaryBox.right /= 2;

	// RandomSpeedObj를 생성하면서 x, y 좌표를 매번 랜덤하게 지정한다. (바운더리 내에서)
	// RandomSpeedObj는 Object의 자식이기 때문에 Object*를 담는 자료구조에 같이 보관 가능하다.
    for (int i = 0; i < 3; ++i)
    {
        Object* pObject = new RandomSpeedObj();
        pObject->SetX(rand() % boundaryBox.right);
        pObject->SetY(rand() % boundaryBox.bottom);
        m_ObjectList.push_back(pObject);
    }

    // 우리가 직접 조종할 뱀의 몸통을 생성한다.
    m_pSnakeBody = new SnakeBody();
    m_pSnakeBody->SetX(boundaryBox.right / 2);  // 중앙에 생성
    m_pSnakeBody->SetY(boundaryBox.bottom / 2); // 중앙에 생성
    m_ObjectList.push_back(m_pSnakeBody);

	// 뱀이 먹을 사과를 생성한다.
	m_pApple = new Apple();
	m_pApple->SetX(rand() % boundaryBox.right);
	m_pApple->SetY(rand() % boundaryBox.bottom);
	m_ObjectList.push_back(m_pApple);

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
        // 현재 가져온 데이터(pObejct)를 delete하여 메모리 할당 해제해준다.
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
    // 먼저 키입력에 대한 처리를 한다.
    KeyInputHandling();

    // 게임이 가지고 있는 모든 객체들에게
    // 각자 자신을 업데이트 하도록 Update를 호출시켜 준다.
    for (auto& pObject : m_ObjectList)
    {
        pObject->Update();
    }

	// 뱀이 사과를 먹었으면 뱀에 꼬리를 추가해주고, 사과를 다른 곳으로 옮긴다.
	if (m_pSnakeBody->GetX() > m_pApple->GetX() - 0.5f &&
		m_pSnakeBody->GetX() < m_pApple->GetX() + 0.5f &&
		m_pSnakeBody->GetY() > m_pApple->GetY() - 0.5f &&
		m_pSnakeBody->GetY() < m_pApple->GetY() + 0.5f)
	{
		m_pSnakeBody->AddTail();

		RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
		boundaryBox.right /= 2;
		m_pApple->SetX(rand() % boundaryBox.right);
		m_pApple->SetY(rand() % boundaryBox.bottom);
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

void GameManager::KeyInputHandling()
{
    // GetAsyncKeyState()함수는 현재 키보드의 특정 키의 눌린 상태를 반환한다.
    // 어떤 키를 확인할지는 인자로 받으며, VK_ 로 시작하는 매크로값으로 정해져있다.
    // 키값 종류 참고: https://docs.microsoft.com/ko-kr/windows/desktop/inputdev/virtual-key-codes
    // 반환값은 키의 눌린 상태에 대한 플래그값이며, short타입(2byte)에서 왼쪽끝과 오른쪽끝 비트를 비트플래그로 사용한다.
    // 현재 키가 눌려있는지를 왼쪽끝 비트로 알려주고, 이전에 눌린적 있었는지를 오른쪽끝 비트로 알려준다.
    // 즉, 총 4가지의 케이스가 존재한다.
    // 1. 0000 0000 0000 0000 = 0x0000 : 이전에 누른 적이 없고 호출 시점에서 안눌린 상태
    // 2. 1000 0000 0000 0000 = 0x8000 : 이전에 누른 적이 없고 호출 시점에서 눌린 상태
    // 3. 0000 0000 0000 0001 = 0x0001 : 이전에 누른 적이 있고 호출 시점에서 안눌린 상태
    // 4. 1000 0000 0000 0001 = 0x8001 : 이전에 누른 적이 있고 호출 시점에서 눌린 상태
    // 이를 통해 키가 현시점에서 처음 눌렸는지, 아니면 누르고 있는 상태였는지 등을 체크할 수 있지만,
    // 사실 일반적으로 이러한 구분까지는 필요없고, 키가 지금 눌려있는지 여부만 알면 되기 때문에
    // 아래와 같이 0x8000 플래그가 있는지를 비트연산하여 키의 눌림여부를 확인한다. (즉, 위의 2, 4번 케이스를 모두 true처리)
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        // ESC 키가 눌리면 프로그램 종료
        Shutdown();
    }

    // 방향키 입력 처리 (else if가 아닌 이유는, 여러 키가 같이 눌렸을때에 모두 처리해줘야하기 때문)
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        // 각 키입력에 대한 처리는 각 클래스의 핸들러에서 구현하도록 넘겨준다.
        // 그래야 메인로직이 깔끔해지고, 이후 작업하기 편해진다.
        m_pSnakeBody->OnKeyPress(VK_UP);

        // 나중에 SnakeBody말고도 키입력을 받을 대상이 생기면 여기에 추가
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        m_pSnakeBody->OnKeyPress(VK_DOWN);
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        m_pSnakeBody->OnKeyPress(VK_LEFT);
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        m_pSnakeBody->OnKeyPress(VK_RIGHT);
    }

    // 영문자키는 해당 문자 캐릭터(char)의 바이트값과 대응된다.
    if (GetAsyncKeyState('Z') & 0x8000)
    {
        m_pSnakeBody->OnKeyPress('Z');
    }
    if (GetAsyncKeyState('X') & 0x8000)
    {
        m_pSnakeBody->OnKeyPress('X');
    }
}
