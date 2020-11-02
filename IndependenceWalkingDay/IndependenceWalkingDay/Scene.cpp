/**********************************************************************************
// Scene (C�digo Fonte)
// 
// Cria��o:		16 Mar 2012
// Atualiza��o:	16 Jul 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Define uma classe para gerenciar o cen�rio do jogo.
//
//				Um gerenciador de cena � respons�vel por guardar os objetos
//				da cena, atualizando-os e desenhando-os de forma mais pr�tica.
//              Ele pode ser usado tamb�m para outras tarefas que impliquem em
//              percorrer a lista de objetos, como detec��o de colis�o.
//
**********************************************************************************/

#include "Scene.h"
#include "Object.h"	

// ---------------------------------------------------------------------------------

Scene::Scene()
{
	processingElements = STATIC;
}

// ---------------------------------------------------------------------------------

Scene::~Scene()
{
	// remove da mem�ria os objetos est�ticos
	for (auto i = staticObjects.begin(); i != staticObjects.end(); ++i)
		delete *i;

	// remove da mem�ria os objetos em movimento
	for (auto i = movingObjects.begin(); i != movingObjects.end(); ++i)
		delete *i;

	// limpa listas
	staticObjects.clear();
	movingObjects.clear();
}

// ---------------------------------------------------------------------------------

void Scene::Add(Object * obj, int type)
{
	// insere novo objeto na cena
	if (type == STATIC)
		staticObjects.push_back(obj);
	else
		movingObjects.push_back(obj);
}


// ---------------------------------------------------------------------------------

void Scene::Remove(Object* obj, int type)
{
	toDelete.push_back(ObjectDel(obj, type));
}

// ---------------------------------------------------------------------------------

void Scene::Remove()
{
	toDelete.push_back(ObjectDel(*it, processingElements));
}

// ---------------------------------------------------------------------------------

void Scene::ProcessDeleted()
{
	// remove objetos repetidos
	toDelete.sort();
	toDelete.unique();

	for (auto i = toDelete.begin(); i != toDelete.end(); ++i)
	{
		// libera mem�ria ocupada pelo objeto
 		delete i->first;

		// remove objeto da cena
		if (i->second == STATIC)
			staticObjects.remove(i->first);
		else
			movingObjects.remove(i->first);

		// remove objeto da lista de objetos registrados para a resolu��o de colis�o
		resolutions.erase(i->first);		
	}

	toDelete.clear();
}

// ---------------------------------------------------------------------------------

void Scene::Update(float gameTime)
{
	// atualiza todos os objetos est�ticos
	processingElements = STATIC;
	for (it = staticObjects.begin(); it != staticObjects.end(); ++it)
		(*it)->Update(gameTime);

	// atualiza todos os objetos em movimento
	processingElements = MOVING;
	for (it = movingObjects.begin(); it != movingObjects.end(); ++it)
		(*it)->Update(gameTime);

	ProcessDeleted();
}

// ---------------------------------------------------------------------------------

void Scene::Draw()
{
	// desenha todos os objetos est�ticos
	processingElements = STATIC;
	for (it = staticObjects.begin(); it != staticObjects.end(); ++it)
		(*it)->Draw();

	// desenha todos os objetos em movimento
	processingElements = MOVING;
	for (it = movingObjects.begin(); it != movingObjects.end(); ++it)
		(*it)->Draw();
}

// ---------------------------------------------------------------------------------

void Scene::Begin()
{
	// aponta para o primeiro elemento de cada lista
	its = staticObjects.begin();
	itm = movingObjects.begin();
	processingElements = STATIC;
}

// ---------------------------------------------------------------------------------

