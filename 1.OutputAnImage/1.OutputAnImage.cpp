// StudyTheRayTracing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include "vec3.h"

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
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2f);
			//vec3 col1(float(j) / float(ny), float(j) / float(ny), float(j) / float(ny));
			//vec3 col2(float(i) / float(nx), float(i) / float(nx), float(i) / float(nx));
			//vec3 col = (col1 + col2) / 2;
			int ir = int(255.9 * col[0]);
			int ig = int(255.9 * col[1]);
			int ib = int(255.9 * col[2]);

			cout << ir << " " << ig << " " << ib << "\n";
		}
	}

	of.flush();
	of.close();

	cout.rdbuf(coutBuf);

	return 0;
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
