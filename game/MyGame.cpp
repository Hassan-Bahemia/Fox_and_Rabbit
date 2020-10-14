#include "stdafx.h"
#include "MyGame.h"
#include <iostream>

using std::cout;
using std::endl;

CMyGame::CMyGame(void)
	: grass("grass-texture.jpg"),
	  rabbit(50, 550, 36, 72, "rabbit.png", CColor::Green(128), 0),
	  fox(750, 50, 119, 162, "fox.png", CColor::Green(128), 0)
{
}

CMyGame::~CMyGame(void)
{
}

float rand(float range)
{
	return ((float)rand() / (float)RAND_MAX) * range * 2 - range;
}

CVector seek(CVector myPos, CVector myVel, CVector targetPos, float speed)
{
	// TO DO [1]: Implement the SEEK behaviour. It is used by the fox
	return myVel;	// This line is NOT a part of the solutiuon - DELETE IT
}

CVector flee(CVector myPos, CVector myVel, CVector targetPos, float speed)
{
	// TO DO [2]: Implement the FLEE behaviour. It is used by the rabbit
	return myVel;	// This line is NOT a part of the solutiuon - DELETE IT
}

CVector wander(CVector myPos, CVector myVel)
{
	// TO DO [4]: Implement the WANDER behaviour. It may also be used by the rabbit
	return myVel;	// This line is NOT a part of the solutiuon - DELETE IT
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	// Fox and Rabbit Maximum Speed Limit
	// TO DO: You can experiment with different maximum speeds
	float foxSpeed = 300.0;
	float rabbitSpeed = 300.0;

	// Fox and Rabbit Steering Forces
	CVector steerFox, steerRabbit;
	
	// Calculate the Fox Steering Force
	steerFox = seek(fox.GetPosition(), fox.GetVelocity(), rabbit.GetPosition(), foxSpeed);

	// Calculate the Rabbit Steering Force
	// TO DO [3]: Change the behaviour of the rabbit so there it flees only if its distance to the fox is less then 300 or 500.
	//            Otherwise let it just wander around (casually nibbling grass)
	// TO DO: Experiment with various values of the wander/flee threshold value
	// INFO:  Distance rabbit-fox can be obtained with:  Distance(rabbit.GetPosition(), fox.GetPosition())
	steerRabbit = flee(rabbit.GetPosition(), rabbit.GetVelocity(), fox.GetPosition(), rabbitSpeed);

	// Apply the Steering Forces
	fox.Accelerate(steerFox / 30);
	rabbit.Accelerate(steerRabbit / 30);
	
	// Limit the speed - to their respective maximum speeds
	if (fox.GetSpeed() > foxSpeed) fox.SetSpeed(foxSpeed);
	if (rabbit.GetSpeed() > rabbitSpeed) rabbit.SetSpeed(rabbitSpeed);
	
	// Rotate both animals so that are always heading their motion direction
	fox.SetRotation(fox.GetDirection());
	rabbit.SetRotation(rabbit.GetDirection());

	// mandatory part: update the rabbit and fox positions
	rabbit.Update(GetTime());
	fox.Update(GetTime());

	// keep the rabbit and the fox within the scene
	extern CGameApp app;
	if (rabbit.GetX() < 0) rabbit.SetX((float)app.GetWidth());
	if (rabbit.GetX() > app.GetWidth()) rabbit.SetX(0);
	if (rabbit.GetY() < 0) rabbit.SetY((float)app.GetHeight());
	if (rabbit.GetY() >app.GetHeight()) rabbit.SetY(0);

	if (fox.GetX() < 0) fox.SetX((float)app.GetWidth());
	if (fox.GetX() > app.GetWidth()) fox.SetX(0);
	if (fox.GetY() < 0) fox.SetY((float)app.GetHeight());
	if (fox.GetY() >app.GetHeight()) fox.SetY(0);

	// hit test condition for the game over
	if (fox.HitTest(&rabbit))
		GameOver();
}

void CMyGame::OnDraw(CGraphics* g)
{
	// Draw the Background
	g->Blit(CVectorI(0, 0), grass);

	rabbit.Draw(g);
	fox.Draw(g);

	if (IsGameOver())
		*g << font(48) << center << vcenter << color(CColor::White()) << "OM NOM NOM NOM!" << endl << font(20) << "PRESS F2 TO RESTART";
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	rabbit.SetVelocity(0, 0);
	rabbit.SetRotation(0);
	rabbit.SetPosition(50, 550);
	fox.SetVelocity(0, 0);
	fox.SetRotation(0);
	fox.SetPosition(750, 50);

	StartGame();	// this allows to start the game immediately
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
}

// called when Game is Over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
	if (!IsGameOver())
		rabbit.SetPosition(x, y);
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
