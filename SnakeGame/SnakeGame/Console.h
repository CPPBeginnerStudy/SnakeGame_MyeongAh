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
	void Releas();
};

