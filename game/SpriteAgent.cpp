#include "stdafx.h"
#include "SpriteAgent.h"

// Constructors
CSpriteAgent::CSpriteAgent(float x, float y, char* pFileBitmap, Uint32 time) : CSprite(x, y, pFileBitmap, time) 
{ wanderTarget = CVector(0, 1); }

CSpriteAgent::CSpriteAgent(float x, float y, char* pFileBitmap, CColor colorKey, Uint32 time) : CSprite(x, y, pFileBitmap, colorKey, time)
{ wanderTarget = CVector(0, 1); }

CSpriteAgent::CSpriteAgent(float x, float y, float w, float h, char* pFileBitmap, Uint32 time) : CSprite(x, y, w, h, pFileBitmap, time)
{ wanderTarget = CVector(0, 1); }

CSpriteAgent::CSpriteAgent(float x, float y, float w, float h, char* pFileBitmap, CColor colorKey, Uint32 time) : CSprite(x, y, w, h, pFileBitmap, colorKey, time)
{ wanderTarget = CVector(0, 1); }

CSpriteAgent::~CSpriteAgent()  
{ }

// Behaviour Steerings

CVector CSpriteAgent::seek(CVector targetPos, float speed)
{
	// TO DO [1]: Implement the SEEK behaviour. It is used by the fox
	return GetVelocity();	// This line is NOT a part of the solutiuon - DELETE IT
}

CVector CSpriteAgent::flee(CVector targetPos, float speed)
{
	// TO DO [2]: Implement the FLEE behaviour. It is used by the rabbit
	return GetVelocity();	// This line is NOT a part of the solutiuon - DELETE IT
}

float random()
{
	return ((float)rand() / (float)RAND_MAX);
}

CVector CSpriteAgent::wander(float speed, float wanderDist, float wanderRadius)
{
	// TO DO [4]: Implement the WANDER behaviour. It may also be used by the rabbit
	return GetVelocity();	// This line is NOT a part of the solutiuon - DELETE IT
}

// Screen functions

void CSpriteAgent::wrapToScreen(int width, int height)
{
	if (GetX() < 0) SetX((float)width);
	if (GetX() > width) SetX(0);
	if (GetY() < 0) SetY((float)height);
	if (GetY() > height) SetY(0);

}
