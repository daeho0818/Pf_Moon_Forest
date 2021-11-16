#pragma once
#include "Singleton.h"

enum ChangeMode
{
	Small = 1,
	Big = 2,
	FadeIn = 4,
	FadeOut = 8,

	Small_FadeIn = 5,
	Small_FadeOut = 9,

	Big_FadeIn = 6,
	Big_FadeOut = 10
};

class ParticleManager : public Singleton<ParticleManager>
{
public:
	ParticleManager();
	~ParticleManager();

	void Update();
	void Render();
	void Release();

	void AddParticleAnim(vector<Image*> animation, Vector2 position, float frameTime, float size = 1);
	// changeMode = ChangeMode::Big | ChangeMode::FadeOut 이런식으로 적용
	void AddParticleEffect(Image* image, Vector2 position, D3DXCOLOR color, ChangeMode changeMode, float size = 1, float destroyTime = 1);

private:
	vector<Particle*> m_particles;
	vector<Effect*> m_effects;

	bool isParticleAnimation;
	bool isParticleEffect;
};
#define PARTICLE ParticleManager::Instance()

class Particle
{
public:
	Particle(vector<Image*> animation, Vector2 position, float frame_time, float size);
	~Particle();

private:
	vector<Image*> m_animation;
	Vector2 m_position;
	float m_frameTime;
	float m_size;
	int m_index;
	bool m_destroy;
};

class Effect
{
public:
	Effect(Image* image, Vector2 position, D3DXCOLOR color, ChangeMode change_mode, float size, float destroy_time);
	~Effect();

private:
	Image* m_image;
	Vector2 m_position;
	D3DXCOLOR m_color;
	ChangeMode m_changeMode;
	float m_size;
	float m_destroyTime;
};