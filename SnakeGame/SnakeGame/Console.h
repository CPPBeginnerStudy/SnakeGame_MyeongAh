#pragma once
#include "Color.hpp"

class Console
{
public: // 다른 데에서 호출할 수 있음
	//싱글톤 패턴
	//게임 매니저 같은 것은 공용이므로 하나만 만들어서 여기저기서 갖다 쓸 수 있게함
	static Console& GetInstance()
	{
		// 전역 함수
		// 어디서든지 클래스를 인스턴스화 하지 않아도 불러서 사용이 가능
		// (멤버함수를 호출하기 위한 인스턴스가 필요하지 않음)
		static Console instance; // static 변수는 데이터 영역에 저장되기 때문에, 어디서든 가져다 쓸 수 있음. 여러 번 불려도 한번만 생성됨.
		return instance;
	}

private:
	Console();
	~Console();

public:
	void Init();
	void Release();

	void Clear();
	void SwapBuffer();

	// 문자 및 문자열 출력에서 char, string이 아닌 wchar_t, wstring을 쓰는 이유?
	// 기본 문자 타입으로는 한글/특수기호를 표현하기 어렵기 때문
	// char은 기본적으로 1바이트만을 저장 가능한데, 한글/특수기호는 최소 2바이트가 필요하기 때문
	// 2바이트 크기로 저장되는 wchar_t (와이드 캐릭터 타입)을 사용해야 하나의 글자를 온전히 표현할 수 있음
	// wstring은 이러한 wchar_t를 이용하는 string인 것
	// 참고로 흔히 사용하는 '유니코드' 인코딩 방법이 wchar_t를 사용한다.
	// 자세히 알고 싶다면, MBCS(Multi Byte)와 WBCS(Wide Byte)의 차이를 구글에게 물어보자!
	void Print(wchar_t _shape, Color _color, short _x, short _y);
	void PrintText(const std::wstring& _text, short _x, short _y);

	RECT GetBoundaryBox() const;

private:
	short m_ScreenWidth;
	short m_ScreenHeight;
	HANDLE m_ScreenBuffer[2];
	short m_BackBufferIdx;
};

