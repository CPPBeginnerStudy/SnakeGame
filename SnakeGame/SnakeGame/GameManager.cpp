#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"
#include "RandomSpeedObj.h"
#include "SnakeBody.h"
#include "Apple.h"
#include "Timer.h"
#include "DeathZone.h"


GameManager::GameManager()
    : m_IsRunning(false)
    , m_IsPlaying(false)
    , m_pSnakeBody(nullptr)
    , m_pApple(nullptr)
    , m_pDeathZone(nullptr)
    , m_GameSpeed(1.f)
    , m_GameLevel(1)
    , m_EatAppleNum(0)
{
}

GameManager::~GameManager()
{
}

void GameManager::Run()
{
    m_IsRunning = true;

    // 이 루프는 게임오버가 되어도 처음으로 돌아가
    // 다시 게임을 시작할 수 있도록 해주기 위한 메인루프이다.
    // 이 루프를 빠져나가면 비로소 프로그램이 종료된다.
    while (m_IsRunning)
    {
        Init();
        GameLoop();
        Release();
    }
}

void GameManager::Shutdown()
{
    // 게임의 상태를 off로 변경함으로써 다음 프레임에 메인루프에서 빠져나오게 한다.
    m_IsRunning = false;
    m_IsPlaying = false;
}

void GameManager::GameOver()
{
    // 플레이 플래그를 off 하여 게임루프를 빠져나오게 한다.
    m_IsPlaying = false;
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

    RECT boundaryBox = console.GetBoundaryBox();

    // RandomSpeedObj를 생성하면서 x, y 좌표를 매번 랜덤하게 지정한다. (바운더리 내에서)
    // RandomSpeedObj는 Object의 자식이기 때문에 Object*를 담는 자료구조에 같이 보관 가능하다.
    //for (int i = 0; i < 3; ++i)
    //{
    //    Object* pObject = new RandomSpeedObj();
    //    pObject->SetX(rand() % boundaryBox.right);
    //    pObject->SetY(rand() % boundaryBox.bottom);
    //    m_ObjectList.push_back(pObject);
    //}

    // 우리가 직접 조종할 뱀의 몸통을 생성한다.
    m_pSnakeBody = new SnakeBody();
    m_pSnakeBody->SetX(boundaryBox.right / 2);  // 중앙에 생성
    m_pSnakeBody->SetY(boundaryBox.bottom / 2); // 중앙에 생성
    m_ObjectList.push_back(m_pSnakeBody);

    // 뱀이 먹을 사과를 생성한다.
    m_pApple = new Apple();
    m_pApple->SetX(rand() % (boundaryBox.right - 2) + 1);
    m_pApple->SetY(rand() % (boundaryBox.bottom - 2) + 1);
    m_ObjectList.push_back(m_pApple);

    // 데스존을 생성한다.
    m_pDeathZone = new DeathZone();
    m_pDeathZone->GenerateLines();
    m_ObjectList.push_back(m_pDeathZone);

    // 모든 초기화가 완료되었으므로, 게임의 상태를 플레이 중으로 설정한다.
    m_IsPlaying = true;
    m_GameSpeed = 1.f;
    m_GameLevel = 1;
    m_EatAppleNum = 0;
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
    m_pSnakeBody = nullptr;
    m_pApple = nullptr;
    m_pDeathZone = nullptr;
}

