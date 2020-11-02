/**********************************************************************************
// Sprite (Arquivo de Cabeçalho)
// 
// Criação:		11 Jul 2007
// Atualização:	23 Jul 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Define uma classe para representar um sprite
//
**********************************************************************************/

#ifndef _DESENVJOGOS_SPRITE_H_
#define _DESENVJOGOS_SPRITE_H_

// ---------------------------------------------------------------------------------

#include "Image.h"
#include "Types.h"

// ---------------------------------------------------------------------------------

class Sprite
{
private:
	SpriteInfo    spriteInfo;						// informações do sprite 
	bool          localImage;						// imagem local ou externa
	const Image * image;							// ponteiro para imagem

public:
	Sprite(string filename);						// constroi sprite a partir de um arquivo
	Sprite(const Image * img);						// constroi sprite a partir de imagem existente
	
	~Sprite();										// destrutor do sprite

	int Width();									// largura do sprite
	int Height();									// altura do sprite

	void Draw(										// desenha sprite
		float x, float y, float z = 0.5f,			// coordenadas da tela
		float scale = 1.0f, float rotation = 0.0f,  // escala e rotação
		Color & color = Color(1, 1, 1, 1));			// efeito de cor

	void Draw(										// desenha sprite
		float x, float y, float z,					// coordenadas da tela
		float scale, float rotation,				// escala e rotação
		Color & color, RECT & region);				// cor e região
};

// ---------------------------------------------------------------------------------
// Funções Inline

// retorna a largura do sprite
inline int Sprite::Width() 
{ return image->Width(); }

// retorna a altura do sprite
inline int Sprite::Height() 
{ return image->Height(); }

// ---------------------------------------------------------------------------------

#endif