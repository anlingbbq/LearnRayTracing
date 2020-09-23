// 12.WhereNext.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "PPMRender.h"

class CoverRender : public PPMRender
{
	void init() override
	{
		nx = 1280;
		ny = 640;
		ns = 100;
		vec3 lookfrom(13, 2, 3);
		vec3 lookat(0, 0, 0);
		float dist_to_focus = 10.0f;
		float aperture = 0.1f;
		cam = new camera(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
		// random scene
		int n = 500;
		hitable** list = new hitable * [n + 1];
		//产生一个超大球 作为地面
		list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
		int i = 1;
		for (int a = -11; a < 11; a++) {
			for (int b = -11; b < 11; b++) {
				float choose_mat = drand48();
				float choose_y = drand48();

				vec3 center(a + 0.9f * drand48(), 0.4f * choose_y, b + 0.9f * drand48());
				
				if ((center - vec3(4, 0.2f, 0)).length() > 0.9f) {
					if (choose_mat < 0.8) {  // diffuse
						list[i++] = new sphere(center, 0.2f, new lambertian(vec3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
					}
					else if (choose_mat < 0.95f) { // metal
						list[i++] = new sphere(center, 0.2f,
							new metal(vec3(0.5f * (1 + drand48()), 0.5f * (1 + drand48()), 0.5f * (1 + drand48())), 0.5f * drand48()));
					}
					else {  // glass
						list[i++] = new sphere(center, 0.2f, new dielectric(1.5f));
					}
				}
			}
		}

		list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
		list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4f, 0.2f, 0.1f)));
		list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7f, 0.6f, 0.5f), 0.0));

		world = new hitable_list(list, i);
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
	CoverRender cr;
	cr.output("CoverRender");
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
