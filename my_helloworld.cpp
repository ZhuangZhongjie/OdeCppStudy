#include <iostream>
#include "ode/ode.h"
#include "ode/odecpp.h"
#include "drawstuff/drawstuff.h" 

// helper functions
void dump_position(const dReal* pos)
{
	const dReal* p = pos;
	std::cout << "pos: (" << p[0] << ", " << p[1] << ", " << p[2] << ")\n";
}

char get_cin_key()
{
	char key;
	std::cin.get(key);
	return key;
}

// test classes
class ITest
{
public:
	virtual int Run(int argc, char* argv[]) = 0;
};

class FallingForeverTest: public ITest
{
public:
	virtual int Run(int argc, char* argv[])
	{
		dWorld world;
		world.setGravity(0, 0, -1.0);

		dMass m;
		m.setSphereTotal(1.0, 0.2);

		dBody ball(world);
		ball.setMass(m);
		ball.setPosition(0, 0, 1.0);

		while(true) {
			const dReal stepsize = 0.1;
			world.step(stepsize);
			dump_position(ball.getPosition());

			if(get_cin_key() == 'q')
				break;
		}

		return 0;
	}
};


// main function
int main (int argc, char **argv)
{
	ITest * test = NULL;

	// create different test classes here
	test = new FallingForeverTest();

	int ret = test->Run(argc, argv);
	delete test;
	return ret;
}

