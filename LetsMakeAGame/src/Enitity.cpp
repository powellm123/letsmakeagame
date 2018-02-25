
#include "Entity.h"

Entity::Entity(std::string type, float x, float y) : m_type(type), X(x), Y(y)
{
	m_components = new std::list < IComponent*>();
	Active = true;
	m_id = Globals::GenerateId();
	m_isDying = false;
}

Entity::Entity(std::string type, float x, float y, SDL_Sprite * sprite) : Entity(type, x, y)
{
	m_sprite = sprite;
}

Entity::~Entity()
{
	for (auto it = m_components->begin(); it != m_components->end();)
	{
		delete *it;
		it = m_components->erase(it);
	}
}

void Entity::Update()
{
	if (m_isDying)
	{
		Active = false;
	}

	for (auto& component : *m_components)
	{
		component->Update();
	}
}

std::string Entity::GetType()
{
	return m_type;
}

IComponent* Entity::GetComponent(std::string name)
{
	std::string lowerName = UtilMethods::ToLower(name);
	for (auto& it : *m_components)
	{
		if (it->GetName() == lowerName)
			return it;
	}

	return nullptr;
}

std::string Entity::GetId()
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
	m_sprite->Draw(Globals::Renderer, X, Y, 0);
	for (auto& component : *m_components)
	{
		component->Draw();
	}

}


void Entity::RemoveAllFromList(list<Entity*> *entities, bool deleteEntities)
{
	for (auto it = entities->begin(); it != entities->end();)
	{
		if (deleteEntities)
			delete *it;
		it = entities->erase((it));
	}
}