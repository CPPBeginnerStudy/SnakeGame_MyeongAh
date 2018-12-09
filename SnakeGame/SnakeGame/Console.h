#pragma once
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

	void Print(char _shape, short _x, short _y);
	void PrintText(const std::string& _text, short _x, short _y);

	RECT GetBoundaryBox() const;

private:
	short m_ScreenWidth;
	short m_ScreenHeight;
	HANDLE m_ScreenBuffer[2];
	short m_BackBufferIdx;
};

