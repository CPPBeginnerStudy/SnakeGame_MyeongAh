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

	// ���� �� ���ڿ� ��¿��� char, string�� �ƴ� wchar_t, wstring�� ���� ����?
	// �⺻ ���� Ÿ�����δ� �ѱ�/Ư����ȣ�� ǥ���ϱ� ��Ʊ� ����
	// char�� �⺻������ 1����Ʈ���� ���� �����ѵ�, �ѱ�/Ư����ȣ�� �ּ� 2����Ʈ�� �ʿ��ϱ� ����
	// 2����Ʈ ũ��� ����Ǵ� wchar_t (���̵� ĳ���� Ÿ��)�� ����ؾ� �ϳ��� ���ڸ� ������ ǥ���� �� ����
	// wstring�� �̷��� wchar_t�� �̿��ϴ� string�� ��
	// ����� ���� ����ϴ� '�����ڵ�' ���ڵ� ����� wchar_t�� ����Ѵ�.
	// �ڼ��� �˰� �ʹٸ�, MBCS(Multi Byte)�� WBCS(Wide Byte)�� ���̸� ���ۿ��� �����!
	void Print(wchar_t _shape, short _x, short _y);
	void PrintText(const std::wstring& _text, short _x, short _y);

	RECT GetBoundaryBox() const;

private:
	short m_ScreenWidth;
	short m_ScreenHeight;
	HANDLE m_ScreenBuffer[2];
	short m_BackBufferIdx;
};

