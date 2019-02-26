#include "pch.h"
#include "Console.h"

// 클래스의 모든 멤버 변수는 반드시 초기화 해주어야
// 값이 대입되지 않은 상태 혹은 비정상적인 값으로 사용될 위험을 줄일 수 있다.
Console::Console()
	: m_ScreenWidth(0)
	, m_ScreenHeight(0)
	, m_BackBufferIdx(0)
{
	// 멤버 변수가 배열인 경우에는 위에서 초기화 하지 않고, 각 배열 항목들을 직접 초기화 해줘야 한다.
	// nullptr = 포인터 변수에 대한 제로값

	// Q. 여기에 들어가는 설명이 맞나요?
	// 아래 변수 타입은 HANDLE 타입이지만, 실제로는 어떤 객체의 포인터 타입
	// 즉, HANDLE 타입 = 포인터 타입
    /// > 넵. 실제로 HANDLE 타입에 커서를 놓고 F12를 누르면 선언코드를 확인할 수 있는데요.
    /// > typedef void* HANDLE; 라고 되어있을 겁니다. 즉, void* 타입을 HANDLE로 명명한 것.
    /// > void* 타입이란, 일단 포인터값을 저장할거긴 한데 어떤 타입의 포인터인지는 안 정해놓을 때 쓰입니다.
    /// > 즉, int* 를 대입하여 저장할 수도 있고, 어떤 구조체나 클래스의 포인터를 저장할 수도 있어요.
    /// > 하지만 실제로 꺼내 쓸 때에는 원래의 타입으로 캐스팅해서 써주어야 합니다.
    /// > 즉, void* 변수에서 바로 -> 로 무언가를 호출할 수는 없다는 점.
    /// > HANDLE이 void*인 이유는, 윈도우 내부에서 어떤 구조체를 만들어서 그 주소값을 포인터로 반환시킬건데
    /// > 그 구조체에 대한 정보는 밖으로 내비치지 않기 위해서라고 볼 수 있습니다.
	m_ScreenBuffer[0] = nullptr;
	m_ScreenBuffer[1] = nullptr;
}

Console::~Console()
{
}

void Console::Init()
{
	// cmd 창 크기 설정 = lines (세로, 줄 수), column (가로, 컬럼 수)
	// cmd에서 실제 거리는 가로 2개 = 세로 1개 (문자의 가로폭이 세로폭의 절반이라서)
	system("mode con: lines=30 cols=90");
	m_ScreenWidth = 90;
	m_ScreenHeight = 30;

	// cmd에서 커서 깜박거리는 것을 제거하기 위한 옵션
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	// 2개의 스크린 버퍼를 생성하여 초기화 (더블 버퍼링 구현)
	// 더블 버퍼링?
	// 객체가 하나씩 그려지는 과정을 실시간으로 보여주지 않고
	// 다 그려진 후 한번에 표시되도록 하여
	// 화면에 잔상이나 깜박임 등이 생기지 않도록 하는 기본적인 랜더링 기법
	DWORD accessFlag = GENERIC_READ | GENERIC_WRITE;
	DWORD bufferFlag = CONSOLE_TEXTMODE_BUFFER;
	m_ScreenBuffer[0] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
	m_ScreenBuffer[1] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
	SetConsoleCursorInfo(m_ScreenBuffer[0], &cci);
	SetConsoleCursorInfo(m_ScreenBuffer[1], &cci);

	// 0번 버퍼를 활성화 하고, 백버퍼 인덱스를 1로 지정한다.
	// = 현재 보이는 버퍼      = 다음에 그려질 버퍼
	// 버퍼? 프로그래밍에서 버퍼란 어떤 작업을 하기 위해 미리 마련(할당)해놓는 메모리 공간을 의미
	// 백버퍼? 더블 버퍼링에서 현재 화면에 노출되지 않는 버퍼를 의미
	SetConsoleActiveScreenBuffer(m_ScreenBuffer[0]);
	m_BackBufferIdx = 1;
}

