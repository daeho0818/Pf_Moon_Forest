#include "DXUT.h"
#include "Enemy1_4.h"

Enemy1_4::Enemy1_4(Object* object)
	:Component(object)
{
}

Enemy1_4::~Enemy1_4()
{
}

void Enemy1_4::Init()
{
	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();

	var image = IMAGE->FindImage("Enemy1");
	renderer->SetRenderer(image, D3DXCOLOR(1, 1, 1, 1));

	var img_info = image->info;
	collider->SetCollider(img_info.Width / 3 * 2, img_info.Height / 3 * 2);

	reflect_count = 0;

	m_transform->m_localScale = Vector2(0, 0);

	m_object->fire_helper = new FireHelper();

	bullet_image = IMAGE->FindImage("Bullet_Enemy_1");

	m_object->spawn_animation = true;

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
}

void Enemy1_4::Update()
{
	if (m_object->spawn_animation)
		m_object->SpawnAnimation(Vector2(0.7f, 0.7f));

	else
	{
		m_object->fire_helper->Update();

		m_transform->Translate(move_direction * DELTA * 200);

		if (reflect_count < 3)
			if ((m_transform->m_position.x > WINSIZEX - 50 && move_direction == m_transform->right) ||
				(m_transform->m_position.x < 0 + 50 && move_direction == m_transform->left))
			{
				move_direction *= -1;
				reflect_count++;
			}

		Vector2 direction;
		if (m_player->m_object)
			direction = m_player->m_transform->m_position - m_transform->m_position;
		else
			direction = m_transform->down;


		m_object->fire_helper->Fire(m_transform->m_position, 0.5f, *D3DXVec2Normalize(&direction, &direction), "Enemy1_4 Bullet", EE_Bullet, 7, bullet_image);
	}
}

void Enemy1_4::Render()
{
}

void Enemy1_4::UIRender()
{
}

void Enemy1_4::Release()
{
}

void Enemy1_4::SetEnemy(Player* player, int enemy_index)
{
	move_direction = enemy_index % 2 == 0 ? m_transform->left : m_transform->right;
	m_player = player;
}
