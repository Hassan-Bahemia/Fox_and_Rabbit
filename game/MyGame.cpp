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

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	// Restart the play automatically - 5 secs after Game Over
	if (IsGameOver())
	{
		if (GetTime() > 5000)
			NewGame();
		return;
	}

	// Fox and Rabbit Maximum Speed Limit
	// TO DO: You can experiment with different maximum speeds
	float foxSpeed = 400;
	float rabbitSpeed = 450;
	float rabbitWanderSpeed = 300;

	// Fox and Rabbit Steering Forces
	CVector steerFox, steerRabbit;
	
	// Calculate the Fox Steering Force
	steerFox = fox.seek(rabbit.GetPosition(), foxSpeed);

	// Calculate the Rabbit Steering Force
	steerRabbit = rabbit.flee(rabbit.GetPosition(), rabbitSpeed);
	if(rabbit.GetPosition() < 300)
	{
	    
	}
	// TO DO [3]: Change the behaviour of the rabbit so there it flees only if its distance to the fox is less then 300 or 500.
	//            Otherwise let it just wander around (casually nibbling grass)
	// TO DO: Experiment with various values of the wander/flee threshold value
	// INFO:  Distance rabbit-fox can be obtained with:  Distance(rabbit.GetPosition(), fox.GetPosition())

	// Apply the Steering Forces
	fox.Accelerate(steerFox * (float)GetDeltaTime() / 1000.f);
	rabbit.Accelerate(steerRabbit * (float)GetDeltaTime() / 1000.f);
	
	// Rotate both animals so that are always heading their motion direction
	fox.SetRotation(fox.GetDirection());
	rabbit.SetRotation(rabbit.GetDirection());

	// mandatory part: update the rabbit and fox positions
	rabbit.Update(GetTime());
	fox.Update(GetTime());

	// keep the rabbit and the fox within the scene
	extern CGameApp app;
	rabbit.wrapToScreen(app.GetWidth(), app.GetHeight());
	fox.wrapToScreen(app.GetWidth(), app.GetHeight());

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
