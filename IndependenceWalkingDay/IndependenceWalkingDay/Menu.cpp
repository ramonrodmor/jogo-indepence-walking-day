/**********************************************************************************
// Home (Código Fonte)
//
// Criação:		14 Fev 2013
// Atualização:	18 Jun 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Tela de abertura do jogo GravityGuy
//
**********************************************************************************/

#include "Engine.h"
#include "Jogo.h"
#include "Menu.h"
#include "GeometryWars.h"

// ------------------------------------------------------------------------------

void Menu::Init()
{
	// joystick
	joy = new Joystick();
	joystickOn = joy->Initialize();

	// pano de fundo
	fundo = new Sprite("Resources/Menu.jpg");

	// toca musica do menu
	Jogo::audio->Volume(MENU, 2.0f);
	Jogo::audio->Play(MENU, TRUE);
}

// ------------------------------------------------------------------------------

void Menu::Update(float gameTime)
{
	window->CloseOnEscape();

	if (joystickOn)
	{
		// seleciona próximo joystick (Page Down)
		if (window->KeyCtrl(VK_NEXT))
			joy->SelectNext();

		// seleciona joystick anterior (Page Up)
		if (window->KeyCtrl(VK_PRIOR))
			joy->SelectPrev();

		joy->GetState();

		if (joy->ButtonCtrl(9))
		{
			Jogo::audio->Stop(MENU);
			Jogo::NextLevel<GeometryWars>();
		}
	}

	else if (window->KeyCtrl(VK_RETURN))
	{
		Jogo::audio->Stop(MENU);
		Jogo::NextLevel<GeometryWars>();
	}
}

// ------------------------------------------------------------------------------

void Menu::Draw()
{
	fundo->Draw(window->CenterX(), window->CenterY(), 1.0f);
}

// ------------------------------------------------------------------------------

void Menu::Finalize()
{
	delete fundo;
}

// ------------------------------------------------------------------------------