Object * Scene::Next()
{
	// se apontador aponta para objeto v�lido
	if (its != staticObjects.end())
	{
		// passa ao pr�ximo objeto
		// guarda apontador para o anterior
		it = its++;
		return *it;
	}
	else
	if (itm != movingObjects.end())
	{
		processingElements = MOVING;
		it = itm++;
		return *it;
	}
	else
		// chegou ao fim das listas
		return nullptr;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Object * oa, Object * ob)
{
	// um dos objetos n�o tem bounding box
	if (!(oa->bbox && ob->bbox))
		return false;

	switch (oa->bbox->type)
	{
		// Point	
	case POINT_T:

		switch (ob->bbox->type)
		{
		case CIRCLE_T:
			// Point && Circle
			return Collision((Point*)oa->bbox, (Circle*)ob->bbox);

		case RECTANGLE_T:
			// Point && Rectangle
			return Collision((Point*)oa->bbox, (Rect*)ob->bbox);

		case POLYGON_T:
			// Point && Polygon
			return Collision((Point*)oa->bbox, (Poly*)ob->bbox);

		case MULTI_T:
			// Point && Multi
			return Collision(oa->bbox, (Multi*)ob->bbox);

		default:
			// Point && Unknown
			return false;
		}

		// Circle	
	case CIRCLE_T:

		switch (ob->bbox->type)
		{
		case POINT_T:
			// Circle && Point
			return Collision((Circle*)oa->bbox, (Point*)ob->bbox);

		case CIRCLE_T:
			// Circle && Circle
			return Collision((Circle*)oa->bbox, (Circle*)ob->bbox);

		case RECTANGLE_T:
			// Circle && Rectangle
			return Collision((Circle*)oa->bbox, (Rect*)ob->bbox);

		case POLYGON_T:
			// Circle && Polygon
			return Collision((Circle*)oa->bbox, (Poly*)ob->bbox);

		case MULTI_T:
			// Circle && Multi
			return Collision(oa->bbox, (Multi*)ob->bbox);

		default:
			// Circle && Unknown
			return false;
		}

		// Rectangle
	case RECTANGLE_T:

		switch (ob->bbox->type)
		{
		case POINT_T:
			// Rectangle && Point
			return Collision((Rect*)oa->bbox, (Point*)ob->bbox);

		case CIRCLE_T:
			// Rectangle && Circle
			return Collision((Rect*)oa->bbox, (Circle*)ob->bbox);

		case RECTANGLE_T:
			// Rectangle && Rectangle
			return Collision((Rect*)oa->bbox, (Rect*)ob->bbox);

		case POLYGON_T:
			// Rectangle && Polygon
			return Collision((Rect*)oa->bbox, (Poly*)ob->bbox);

		case MULTI_T:
			// Rectangle && Multi
			return Collision(oa->bbox, (Multi*)ob->bbox);

		default:
			// Rectangle && Unknown
			return false;
		}

		// Polygon
	case POLYGON_T:

		switch (ob->bbox->type)
		{
		case POINT_T:
			// Polygon && Point
			return Collision((Poly*)oa->bbox, (Point*)ob->bbox);

		case CIRCLE_T:
			// Polygon && Circle
			return Collision((Poly*)oa->bbox, (Circle*)ob->bbox);

		case RECTANGLE_T:
			// Polygon && Rectangle
			return Collision((Poly*)oa->bbox, (Rect*)ob->bbox);

		case POLYGON_T:
			// Polygon && Polygon
			return Collision((Poly*)oa->bbox, (Poly*)ob->bbox);

		case MULTI_T:
			// Polygon && Multi
			return Collision(oa->bbox, (Multi*)ob->bbox);

		default:
			// Polygon && Unknown
			return false;
		}

		// Multi
	case MULTI_T:
		// Multi && Geometry
		return Collision((Multi*)oa->bbox, ob->bbox);


		// Unknown
	default:
		return false;
	}
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Point * p, Rect * r)
{
	// se as coordenadas  do ponto est�o dentro do ret�ngulo
	if (p->X() >= r->Left() && p->X() <= r->Right())
		if (p->Y() >= r->Top() && p->Y() <= r->Bottom())
			return true;

	// caso contr�rio n�o h� colis�o
	return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Point * p, Circle * c)
{
	// se a dist�ncia entre o ponto e o centro do c�rculo
	// for menor que o raio do c�rculo ent�o h� colis�o
	if (p->Distance(Point(c->X(), c->Y())) <= c->radius)
		return true;
	else
		return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Point * p, Poly * pol)
{
	// se o ponto colidir com a bounding box do pol�gono,
	// passe para uma investiga��o mais profunda e lenta
	// caso contr�rio n�o h� colis�o

	if (Collision(p, pol->BBox()))
	{
		bool crossings = false;
		int nvertex = pol->vertexCount;
		Point * vertex = pol->vertexList;

		float Ix, Iy, Jx, Jy;

		for (int i = 0, j = nvertex - 1; i < nvertex; j = i++)
		{
			// transforma coordenadas locais em globais
			Ix = vertex[i].X() + pol->X();
			Iy = vertex[i].Y() + pol->Y();
			Jx = vertex[j].X() + pol->X();
			Jy = vertex[j].Y() + pol->Y();

			if (((Iy < p->Y()) && (Jy >= p->Y())) || ((Jy < p->Y()) && (Iy >= p->Y())))
				if (Jx - (((Jy - p->Y())*(Jx - Ix)) / (Jy - Iy)) < p->X())
					crossings = !crossings;
		}

		return crossings;
	}

	return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Rect * ra, Rect * rb)
{
	// verificando sobreposi��o no eixo x
	bool overlapX = (rb->Left() <= ra->Right() && ra->Left() <= rb->Right());

	// verificando sobreposi��o no eixo y
	bool overlapY = (rb->Top() <= ra->Bottom() && ra->Top() <= rb->Bottom());

	// existe colis�o se h� sobreposi��o nos dois eixos
	return overlapX && overlapY;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Rect * r, Circle * c)
{
	// encontra o ponto do ret�ngulo mais pr�ximo do centro do c�rculo
	float px, py;

	// eixo x
	if (c->X() < r->Left())
		px = r->Left();
	else
	if (c->X() > r->Right())
		px = r->Right();
	else
		px = c->X();

	// eixo y
	if (c->Y() < r->Top())
		py = r->Top();
	else
	if (c->Y() > r->Bottom())
		py = r->Bottom();
	else
		py = c->Y();

	// verifica se h� colis�o entre este ponto e o c�rculo
	Point point(px, py);
	return Collision(&point, c);
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Rect * r, Poly * pol)
{
	// se o ret�ngulo colidir com a bounding box do pol�gono,
	// passe para uma investiga��o mais profunda e lenta
	// caso contr�rio n�o h� colis�o

	if (Collision(r, pol->BBox()))
	{
		// recupera os cantos do ret�ngulo
		Point corners[4] =
		{
			Point(r->Left(), r->Top()),
			Point(r->Right(), r->Top()),
			Point(r->Right(), r->Bottom()),
			Point(r->Left(), r->Bottom())
		};

		// verifica se algum canto do ret�ngulo est� dentro do pol�gono
		for (int i = 0; i < 4; ++i)
			if (Collision(&corners[i], pol))
				return true;

		// recupera v�rtices do pol�gono
		int nv = pol->vertexCount;
		Point * v = pol->vertexList;

		// verifica se algum v�rtice est� dentro do ret�ngulo
		float pX, pY;
		for (int i = 0; i < nv; ++i)
		{
			// transforma coordenadas locais em globais
			pX = v[i].X() + pol->X();
			pY = v[i].Y() + pol->Y();

			Point p(pX, pY);

			if (Collision(&p, r))
				return true;
		}
	}

	return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Circle * ca, Circle * cb)
{
	// deltas podem ser negativos se a subtra��o � feita na ordem errada
	// levando essa possibilidade em conta � melhor pegar os valores absolutos
	float deltaX = abs(ca->X() - cb->X());
	float deltaY = abs(ca->Y() - cb->Y());

	// calcule a dist�ncia entre os centros dos c�rculos
	float distance = sqrt(deltaX*deltaX + deltaY*deltaY);

	// se a dist�ncia � menor que a soma dos raios
	// existe colis�o entre os c�rculos
	if (distance <= (ca->radius + cb->radius))
		return true;

	// nenhum colis�o detectada
	return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Circle * c, Poly * pol)
{
	// se o c�rculo colidir com a bounding box do pol�gono,
	// passe para uma investiga��o mais profunda e lenta
	// caso contr�rio n�o h� colis�o

	if (Collision(c, pol->BBox()))
	{
		// recupera v�rtices do pol�gono
		int nv = pol->vertexCount;
		Point * v = pol->vertexList;

		// TODO: identificar o ponto do c�rculo mais pr�ximo de cada aresta 
		// e verificar se este ponto est� dentro do pol�gono

		// verifica se v�rtices est�o dentro do c�rculo
		float pX, pY;
		for (int i = 0; i < nv; ++i)
		{
			// transforma coordenadas locais em globais
			pX = v[i].X() + pol->X();
			pY = v[i].Y() + pol->Y();

			Point p(pX, pY);

			if (Collision(&p, c))
				return true;
		}
	}

	return false;

}

