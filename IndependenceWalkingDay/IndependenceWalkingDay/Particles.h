/**********************************************************************************
// Particles (Arquivo de Cabe�alho)
// 
// Cria��o:		07 Out 2012
// Atualiza��o:	17 Jul 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Define um sistema de part�culas
//
**********************************************************************************/

#ifndef _DESENVJOGOS_PARTICLES_H_
#define _DESENVJOGOS_PARTICLES_H_

// ---------------------------------------------------------------------------------

#include "Sprite.h"									// sprite formador da part�cula
#include "Timer.h"									// controla tempo para gera��o de part�culas
#include "Types.h"									// tipos espec�ficos da engine
#include "Vector.h"									// as particulas tem uma dire��o
#include <vector>									// usando vetores da biblioteca STL	
using std::vector;

// ---------------------------------------------------------------------------------

struct ParticleDesc 
{
	string imgFile;									// nome do arquivo de imagem da part�cula
	int    baseAngle;								// dire��o do emissor de part�culas
	int    spread;									// �ngulo de espalhamento das part�culas
	float  lifeTime;								// tempo de vida das part�culas
	float  genTime;									// tempo entre gera��o de part�culas
	float  minSpeed;								// velocidade m�nima das part�culas
	float  maxSpeed;								// velocidade m�xima das part�culas
	float  r, g, b, a;								// cor das part�culas
};

struct Particle
{
	float  x, y;									// posi��o da part�cula
	Vector speed;									// dire��o e velocidade
	llong  timeStamp;								// instante de cria��o
};

// ---------------------------------------------------------------------------------

class Particles
{
private:
	Timer    timer;									// controle de tempo
	Sprite * sprite;								// sprite da part�cula
	int      baseAngle;								// dire��o do emissor de part�culas
	int      spread;								// �ngulo de espalhamento das part�culas
	float    lifeTime;								// tempo de vida
	float    genTime;								// tempo entre gera��o de part�culas
	float    minSpeed;								// velocidade m�nima das part�culas
	float    maxSpeed;								// velocidade m�xima das part�culas
	float    r, g, b, a;							// cor RGBA da part�cula
	vector<Particle*> particles;					// vetor de part�culas
	
	void GenParticle(float posX, float posY);		// gera part�cula

public:
	Particles(const ParticleDesc& desc);			// construtor
	~Particles();									// destrutor

	int  Size();									// n�mero de part�culas
	bool Inactive();								// part�culas est�o inativas?
	void Generate(float x, float y, int num = 1);	// gera novas part�culas
	void Update(float deltaT);						// atualiza posi��o das part�culas por deltaT
	void Draw(float z, float scaleFactor = 0.0f);	// desenha part�culas		
}; 

// ---------------------------------------------------------------------------------

inline int Particles::Size()
{ return particles.size(); }

inline bool Particles::Inactive()
{ return (particles.size() == 0); }

// ---------------------------------------------------------------------------------

#endif