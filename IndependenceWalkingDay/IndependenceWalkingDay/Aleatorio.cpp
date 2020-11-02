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
#include "Aleatorio.h"
#include "Game.h"
#include <ctime>

// ---------------------------------------------------------------------------------

Aleatorio::Aleatorio(Player * p)
{
	player = p;
	type = 2;

	//definicao de animacao
	tileset = new TileSet("Resources/gordo.png", 1, 2);
	ani = new Animation(tileset, 0.25f, true);

	//animacoes
	uint andando[2] = { 0, 1 };  ani->Add(ANDANDO, andando, 2);

	bbox = new Circle(18.0f);
	speed = new Vector(0, 2.0f);

	timer.Start();
	srand(int(timer.TimeStamp()));
	MoveTo(float(rand() % int(Game::WorldWidth())), float(rand() % int(Game::WorldHeight())));

	Direction();
}

// ---------------------------------------------------------------------------------

void Aleatorio::Direction()
{
	speed->magnitude = 3.0f - float(rand() % 2);
	speed->angle = float(rand() % 360);
	delay = 0.1f + (0.04f * (rand() % 11));
	timer.Start();
}

// ---------------------------------------------------------------------------------

Aleatorio::~Aleatorio()
{
	delete tileset;
	delete ani;
	delete speed;
	delete bbox;
	delete sprite;
}

// -------------------------------------------------------------------------------

void Aleatorio::OnCollision(Object * obj)
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

void Aleatorio::Update(float gameTime)
{
	float deltaT = 2 * gameTime;

	// muda direção da mosca após transcorrer certo tempo 
	if (timer.Elapsed(delay))
		Direction();

	// movimenta mosca pelo seu vetor velocidade
	Translate(speed->CompX() * deltaT, -speed->CompY() * deltaT);

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