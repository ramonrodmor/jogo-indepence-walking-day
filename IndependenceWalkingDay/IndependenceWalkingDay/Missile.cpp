/**********************************************************************************
// Missile (C�digo Fonte)
// 
// Cria��o:		23 Nov 2011
// Atualiza��o:	14 Mar 2013
// Compilador:	Visual C++ 11
//
// Descri��o:	Define uma classe para um m�ssil/proj�til
//
**********************************************************************************/

#include "Missile.h"
#include "GeometryWars.h"
#include "Game.h"
#include "Jogo.h"

// ------------------------------------------------------------------------------

Missile::Missile(Player * player)
{
	type = 1;

	// inicializa sprite
	sprite = new Sprite("Resources/missil.png");

	// cria bounding box
	bbox = new Point();
	type = 1;

	// inicializa velocidade
	speed.angle = player->speed->angle;
	speed.magnitude = 10.0f;
	
	// move para posi��o
	MoveTo(player->X(), player->Y());
}

// ------------------------------------------------------------------------------

Missile::~Missile()
{
	delete sprite;
	delete bbox;
}

// -------------------------------------------------------------------------------

void Missile::OnCollision(Object * obj)
{
}

// -------------------------------------------------------------------------------

void Missile::Update(float gameTime)
{
	// move m�ssel com vetor resultante
	Translate(speed.CompX() * gameTime, -speed.CompY() * gameTime);
	
	if (X() > Game::WorldWidth() || X() < 0 || Y() > Game::WorldHeight() || Y() < 0)
	{
		GeometryWars::scene->Remove();
	}
}

// -------------------------------------------------------------------------------

void Missile::Draw()
{
	sprite->Draw(X(), Y(), 0.2f);
}

// -------------------------------------------------------------------------------
