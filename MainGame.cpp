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
	SCENE->AddScene("Scene_Loading", new Scene_Loading());
	SCENE->AddScene("Scene_Title", new Scene_Title());
	SCENE->AddScene("Scene_Stage1", new Scene_Stage1());
	SCENE->AddScene("Scene_Stage2", new Scene_Stage2());

	SCENE->Init();
	OBJECT->Init();
	PARTICLE->Init();
	CAMERA->Init();

	SCENE->ChangeScene("Scene_Loading");
}

void MainGame::Update()
{
	INPUT->Update();
	SCENE->Update();
	OBJECT->Update();
	PARTICLE->Update();
	SOUND->Update();
	CAMERA->Update();
}

void MainGame::Render()
{
	RENDER->Begin();


	SCENE->Render();
	CAMERA->Render();

	OBJECT->Render();
	PARTICLE->Render();

	OBJECT->UIRender();

	SCENE->UIRender();
	CAMERA->UIRender();


	RENDER->End();
}

void MainGame::Release()
{
	OBJECT->Release();
	PARTICLE->Release();
	SCENE->Release();
	CAMERA->Release();
	SOUND->StopAll();

	CameraManager::Destroy();
	ImageManager::Destroy();
	RenderManager::Destroy();
	BulletPool::Destroy();
	SceneManager::Destroy();
	SoundManager::Destroy();
	ObjectManager::Destroy();
	InputManager::Destroy();
	ParticleManager::Destroy();
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
