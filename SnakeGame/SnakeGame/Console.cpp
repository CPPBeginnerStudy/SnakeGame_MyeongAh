#include "pch.h"
#include "Console.h"

// Ŭ������ ��� ��� ������ �ݵ�� �ʱ�ȭ ���־��
// ���� ���Ե��� ���� ���� Ȥ�� ���������� ������ ���� ������ ���� �� �ִ�.
Console::Console()
	: m_ScreenWidth(0)
	, m_ScreenHeight(0)
	, m_BackBufferIdx(0)
{
	// ��� ������ �迭�� ��쿡�� ������ �ʱ�ȭ ���� �ʰ�, �� �迭 �׸���� ���� �ʱ�ȭ ����� �Ѵ�.
	// nullptr = ������ ������ ���� ���ΰ�

	// Q. ���⿡ ���� ������ �³���?
	// �Ʒ� ���� Ÿ���� HANDLE Ÿ��������, �����δ� � ��ü�� ������ Ÿ��
	// ��, HANDLE Ÿ�� = ������ Ÿ��
    /// > ��. ������ HANDLE Ÿ�Կ� Ŀ���� ���� F12�� ������ �����ڵ带 Ȯ���� �� �ִµ���.
    /// > typedef void* HANDLE; ��� �Ǿ����� �̴ϴ�. ��, void* Ÿ���� HANDLE�� ����� ��.
    /// > void* Ÿ���̶�, �ϴ� �����Ͱ��� �����Ұű� �ѵ� � Ÿ���� ������������ �� ���س��� �� ���Դϴ�.
    /// > ��, int* �� �����Ͽ� ������ ���� �ְ�, � ����ü�� Ŭ������ �����͸� ������ ���� �־��.
    /// > ������ ������ ���� �� ������ ������ Ÿ������ ĳ�����ؼ� ���־�� �մϴ�.
    /// > ��, void* �������� �ٷ� -> �� ���𰡸� ȣ���� ���� ���ٴ� ��.
    /// > HANDLE�� void*�� ������, ������ ���ο��� � ����ü�� ���� �� �ּҰ��� �����ͷ� ��ȯ��ų�ǵ�
    /// > �� ����ü�� ���� ������ ������ ����ġ�� �ʱ� ���ؼ���� �� �� �ֽ��ϴ�.
	m_ScreenBuffer[0] = nullptr;
	m_ScreenBuffer[1] = nullptr;
}

Console::~Console()
{
}

void Console::Init()
{
	// cmd â ũ�� ���� = lines (����, �� ��), column (����, �÷� ��)
	// cmd���� ���� �Ÿ��� ���� 2�� = ���� 1�� (������ �������� �������� �����̶�)
	system("mode con: lines=30 cols=90");
	m_ScreenWidth = 90;
	m_ScreenHeight = 30;

	// cmd���� Ŀ�� ���ڰŸ��� ���� �����ϱ� ���� �ɼ�
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	// 2���� ��ũ�� ���۸� �����Ͽ� �ʱ�ȭ (���� ���۸� ����)
	// ���� ���۸�?
	// ��ü�� �ϳ��� �׷����� ������ �ǽð����� �������� �ʰ�
	// �� �׷��� �� �ѹ��� ǥ�õǵ��� �Ͽ�
	// ȭ�鿡 �ܻ��̳� ������ ���� ������ �ʵ��� �ϴ� �⺻���� ������ ���
	DWORD accessFlag = GENERIC_READ | GENERIC_WRITE;
	DWORD bufferFlag = CONSOLE_TEXTMODE_BUFFER;
	m_ScreenBuffer[0] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
	m_ScreenBuffer[1] = CreateConsoleScreenBuffer(accessFlag, 0, nullptr, bufferFlag, nullptr);
	SetConsoleCursorInfo(m_ScreenBuffer[0], &cci);
	SetConsoleCursorInfo(m_ScreenBuffer[1], &cci);

	// 0�� ���۸� Ȱ��ȭ �ϰ�, ����� �ε����� 1�� �����Ѵ�.
	// = ���� ���̴� ����      = ������ �׷��� ����
	// ����? ���α׷��ֿ��� ���۶� � �۾��� �ϱ� ���� �̸� ����(�Ҵ�)�س��� �޸� ������ �ǹ�
	// �����? ���� ���۸����� ���� ȭ�鿡 ������� �ʴ� ���۸� �ǹ�
	SetConsoleActiveScreenBuffer(m_ScreenBuffer[0]);
	m_BackBufferIdx = 1;
}

