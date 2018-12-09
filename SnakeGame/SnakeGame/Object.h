#pragma once
// [virtual Ű������ �ǹ�]
// � Ŭ�������� ���� ��Ӱ��迡 ���� �� virtual Ű���尡 � ������ �ϴ��� ������ �����ϸ�,
// 1. Ŭ���� ���ǿ��� virtual Ű���尡 �ϳ��� �����ϸ� �� Ŭ������ ���� virtual ���̺��� �����ȴ�.
// 2. �� ���̺��� virtual Ű����� ����� ��� �Լ����� �ּҰ� ����ȴ�.
// 3. �� ���̺��� ����Ű�� �����Ͱ��� �ش� Ŭ������ ������ �� ������ ��������� �߰��ȴ�.
// 4. ������ �ν��Ͻ��� ���� �θ�Ŭ������ ������Ÿ������ ����Ǿ� �ִٰ� �ϴ���,
//    �� ������ ��������� �����Ͱ��� �������� Ŭ����(���� �ڽ��� Ŭ����)�� ���� virtual ���̺��� ����Ű�� �ֱ� ������
//    virtual Ű���尡 �ִ� �Լ��� ȣ���ϴ� ��� �� ���̺��� �����Ͽ� ���� �ڽ��� �Լ��� ã�Ƽ� ȣ���� �� �ְ� �ȴ�.
// ���� �̹���: https://candide-guevara.github.io/diagram/cpp/2015/07/07/cpp-virtual-table.html
// �� �̹������� Object1�� new BaseClass()�� �����ư�, Object2�� new DerivedClass()�� �����ƴٰ� ���� �ȴ�.
class Object
{
public:
    Object();
    virtual ~Object();

    virtual void    Update();
    virtual void    Render();

public:
    wchar_t         GetShape() const { return m_Shape; }
    float           GetX() const { return m_X; }
    float           GetY() const { return m_Y; }

    void            SetShape(wchar_t _shape) { m_Shape = _shape; }
    void            SetX(float _x) { m_X = _x; }
    void            SetY(float _y) { m_Y = _y; }

    // private: ������ ������ �� Ŭ���� �������� ������ �����ϱ� ������
    // protected: ������ �����Ͽ���. �� ������ �ڽ� Ŭ���������� ������ ������ �����̴�.
protected:
    // �������� ��ü�� �ڽ��� ����� �ϳ��� ����(wchar_t)�� ��Ÿ����,
    // x, y ��ǥ�� ���� ���� ��ġ�� �� �� �ְ� �Ѵ�.
    // cmd���� ���̺귯�� �Լ����� ��ǥ������ shortŸ������ �ٷ�� ������
    // ���⼭�� shortŸ������ ��ǥ������ �����Ѵ�.
    wchar_t         m_Shape;
    float           m_X;
    float           m_Y;

    // ���� �̵������� ������/���� ����, ��/�Ʒ� ���� �ϱ� ���� �����̴�.
    bool            m_IsRight;
    bool            m_IsBottom;
};
