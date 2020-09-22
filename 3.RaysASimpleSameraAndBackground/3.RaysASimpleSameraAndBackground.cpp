// 3.RaysASimpleSameraAndBackground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include "vec3.h"
#include "ray.h"

vec3 color(const ray& r)
{
	vec3 uint_direciton = unit_vector(r.direction());
	float t = 0.5f * (uint_direciton.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}


int main()
{
	using namespace std;

	streambuf* coutBuf = cout.rdbuf();

	ofstream of("out.ppm");
	streambuf* fileBuf = of.rdbuf();
	cout.rdbuf(fileBuf);

	int nx = 200;
	int ny = 100;
	cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; ++i)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);
			int ir = int(255.9 * col[0]);
			int ig = int(255.9 * col[1]);
			int ib = int(255.9 * col[2]);

			cout << ir << " " << ig << " " << ib << "\n";
		}
	}

	of.flush();
	of.close();

	cout.rdbuf(coutBuf);
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
