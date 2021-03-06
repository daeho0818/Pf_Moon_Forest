#include "DXUT.h"
#include "Enemy2_1.h"

Enemy2_1::Enemy2_1(Object* object)
	:Component(object)
{
}

Enemy2_1::~Enemy2_1()
{
}

void Enemy2_1::Init()
{
	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();

	var image = IMAGE->FindImage("Enemy1");
	renderer->SetRenderer(image, D3DXCOLOR(1, 1, 1, 1));

	var img_info = image->info;
	collider->SetCollider(img_info.Width / 3 * 2, img_info.Height / 3 * 2);

	m_transform->m_localScale = Vector2(0.5f, 0.5f);

	bullet_image = IMAGE->FindImage("Bullet_Enemy_1");

	move_able = true;

	m_object->fire_helper = new FireHelper();

	m_object->OnCollisionEnter = [&](Object* other) -> void
	{
		if (other->m_type == EP_Bullet)
		{
			m_object->HitAnimation(D3DXCOLOR(1, 0, 0, 1));
			m_object->m_hp--;
		}
		else if (other->m_type == EPlayer)
		{
			m_object->is_destroy_check = true;
		}
	};
	m_object->OnDestroy = [&]()->void
	{
		PARTICLE->AddParticleAnim(IMAGE->MakeAnimation("Explosion"), m_transform->m_position, 0.01f);
	};

	m_object->m_hp = m_object->m_maxHp = 5;

	int temp = rand() % 100;
	stop_position_y = temp % 2 == 0 ? 400 : 200;
}

void Enemy2_1::Update()
{
	m_object->fire_helper->Update();

	m_object->fire_helper->Fire(m_transform->m_position, 0.5f,
		m_transform->down, "Enemy2_1 Bullet", EE_Bullet, 7, bullet_image);

	if (m_transform->m_position.y < stop_position_y - 20)
		D3DXVec2Lerp(&m_transform->m_position,
			&m_transform->m_position,
			&Vector2(m_transform->m_position.x, stop_position_y), DELTA);
	else
	{
		if (!wait_timer && move_able)
		{
			move_able = false;
			wait_timer = new Timer(3, 0, [&]()->void {move_able = true; });
			wait_timer->TimerStart();
		}

		if (move_able)
			m_transform->Translate(m_transform->down * DELTA * 500);
	}
}

void Enemy2_1::Render()
{
}

void Enemy2_1::UIRender()
{
}

void Enemy2_1::Release()
{
	if (wait_timer)
		wait_timer->ShutTimer();
}
