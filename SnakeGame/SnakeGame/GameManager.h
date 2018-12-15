#pragma once
class Object;
class SnakeHead;

class GameManager
{
public: // 다른 데에서 호출할 수 있음
	//싱글톤 패턴
	//게임 매니저 같은 것은 공용이므로 하나만 만들어서 여기저기서 갖다 쓸 수 있게함
	static GameManager& GetInstance()
	{
		// 전역 함수
		// 어디서든지 클래스를 인스턴스화 하지 않아도 불러서 사용이 가능
		// (멤버함수를 호출하기 위한 인스턴스가 필요하지 않음)
		static GameManager instance; // static 변수는 데이터 영역에 저장되기 때문에, 어디서든 가져다 쓸 수 있음. 여러 번 불려도 한번만 생성됨.
		return instance;
	}
	
private:
	GameManager();
	~GameManager();

public:
	void Run();
	void Shutdown();

private: // 클래스 내에서만 호출할 수 있음
	void Init();
	void Release();
	void MainLoop();

	void Update();
	void Render();

	void KeyInputHandling();

private:
	bool m_IsOn;
	std::list<Object*> m_ObjectList;
	// 한 프레임마다 움직여야 할 오브젝트를 찾아갈 수 있도록 힙메모리에 저장될 오브젝트의 주소를 저장하는 리스트

	// 포인터 변수의 이름 앞에 p를 붙여주는 네이밍 관습이 있다.
	SnakeHead* m_pSnakeHead;
};

// 멤버 변수에는 m_대문자로 시작
// 함수명은 대문자로 시작