//
//#include "Frame.h"
//
//void Frame::Draw(SDL_Texture* spriteSheet, float x, float y)
//{
//
//}
//
//void Frame::Load(std::ifstream & file)
//{
//	std::string buffer;
//
//	std::getline(file, buffer);
//
//	std::getline(file, buffer);
//	std::stringstream ss;
//	SDL_Rect Clip;
//	ss << buffer;
//	ss >> Clip.x >> Clip.y >> Clip.w >> Clip.h;
//
//	//offset/pivot
//	getline(file, buffer);
//	ss.clear();
//	SDL_Point Offset;
//	ss << buffer;
//	ss >> Offset.x >> Offset.y;
//
//	//duration
//	getline(file, buffer);
//	ss.clear();
//
//	ss << buffer;
//	ss >> Duration;
//	//index
//	getline(file, buffer);
//	ss.clear();
//
//	ss << buffer;
//	ss >> FrameNumber;
//}
