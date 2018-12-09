#include "pch.h"
#include "GameManager.h"
#include "Console.h"
#include "Object.h"
#include "RandomSpeedObj.h"
#include "SnakeBody.h"


GameManager::GameManager()
    : m_IsOn(false)
    , m_pSnakeBody(nullptr)
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
    // ������ ���¸� off�� ���������ν� ���� �����ӿ� ���η������� ���������� �Ѵ�.
    m_IsOn = false;
}

void GameManager::Init()
{
    // ������ ����� ���� �����õ带 �ʱ�ȭ�Ѵ�.
    srand((unsigned int)time(nullptr));

    // Console��ü�� �ν��Ͻ��� �����ͼ� console�̶�� ���������� �����Ͽ� ���.
    // �Ź� Console::GetInstance()�� ���ֱ⺸�� �̷��� ���������� �̿��ϴ� ����
    // ������ ���鿡���� ����.. ������� ����.
    // auto Ű����� ���ԵǴ� Ÿ�԰� ������ Ÿ������ �ڵ����� �޾��ִ� �����̴�.
    // ��, �Ʒ��� ���� Console& console = Console::GetInstance(); �� ������ �����ϴ�.
    auto& console = Console::GetInstance();
    console.Init();

    // 5���� Object�� �����ϸ鼭 x, y ��ǥ�� �Ź� �����ϰ� �����Ѵ�. (�ٿ���� ������)
    RECT boundaryBox = console.GetBoundaryBox();

    // 2���� �⺻ ������Ʈ�� ����
    for (int i = 0; i < 2; ++i)
    {
        Object* pObject = new Object();
        pObject->SetShape(L'��');
        pObject->SetX(rand() % boundaryBox.right);
        pObject->SetY(rand() % boundaryBox.bottom);
        m_ObjectList.push_back(pObject);
    }
    // 3���� Object�� ��ӹ��� RandomSpeedObj��� Ŭ������ ����
    // RandomSpeedObj�� Object�� �ڽ��̱� ������ Object*�� ��� �ڷᱸ���� ���� ���� �����ϴ�.
    for (int i = 0; i < 3; ++i)
    {
        Object* pObject = new RandomSpeedObj();
        pObject->SetShape(L'��');
        pObject->SetX(rand() % boundaryBox.right);
        pObject->SetY(rand() % boundaryBox.bottom);
        m_ObjectList.push_back(pObject);
    }

    // �츮�� ���� ������ ���� ������ �����Ѵ�.
    m_pSnakeBody = new SnakeBody();
    m_pSnakeBody->SetShape(L'��');
    m_pSnakeBody->SetX(boundaryBox.right / 2);  // �߾ӿ� ����
    m_pSnakeBody->SetY(boundaryBox.bottom / 2); // �߾ӿ� ����
    m_ObjectList.push_back(m_pSnakeBody);

    // ��� �ʱ�ȭ�� �Ϸ�Ǿ����Ƿ�, ������ ���¸� on���� �����Ѵ�.
    m_IsOn = true;
}

void GameManager::Release()
{
    // ���� ���Ӱ� ���õ� ��� ��ü���� Release�Ѵ�.
    // ������ ���� Init()���� Init�� ��ü���� ���⼭ Release���ָ� �ȴ�.
    Console::GetInstance().Release();

    // m_ObjectList��� �ڷᱸ������ �� ����� �����͵��� �ϳ��� �������� �ݺ����̴�.
    // ��, m_ObjectList�� ����������ŭ �ݺ����� ����ȴ�. (5�� �������̸� 5��)
    for (auto& pObject : m_ObjectList)
    {
        // ���� ������ ������(pObejct)�� delete�Ͽ� �޸� �Ҵ� �������ش�.
        delete pObject;
    }
    // �������̴� ��� �����͵��� �� ����Ű�� �ν��Ͻ����� �� �Ҵ�����������,
    // m_ObjectList�� ����ֵ��� �Ѵ�. �̷��� ���ϸ� ���ξ��� �����͵��� ������ �ְ� �ȴ�.
    m_ObjectList.clear();
}

void GameManager::MainLoop()
{
    while (m_IsOn)
    {
        Update();
        Render();

        // Sleep()�Լ��� ���ڷ� ���� ��ġ��ŭ(�и������� ����) ���α׷��� ������Ų��.
        // ���η����� �ʹ� ���� ���� ȭ���� �˾ƺ��� �����,
        // 0.03�ʸ��� �� �����Ӿ� ����ǵ��� �̷��� ó���� �߰��Ͽ���.
        // ��, 1�ʿ� 33�� �������� ���ԵǴ� 33�������� �����̶�� ���� �ȴ�.
        // (����� ���� ��� ������ Update�� Render�� �������� �и��Ͽ�,
        //  ������ 60������ ����, ������Ʈ�� ����~��õ ���������� ���� �س��´�.)
        Sleep(30);
    }
}

