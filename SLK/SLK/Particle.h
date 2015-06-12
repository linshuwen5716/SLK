#include <vector>
#include "slkheader.h"
#include "Point2D.h"


using namespace::std;

class Particle
{
public:
	Particle();
	Particle(int, int, Point2D *, Point2D *);
	~Particle();
	Point2D * getParticlePos();
	void setParticlePos(Point2D *);
	static Point2D * getF(vector<Particle *>*, int); //粒子组 本粒子在粒子组中位置;
	Point2D * updatePos(Point2D *);

protected:
	int type; //粒子类型
	int mass; //粒子的质量
	Point2D *pos;
	Point2D *vel;
};