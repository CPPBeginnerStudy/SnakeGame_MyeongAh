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

	// Init(), Release()�� ��û ū ������Ʈ�� ������� ��,
	// Delete ������ �ʰ�, �ٽ� �ʱ�ȭ �ؼ� ���� ������� �����.
	// �츮 ������ �������� ū ������Ʈ�� �ƴϰ�, �����ڿ��� �ʱ�ȭ �� ���� �� �ִ� �����̶� ������!

	// ������ ��, virtual�� ���� ������ �ڽ� ������Ʈ���� �������̵� �ؼ� �� �� ����
	// ������Ʈ Ÿ���� ��ü ����Ʈ�� �ڽ� ������Ʈ�� ��� ����Ϸ��� �� ��,
	// virtual�� �ƴ϶�� �ڽ��� ��ӹ��� �� �Լ��� ã�� �� ����.
	// �ڽ�/�θ� �Լ� �� �ٿ� virtual�� �ְ�, �ڽ� �Լ��� override�� �־�� �� �� ����
	// �� �׷��� Ÿ�� �ɽ��� �ؼ� ��� ��

	wchar_t GetShape() const { return m_Shape; }
	short GetX() const { return m_X; }
	short GetY() const { return m_Y; }

	void SetShape(wchar_t _shape) { m_Shape = _shape; }
	void SetX(short _x) { m_X = _x; }
	void SetY(short _y) { m_Y = _y; }

	// private: �� Ŭ���� �������� ���� ���� (�ڽ� Ŭ���������� ���� X, ��¥ �� �ڽŸ� ���� �Ǵ� ��)
	// protected: �ڽ� Ŭ���������� ���� ����
protected:
	// ������ �� ��ü�� �ڽ��� ����� �ϳ��� ����(wchar_t)�� ��Ÿ����,
	// x, y ��ǥ�� ���� ���� ��ġ�� �� �� �ְ� �Ѵ�.
	// cmd���� ���̺귯�� �Լ����� ��ǥ������ short Ÿ������ �ٷ�� ������
	// ���⼭�� short Ÿ������ ��ǥ ������ �����Ѵ�.
	wchar_t m_Shape;
	short m_X;
	short m_Y;

	// ���� �̵� ������ ��/��, ��/�Ʒ� �����ϱ� ���� ����
	bool m_IsRight;
	bool m_IsBottom;
};