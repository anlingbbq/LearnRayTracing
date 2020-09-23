// 5.SurfaceNormalsAndMultipleObjects.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "float.h"
#include "PPMRender.h"

class NormalRender : public PPMRender
{
public:
	float hit_sphere(const vec3& center, float radius, const ray& r)
	{
		vec3 oc = r.origin() - center;
		float a = dot(r.direction(), r.direction());
		float b = 2.0f * dot(oc, r.direction());
		float c = dot(oc, oc) - radius * radius;
		float discriminant = b * b - 4 * a * c;

		if (discriminant < 0)
		{
			return -1.0f;
		}
		return (-b - sqrt(discriminant)) / (2.0f * a);
	}

	vec3 color(const ray& r, hitable* world = nullptr, int depth = 0) override
	{
		float t = hit_sphere(vec3(0, 0, -1), 0.5f, r);
		if (t > 0)
		{
			vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
			return 0.5f * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
		}
		return PPMRender::color(r);
	}
};

class NormalListRender : public PPMRender
{
public:
	void init() override
	{
		hitable** list = new hitable * [2];
		list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
		list[1] = new sphere(vec3(0, -100.5, -1), 100);
		world = new hitable_list(list, 2);
	}

	vec3 color(const ray& r, hitable* world)
	{
		hit_record rec;
		if (world->hit(r, 0, FLT_MAX, rec))
		{
			return 0.5f * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
		}
		return PPMRender::color(r);
	}
};

int main()
{
	NormalRender nr;
	nr.output("NormalRender");

	NormalListRender nlr;
	nlr.output("NormalListRender");
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
