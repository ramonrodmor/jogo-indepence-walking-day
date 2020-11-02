/**********************************************************************************
// Geometry (C�digo Fonte)
//
// Cria��o:		05 Oct 2007
// Atualiza��o:	16 Jul 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Agrupa a defini��o de todas as formas geom�tricas suportadas:
//              ponto, linha, ret�ngulo, c�rculo, pol�gono e multi (agrupamento
//              de uma ou mais geometrias)
//
**********************************************************************************/

#include <cmath>
#include "Geometry.h"

// --------------------------------------------------------------------------
// Geometry
// --------------------------------------------------------------------------

Geometry::Geometry()
{ 
	x = y = 0.0f;
	type = UNKNOWN_T; 
}
									
// --------------------------------------------------------------------------
	
Geometry::~Geometry()
{}				


// --------------------------------------------------------------------------
// Point
// --------------------------------------------------------------------------

Point::Point()
{
	type = POINT_T;
}

// --------------------------------------------------------------------------

Point::Point(float posX, float posY)
{
	MoveTo(posX, posY);
	type = POINT_T;
}

// --------------------------------------------------------------------------

Point::Point(int posX, int posY)
{
	MoveTo(float(posX), float(posY)); 
	type = POINT_T;
}

// --------------------------------------------------------------------------

float Point::Distance(Point & p) const
{
	// acha a dist�ncia para um outro ponto

	// os deltas podem resultar em valores negativos 
	// para evitar isso pega-se os valores absolutos
	float deltaX = abs(p.X() - x);
	float deltaY = abs(p.Y() - y);

	// calcula e retorna a dist�ncia
	return sqrt(deltaX*deltaX + deltaY*deltaY);
}

// --------------------------------------------------------------------------
// Line
// --------------------------------------------------------------------------

Line::Line()
{
	// linha padr�o vai de (0,0) at� (0,0)
	a = Point();
	b = Point();
	type = LINE_T;
}

// --------------------------------------------------------------------------

Line::Line(float x1, float y1, float x2, float y2)
{
	// cria linha de (x1,y1) at� (x2,y2)
	a = Point(x1,y1);	
	b = Point(x2,y2);
	type = LINE_T;
}

// --------------------------------------------------------------------------
	
Line::Line(Point& pa, Point& pb)
{
	// cria linha de pa at� pb
	a = pa;
	b = pb;
	type = LINE_T;
}

// --------------------------------------------------------------------------

void Line::Rotate(float angle)
{
	float xr, yr, theta;
	const double PIdiv180 = 0.0174532925194444;

	// converte �ngulo em radianos
	theta = float(angle * PIdiv180);

	// rotaciona cada ponto em rela��o a origem
	xr = a.X() * cos(theta) - a.Y() * sin(theta);
	yr = a.X() * sin(theta) + a.Y() * cos(theta);
	a.MoveTo(xr, yr);

	xr = b.X() * cos(theta) - b.Y() * sin(theta);
	yr = b.X() * sin(theta) + b.Y() * cos(theta);
	b.MoveTo(xr, yr);
}


// --------------------------------------------------------------------------
// Rect  
// --------------------------------------------------------------------------

Rect::Rect()
{
	// cria ret�ngulo de (0,0) at� (0,0)
	left = right  = 0.0f;
	top  = bottom = 0.0f;
	type = RECTANGLE_T;
}

// --------------------------------------------------------------------------

Rect::Rect(float x1, float y1, float x2, float y2)
{
	// cria ret�ngulo de (x1,y1) at� (x2,y2)
	left   = x1;
	top    = y1;
	right  = x2; 
	bottom = y2;
	type   = RECTANGLE_T;
}

// --------------------------------------------------------------------------
Rect::Rect(Point& a, Point& b)
{
	// cria ret�ngulo
	left   = a.X();
	top    = a.Y();
	right  = b.X(); 
	bottom = b.Y();
	type   = RECTANGLE_T;
}

// --------------------------------------------------------------------------
// Circle  
// --------------------------------------------------------------------------

Circle::Circle()
{
	// c�rculo padr�o tem raio nulo
	radius   = 0;
	type     = CIRCLE_T;
}

// --------------------------------------------------------------------------

Circle::Circle(float r)
{
	// define c�rculo de raio r
	x = r;
	y = r;
	radius   = r;
	type     = CIRCLE_T;
}

// --------------------------------------------------------------------------
// Poly 
// --------------------------------------------------------------------------

Poly::Poly()
{
	vertexCount = 0;						// pol�gono n�o tem v�rtices
	vertexList  = nullptr;					// inicialmente a lista de v�rtices � vazia
	bbox = new Circle();					// bounding box padr�o � um c�rculo
	type = POLYGON_T;
}

// --------------------------------------------------------------------------

Poly::Poly(Point * vList, uint vCount)
{
	// guarda n�mero de v�rtices do pol�gono
	vertexCount = vCount;					
	
	// aloca mem�ria para os v�rtices
	vertexList = new Point[vCount];	

	// guarda lista de v�rtices do pol�gono
	for (uint i=0; i < vCount; ++i)		
		vertexList[i].MoveTo(vList[i].X(), vList[i].Y());

	// calcula bounding box deste pol�gono
	BoundingBox();

	type = POLYGON_T;
}

