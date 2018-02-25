//
//#include "AnimationSet.h"
//
//
//void AnimationSet::LoadAnimationSet(std::string filename, bool setColorKey, int transparentPixelIndex, bool createWhiteTexture)
//{
//	/*std::ifstream file;
//	std::string resPath = Globals::GetResourcePath();
//
//	file.open(resPath + filename);
//	if (file.good())
//	{
//		std::getline(file, ImageName);
//		if (setColorKey)
//		{
//			SDL_Surface *spriteSurface = IMG_Load(std::string(resPath + ImageName).c_str());
//
//			SDL_Color *transparentPixel = &spriteSurface->format->palette->colors[transparentPixelIndex];
//			SDL_SetColorKey(spriteSurface, 1, SDL_MapRGB(spriteSurface->format, transparentPixel->r, transparentPixel->g, transparentPixel->b));
//
//			SpriteSheet = SDL_CreateTextureFromSurface(&Globals::Renderer, spriteSurface);
//
//			if (createWhiteTexture)
//			{
//				SDL_Surface *whiteSurface = IMG_Load(std::string(resPath + "allwhite.png").c_str());
//
//				SDL_Color *transparentPixel = &whiteSurface->format->palette->colors[transparentPixelIndex];
//				SDL_SetColorKey(whiteSurface, 1, SDL_MapRGB(whiteSurface->format, transparentPixel->r, transparentPixel->g, transparentPixel->b));
//
//				WhiteSpriteSheet = SDL_CreateTextureFromSurface(&Globals::Renderer, whiteSurface);
//
//				SDL_FreeSurface(whiteSurface);
//			}
//			else {
//				WhiteSpriteSheet = nullptr;
//			}
//			SDL_FreeSurface(spriteSurface);
//		}
//		else {
//			SpriteSheet = IMG_LoadTexture(&Globals::Renderer, std::string(resPath + ImageName).c_str());
//		}
//
//		std::string buffer;
//		std::getline(file, buffer);
//		std::stringstream ss;
//		
//		ss << buffer;
//		
//		int numberOfAnimations;
//		ss >> numberOfAnimations;
//
//		for (int i = 0; i < numberOfAnimations; i++)
//		{
//			Animation newAnimation;
//			newAnimation.Load(file);
//			Animations.push_back(newAnimation);
//		}
//	}
//	file.close();*/
//}
//
//AnimationSet::~AnimationSet()
//{
//
//}
//
//Animation* AnimationSet::GetAnimation(std::string name)
//{
//	return nullptr;
//}