#pragma once
class Object;
class SnakeHead;

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
	
private:
	GameManager();
	~GameManager();

public:
	void Run();
	void Shutdown();

private: // Ŭ���� �������� ȣ���� �� ����
	void Init();
	void Release();
	void MainLoop();

	void Update();
	void Render();

	void KeyInputHandling();

private:
	bool m_IsOn;
	std::list<Object*> m_ObjectList;
	// �� �����Ӹ��� �������� �� ������Ʈ�� ã�ư� �� �ֵ��� ���޸𸮿� ����� ������Ʈ�� �ּҸ� �����ϴ� ����Ʈ

	// ������ ������ �̸� �տ� p�� �ٿ��ִ� ���̹� ������ �ִ�.
	SnakeHead* m_pSnakeHead;
};

// ��� �������� m_�빮�ڷ� ����
// �Լ����� �빮�ڷ� ����