// --------------------------------------------------------------------------

Poly::Poly(const Poly& p)
{
	// guarda n�mero de v�rtices do pol�gono
	vertexCount = p.vertexCount;					
	
	// aloca mem�ria para os v�rtices
	vertexList = new Point[vertexCount];	

	// guarda lista de v�rtices do pol�gono
	for (uint i=0; i < vertexCount; ++i)
		vertexList[i].MoveTo(p.vertexList[i].X(), p.vertexList[i].Y());

	// calcula bounding box deste pol�gono
	BoundingBox();

	type = POLYGON_T;
}

// --------------------------------------------------------------------------

const Poly& Poly::operator=(const Poly& p)
{
	// libera mem�ria alocada por v�rtices antigos, se existirem
	if (vertexList)
		delete [] vertexList;

	// guarda n�mero de v�rtices do pol�gono
	vertexCount = p.vertexCount;					
	
	// aloca mem�ria para os v�rtices
	vertexList = new Point[vertexCount];	

	// guarda lista de v�rtices do pol�gono
	for (uint i=0; i < vertexCount; ++i)
		vertexList[i].MoveTo(p.vertexList[i].X(), p.vertexList[i].Y());

	// calcula bounding box deste pol�gono
	BoundingBox();

	type = POLYGON_T;

	return *this;
}

// --------------------------------------------------------------------------

void Poly::Translate(float dx, float dy)
{
	Geometry::Translate(dx, dy);
	bbox->Translate(dx, dy);
}

// --------------------------------------------------------------------------

void Poly::MoveTo(float px, float py)
{
	Geometry::MoveTo(px, py);
	bbox->MoveTo(px, py);
}

// --------------------------------------------------------------------------

void Poly::Rotate(float angle)
{
	// se o pol�gono tem v�rtices
	if (vertexList)
	{
		float xr, yr, theta;
		const double PIunder180 = 0.0174532925194444;

		// converte �ngulo para radianos
		theta = float(angle * PIunder180);

		// rotacione cada v�rtice do pol�gono
		for (uint i = 0; i < vertexCount; ++i)
		{
			xr = vertexList[i].X() * cos(theta) - vertexList[i].Y() * sin(theta);
			yr = vertexList[i].X() * sin(theta) + vertexList[i].Y() * cos(theta);
			vertexList[i].MoveTo(xr, yr);
		}
	}
}

// --------------------------------------------------------------------------


void Poly::Vertices(const Point * vList, uint vCount)
{
	// libera mem�ria alocada por v�rtices antigos, se existirem
	if (vertexList)
		delete[] vertexList;

	// guarda n�mero de v�rtices do pol�gono
	vertexCount = vCount;
	
	// aloca mem�ria para os v�rtices
	vertexList = new Point[vCount];

	// guarda lista de v�rtices do pol�gono
	for (uint i = 0; i < vCount; ++i)
		vertexList[i].MoveTo(vList[i].X(), vList[i].Y());

	// calcula bounding box deste pol�gono
	BoundingBox();
}

// --------------------------------------------------------------------------

void Poly::BoundingBox()
{
	float curRadius;
	float maxRadius = 0.0f;

	for (uint i = 0; i < vertexCount; ++i)
	{
		// calcula o raio de cada v�rtice do pol�gono
		curRadius = vertexList[i].Distance(Point());
		if (maxRadius < curRadius)
			maxRadius = curRadius;
	}

	// a bounding box � definida pelo maior raio
	if (bbox) delete bbox;
	bbox = new Circle(maxRadius);
	bbox->MoveTo(x, y);
}

// --------------------------------------------------------------------------

Poly::~Poly()
{
	// libera mem�ria alocada para os v�rtices
	if (vertexList)
		delete [] vertexList;

	delete bbox;
}



// --------------------------------------------------------------------------
// Multi 
// --------------------------------------------------------------------------

Multi::Multi()
{
	type = MULTI_T;
}

// --------------------------------------------------------------------------

Multi::~Multi()
{
	// libera da mem�ria as geometrias que comp�em essa forma geom�trica
	for (auto i= shapes.begin(); i != shapes.end(); ++i)
		delete (*i);

	// limpa lista
	shapes.clear();
}

// --------------------------------------------------------------------------

void Multi::Insert(Geometry * s)
{
	shapes.push_back(s);
}

// --------------------------------------------------------------------------

void Multi::Remove(Geometry * s)
{
	auto i = find(shapes.begin(), shapes.end(), s);
	shapes.erase(i);
}

// --------------------------------------------------------------------------

void Multi::Translate(float dx, float dy)
{
	x += dx;
	y += dy;

	for (auto i = shapes.begin(); i != shapes.end(); ++i)
		(*i)->Translate(dx, dy);
}

// --------------------------------------------------------------------------

void Multi::MoveTo(float px, float py)
{
	for (auto i = shapes.begin(); i != shapes.end(); ++i)
	{
		float deltaX = (*i)->X() - x;
		float deltaY = (*i)->Y() - y;
		(*i)->MoveTo(px + deltaX, py + deltaY);
	}

	x = px;
	y = py;
}

// --------------------------------------------------------------------------
