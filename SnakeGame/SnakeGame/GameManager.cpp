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
    for (int i = 0; i < 5; ++i)
    {
        Object* pObject = new Object();
        pObject->Init();
        pObject->SetShape('O');
        pObject->SetX(rand() % boundaryBox.right);
        pObject->SetY(rand() % boundaryBox.bottom);
        m_ObjectList.push_back(pObject);
    }

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
        // ���� ������ ������(pObejct)�� ���� Release()�� ȣ�����ְ�,
        // �ش� �ν��Ͻ��� delete�Ͽ� �޸� �Ҵ� �������ش�.
        pObject->Release();
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
