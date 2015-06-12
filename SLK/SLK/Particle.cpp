#include "stdafx.h"
#include "Particle.h"

Particle::Particle()
{
	type = 0; 
	mass = 0;

	pos = new Point2D(0.0f, 0.0f);
	vel = new Point2D(0.0f, 0.0f);
}

Particle::Particle(int t, int m, Point2D *p, Point2D *v)
{
	type = t;
	mass = m;
	pos = p;
	vel = v;
}

Particle::~Particle()
{
	delete pos;
}

Point2D* Particle::getParticlePos()
{
	return pos;
}

void Particle::setParticlePos(Point2D *p)
{
	pos = p;
}

Point2D * Particle::getF(vector<Particle *>* ps, int idx)
{
	Point2D *vecF = new Point2D(); //return vector F

	double fx = 0.0f;
	double fy = 0.0f;
	Particle *tp = ps->at(idx);
	Point2D *tpp = tp->getParticlePos();
	float tppx = tpp->x;
	float tppy = tpp->y;

	int size = ps->size();
	for (int i = 0; i < size; ++i) {
		if (i == idx) continue;

		Particle *p = ps->at(i);
		Point2D *pp = p->getParticlePos();
		float ppx = pp->x;
		float ppy = pp->y;
		float dx = ppx - tppx;
		float dy = ppy - tppy;

		double l = sqrt((ppx - tppx)*(ppx - tppx) + (ppy - tppy)*(ppy - tppy));

		fx += tp->mass * p->mass * dx / (l * l);
		fy += tp->mass * p->mass * dy / (l * l);

		if (l < PARTICLE_F2_LENGTH_VAL) {
			fx -= PARTICLE_F2_FACTOR * tp->mass * p->mass * dx / (l * l);
			fy -= PARTICLE_F2_FACTOR * tp->mass * p->mass * dy / (l * l);
		}
	}

	vecF->x = (float)fx;
	vecF->y = (float)fy;

	return vecF;
}

Point2D * Particle::updatePos(Point2D *vecF) {
	vel->x += vecF->x;
	vel->y += vecF->y;

	this->pos->x += vel->x;
	this->pos->y += vel->y;

	return pos;
}