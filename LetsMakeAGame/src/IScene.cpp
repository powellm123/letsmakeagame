
#include "IScene.h"

std::list<Entity*>* IScene::m_entities = new std::list<Entity*>();

std::list<SpriteObjects*> * IScene::m_spriteobjects = new std::list<SpriteObjects*>();

IScene::IScene()
{
}

IScene::~IScene()
{
	while (!m_spriteobjects->empty())
	{
		m_spriteobjects->pop_back();
	}
}

void IScene::Update()
{
	
	for (auto& entity : *m_entities)
	{
		if(entity->Active)
			entity->Update();
	}
}

void IScene::Draw()
{
	for (auto& sprite : *m_spriteobjects)
	{
		sprite->Draw();
	}

}

std::list<Entity*> IScene::GetEntiries(std::string type)
{
	std::list<Entity*> entities;
	for (auto& entity : *m_entities)
	{
		if (entity->GetType() == type)
			entities.push_back(entity);
	}

	return entities;
}

int IScene::GetAliveCount()
{
	std::list<Entity*> entities = GetEntiries("tank");
	int count = 0;
	for (auto& entity : entities)
	{
		Player *p = (Player*)entity;
		if (p->IsAlive())
		{
			count++;
		}
	}
	return count;
}