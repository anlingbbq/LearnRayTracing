// 7.DiffuseMaterials.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "PPMRender.h"

static int max_diffuse_count = 0;
static int diffuse_count = 0;

class DiffuseRender : public PPMRender
{
public:
	void init() override
	{
		nx = 200;
		ny = 100;
		ns = 10;
		
		hitable** list = new hitable * [2];
		list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
		list[1] = new sphere(vec3(0, -100.5, -1), 100);
		world = new hitable_list(list, 2);
	}
	
	vec3 random_in_uint_shpere()
	{
		vec3 p;
		do
		{
			vec3 random_vec3 = vec3((float)drand48(), (float)drand48(), (float)drand48());
			p = 2.0f * random_vec3 - vec3(1.0f, 1.0f, 1.0f);
		}
		while (dot(p, p) > 1.0f);
		return p;
	}

	vec3 color(const ray& r, hitable* world)
	{
		hit_record rec;
		if (world->hit(r, 0.0f, FLT_MAX, rec))
		{
			vec3 target = rec.p + rec.normal + random_in_uint_shpere();
			return 0.5f * color(ray(rec.p, target - rec.p), world);
		}
		if (diffuse_count > max_diffuse_count)
			max_diffuse_count = diffuse_count;
		diffuse_count = 0;
		
		return PPMRender::color(r, world);
	}
};

int main()
{
	DiffuseRender dr;
	dr.output("DiffuseRender");

	cout << "max_diffuse_count: " << max_diffuse_count << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