void Console::Release()
{
	// 사용 완료한 버퍼는 반드시 핸들을 닫아준다.
	// Q. 핸들이 뭔가요?
    /// > 위에서 간단히(?) 좀 길게.. 설명했지만, 어떤 구조체에 대한 주소값을 저장한 것, 즉, 포인터 변수입니다.
    /// > 대체로 윈도우 내부에서 생성되는 구조체는 그 주소값을 HANDLE 타입으로 반환하고,
    /// > 우리는 그 HANDLE값을 보관하고 있다가 해당 구조체를 사용해야할 때
    /// > 윈도우API함수에 그 HANDLE값을 넘겨줘서 그 함수 내부에서 해당 구조체를 사용할 수 있도록 합니다.
    /// > 즉, 우리가 직접적으로 참조는 못하지만(실제로 어떤 구조체인지 모르기 때문에)
    /// > 그 생성된 인스턴스를 다룰 수는 있게 되는 것이지요. (그래서 핸들링 하기 위한 용도라는 의미로 HANDLE 타입)
    /// > 이렇게 윈도우 내부에서 생성된 객체는 delete도 우리가 직접 할 수 없기 때문에
    /// > CloseHandle()이라는 함수에 HANDLE을 넘겨서 윈도우가 해당 인스턴스를 할당해제할 수 있도록 하는 것입니다.
	CloseHandle(m_ScreenBuffer[0]);
	CloseHandle(m_ScreenBuffer[1]);
}

void Console::Clear()
{
	// 백버퍼 전체를 ' ' (공백)문자로 채운다.
	// 아무 글자도 보이지 않도록 지워주는 것
	DWORD dw;
	DWORD screenSize = m_ScreenWidth * m_ScreenHeight;
	FillConsoleOutputCharacter(m_ScreenBuffer[m_BackBufferIdx], L' ', screenSize, { 0, 0 }, &dw);
}

void Console::SwapBuffer()
{
	// 현재 백버퍼를 화면에 노출되는 스크린 버퍼로 지정하고, 백버퍼 인덱스를 교체
	// 이를 통해, 현재 프레임에서 백버퍼에 print한 모든 글자들이 스크린에 출력된다. (렌더링)
	// 이후 원래 표시되고 있던 버퍼는 백버퍼로 전환되고, 다음 프레임에서 해당 버퍼에 그리게 된다.
	SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_BackBufferIdx]);
	switch (m_BackBufferIdx)
	{
		case 0: m_BackBufferIdx = 1; break;
		case 1: m_BackBufferIdx = 0; break;
	}
}

void Console::Print(wchar_t _shape, short _x, short _y)
{
	// 현재의 백버퍼에서 커서를 지정한 위치로 이동시키고, 그 위치에 1개의 글자를 Write.
	DWORD dw;
	SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
	WriteConsole(m_ScreenBuffer[m_BackBufferIdx], &_shape, 1, &dw, nullptr);
}

void Console::PrintText(const std::wstring & _text, short _x, short _y)
{
	// Print와 동일하지만, 1개의 글자가 아닌 여러 개의 글자(문자열)을 Write.
	// std::wstirng에서 c_str() 멤버 함수는 해당 스트링의 첫번째 글자의 주소를 가져옴
	// Print의 &_shape와 동일하게 Write할 문자열의 시작 주소가 넘어오고,
	// 그 다음 인수인 _text.length()를 통해 얼만큼의 길이만큼 문자열을 끊어 Write할지 알려주는 것
	// 기본적으로는 Print() 함수만 구현해도 되지만, 메뉴 등 텍스트 정보를 편하게 출력하려면
	// 이러한 문자열 출력용 함수를 구현해 놓는 것이 좋음
	DWORD dw;
	SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
	WriteConsole(m_ScreenBuffer[m_BackBufferIdx], _text.c_str(), _text.length(), &dw, nullptr);
}

RECT Console::GetBoundaryBox() const
{
	// 현재 콘솔창의 상하좌우 끝좌표(바운더리)를 RECT(사각형)에 담아 반환
	// 실제 보여지는 구간은 1칸씩 적기 때문에 -2, -1의 계산이 추가됨.
	// (가로는 세로의 절반길이니까, 세로와 동일한 길이 줄이려면 2배여야 하는 것!)
	RECT boundaryBox;
	boundaryBox.top = 0;
	boundaryBox.left = 0;
	boundaryBox.right = m_ScreenWidth - 2;
	boundaryBox.bottom = m_ScreenHeight - 2; // 아래 한 줄을 비우기 위해 -1 추가 (마지막 줄은 오른쪽 끝이 표시 불가)
	return boundaryBox;
}
