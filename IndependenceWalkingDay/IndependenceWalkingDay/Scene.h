/**********************************************************************************
// Scene (Arquivo de Cabeçalho)
// 
// Criação:		16 Mar 2012
// Atualização:	16 Jul 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Define uma classe para gerenciar o cenário do jogo.
//				
//				Um gerenciador de cena é responsável por guardar os objetos 
//				da cena, atualizando-os e desenhando-os de forma mais prática. 
//              Ele pode ser usado também para outras tarefas que impliquem em
//              percorrer a lista de objetos, como detecção de colisão.
//
**********************************************************************************/

#ifndef _DESENVJOGOS_SCENE_H_
#define _DESENVJOGOS_SCENE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Geometry.h"							// bounding boxes dos objetos
#include <list>									// lista da biblioteca STL 
#include <unordered_set>						// tabela de dispersão
using std::list;								// acessa list sem precisar do std::
using std::pair;								// acessa pair sem precisar do std:
using std::unordered_set;						// acesssa unorndered_map sem std::
class Object;									// declaração avançada

// ---------------------------------------------------------------------------------

typedef pair<Object*, Object*>  ObjectPair;
typedef pair<Object*, int>      ObjectDel;

// ---------------------------------------------------------------------------------

class Scene
{
private:
	list<Object*>          staticObjects;		// lista de objetos estáticos (não colidem entre si)
	list<Object*>          movingObjects;		// lista de objetos em movimento (podem colidir entre si e com os estáticos)
	list<ObjectPair>       collisions;			// lista de pares de objetos em colisão
	list<ObjectDel>        toDelete;			// lista de objetos a deletar da cena
	unordered_set<Object*> resolutions;			// objetos registrados para a resolução de colisão

	list<Object*>::iterator its;				// iterador para elemento estático
	list<Object*>::iterator itm;				// iterador para elemento em movimento
	list<Object*>::iterator it;					// iterador para elemento atual

	int processingElements;						// indica qual lista está sendo processada

	bool Collision(Object* oa, Object* ob);		// verifica se há colisão entre dois objetos

	bool Collision(Point* p, Rect* r);			// colisão entre ponto e retângulo	
	bool Collision(Point* p, Circle* c);		// colisão entre ponto e círculo
	bool Collision(Point* p, Poly* pol);		// colisão entre ponto e polígono

	bool Collision(Rect* ra, Rect* rb);			// colisão entre retângulos
	bool Collision(Rect* r, Point* p);			// colisão entre retângulo e ponto (inline)
	bool Collision(Rect* r, Circle* c);			// colisão entre retângulo e círculo
	bool Collision(Rect* r, Poly* pol);			// colisão entre retângulo e polígono

	bool Collision(Circle* ca, Circle* cb);		// colisão entre círculos
	bool Collision(Circle* c, Point* p);		// colisão entre círculo e ponto (inline)
	bool Collision(Circle* c, Rect* r);			// colisão entre círculo e retângulo (inline)
	bool Collision(Circle* c, Poly* pol);		// colisão entre círculo e polígono

	bool Collision(Poly* pa, Poly* pb);			// colisão entre polígonos
	bool Collision(Poly* pol, Point* p);		// colisão entre polígono e ponto (inline)
	bool Collision(Poly* pol, Rect* r);			// colisão entre polígono e retângulo (inline)
	bool Collision(Poly* pol, Circle* c);		// colisão entre polígono e círculo (inline)

	bool Collision(Multi* m, Geometry* s);		// colisão entre multi e uma forma qualquer
	bool Collision(Geometry* s, Multi* m);		// colisão entre uma forma qualquer e multi (inline)
	
public:
	Scene();									// construtor
	~Scene();									// destrutor da cena

	void Add(Object* obj, int type);			// adiciona objeto na cena (tipo STATIC ou MOVING)
	void Remove(Object* obj, int type);			// adiciona objeto a lista de elementos a remover
	void Remove();								// remove objeto sendo processado na cena
	void ProcessDeleted();						// apaga elementos marcados para exclusão
	uint Size();								// retorna quantidade de objetos na cena

	void Begin();								// inicia percurso na lista de objetos
	Object * Next();							// retorna próximo objeto da lista

	void Update(float gameTime);				// atualiza todos os objetos da cena
	void Draw();								// desenha todos os objetos da cena

	void CollisionDetection();					// trata a colisão entre objetos da cena
	void CollisionResolution(Object* obj);		// registra função para tratar colisão de objeto	
};

// --------------------------------------------------------------------------------
// Funções Membro Inline

// retorna quantidade de objetos na cena
inline uint Scene::Size()
{ return staticObjects.size() + movingObjects.size(); }

// colisão entre retângulo e ponto
inline bool Scene::Collision(Rect* r, Point* p)
{ return Collision(p, r); }

// colisão entre círculo e ponto
inline bool Scene::Collision(Circle* c, Point* p)
{ return Collision(p, c); }

// colisão entre círculo e retângulo
inline bool Scene::Collision(Circle* c, Rect* r)
{ return Collision(r, c); }

// colisão entre polígono e ponto
inline bool Scene::Collision(Poly* pol, Point* p)
{ return Collision(p, pol); }

// colisão entre polígono e retângulo
inline bool Scene::Collision(Poly* pol, Rect* r)
{ return Collision(r, pol); }

// colisão entre polígono e círculo
inline bool Scene::Collision(Poly* pol, Circle* c)
{ return Collision(c, pol); }

// colisão entre multi e uma forma qualquer
inline bool Scene::Collision(Geometry* s, Multi* m)
{ return Collision(m, s); }

// ---------------------------------------------------------------------------------

#endif