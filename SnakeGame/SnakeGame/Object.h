#pragma once
class Object
{
public:
    Object();
    virtual ~Object();

    virtual void Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();
};

