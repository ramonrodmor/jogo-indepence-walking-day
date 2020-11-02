/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:		23 Nov 2011
// Atualização:	14 Mar 2013
// Compilador:	Visual C++ 11
//
// Descrição:	Define uma classe para um míssil/projétil
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
	
	// move para posição
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
	// move míssel com vetor resultante
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
