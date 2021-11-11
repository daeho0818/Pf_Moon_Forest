#include "DXUT.h"
#include "Scene_Title.h"

Scene_Title::Scene_Title()
{
}

Scene_Title::~Scene_Title()
{
}

void Scene_Title::Init()
{
}

void Scene_Title::Update()
{
}

void Scene_Title::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Screen"), CENTER, 0.3f, false, D3DXCOLOR(0, 0, 0, 1));
}

void Scene_Title::UIRender()
{
	RENDER->CenterRender(IMAGE->FindImage("Screen"), Vector2(0, 0), 0.1f, true);
}
void Scene_Title::Release()
{
}
