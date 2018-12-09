#pragma once
class Console
{
public: // �ٸ� ������ ȣ���� �� ����
	//�̱��� ����
	//���� �Ŵ��� ���� ���� �����̹Ƿ� �ϳ��� ���� �������⼭ ���� �� �� �ְ���
	static Console& GetInstance()
	{
		// ���� �Լ�
		// ��𼭵��� Ŭ������ �ν��Ͻ�ȭ ���� �ʾƵ� �ҷ��� ����� ����
		// (����Լ��� ȣ���ϱ� ���� �ν��Ͻ��� �ʿ����� ����)
		static Console instance; // static ������ ������ ������ ����Ǳ� ������, ��𼭵� ������ �� �� ����. ���� �� �ҷ��� �ѹ��� ������.
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

