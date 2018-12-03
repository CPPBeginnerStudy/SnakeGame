#pragma once
class Object
{
public:
    Object();
    virtual ~Object();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update();
    virtual void    Render();

    char            GetShape() const { return m_Shape; }
    short           GetX() const { return m_X; }
    short           GetY() const { return m_Y; }

    void            SetShape(char _shape) { m_Shape = _shape; }
    void            SetX(short _x) { m_X = _x; }
    void            SetY(short _y) { m_Y = _y; }

private:
    // �������� ��ü�� �ڽ��� ����� �ϳ��� ����(char)�� ��Ÿ����,
    // x, y ��ǥ�� ���� ���� ��ġ�� �� �� �ְ� �Ѵ�.
    // cmd���� ���̺귯�� �Լ����� ��ǥ������ shortŸ������ �ٷ�� ������
    // ���⼭�� shortŸ������ ��ǥ������ �����Ѵ�.
    char            m_Shape;
    short           m_X;
    short           m_Y;

    // ���� �̵������� ������/���� ����, ��/�Ʒ� ���� �ϱ� ���� �����̴�.
    bool            m_IsRight;
    bool            m_IsBottom;
};
