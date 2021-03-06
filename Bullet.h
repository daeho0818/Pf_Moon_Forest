#pragma once
#include "BulletPool.h"
class Bullet : public Component
{
public:
	Bullet(Object* object);
	~Bullet();

	void SetBullet(Vector2 direction, float move_speed, Image* image,
		D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1));

	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void ReturnBullet();

private:
	BoxColliderC* collider = nullptr;
	RendererC* renderer = nullptr;

	const Vector2* m_position = nullptr;
	Vector2 m_direction;

	bool is_set;
	float m_moveSpeed = 0;

};