void Console::Release()
{
	// ��� �Ϸ��� ���۴� �ݵ�� �ڵ��� �ݾ��ش�.
	// Q. �ڵ��� ������?
    /// > ������ ������(?) �� ���.. ����������, � ����ü�� ���� �ּҰ��� ������ ��, ��, ������ �����Դϴ�.
    /// > ��ü�� ������ ���ο��� �����Ǵ� ����ü�� �� �ּҰ��� HANDLE Ÿ������ ��ȯ�ϰ�,
    /// > �츮�� �� HANDLE���� �����ϰ� �ִٰ� �ش� ����ü�� ����ؾ��� ��
    /// > ������API�Լ��� �� HANDLE���� �Ѱ��༭ �� �Լ� ���ο��� �ش� ����ü�� ����� �� �ֵ��� �մϴ�.
    /// > ��, �츮�� ���������� ������ ��������(������ � ����ü���� �𸣱� ������)
    /// > �� ������ �ν��Ͻ��� �ٷ� ���� �ְ� �Ǵ� ��������. (�׷��� �ڵ鸵 �ϱ� ���� �뵵��� �ǹ̷� HANDLE Ÿ��)
    /// > �̷��� ������ ���ο��� ������ ��ü�� delete�� �츮�� ���� �� �� ���� ������
    /// > CloseHandle()�̶�� �Լ��� HANDLE�� �Ѱܼ� �����찡 �ش� �ν��Ͻ��� �Ҵ������� �� �ֵ��� �ϴ� ���Դϴ�.
	CloseHandle(m_ScreenBuffer[0]);
	CloseHandle(m_ScreenBuffer[1]);
}

void Console::Clear()
{
	// ����� ��ü�� ' ' (����)���ڷ� ä���.
	// �ƹ� ���ڵ� ������ �ʵ��� �����ִ� ��
	DWORD dw;
	DWORD screenSize = m_ScreenWidth * m_ScreenHeight;
	FillConsoleOutputCharacter(m_ScreenBuffer[m_BackBufferIdx], L' ', screenSize, { 0, 0 }, &dw);
}

void Console::SwapBuffer()
{
	// ���� ����۸� ȭ�鿡 ����Ǵ� ��ũ�� ���۷� �����ϰ�, ����� �ε����� ��ü
	// �̸� ����, ���� �����ӿ��� ����ۿ� print�� ��� ���ڵ��� ��ũ���� ��µȴ�. (������)
	// ���� ���� ǥ�õǰ� �ִ� ���۴� ����۷� ��ȯ�ǰ�, ���� �����ӿ��� �ش� ���ۿ� �׸��� �ȴ�.
	SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_BackBufferIdx]);
	switch (m_BackBufferIdx)
	{
		case 0: m_BackBufferIdx = 1; break;
		case 1: m_BackBufferIdx = 0; break;
	}
}

void Console::Print(wchar_t _shape, short _x, short _y)
{
	// ������ ����ۿ��� Ŀ���� ������ ��ġ�� �̵���Ű��, �� ��ġ�� 1���� ���ڸ� Write.
	DWORD dw;
	SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
	WriteConsole(m_ScreenBuffer[m_BackBufferIdx], &_shape, 1, &dw, nullptr);
}

void Console::PrintText(const std::wstring & _text, short _x, short _y)
{
	// Print�� ����������, 1���� ���ڰ� �ƴ� ���� ���� ����(���ڿ�)�� Write.
	// std::wstirng���� c_str() ��� �Լ��� �ش� ��Ʈ���� ù��° ������ �ּҸ� ������
	// Print�� &_shape�� �����ϰ� Write�� ���ڿ��� ���� �ּҰ� �Ѿ����,
	// �� ���� �μ��� _text.length()�� ���� ��ŭ�� ���̸�ŭ ���ڿ��� ���� Write���� �˷��ִ� ��
	// �⺻�����δ� Print() �Լ��� �����ص� ������, �޴� �� �ؽ�Ʈ ������ ���ϰ� ����Ϸ���
	// �̷��� ���ڿ� ��¿� �Լ��� ������ ���� ���� ����
	DWORD dw;
	SetConsoleCursorPosition(m_ScreenBuffer[m_BackBufferIdx], { _x, _y });
	WriteConsole(m_ScreenBuffer[m_BackBufferIdx], _text.c_str(), _text.length(), &dw, nullptr);
}

RECT Console::GetBoundaryBox() const
{
	// ���� �ܼ�â�� �����¿� ����ǥ(�ٿ����)�� RECT(�簢��)�� ��� ��ȯ
	// ���� �������� ������ 1ĭ�� ���� ������ -2, -1�� ����� �߰���.
	// (���δ� ������ ���ݱ��̴ϱ�, ���ο� ������ ���� ���̷��� 2�迩�� �ϴ� ��!)
	RECT boundaryBox;
	boundaryBox.top = 0;
	boundaryBox.left = 0;
	boundaryBox.right = m_ScreenWidth - 2;
	boundaryBox.bottom = m_ScreenHeight - 2; // �Ʒ� �� ���� ���� ���� -1 �߰� (������ ���� ������ ���� ǥ�� �Ұ�)
	return boundaryBox;
}
