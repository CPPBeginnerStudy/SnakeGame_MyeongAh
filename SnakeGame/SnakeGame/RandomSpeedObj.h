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
	virtual void Update(float _dt) override;
	virtual void Render() override;

private:
	float m_XSpeed;
	float m_YSpeed;

	// 현재 이동 방향을 오른쪽/왼쪽 구분, 위/아래 구분하기 위한 변수이다.
	bool m_IsRight;
	bool m_IsBottom;
};