void GameManager::GameLoop()
{
    Timer mainTimer;
    Timer updateTimer;
    Timer renderTimer;
    updateTimer.SetDelay(0.1f);     // 1초에 10번 업데이트 되도록 하자.
    renderTimer.SetDelay(0.05f);    // 1초에 20번 렌더링 되도록 하자.
    while (m_IsPlaying)
    {
        float realDT = mainTimer.GetDeltaTime();
        float gameDT = realDT * m_GameSpeed;

        // 게임의 업데이트는 게임 스피드가 적용된 dt를 넘겨서 스피드 조절이 가능하게 한다.
        if (updateTimer.CheckDelay(gameDT))
        {
            Update(gameDT);
        }
        // 렌더 프레임 제한은 실제 dt로 체크한다. (게임 속도와 무관하게)
        if (renderTimer.CheckDelay(realDT))
        {
            // 렌더링 프레임이 너무 빠르면 오히려 화면이 버벅인다.
            // Update와 다르게 눈에 편한정도로 제한을 두는 것이 좋다.
            Render();
        }
        // Sleep()함수는 인자로 받은 수치만큼(밀리세컨드 단위) 프로그램을 정지시킨다.
        // 메인루프가 너무 빨리 돌면 화면을 알아보기 힘드니,
        // 0.03초마다 한 프레임씩 수행되도록 이러한 처리를 추가하였다.
        // 즉, 1초에 33번 프레임이 돌게되니 33프레임의 게임이라고 보면 된다.
        // (참고로 보통 상용 게임은 Update와 Render의 프레임을 분리하여,
        //  렌더는 60프레임 고정, 업데이트는 수백~수천 프레임으로 돌게 해놓는다.)
        //Sleep(30 / m_GameSpeed);
    }
    // 게임이 종료되었을 때 표시할 여러가지들은 아래 함수에서 처리한다.
    ShowGameOverState();
}

void GameManager::Update(float _dt)
{
    // 먼저 키입력에 대한 처리를 한다.
    KeyInputHandling(_dt);

    // 게임이 가지고 있는 모든 객체들에게
    // 각자 자신을 업데이트 하도록 Update를 호출시켜 준다.
    for (auto& pObject : m_ObjectList)
    {
        pObject->Update(_dt);
    }

    // 뱀이 사과를 먹었으면 뱀에 꼬리를 추가해주고, 사과를 다른 곳으로 옮긴다.
    if (m_pSnakeBody->GetX() == m_pApple->GetX() &&
        m_pSnakeBody->GetY() == m_pApple->GetY())
    {
        m_EatAppleNum++;
        m_pSnakeBody->AddTail();

        RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
        m_pApple->SetX(rand() % (boundaryBox.right - 2) + 1);
        m_pApple->SetY(rand() % (boundaryBox.bottom - 2) + 1);
    }

    // 뱀이 데스존에 들어가면 게임오버
    if (m_pDeathZone->IsInDeathZone(m_pSnakeBody))
    {
        GameManager::GetInstance().GameOver();
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

    // 화면 최하단의 빈 공간에 게임 상태 관련 텍스트들을 출력해준다.
    RECT boundaryBox = console.GetBoundaryBox();
    std::wostringstream oss;
    oss << L"GameSpeed: " << m_GameSpeed << L"\t"
        << L"GameLevel: " << m_GameLevel << L"\t"
        << L"Eat Apple: " << m_EatAppleNum;
    console.PrintText(oss.str(), boundaryBox.left, boundaryBox.bottom + 1);

    // 모든 객체의 렌더링이 끝나면, 백버퍼와 스크린버퍼를 교체하여
    // 화면에 한번에 이번 프레임에 바뀐 렌더링 내용이 표시되도록 한다.
    console.SwapBuffer();
}

void GameManager::KeyInputHandling(float _dt)
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

        // 게임 속도 줄이기 (최소 0.5배)
        m_GameSpeed = std::max<float>(m_GameSpeed - 0.1f, 0.5f);
    }
    if (GetAsyncKeyState('X') & 0x8000)
    {
        m_pSnakeBody->OnKeyPress('X');

        // 게임 속도 늘리기 (최대 2배)
        m_GameSpeed = std::min<float>(m_GameSpeed + 0.1f, 2.f);
    }
}

void GameManager::ShowGameOverState()
{
    // 결과 화면 표시
    auto& console = Console::GetInstance();
    console.Clear();
    RECT boundaryBox = console.GetBoundaryBox();
    std::wostringstream oss;
    oss << L"\t\t\t\t    --- GameOver ---\n\n"
        << L"\t\t\t\t     Score:   " << m_EatAppleNum << L"\n"
        << L"\t\t\t\t     Restart: ENTER\n"
        << L"\t\t\t\t     Exit:    ESC";
    console.PrintText(oss.str(), boundaryBox.left, boundaryBox.bottom  / 2.3f);
    console.SwapBuffer();

    // 유저 입력 대기
    while (_getch())
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            Shutdown();
            return;
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x8000)
        {
            return;
        }
    }
}
