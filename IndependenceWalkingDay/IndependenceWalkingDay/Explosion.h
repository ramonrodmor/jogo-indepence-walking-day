/**********************************************************************************
// Explosion (Arquivo de Cabeçalho)
//
// Criação:		17 Mar 2013
// Atualização:	17 Jul 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Efeito de explosão usando sistema de partículas
//
**********************************************************************************/

#ifndef _PARTICLESDEMO_EXPLOSION_H_
#define _PARTICLESDEMO_EXPLOSION_H_

// ---------------------------------------------------------------------------------

#include "Object.h"	
#include "Particles.h"
#include "Types.h"
#include "GeometryWars.h"

// ---------------------------------------------------------------------------------

class Explosion : public Object
{
private:
	Particles * explosion;				// partículas da explosão

public:
	Explosion(float x, float y);			// inicia fumaça na posição do mouse
	~Explosion();						// destrutor

	int  Size();						// quantidade de partículas
	void Update(float gameTime);		// atualiza estado do objeto
	void Draw();						// desenha objeto
};

// ---------------------------------------------------------------------------------

inline int Explosion::Size()
{
	return explosion->Size();
}

inline void Explosion::Draw()
{
	explosion->Draw(0.7f, 0.0f);
}

// ---------------------------------------------------------------------------------


#endif