void GameManager::Update()
{
    // ���� Ű�Է¿� ���� ó���� �Ѵ�.
    KeyInputHandling();

    // ������ ������ �ִ� ��� ��ü�鿡��
    // ���� �ڽ��� ������Ʈ �ϵ��� Update�� ȣ����� �ش�.
    for (auto& pObject : m_ObjectList)
    {
        pObject->Update();
    }
}

void GameManager::Render()
{
    // �̹� �������� �������� �����ϱ⿡ �ռ� ���� ����۸� ������ �����ش�.
    auto& console = Console::GetInstance();
    console.Clear();

    // �� ��ȭ�� ������ ����ۿ� �� ��ü���� �������� �����Ų��.
    for (auto& pObject : m_ObjectList)
    {
        pObject->Render();
    }

    // ��� ��ü�� �������� ������, ����ۿ� ��ũ�����۸� ��ü�Ͽ�
    // ȭ�鿡 �ѹ��� �̹� �����ӿ� �ٲ� ������ ������ ǥ�õǵ��� �Ѵ�.
    console.SwapBuffer();
}

void GameManager::KeyInputHandling()
{
    // GetAsyncKeyState()�Լ��� ���� Ű������ Ư�� Ű�� ���� ���¸� ��ȯ�Ѵ�.
    // � Ű�� Ȯ�������� ���ڷ� ������, VK_ �� �����ϴ� ��ũ�ΰ����� �������ִ�.
    // Ű�� ���� ����: https://docs.microsoft.com/ko-kr/windows/desktop/inputdev/virtual-key-codes
    // ��ȯ���� Ű�� ���� ���¿� ���� �÷��װ��̸�, shortŸ��(2byte)���� ���ʳ��� �����ʳ� ��Ʈ�� ��Ʈ�÷��׷� ����Ѵ�.
    // ���� Ű�� �����ִ����� ���ʳ� ��Ʈ�� �˷��ְ�, ������ ������ �־������� �����ʳ� ��Ʈ�� �˷��ش�.
    // ��, �� 4������ ���̽��� �����Ѵ�.
    // 1. 0000 0000 0000 0000 = 0x0000 : ������ ���� ���� ���� ȣ�� �������� �ȴ��� ����
    // 2. 1000 0000 0000 0000 = 0x8000 : ������ ���� ���� ���� ȣ�� �������� ���� ����
    // 3. 0000 0000 0000 0001 = 0x0001 : ������ ���� ���� �ְ� ȣ�� �������� �ȴ��� ����
    // 4. 1000 0000 0000 0001 = 0x8001 : ������ ���� ���� �ְ� ȣ�� �������� ���� ����
    // �̸� ���� Ű�� ���������� ó�� ���ȴ���, �ƴϸ� ������ �ִ� ���¿����� ���� üũ�� �� ������,
    // ��� �Ϲ������� �̷��� ���б����� �ʿ����, Ű�� ���� �����ִ��� ���θ� �˸� �Ǳ� ������
    // �Ʒ��� ���� 0x8000 �÷��װ� �ִ����� ��Ʈ�����Ͽ� Ű�� �������θ� Ȯ���Ѵ�. (��, ���� 2, 4�� ���̽��� ��� trueó��)
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        // ESC Ű�� ������ ���α׷� ����
        Shutdown();
    }

    // ����Ű �Է� ó�� (else if�� �ƴ� ������, ���� Ű�� ���� ���������� ��� ó��������ϱ� ����)
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        // �� Ű�Է¿� ���� ó���� �� Ŭ������ �ڵ鷯���� �����ϵ��� �Ѱ��ش�.
        // �׷��� ���η����� ���������, ���� �۾��ϱ� ��������.
        m_pSnakeBody->OnKeyPress(VK_UP);

        // ���߿� SnakeBody���� Ű�Է��� ���� ����� ����� ���⿡ �߰�
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

    // ������Ű�� �ش� ���� ĳ����(char)�� ����Ʈ���� �����ȴ�.
    if (GetAsyncKeyState('Z') & 0x8000)
    {
        m_pSnakeBody->OnKeyPress('Z');
    }
    if (GetAsyncKeyState('X') & 0x8000)
    {
        m_pSnakeBody->OnKeyPress('X');
    }
}
