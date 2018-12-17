#include "pch.h"
#include "Object.h"
#include "Console.h"


Object::Object()
    : m_Shape(L' ') // ' '�� �ƴ� L' '�� ������, char�� �ƴ� wchar_t�̱� ����.
    , m_X(0.f)
    , m_Y(0.f)
{
}

Object::~Object()
{
}

void Object::Update()
{
}

void Object::Render()
{
    // ���� �� ��ġ(m_X, m_Y)�� �� ���(m_Shape)�� �ܼ��� �׸����� �Ѵ�.
    Console::GetInstance().Print(m_Shape, (short)m_X, (short)m_Y);
}

bool Object::Move(Direction _dir, float _distance)
{
    RECT boundaryBox = Console::GetInstance().GetBoundaryBox();
    switch (_dir)
    {
    case Direction::UP:
        {
            // ���� y��ǥ�� ���� ��輱���� ũ��(�Ʒ����̸�) �������� �̵��� �����ϴ�.
            if (m_Y > boundaryBox.top)
            {
                // ��û�� �Ÿ���ŭ �̵��� �õ��ϸ�, �ٿ������ �Ѿ�� �ʵ��� ó���Ѵ�.
                // std::max�� �ΰ��� ������ �� ū���� ��ȯ�ϴ� �Լ��̴�.
                // ��, m_Y - _distance �� �ٿ�������� ������, �ٿ�������� ��ȯ�Ͽ� �� ���ϰ��� ������ �ʰ��Ѵ�.
                m_Y = std::max<float>(m_Y - _distance, boundaryBox.top);

                // ���⿡ �Դٴ°� ����Ƶ� ������� �̵��� �Ѵٴ� ���̴�.
                return true;
            }
        }
        break;
    case Direction::DOWN:
        {
            // ���� y��ǥ�� �Ʒ��� ��輱���� ������(�����̸�) �Ʒ������� �̵��� �����ϴ�.
            if (m_Y < boundaryBox.bottom)
            {
                m_Y = std::min<float>(m_Y + _distance, boundaryBox.bottom);
                return true;
            }
        }
        break;
    case Direction::LEFT:
        {
            // ���� x��ǥ�� ���� ��輱���� ũ��(�������̸�) �������� �̵��� �����ϴ�.
            if (m_X > boundaryBox.left)
            {
                // �Ÿ��� 2�� ���ϴ� ������ x��ǥ�� y��ǥ�� �����̱� ����.
                m_X = std::max<float>(m_X - _distance * 2, boundaryBox.left);
                return true;
            }
        }
        break;
    case Direction::RIGHT:
        {
            // ���� x��ǥ�� ������ ��輱���� ������(�����̸�) ���������� �̵��� �����ϴ�.
            if (m_X < boundaryBox.right)
            {
                m_X = std::min<float>(m_X + _distance * 2, boundaryBox.right);
                return true;
            }
        }
        break;
    }
    // ���⿡ �Դٴ°� �ƹ� �̵��� ���� �ʾҴٴ� ���̴�.
    return false;
}
