/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:		10 Out 2012
// Atualização:	21 Mar 2013
// Compilador:	Visual C++ 11
//
// Descrição:	Define a classe jogador
//
**********************************************************************************/

#include "Player.h" 
#include "Missile.h"
#include "Game.h"
#include "GeometryWars.h"
#include "Animation.h"
#include "Jogo.h"
#include "Explosion.h"

// -------------------------------------------------------------------------------

Player::Player()
{
	// cria e inicializa joystick
	joy = new Joystick();
	joystickOn = joy->Initialize();


	//definicao de animacao
	tileset = new TileSet("Resources/movplayer1.png", 1, 3);
	ani = new Animation(tileset, 0.150f, true);


	//animacoes
	uint parado[1] = { 2 };  ani->Add(PARADO, parado, 1);
	uint andando[2] = { 0, 1 };  ani->Add(ANDANDO, andando, 2);
	
	//sprite = new Sprite("Resources/player1.png");
	speed  = new Vector(90.0f, 0.4);
	bbox   = new Rect(-5,5,-5,5);//mudar


	//estado
	estado = estadoAnterior = PARADO;
	
	MoveTo(Game::WorldCenterX(), Game::WorldCenterY());
	timer.Start();

	type = 0;
}

// -------------------------------------------------------------------------------

Player::~Player()
{
	delete tileset;
	delete ani;
	delete speed;
	delete bbox;
	delete joy;
}

// -------------------------------------------------------------------------------

void Player::Move(Vector & v)
{
	if (timer.Elapsed(0.0333f))
	{
		// suaviza curva ao acelerar a partir do repouso
		if (v.magnitude > 0.4 && speed->magnitude < 1)
			speed->magnitude = 1.0f;

		speed->Add(v);

		// limita velocidade máxima
		if (speed->magnitude > 5.0f)
			speed->magnitude = 5.0f;

		timer.Reset();
	}
}

// -------------------------------------------------------------------------------

void Player::Update(float gameTime)
{
	// modifica vetor velocidade do player
	if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_UP))
	{
		Move(Vector(45.0f, 0.5f));
		estado = ANDANDO;
	}
	else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_UP))
	{
		Move(Vector(135.0f, 0.5f));
		estado = ANDANDO;
	}
	else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_DOWN))
	{
		Move(Vector(225.0f, 0.5f));
		estado = ANDANDO;
	}
	else if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_DOWN))
	{
		Move(Vector(315.0f, 0.5f));
		estado = ANDANDO;
	}
	else if (window->KeyDown(VK_RIGHT))
	{
		Move(Vector(0.0f, 0.5f));
		estado = ANDANDO;
	}
	else if (window->KeyDown(VK_LEFT))
	{
		Move(Vector(180.0f, 0.5f));
		estado = ANDANDO;
	}
	else if (window->KeyDown(VK_UP))
	{
		Move(Vector(90.0f, 0.5f));
		estado = ANDANDO;
	}
	else if (window->KeyDown(VK_DOWN))
	{
		Move(Vector(270.0f, 0.5f));
		estado = ANDANDO;
	}
	else if (speed->magnitude > 0.1f)
	{
		Move(Vector(speed->angle + 180.0f, 0.1f));
		estado = ANDANDO;
	}
	else
	{
		speed->magnitude = 0.0f;
		estado = PARADO;
	}

	if (window->KeyCtrl(VK_SPACE))
	{
		GeometryWars::scene->Add(new Missile(this), STATIC);
		Jogo::audio->Play(TIRO);
	}
	
	// --------------------------
	// Joystick
	// --------------------------
	if (joystickOn)
	{
		// seleciona próximo joystick (Page Down)
		if (window->KeyCtrl(VK_NEXT))
			joy->SelectNext();

		// seleciona joystick anterior (Page Up)
		if (window->KeyCtrl(VK_PRIOR))
			joy->SelectPrev();

		joy->GetState();
		float x = joy->Axis(JoyAxisX) / 250 * gameTime;
		float y = joy->Axis(JoyAxisY) / 250 * gameTime;
		Translate(x,y);
		if (x != 0 || y != 0) estado = ANDANDO;
		else estado = PARADO;

		Vector * mira = new Vector;
		float rx = joy->Axis(JoyAxisZ) / 250 * gameTime;
		float ry = -joy->Axis(JoyAxisRZ) / 250 * gameTime;
		mira->angle = mira->Angle(0.0f, 0.0f, rx, ry);
		if (rx != 0 || ry != 0) Move(Vector(mira->angle, 0));

		if (joy->ButtonCtrl(5))
		{
			GeometryWars::scene->Add(new Missile(this), STATIC);
			Jogo::audio->Play(TIRO);
		}		
	}
	// movimenta objeto pelo seu vetor velocidade
	Translate(speed->CompX() * gameTime, -speed->CompY() * gameTime);

	// mantém player dentro do mundo
	if (X() < 0)
		MoveTo(0, Y());
	if (Y() < 0)
		MoveTo(X(), 0);
	if (X() > Game::WorldWidth())
		MoveTo(Game::WorldWidth(), Y());
	if (Y() > Game::WorldHeight())
		MoveTo(X(), Game::WorldHeight());

	ani->Select(estado);
	ani->NextFrame();

	if (joy->ButtonCtrl(8))
	{
		Jogo::inimigos--;
	}
}

// -------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
	if (obj->Type() == 2)
	{
		GeometryWars::scene->Add(new Explosion(x, y), STATIC);
		GeometryWars::jogador = 0;
	}
}

// -------------------------------------------------------------------------------
