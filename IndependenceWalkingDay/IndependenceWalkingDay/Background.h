/**********************************************************************************
// Background (Arquivo de Cabeçalho)
// 
// Criação:		07 Dez 2011
// Atualização:	30 Jul 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Define uma classe para construir backgrounds
//
**********************************************************************************/

#ifndef _DESENVJOGOS_BACKGROUND_H_
#define _DESENVJOGOS_BACKGROUND_H_

// -------------------------------------------------------------------------------

#include "Types.h"          // tipos específicos da engine
#include "Image.h"			// imagem do background
#include <string>			// string de C++
using std::string;			// usando strings

// -------------------------------------------------------------------------------

class Background
{
private:
	SpriteInfo spriteInfo;				// informações do sprite 
	const Image * image;				// imagem da superfície

public:
	Background(string filename);		// construtor	
	~Background();						// destrutor

	void Draw(ViewPort & sourceRect);	// desenha uma porção da imagem na tela
	uint Width();						// retorna a largura do background
    uint Height();						// retorna a altura do background
}; 

// ---------------------------------------------------------------------------------
// Funções Inline

// retorna a largura do sprite
inline uint Background::Width() 
{ return image->Width(); }

// retorna a altura do sprite
inline uint Background::Height() 
{ return image->Height(); }

// -------------------------------------------------------------------------------


#endif