// --------------------------------------------------------------------------------

bool Scene::Collision(Poly* pa, Poly* pb)
{
	// se as bounding boxes estiverem colidindo, 
	// passe para uma investiga��o mais profunda e lenta
	// caso contr�rio n�o h� colis�o

	if (Collision(pa->BBox(), pb->BBox()))
	{
		// recupera v�rtices do pol�gono A
		int nva = pa->vertexCount;
		Point * va = pa->vertexList;

		float pX, pY;

		// verifica se v�rtices de A est�o dentro do pol�gono B
		for (int i = 0; i < nva; ++i)
		{
			// transforma coordenadas locais em globais
			pX = va[i].X() + pa->X();
			pY = va[i].Y() + pa->Y();
			
			Point p(pX, pY);

			if (Collision(&p, pb))
				return true;
		}

		// recupera v�rtices do pol�gono B
		int nvb = pb->vertexCount;
		Point * vb = pb->vertexList;

		// verifica se v�rtices de B est�o dentro do pol�gono A
		for (int i = 0; i < nvb; ++i)
		{
			// transforma coordenadas locais em globais
			pX = vb[i].X() + pb->X();
			pY = vb[i].Y() + pb->Y();
			
			Point p(pX, pY);

			if (Collision(&p, pa))
				return true;
		}
	}

	return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Multi* m, Geometry* s)
{
	bool collision = false;

	// percorra lista at� achar uma colis�o
	auto i = m->shapes.begin();

	while (!collision && i != m->shapes.end())
	{
		switch ((*i)->type)
		{
			// Point
		case POINT_T:
			switch (s->type)
			{
			case CIRCLE_T:    collision = Collision((Point*)(*i), (Circle*)s); break;
			case RECTANGLE_T: collision = Collision((Point*)(*i), (Rect*)s);   break;
			case POLYGON_T:   collision = Collision((Point*)(*i), (Poly*)s);   break;
			case MULTI_T:     collision = Collision((Point*)(*i), (Multi*)s);  break;
			}
			break;

			// Circle
		case CIRCLE_T:
			switch (s->type)
			{
			case POINT_T:     collision = Collision((Circle*)(*i), (Point*)s);  break;
			case CIRCLE_T:    collision = Collision((Circle*)(*i), (Circle*)s); break;
			case RECTANGLE_T: collision = Collision((Circle*)(*i), (Rect*)s);	break;
			case POLYGON_T:   collision = Collision((Circle*)(*i), (Poly*)s);   break;
			case MULTI_T:     collision = Collision((Circle*)(*i), (Multi*)s);	break;
			}
			break;

			// Rectangle
		case RECTANGLE_T:
			switch (s->type)
			{
			case POINT_T:     collision = Collision((Rect*)(*i), (Point*)s);  break;
			case CIRCLE_T:    collision = Collision((Rect*)(*i), (Circle*)s); break;
			case RECTANGLE_T: collision = Collision((Rect*)(*i), (Rect*)s);	  break;
			case POLYGON_T:   collision = Collision((Rect*)(*i), (Poly*)s);   break;
			case MULTI_T:     collision = Collision((Rect*)(*i), (Multi*)s);  break;
			}
			break;

			// Polygon
		case POLYGON_T:
			switch (s->type)
			{
			case POINT_T:     collision = Collision((Poly*)(*i), (Point*)s);  break;
			case CIRCLE_T:    collision = Collision((Poly*)(*i), (Circle*)s); break;
			case RECTANGLE_T: collision = Collision((Poly*)(*i), (Rect*)s);	  break;
			case POLYGON_T:   collision = Collision((Poly*)(*i), (Poly*)s);   break;
			case MULTI_T:     collision = Collision((Poly*)(*i), (Multi*)s);  break;
			}
			break;

			// Multi
		case MULTI_T:
			collision = Collision((Multi*)(*i), s);
			break;
		}

		// passa para a pr�xima geometria do multi
		++i;
	}

	return collision;
}

