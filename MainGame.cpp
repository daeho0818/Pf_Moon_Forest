#include "DXUT.h"
#include "MainGame.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	IMAGE->AddImage("Speed+", "Speed+");
	IMAGE->Loading();

	SCENE->AddScene("Scene_Loading", new Scene_Loading());
	SCENE->AddScene("Scene_Title", new Scene_Title());
	SCENE->ChangeScene("Scene_Title");

	SCENE->Init();
	OBJECT->Init();
	CAMERA->Init();
}

void MainGame::Update()
{
	SCENE->Update();
	OBJECT->Update();
	SOUND->Update();
	CAMERA->Update();
}

void MainGame::Render()
{
	RENDER->Begin();


	SCENE->Render();
	CAMERA->Render();

	OBJECT->Render();

	SCENE->UIRender();
	CAMERA->UIRender();


	RENDER->End();
}

void MainGame::Release()
{
	OBJECT->Release();
	SCENE->Release();
	CAMERA->Release();
	SOUND->StopAll();

	CameraManager::Destroy();
	ImageManager::Destroy();
	RenderManager::Destroy();
	SceneManager::Destroy();
	SoundManager::Destroy();
	ObjectManager::Destroy();
}

void MainGame::Begin()
{
	RENDER->Begin();
}

void MainGame::End()
{
	RENDER->End();
}

void MainGame::Lost()
{
	RENDER->Lost();
}

void MainGame::Reset()
{
	RENDER->Reset();
}
