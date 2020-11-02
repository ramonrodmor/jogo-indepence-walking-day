/**********************************************************************************
// Blue (Código Fonte)
// 
// Criação:		10 Out 2012
// Atualização:	21 Mar 2013
// Compilador:	Visual C++ 11
//
// Descrição:	Blue faz perseguição suavizada
//
**********************************************************************************/

#include "GeometryWars.h"
#include "Blue.h"
#include "Game.h"
#include <ctime>

// ---------------------------------------------------------------------------------

Blue::Blue(Player * p)
{
	player = p;
	type = 2;

	//definicao de animacao
	tileset = new TileSet("Resources/Blue.png", 1, 2);
	ani = new Animation(tileset, 0.25f, true);

	//animacoes
	uint andando[2] = { 0, 1 };  ani->Add(ANDANDO, andando, 2);

	bbox   = new Circle(18.0f);
	speed  = new Vector(0, 2.0f);
	
	timer.Start();
	srand(int(timer.TimeStamp()));
	MoveTo(float(rand() % int(Game::WorldWidth())), float(rand() % int(Game::WorldHeight())));
}

// ---------------------------------------------------------------------------------

Blue::~Blue()
{
	delete tileset;
	delete ani;
	delete speed;
	delete bbox;
	delete sprite;
}

// -------------------------------------------------------------------------------

void Blue::OnCollision(Object * obj)
{
	if (obj->Type() == MISSIL)
	{
		GeometryWars::scene->Remove(this, MOVING);
		GeometryWars::scene->Remove(obj, STATIC);
		GeometryWars::scene->Add(new Explosion(x, y), STATIC);
		Jogo::pontuacao += 100;
		Jogo::inimigos -= 1;
	}
}

// -------------------------------------------------------------------------------

void Blue::Update(float gameTime)
{
	// atualização é feita a uma taxa de 30 Hz
	if (timer.Elapsed(0.0333f))
	{
		// a magnitude do vetor target controla quão 
		// rápido o objeto converge para a direção do alvo
		Vector target = Vector(speed->Angle(X(), Y(), player->X(), player->Y()), 0.2f);
		speed->Add(target);
	
		// limita a magnitude da velocidade para impedir 
		// seu crescimento indefinido na soma vetorial
		if (speed->magnitude > 2)
			speed->magnitude = 2.0f;

		timer.Reset();
	}

	// move o objeto pelo seu vetor velocidade
	Translate(speed->CompX() * gameTime, speed->CompY() * gameTime);
	ani->NextFrame();
}

// -------------------------------------------------------------------------------