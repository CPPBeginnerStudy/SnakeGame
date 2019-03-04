#pragma once

// 1.cpp와 헤더를 분리할 필요없는 간단한 정의만 작성할 코드는
//   hpp파일로 만들어서 include하면 됩니다.
//
// 2.CMD에서 표현할 수 있는 색상은 아래 색상이 전부입니다.
//   실제론 0 ~ 15의 정수값이지만, 사용이 편하도록 enum으로 이름을 붙여줍니다.
//
// 3.이 색상들에 비트연산을 약간 더하면 배경색상 설정도 가능하지만 일단 보류합니다.

enum Color : unsigned short
{
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_CYAN,
    DARK_RED,
    DARK_MAGENTA,
    DARK_YELLOW,
    DARK_WHITE,
    GREY,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    YELLOW,
    WHITE,
};
