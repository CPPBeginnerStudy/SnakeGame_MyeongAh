#pragma once
class Object
{
public:
	Object();
	virtual ~Object();
	// ��� �ؼ� ������ Virtual�� �� ��� ��
	// Java���� Abstract �� �Ͱ� ���� ��

	// ������Ʈ ������ �� Init, �Ҹ��ų �� Release
	// ������Ʈ���� ���� �˾Ƽ� ������Ʈ, ������
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	// ������ ��, virtual�� ���� ������ �ڽ� ������Ʈ���� �������̵� �ؼ� �� �� ����
	// ������Ʈ Ÿ���� ��ü ����Ʈ�� �ڽ� ������Ʈ�� ��� ����Ϸ��� �� ��,
	// virtual�� �ƴ϶�� �ڽ��� ��ӹ��� �� �Լ��� ã�� �� ����.
	// �ڽ�/�θ� �Լ� �� �ٿ� virtual�� �ְ�, �ڽ� �Լ��� override�� �־�� �� �� ����
	// �� �׷��� Ÿ�� �ɽ��� �ؼ� ��� ��
};