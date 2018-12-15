#pragma once
#include "Object.h"


// 어떤 클래스를 상속받는 경우, : public 부모 클래스를 뒤에 붙여준다.
// 그리고, 반드시 소멸자에 virtual을 붙여서, 추후 delete할 때 메모리 릭이 발생하지 않도록 유의한다.
class RandomSpeedObj : public Object
{
public:
	RandomSpeedObj();
	virtual ~RandomSpeedObj();

	// 상속받는(오버라이딩) 함수들은 뒤에 override 키워드를 붙여준다.
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	float m_XSpeed;
	float m_YSpeed;
};

