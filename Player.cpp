#include "DXUT.h"
#include "Player.h"

Player::Player(Object* object) : Component(object)
{
}

Player::~Player()
{
}

void Player::Init()
{
	move_range =
	{
		0,
		0,
		WINSIZEX,
		WINSIZEY
	};

	m_position = &(m_transform->m_position);
	m_transform->m_localScale = Vector2(0.5f, 0.5f);

	move_speed = 1000;
	fire_range = 0.5f;
	m_object->OnCollisionEnter = [&](Object* other)->void {};

	bullet_image = IMAGE->FindImage("Bullet_Player");

	collider = m_object->AddComponent<BoxColliderC>();
	renderer = m_object->AddComponent<RendererC>();

	renderer->Setting(IMAGE->FindImage("Player"), D3DXCOLOR(1, 1, 1, 1));

	bullet_pool = m_object->GetBulletPool();
}

void Player::Update()
{
	ChkMoveRange();

	if (GetKey('A'))
	{
		m_transform->m_position += m_transform->left * DELTA * move_speed;
	}
	if (GetKey('D'))
	{
		m_transform->m_position += m_transform->right * DELTA * move_speed;
	}
	if (GetKey('W'))
	{
		m_transform->m_position += m_transform->up * DELTA * move_speed;
	}
	if (GetKey('S'))
	{
		m_transform->m_position += m_transform->down * DELTA * move_speed;
	}

	if (GetKey(VK_SPACE)) Fire();

	if (GetKey('R')) m_transform->m_rotationZ++;
}

void Player::Render()
{
}

void Player::UIRender()
{
}

void Player::Release()
{
}

void Player::ChkMoveRange()
{
	if (m_position->x < move_range.left)
		m_transform->m_position.x = move_range.left;
	else if (m_position->x > move_range.right)
		m_transform->m_position.x = move_range.right;

	if (m_position->y < move_range.top)
		m_transform->m_position.y = move_range.top;
	else if (m_position->y > move_range.bottom)
		m_transform->m_position.y = move_range.bottom;
}

void Player::Fire()
{
	Bullet* bullet = bullet_pool->GetBullet(m_transform->m_position, "Player Bullet", EE_Bullet);
	if (bullet)
	{
		Vector2 dir = INPUT->GetMousePosition() - (*m_position);
		bullet->SetBullet(*D3DXVec2Normalize(&dir, &dir), 1, bullet_image, bullet_pool);
	}
}
