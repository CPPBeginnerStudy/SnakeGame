#include "pch.h"
#include "GameManager.h"


GameManager::GameManager()
    : m_IsOn(false)
    , m_LoopCount(0)
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
    m_IsOn = false;
}

void GameManager::Init()
{
    m_LoopCount = 10;
    m_IsOn = true;
}

void GameManager::Release()
{
}

void GameManager::MainLoop()
{
    while (m_IsOn)
    {
        std::cout << "Hello World!\n";

        if (--m_LoopCount < 1)
        {
            Shutdown();
        }
    }
}