// ---------------------------------------------------------------------------------

void Scene::CollisionDetection()
{
	// iteradores para as listas
	list<Object*>::iterator start, end;

	// limpa lista de colis�es
	collisions.clear();

	// -------------------
	// Detec��o da colis�o
	// -------------------
	// se existe pelo menos dois objetos que se movem, teste a colis�o entre eles
	if (movingObjects.size() >= 2)
	{
		// pega iterador para �ltimo elemento da lista
		end = movingObjects.end();
		end--;

		// testa colis�o entre todos os pares de objetos que se movem
		for (auto i = movingObjects.begin(); i != end; ++i)
		{
			start = i;

			// j inicia no segundo elemento da lista
			for (auto j = ++start; j != movingObjects.end(); ++j)
			{
				if (Collision(*i, *j))
					collisions.push_back(ObjectPair(*i, *j));
			}
		}
	}

	// testa colis�o entre objetos que se movem e objetos est�ticos
	for (auto i = movingObjects.begin(); i != movingObjects.end(); ++i)
	{
		for (auto j = staticObjects.begin(); j != staticObjects.end(); ++j)
		{
			if (Collision(*i, *j))
				collisions.push_back(ObjectPair(*i, *j));
		}
	}

	// --------------------
	// Resolu��o da colis�o
	// --------------------
	if (!collisions.empty())
	{
		for (auto i = collisions.begin(); i != collisions.end(); ++i)
		{
			// se o primeiro elemento se registrou para resolver colis�o
			if (resolutions.count(i->first))
				i->first->OnCollision(i->second);

			// se o segundo elemento se registrou para resolver colis�o
			if (resolutions.count(i->second))
				i->second->OnCollision(i->first);				
		}
	}

	ProcessDeleted();
}

// --------------------------------------------------------------------------------

void Scene::CollisionResolution(Object* obj)
{
	resolutions.insert(obj);
}

// --------------------------------------------------------------------------------



