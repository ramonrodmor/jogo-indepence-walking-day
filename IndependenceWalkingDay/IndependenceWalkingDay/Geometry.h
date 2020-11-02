/**********************************************************************************
// Geometry (Arquivo de Cabeçalho)
//
// Criação:		05 Oct 2007
// Atualização:	16 Jul 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Agrupa a definição de todas as formas geométricas suportadas:
//              ponto, linha, retângulo, círculo, polígono e multi (agrupamento
//              de uma ou mais geometrias)
//
**********************************************************************************/

#ifndef _DESENVJOGOS_GEOMETRY_H_
#define _DESENVJOGOS_GEOMETRY_H_

// ---------------------------------------------------------------------------
// Inclusões

#include "Types.h"		// tipos da engine
#include <list>			// lista da STL
using std::list;		// usa list sem std::

// ---------------------------------------------------------------------------
// Geometry
// ---------------------------------------------------------------------------

class Geometry
{
protected:
	float x, y;											// posição da geometria

public:
	uint type;											// tipo da geometria
	
	Geometry();											// construtor
	virtual ~Geometry();								// destrutor

	virtual float X() const { return x; }				// coordenada x da geometria
	virtual float Y() const { return y; }				// coordenada y da geometria
		
	virtual void Translate(float dx, float dy)			// move a geometria pelo delta (dx,dy)
	{ x += dx; y += dy; }

	virtual void MoveTo(float px, float py)				// move a geometria para a posição (px,py)
	{ x = px; y = py; }

	virtual void Rotate(float angle) = 0;				// rotaciona uma geometria
};

// --------------------------------------------------------------------------
// Point
// --------------------------------------------------------------------------

class Point : public Geometry
{
public:

	Point();											// construtor padrão
	Point(float posX, float posY);						// construtor usando pontos-flutuantes
	Point(int posX, int posY);							// construtor usando inteiros
	
	void Rotate(float angle) {};						// rociona o ponto pelo ângulo dado
	
	float Distance(Point & p) const;					// calcula a distância até outro ponto
};

// --------------------------------------------------------------------------
// Line
// -------------------------------------------------------------------------

class Line : public Geometry
{
public:
	Point a, b;											// linha vai do ponto A ao ponto B
	
	Line();												// construtor padrão
	Line(float x1, float y1, float x2, float y2);		// construtor usando pontos-flutuantes
	Line(Point& pa, Point& pb);							// construtor usando pontos

	void Rotate(float angle);							// rociona uma linha pelo ângulo dado

	float Ax() const { return x + a.X(); }				// coordenadas do mundo do ponto A eixo x
	float Ay() const { return y + a.Y(); }				// coordenadas do mundo do ponto A eixo y
	float Bx() const { return x + b.X(); }				// coordenadas do mundo do ponto B eixo x
	float By() const { return y + b.Y(); }				// coordenadas do mundo do ponto B eixo y
};

// --------------------------------------------------------------------------
// Rect
// --------------------------------------------------------------------------

class Rect : public Geometry
{
public:
	float left;											// coordenada esquerda do retângulo
	float top;											// coordenada superior do retângulo
	float right;										// coordenada direita do retângulo
	float bottom;										// coordenada inferior do retângulo

	Rect();												// construtor padrão
	Rect(float x1, float y1, float x2, float y2);		// construtor usando pontos-flutuantes
	Rect(Point& a, Point& b);							// construtor usando pontos

	void  Rotate(float angle) {};						// rotaciona o retângulo pelo ângulo dado

	float Left() const   { return x + left; }			// coordenadas do mundo do menor valor do eixo x
	float Top() const    { return y + top; }			// coordenadas do mundo do menor valor do eixo y
	float Right() const  { return x + right; }			// coordenadas do mundo do maior valor do eixo x
	float Bottom() const { return y + bottom; }			// coordenadas do mundo do maior valor do eixo y
};

// --------------------------------------------------------------------------
// Circle
// --------------------------------------------------------------------------

class Circle : public Geometry
{
public:
	float radius;										// raio do círculo

	void  Rotate(float angle) {};						// rotaciona o círculo pelo ângulo dado

	Circle();											// construtor padrão
	Circle(float r);									// contrutor com raio
};

// --------------------------------------------------------------------------
// Poly
// --------------------------------------------------------------------------

class Poly : public Geometry
{
private:
	Circle *  bbox;										// bounding box do polígono
	void      BoundingBox();							// calcula a bounding box do polígono

public:
	uint      vertexCount;								// número de vértices 
	Point*    vertexList;								// vetor de vértices do polígono

	Poly();												// construtor padrão
	Poly(Point * vList, uint vCount);					// construtor
	Poly(const Poly& p);								// construtor de cópia
	~Poly();											// destructor

	// necessário para tratar o ponteiro na atribuição
	const Poly& operator=(const Poly& p);				// operador de atribuição

	void Translate(float dx, float dy);					// move polígono pelo delta (dx,dy)
	void MoveTo(float px, float py);					// move plígono para a posição (px,py)
	void Rotate(float angle);							// rotaciona polígono
	
	void Vertices(const Point * vList, uint vCount);	// muda lista de vértices do polígono
	Circle* BBox() { return bbox; }						// retorna bounding box do polígono
}; 

// --------------------------------------------------------------------------
// Multi
// --------------------------------------------------------------------------

class Multi : public Geometry
{
public:
	list<Geometry*> shapes;								// lista de formas geométricas
	
	Multi();											// construtor padrão
	~Multi();											// destructor

	void Insert(Geometry * s);							// insere geometria na lista
	void Remove(Geometry * s);							// remove geometria da lista

	void Translate(float dx, float dy);					// move a geometria pelo delta (dx,dy)
	void MoveTo(float px, float py);					// move a geometria para a posição (px,py)
};

// --------------------------------------------------------------------------

#endif
