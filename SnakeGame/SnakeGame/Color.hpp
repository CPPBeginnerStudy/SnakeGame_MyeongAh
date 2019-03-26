#pragma once

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


// hpp
// 헤더인데 cpp 처럼 쓰겠다

// 1. cpp와 헤더를 분리할 필요가 없는 간단한 정의만 작성할 코드는 hpp파일로 만들어서 include해서 사용
// 2. CMD에서 표현할 수 있는 색상은 위의 색상이 전부이며,
//	  실제로는 0~15의 정수값이지만, 사용이 편하도록 enum으로 이름을 붙여줌
// 3. 이 색상들에 비트 연산을 약간 더하면 배경 색상 설정도 가능

// 참고로 저 Color enum은 다음과 같이 쓰임
// BLACK => 0	   == 검은 바탕에 검은 글씨
// DARK_BLUE => 1  == 검은 바탕에 남색 글씨
// DARK_GREEN => 2 == 검은 바탕에 짙은 초록색 글씨
// ...
// WHITE => 15     == 검은 바탕에 흰 글씨
// 16 => 남색 바탕에 검은 글씨
// 17 => 남색 바탕에 남색 글씨
// 이런 순서로 바탕색/글씨색을 해서 총 16*16 = 2^8 = 256개의 색깔 표현이 가능하다.