/**********************************************************************************
// Object (Código Fonte)
//
// Criação:		01 Out 2007
// Atualização:	14 Mai 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Essa é a classe base para todos objetos do jogo.
//
//				Um objeto do jogo é qualquer coisa que possámos querer desenhar
//				ou interagir dentro do jogo. Por exemplo, um soldado, um prédio,
//				um projétil, uma forma geométrica, etc.
//
**********************************************************************************/

#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe

Window * Object::window = nullptr;		// referência para a janela do jogo

// -------------------------------------------------------------------------------

Object::Object()
{
	// posição do objeto
	x = y = 0.0f;

	// profundidade do objeto
	z = 0.5f;

	//tipo do objeto
	type = 0;

	if (!window)
		window = Engine::window;
}

// -------------------------------------------------------------------------------

Object::~Object()
{
}

// -------------------------------------------------------------------------------

void Object::Translate(float dx, float dy, float dz)
{
	x += dx; 
	y += dy; 
	z += dz;

	if (bbox)
		bbox->Translate(dx, dy);
}

// -------------------------------------------------------------------------------

void Object::MoveTo(float px, float py, float pz)
{
	x = px; 
	y = py; 
	z = pz;

	if (bbox)
		bbox->MoveTo(px, py);
}

// -------------------------------------------------------------------------------

void Object::MoveTo(float px, float py)
{
	x = px; 
	y = py;

	if (bbox)
		bbox->MoveTo(px, py);
}

// -------------------------------------------------------------------------------

void Object::OnCollision(Object * obj)
{
}

// -------------------------------------------------------------------------------