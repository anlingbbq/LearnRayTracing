// 9.Dielectrics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "PPMRender.h"

class DielectricsRender : public PPMRender
{
	void init() override
	{
		ns = 100;
		hitable** list = new hitable * [5];
		list[0] = new sphere(vec3(0, 0, -1.0f), 0.5f, new lambertian(vec3(0.8f, 0.3f, 0.3f)));
		list[1] = new sphere(vec3(0, -100.5f, -1.0f), 100, new lambertian(vec3(0.8f, 0.8f, 0)));
		list[2] = new sphere(vec3(1.0f, 0, -1.0f), 0.5f, new metal(vec3(0.8f, 0.6f, 0.2f)));
		list[3] = new sphere(vec3(-1.0f, 0, -1.0f), 0.5f, new dielectric(1.5f));
		list[4] = new sphere(vec3(-1.0f, 0, -1.0f), -0.45f, new dielectric(1.5f));
		world = new hitable_list(list, 5);
	}

	vec3 color(const ray& r, hitable* world, int depth) override
	{
		hit_record rec;
		if (world->hit(r, 0.001f, FLT_MAX, rec))
		{
			ray scattered;
			vec3 attenuation;
			if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			{
				return attenuation * color(scattered, world, depth + 1);
			}
			return vec3(0, 0, 0);
		}
		return PPMRender::color(r, world, depth);
	}
};

int main()
{
	DielectricsRender dr;
	dr.output("DielectricsRender ");
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
