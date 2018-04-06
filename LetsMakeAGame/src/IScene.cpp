
#include "IScene.h"
#include "Tank.h"
#include "Helper_Functions.h"

std::list<Entity*>* IScene::m_entities = new std::list<Entity*>();
std::list<IMenu*> * IScene::m_menus = new std::list<IMenu*>();
std::list<SpriteObjects*> * IScene::m_spriteobjects = new std::list<SpriteObjects*>();

IScene::IScene()
{
}

IScene::~IScene()
{
	m_spriteobjects->clear();
	m_menus->clear();
}

void IScene::Update()
{
	if (!m_menus->empty())
	{
		m_menus->back()->Update();
	}
	else {
		for (auto& entity : *m_entities)
		{
			if (entity->Active)
				entity->Update();
		}
	}
}

void IScene::Draw()
{
	if (!m_menus->empty())
		m_menus->back()->Draw();

	for (auto& sprite : *m_spriteobjects)
	{
		sprite->Draw();
	}

}

std::list<Entity*> IScene::GetEntiries(size_t type)
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
	std::list<Entity*> entities = GetEntiries(Tank::type);
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

void IScene::RemoveInactiveSpriteObjects()
{
	for (auto it = m_spriteobjects->begin(); it != m_spriteobjects->end(); )
	{
		if (!(*it)->GetActive())
		{
			delete *it;
			it = m_spriteobjects->erase(it);
		}
		else
			it++;
	}
}


SDL_Texture* IScene::GetTexture(std::string name)
{
	SDL_Surface* surface = loadSurface(std::string(Globals::GetResourcePath() + name), Globals::Renderer);
	SDL_Surface* scaledSurface = SDL_CreateRGBSurface(0, Globals::ScreenWidth, Globals::ScreenHeight, 32, 0xFF, 0xFF00, 0xFF0000, 0XFF000000);


	static SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = Globals::ScreenWidth;
	rect.h = Globals::ScreenHeight;
	int error;
	if (error = SDL_BlitScaled(surface, NULL, scaledSurface, &rect))
	{
		std::cout << "Error Happened" << std::endl;
	}

	SDL_Texture* testMap = SDL_CreateTextureFromSurface(Globals::Renderer, scaledSurface);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(scaledSurface);
	return testMap;
}