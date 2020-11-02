/**********************************************************************************
// Green (Código Fonte)
// 
// Criação:		15 Out 2012
// Atualização:	26 Mar 2013
// Compilador:	Visual C++ 11
//
// Descrição:	Green faz a fuga suavizada
//
**********************************************************************************/

#include "Green.h"
#include "Game.h"
#include "GeometryWars.h"
#include <ctime>

// ---------------------------------------------------------------------------------

Green::Green(Player * p)
{
	player = p;
	type = 2;

	//definicao de animacao
	tileset = new TileSet("Resources/Green.png", 1, 2);
	ani = new Animation(tileset, 0.25f, true);

	//animacoes
	uint andando[2] = { 0, 1 };  ani->Add(ANDANDO, andando, 2);

	bbox   = new Circle(18.0f);
	speed  = new Vector(0, 0.0f);

	timer.Start();
	srand(int(timer.TimeStamp()));
	MoveTo(float(rand() % int(Game::WorldWidth())), float(rand() % int(Game::WorldHeight())));	
}

// ---------------------------------------------------------------------------------

Green::~Green()
{
	delete tileset;
	delete ani;
	delete speed;
	delete bbox;
}

// -------------------------------------------------------------------------------

void Green::OnCollision(Object * obj)
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

void Green::Update(float gameTime)
{
	// atualização é feita a uma taxa de 30 Hz
	if (timer.Elapsed(0.0333f))
	{
		// a magnitude do vetor target controla quão 
		// rápido o objeto converge para a direção do alvo
		Vector target = Vector(speed->Angle(X(), Y(), player->X(), player->Y()), 0.8f);
		
		if (speed->Distance(X(), Y(), player->X(), player->Y()) < 200)
			target.Rotate(180.0f);
		speed->Add(target);
	
		// limita a magnitude da velocidade para impedir 
		// seu crescimento indefinido na soma vetorial
		if (speed->magnitude > 3)
			speed->magnitude = 5.0f;

		timer.Reset();
	}

	// move o objeto pelo seu vetor velocidade
	Translate(speed->CompX() * gameTime, speed->CompY() * gameTime);
	ani->NextFrame();

	// mantém o objeto dentro do mundo
	if (X() < 0)
		MoveTo(0, Y());
	if (Y() < 0)
		MoveTo(X(), 0);
	if (X() > Game::WorldWidth())
		MoveTo(Game::WorldWidth(), Y());
	if (Y() > Game::WorldHeight())
		MoveTo(X(), Game::WorldHeight());
}

// -------------------------------------------------------------------------------