#pragma once
#include "Object.h"

class Apple : public Object
{
public:
	Apple();
	virtual ~Apple();

	virtual void Update(float _dt) override; // 오버라이드는 이거 자체로 역할이 있는 건 아니고 버츄얼 했을 떄, 상속 받은 것을 확인하고 컴파일 할 때 빨간 줄을 띄워주는 용도. 안붙여도 동작은 같으나 좀더 안전한 코딩을 위해 사용. 어차피 위에 오브젝트 상속 받았으니까.
	virtual void Render() override;
};

