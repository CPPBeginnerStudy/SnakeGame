#include "pch.h"
#include "RandomSpeedObj.h"
#include "Console.h"


// ��ӹ��� Ŭ������ �����ڴ� �θ�Ŭ������ �����ڰ� ���� ȣ��� ���Ŀ� �� �����ڰ� ȣ��ȴ�.
// �̴� ���� �ڵ带 �߰����� �ʾƵ� �ڵ����� ����Ǵ� �۾��̴�.
// ���� �ڽ�Ŭ�������� �θ�Ŭ������ ������� �ʱ�ȭ�� �Ű澲�� �ʾƵ� �ȴ�. (�θ�����ڰ� ���ֹǷ�)
// �����ڵ�)
// class A { virtual ~A(){} }
// class B : public A { virtual ~B(){} }
// class C : public B { virtual ~C(){} }
// int main()
// {
//     C* pC = new C(); // A������->B������->C������ ������ ȣ���.
// }
RandomSpeedObj::RandomSpeedObj()
    : m_XSpeed(0.f)
    , m_YSpeed(0.f)
{
}

// ��ӹ��� Ŭ������ �Ҹ��ڴ� �ڽ��� ���� ȣ��� �� �θ�Ŭ������ �Ҹ��ڸ� ȣ���Ѵ�.
// �̴� ���� �ڵ带 �߰����� �ʾƵ� �ڵ����� ����Ǵ� �۾��̴�.
// �����ڿ� ȣ������� �ݴ��� ������ ����������..�ִµ� ������ ����ϸ�,
// �Ҵ������� �Ҵ�� ������ �ݴ�� ����Ǵ� ���� �����ϰ� ȿ�����̱� ����
// �����ڵ�)
// class A { virtual ~A(){} }
// class B : public A { virtual ~B(){} }
// class C : public B { virtual ~C(){} }
// int main()
// {
//     A* pC = new C(); // A������->B������->C������ ������ ȣ���.
//     delete pC;       // C�Ҹ���->B�Ҹ���->A�Ҹ��� ������ ȣ���.
//     // �׸��� ���⼭ ��ġë�� ���� �ְ�����,
//     // �����ڴ� �׻� ���� �ڽ��� �ƴ� �����̱� ������ virtual Ű���尡 �ʿ������
//     // �Ҹ��ڴ� �Ҹ������ �θ�Ŭ���� ������Ÿ�Կ� ����� ������ ���� delete�� ���ɼ��� �ֱ� ������
//     // virtual Ű���尡 ���ٸ� ���� �ڽ��� �Ҹ��ڸ� ã�� ���� ��� �ݵ�� Ű���带 �߰��ؾ� �ϴ� ���̴�.
//     // �� �ڵ忡�� ���� virtual Ű���尡 �����ٸ�, A�Ҹ��ڸ� ȣ��Ǿ� �޸� ���� �߻��Ѵ�.
// }
RandomSpeedObj::~RandomSpeedObj()
{
}

void RandomSpeedObj::Init()
{
    // �������̵��� �Լ��� �⺻������ �θ��Լ��� ȣ������ �ʴ´�.
    // ���� �θ��Լ��� ȣ���� �ʿ䰡 ���� ��� �Ʒ��� ���� �θ�Ŭ����::�Լ��� ���� ȣ�����ش�.
    // Init()�� ���� �θ��� Init()�� ���� ȣ���ϰ�, �߰��� ��(�ڽ�)�� �ʱ�ȭ�� ���� ���ش�.
    Object::Init();
    m_XSpeed = 1.f;
    m_YSpeed = 1.f;
}

void RandomSpeedObj::Release()
{
    // �θ� Ŭ������ ������ �ٸ��� ó���� �� ���ٸ�, �׳� �θ𲨸� ���⼭ �ٽ� ȣ�����ָ� �ȴ�.
    Object::Release();
}

void RandomSpeedObj::Update()
{
    // Update()�� ���� �θ��� ������ �ƿ� ���� �ʰ�, ���Ӱ� ������ �������ϱ� ����
    // �θ��� Update()�� ȣ������ ���� �� ����.
    RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
    if (m_IsRight)
    {
        m_X += 2 * m_XSpeed;
        if (m_X > boundaryBox.right)
        {
            m_X = boundaryBox.right;
            m_IsRight = false;
            m_XSpeed = (rand() % 5 + 1) * 0.5f; // 0.5�� ~ 3��
        }
    }
    else
    {
        m_X -= 2 * m_XSpeed;
        if (m_X < boundaryBox.left)
        {
            m_X = boundaryBox.left;
            m_IsRight = true;
            m_XSpeed = (rand() % 6 + 1) * 0.5f;
        }
    }
    if (m_IsBottom)
    {
        m_Y += 1 * m_YSpeed;
        if (m_Y > boundaryBox.bottom)
        {
            m_Y = boundaryBox.bottom;
            m_IsBottom = false;
            m_YSpeed = (rand() % 6 + 1) * 0.5f;
        }
    }
    else
    {
        m_Y -= 1 * m_YSpeed;
        if (m_Y < boundaryBox.top)
        {
            m_Y = boundaryBox.top;
            m_IsBottom = true;
            m_YSpeed = (rand() % 6 + 1) * 0.5f;
        }
    }
}

void RandomSpeedObj::Render()
{
    Object::Render();
}
