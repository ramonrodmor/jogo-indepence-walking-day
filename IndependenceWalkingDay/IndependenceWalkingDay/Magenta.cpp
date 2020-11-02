/**********************************************************************************
// Magenta (Código Fonte)
// 
// Criação:		10 Out 2012
// Atualização:	21 Mar 2013
// Compilador:	Visual C++ 11
//
// Descrição:	Magenta faz perseguição direta
//
**********************************************************************************/

#include "GeometryWars.h"
#include "Game.h"
#include "Magenta.h"
#include <ctime>

// ---------------------------------------------------------------------------------

Magenta::Magenta(Player * p)
{
	player = p;
	type = 2;

	//definicao de animacao
	tileset = new TileSet("Resources/Magenta.png", 1, 2);
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

Magenta::~Magenta()
{
	delete tileset;
	delete ani;
	delete speed;
	delete bbox;
}

// -------------------------------------------------------------------------------

void Magenta::OnCollision(Object * obj)
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

void Magenta::Update(float gameTime)
{
	// ajusta ângulo do vetor 
	speed->angle = speed->Angle(X(), Y(), player->X(), player->Y());

	// movimenta objeto pelo seu vetor velocidade
	Translate(speed->CompX() * gameTime, speed->CompY() * gameTime);
	ani->NextFrame();
}

// -------------------------------------------------------------------------------