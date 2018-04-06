
#include "Entity.h"

Entity::Entity(size_t type, float x, float y) : m_type(type), X(x), Y(y)
{
	m_components = new std::list < IComponent*>();
	Active = true;
	m_id = Globals::GenerateId();
	m_isDying = false;
	m_setActiveToFalse = true;
}

Entity::Entity(size_t type, float x, float y, Sprite * sprite) : Entity(type, x, y)
{
	m_sprite = sprite;
}

Entity::~Entity()
{
	for (auto it : *m_components)
	{
		delete it;
	}
	m_components->clear();
}

void Entity::Update()
{
	if (m_isDying)
	{
		if (m_setActiveToFalse)
		{
			Active = false;
		}
	}

	for (auto& component : *m_components)
	{
		component->Update();
	}
}

size_t Entity::GetType()
{
	return m_type;
}

IComponent* Entity::GetComponent(size_t type)
{
	for (auto& it : *m_components)
	{
		if (it->GetType() == type)
			return it;
	}

	return nullptr;
}


size_t Entity::GetId()
{
	return m_id;
}

void Entity::SetIsDying(bool isdying)
{
	m_isDying = isdying;
}

bool Entity::GetIsDying()
{
	return m_isDying;
}

bool Entity::EntityCompare(const Entity * const & a, const Entity * const & b)
{
	if (a != 0 && b != 0)
		return a->m_type > b->m_type;

	return false;
}


void Entity::RemoveInactiveEntitiesFromList(std::list<Entity*>* entities, bool deleteEntities)
{
	for (auto it = entities->begin(); it != entities->end();)
	{
		if (!(*it)->Active)
		{
			if (deleteEntities)
				delete *it;
			it = entities->erase((it));
		}
		else {
			it++;
		}
	}
}

void Entity::Draw()
{
	if(m_sprite != nullptr)
		m_sprite->Draw(MathHelper::CreatePoint(X, Y), 1,1);
	for (auto& component : *m_components)
	{
		component->Draw();
	}

}


void Entity::RemoveAllFromList(std::list<Entity*> *entities, bool deleteEntities)
{
	for (auto it = entities->begin(); it != entities->end();)
	{
		if (deleteEntities)
		{
			delete *it;
			*it = NULL;
		}
		it = entities->erase((it));
	}
}