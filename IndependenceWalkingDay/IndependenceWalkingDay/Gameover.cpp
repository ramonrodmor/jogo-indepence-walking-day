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
#include "Gameover.h"
#include "GeometryWars.h"

// ------------------------------------------------------------------------------

void Gameover::Init()
{
	// cria fontes para exibição de texto
	font = new Font("Resources/Tahoma10.png");
	font->Spacing("Resources/Tahoma10.dat");

	// joystick
	joy = new Joystick();
	joystickOn = joy->Initialize();

	// pano de fundo
	fundo = new Sprite("Resources/Gameover.jpg");
	keyMap = new Sprite("Resources/Keymap.png");

	// toca musica do menu
	Jogo::audio->Volume(GAMEOVER, 5.0f);
	Jogo::audio->Play(GAMEOVER, TRUE);
}

// ------------------------------------------------------------------------------

void Gameover::Update(float gameTime)
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
			Jogo::audio->Stop(GAMEOVER);
			Jogo::NextLevel<Menu>();
		}
	}
}

// ------------------------------------------------------------------------------

void Gameover::Draw()
{
	fundo->Draw(window->CenterX(), window->CenterY(), 1.0f);
	keyMap->Draw(viewport.left + window->CenterX(), viewport.top + window->Height() - 16.0f);
	text.str("");
	text << "Pontuação: " << Jogo::pontuacao;
	font->Draw(window->CenterX() - 30.0f, window->Height() - 17.0f, text.str());
}

// ------------------------------------------------------------------------------

void Gameover::Finalize()
{
	delete fundo;
}

// ------------------------------------------------------------------------------