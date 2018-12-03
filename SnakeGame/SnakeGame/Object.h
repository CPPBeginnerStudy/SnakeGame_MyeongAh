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

	// 선언할 때, virtual을 쓰지 않으면 자식 오브젝트에서 오버라이딩 해서 쓸 수 없음
	// 오브젝트 타입의 객체 리스트에 자식 오브젝트를 담고 사용하려고 할 때,
	// virtual이 아니라면 자식이 상속받은 그 함수를 찾을 수 없음.
	// 자식/부모 함수 둘 다에 virtual이 있고, 자식 함수에 override가 있어야 쓸 수 있음
	// 안 그러면 타입 케스팅 해서 써야 됨
};