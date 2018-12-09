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

	char GetShape() const { return m_Shape; }
	short GetX() const { return m_X; }
	short GetY() const { return m_Y; }

	void SetShape(char _shape) { m_Shape = _shape; }
	void SetX(short _x) { m_X = _x; }
	void SetY(short _y) { m_Y = _y; }

private:
	// ������ �� ��ü�� �ڽ��� ����� �ϳ��� ����(char)�� ��Ÿ����,
	// x, y ��ǥ�� ���� ���� ��ġ�� �� �� �ְ� �Ѵ�.
	// cmd���� ���̺귯�� �Լ����� ��ǥ������ short Ÿ������ �ٷ�� ������
	// ���⼭�� short Ÿ������ ��ǥ ������ �����Ѵ�.
	char m_Shape;
	short m_X;
	short m_Y;

	// ���� �̵� ������ ��/��, ��/�Ʒ� �����ϱ� ���� ����
	bool m_IsRight;
	bool m_IsBottom;
};