#pragma once
class GameManager
{
public: // �ٸ� ������ ȣ���� �� ����
	//�̱��� ����
	//���� �Ŵ��� ���� ���� �����̹Ƿ� �ϳ��� ���� �������⼭ ���� �� �� �ְ���
	static GameManager& GetInstance()
	{
		// ���� �Լ�
		// ��𼭵��� Ŭ������ �ν��Ͻ�ȭ ���� �ʾƵ� �ҷ��� ����� ����
		// (����Լ��� ȣ���ϱ� ���� �ν��Ͻ��� �ʿ����� ����)
		static GameManager instance; // static ������ ������ ������ ����Ǳ� ������, ��𼭵� ������ �� �� ����. ���� �� �ҷ��� �ѹ��� ������.
		return instance;
	}

public:
	void Run();
	void Shutdown();

private: // Ŭ���� �������� ȣ���� �� ����
	void Init();
	void Release();
	void MainLoop();

private:
	GameManager() {}
	~GameManager() {}

private:
	bool m_IsOn;
};

// ��� �������� m_�빮�ڷ� ����
// �Լ����� �빮�ڷ� ����