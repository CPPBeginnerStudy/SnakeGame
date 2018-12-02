#include "pch.h"
#include "GameManager.h"
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
    m_IsOn = false;
}

void GameManager::Init()
{
    m_IsOn = true;
}

void GameManager::Release()
{
    for (auto& pObject : m_ObjectList)
    {
        pObject->Release();
        delete pObject;
    }
}

void GameManager::MainLoop()
{
    while (m_IsOn)
    {
        Update();
        Render();
    }
}

void GameManager::Update()
{
    for (auto& pObject : m_ObjectList)
    {
        pObject->Update();
    }
}

void GameManager::Render()
{
    for (auto& pObject : m_ObjectList)
    {
        pObject->Render();
    }
}
