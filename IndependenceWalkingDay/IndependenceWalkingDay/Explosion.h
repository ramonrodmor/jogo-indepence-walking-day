/**********************************************************************************
// Explosion (Arquivo de Cabe�alho)
//
// Cria��o:		17 Mar 2013
// Atualiza��o:	17 Jul 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Efeito de explos�o usando sistema de part�culas
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
	Particles * explosion;				// part�culas da explos�o

public:
	Explosion(float x, float y);			// inicia fuma�a na posi��o do mouse
	~Explosion();						// destrutor

	int  Size();						// quantidade de part�culas
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