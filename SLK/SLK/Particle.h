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
	static Point2D * getF(vector<Particle *>*, int); //������ ����������������λ��;
	Point2D * updatePos(Point2D *);

protected:
	int type; //��������
	int mass; //���ӵ�����
	Point2D *pos;
	Point2D *vel;
};