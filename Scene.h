#pragma once
class Scene abstract
{
	friend class SceneManager;
public:
	virtual ~Scene() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void UIRender() = 0;
	virtual void Release() = 0;

private:
	string scene_name;
};

