#include <fstream>
#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"

using namespace std;

class PPMRender
{
public:
	virtual void init() {};
	
	virtual vec3 color(const ray& r, hitable* world = nullptr)
	{
		vec3 uint_direciton = unit_vector(r.direction());
		float t = 0.5f * (uint_direciton.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
	
	void output(string fileName = "out")
	{
		init();
		
		string suffix = ".ppm";
		fileName.append(suffix);
		
		streambuf* coutBuf = cout.rdbuf();
		ofstream of(fileName);
		streambuf* fileBuf = of.rdbuf();
		cout.rdbuf(fileBuf);

		cout << "P3\n" << nx << " " << ny << "\n255\n";

		camera cam;
		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				vec3 col(0, 0, 0);
				if (ns > 0)
				{
					for (int s = 0; s < ns; s++)
					{
						float u = float(i + drand48()) / float(nx);
						float v = float(j + drand48()) / float(ny);
						ray r = cam.get_ray(u, v);
						col += color(r, world);
					}
					col /= float(ns);
					//col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
				}
				else
				{
					float u = float(i) / float(nx);
					float v = float(j) / float(ny);
					ray r = cam.get_ray(u, v);
					col = color(r, world);
				}
				
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

protected:
	hitable* world;
	int nx = 200;
	int ny = 100;
	int ns = 0;
};