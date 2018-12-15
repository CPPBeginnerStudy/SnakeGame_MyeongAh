#pragma once
class Object
{
public:
	Object();
	virtual ~Object();
	// 상속 해서 쓰려면 Virtual을 써 줘야 함
	// Java에서 Abstract 그 것과 같은 것

	// 오브젝트 생성할 때 Init, 소멸시킬 때 Release
	// 오브젝트마다 각자 알아서 업데이트, 랜더링
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	// Init(), Release()는 엄청 큰 오브젝트를 만들었을 때,
	// Delete 해주지 않고, 다시 초기화 해서 쓰는 방식으로 사용함.
	// 우리 게임은 그정도로 큰 오브젝트가 아니고, 생성자에서 초기화 다 해줄 수 있는 수준이라 삭제함!

	// 선언할 때, virtual을 쓰지 않으면 자식 오브젝트에서 오버라이딩 해서 쓸 수 없음
	// 오브젝트 타입의 객체 리스트에 자식 오브젝트를 담고 사용하려고 할 때,
	// virtual이 아니라면 자식이 상속받은 그 함수를 찾을 수 없음.
	// 자식/부모 함수 둘 다에 virtual이 있고, 자식 함수에 override가 있어야 쓸 수 있음
	// 안 그러면 타입 케스팅 해서 써야 됨

	wchar_t GetShape() const { return m_Shape; }
	short GetX() const { return m_X; }
	short GetY() const { return m_Y; }

	void SetShape(wchar_t _shape) { m_Shape = _shape; }
	void SetX(short _x) { m_X = _x; }
	void SetY(short _y) { m_Y = _y; }

	// private: 본 클래스 내에서만 접근 가능 (자식 클래스에서는 접근 X, 진짜 나 자신만 접근 되는 것)
	// protected: 자식 클래스에서도 접근 가능
protected:
	// 랜더링 될 객체는 자신의 모양을 하나의 문자(wchar_t)로 나타내며,
	// x, y 좌표를 통해 현재 위치를 알 수 있게 한다.
	// cmd관련 라이브러리 함수에서 좌표값들을 short 타입으로 다루기 때문에
	// 여기서도 short 타입으로 좌표 변수를 지정한다.
	wchar_t m_Shape;
	short m_X;
	short m_Y;

	// 현재 이동 방향을 오/왼, 위/아래 구분하기 위한 변수
	bool m_IsRight;
	bool m_IsBottom;
};