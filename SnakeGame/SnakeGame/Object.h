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
    // 렌더링될 객체는 자신의 모양을 하나의 문자(char)로 나타내며,
    // x, y 좌표를 통해 현재 위치를 알 수 있게 한다.
    // cmd관련 라이브러리 함수에서 좌표값들을 short타입으로 다루기 때문에
    // 여기서도 short타입으로 좌표변수를 지정한다.
    char            m_Shape;
    short           m_X;
    short           m_Y;

    // 현재 이동방향을 오른쪽/왼쪽 구분, 위/아래 구분 하기 위한 변수이다.
    bool            m_IsRight;
    bool            m_IsBottom;
};
