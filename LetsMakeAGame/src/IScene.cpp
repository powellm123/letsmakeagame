
#include "IScene.h"

std::list<Entity*>* IScene::m_entities = new std::list<Entity*>();

IScene::IScene()
{
}

IScene::~IScene()
{
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
	for (auto& entity : *m_entities)
	{
		if (entity->Active)
			entity->Draw();
	}
}