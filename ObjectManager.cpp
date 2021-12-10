#include "DXUT.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Init()
{
}

void ObjectManager::Update()
{
	for (var iter = m_objects.begin(); iter != m_objects.end();)
	{
		if (!(*iter)->is_destroy)
		{
			if ((*iter)->activeSelf)
			{
				for (var c_iter = (*iter)->components.begin(); c_iter != (*iter)->components.end();)
				{
					if ((c_iter)->second->enabled)
						c_iter->second->Update();
					++c_iter;
				}
				++iter;
			}
		}
		else
		{
			if ((*iter)->m_type == ObjType::EE_Bullet || (*iter)->m_type == ObjType::EP_Bullet)
			{
				Bullet* bullet = (*iter)->GetComponent<Bullet>();
				bullet->ReturnBullet();
			}

			iter = m_objects.erase(iter);
		}
	}

	CheckAllCollider();
}

void ObjectManager::Render()
{
	for (var iter = m_objects.begin(); iter != m_objects.end();)
	{
		if ((*iter) != null)
		{
			if ((*iter)->activeSelf)
			{
				for (var c_iter = (*iter)->components.begin(); c_iter != (*iter)->components.end();)
				{
					if ((*c_iter).second != null)
					{
						if ((c_iter)->second->enabled)
							c_iter->second->Render();
						++c_iter;
					}
				}
				++iter;
			}
		}
	}
}

void ObjectManager::UIRender()
{
	for (var iter = m_objects.begin(); iter != m_objects.end();)
	{
		if ((*iter) != null)
		{
			if ((*iter)->activeSelf)
			{
				for (var c_iter = (*iter)->components.begin(); c_iter != (*iter)->components.end();)
				{
					if ((*c_iter).second != null)
					{
						if ((c_iter)->second->enabled)
							c_iter->second->UIRender();
						++c_iter;
					}
				}
				++iter;
			}
		}
	}
}

void ObjectManager::Release()
{
	DestroyAllObject();
}

Object* ObjectManager::CreateObject(string name, ObjType type, Vector2 position)
{
	Object* object = new Object(name, type, position);

	m_objects.push_back(object);

	switch (object->m_type)
	{
	case ObjType::EPlayer:
		m_player = object;
		break;
	case ObjType::EEnemy:
		m_enemies.push_back(object);
		break;
	case ObjType::EE_Bullet:
		m_eBullets.push_back(object);
		break;
	case ObjType::EP_Bullet:
		m_pBullets.push_back(object);
		break;
	case ObjType::EItem:
		m_items.push_back(object);
		break;
	}

	return object;
}

list<Object*> ObjectManager::FindObject(string name)
{
	list<Object*> obj_list;

	for (var iter : m_objects)
	{
		if (iter->m_name == name)
			obj_list.push_back(iter);
	}

	return obj_list;
}

list<Object*> ObjectManager::FindObject(ObjType type)
{
	list<Object*> obj_list;

	for (var iter : m_objects)
	{
		if (iter->m_type == type)
			obj_list.push_back(iter);
	}

	return obj_list;
}

void ObjectManager::DestroyAllObject()
{
	for (var iter : m_objects)
	{
		for (var c_iter : iter->components)
		{
			c_iter.second->Release();
			SAFE_DELETE(c_iter.second);
		}
		iter->components.clear();
		SAFE_DELETE(iter);
	}
	m_objects.clear();
}

void ObjectManager::CheckAllCollider()
{
	if (!m_player) return;

	BoxColliderC* player_collider = m_player->GetComponent<BoxColliderC>();
	BoxColliderC* other_collider;

	for (var e_iter = m_enemies.begin(); e_iter != m_enemies.end();)
	{
		if (!(*e_iter)->is_destroy)
		{
			other_collider = (*e_iter)->GetComponent<BoxColliderC>();
			if (player_collider->enabled && other_collider->enabled)
			{
				if (player_collider->OBBCheck((*e_iter)->m_transform))
				{
					if (player_collider->m_object->OnCollisionEnter)
						player_collider->m_object->OnCollisionEnter((*e_iter));

					if ((*e_iter)->OnCollisionEnter)
						(*e_iter)->OnCollisionEnter(player_collider->m_object);
				}
			}

			for (var pb_iter = m_pBullets.begin(); pb_iter != m_pBullets.end();)
			{
				if (!(*pb_iter)->is_destroy)
				{
					if (other_collider->enabled && (*pb_iter)->GetComponent<BoxColliderC>()->enabled)
					{
						if (other_collider->OBBCheck((*pb_iter)->m_transform))
						{
							if ((*e_iter)->OnCollisionEnter)
								(*e_iter)->OnCollisionEnter((*pb_iter));

							if ((*pb_iter)->OnCollisionEnter)
								(*pb_iter)->OnCollisionEnter((*e_iter));
						}
					}
					pb_iter++;
				}
				else
				{
					pb_iter = m_pBullets.erase(pb_iter);
				}
			}
			e_iter++;
		}
		else
		{
			e_iter = m_enemies.erase(e_iter);
		}
	}

	for (var eb_iter = m_eBullets.begin(); eb_iter != m_eBullets.end();)
	{
		if (!(*eb_iter)->is_destroy)
		{
			if (player_collider->enabled && (*eb_iter)->GetComponent<BoxColliderC>()->enabled)
			{
				if (player_collider->OBBCheck((*eb_iter)->m_transform))
				{
					if (player_collider->m_object->OnCollisionEnter)
						player_collider->m_object->OnCollisionEnter((*eb_iter));

					if ((*eb_iter)->OnCollisionEnter)
						(*eb_iter)->OnCollisionEnter(player_collider->m_object);
				}
			}
			eb_iter++;
		}
		else
		{
			eb_iter = m_eBullets.erase(eb_iter);
		}
	}

	for (var i_iter = m_items.begin(); i_iter != m_items.end();)
	{
		if (!(*i_iter)->is_destroy)
		{
			if (player_collider->enabled && (*i_iter)->GetComponent<BoxColliderC>()->enabled)
			{
				if (player_collider->OBBCheck((*i_iter)->m_transform))
				{
					if (player_collider->m_object->OnCollisionEnter)
						player_collider->m_object->OnCollisionEnter((*i_iter));

					if ((*i_iter)->OnCollisionEnter)
						(*i_iter)->OnCollisionEnter(player_collider->m_object);
				}
			}
			i_iter++;
		}
		else
		{
			i_iter = m_items.erase(i_iter);
		}
	}
}
