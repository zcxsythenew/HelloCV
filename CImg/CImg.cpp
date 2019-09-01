// CImg.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "CImg.h"

///
/// 注释该行以不使用 CImg 作图（画三角形、圆形、线段）
///
//#define USE_CIMG_LIBRARY_FOR_DRAWING

using namespace cimg_library;
using namespace std;

class BasicImage
{
	CImg<unsigned char>* image;

	void ReplaceColor(unsigned char old_r, unsigned char old_g, unsigned char old_b, unsigned char new_r, unsigned char new_g, unsigned char new_b)
	{
		cimg_forXY(*image, x, y)
		{
			if ((*image)(x, y, 0) == old_r && (*image)(x, y, 1) == old_g && (*image)(x, y, 2) == old_b)
			{
				(*image)(x, y, 0) = new_r;
				(*image)(x, y, 1) = new_g;
				(*image)(x, y, 2) = new_b;
			}
		}
	}
public:
	BasicImage(const char* const fileName)
	{
		image = new CImg<unsigned char>(fileName);
	}

	void Display()
	{
		image->display();
		cout << endl;
	}

	void WhiteToRed()
	{
		ReplaceColor(255, 255, 255, 255, 0, 0);
	}

	void BlackToGreen()
	{
		ReplaceColor(0, 0, 0, 0, 255, 0);
	}

	void DrawEquTriangle(int center_x, int center_y, int length, unsigned char r, unsigned char g, unsigned char b)
	{
#ifdef USE_CIMG_LIBRARY_FOR_DRAWING

		unsigned char color[3];

		color[0] = r;
		color[1] = g;
		color[2] = b;

		int x0 = center_x;
		int y0 = center_y - length * sqrt(3) / 3;
		int x1 = center_x - length / 2;
		int y1 = center_y + length * sqrt(3) / 6;
		int x2 = center_x + length / 2;
		int y2 = center_y + length * sqrt(3) / 6;
		image->draw_triangle(x0, y0, x1, y1, x2, y2, color);

#else

		double y_top = center_y - length * sqrt(3) / 3;
		double y_bottom = center_y + length * sqrt(3) / 6;
		int current_width = 0;

		for (int y = ceil(y_top); y <= floor(y_bottom); y++)
		{
			current_width = floor(y - y_top) * sqrt(3) / 3;
			for (int x = center_x - current_width; x <= center_x + current_width; x++)
			{
				(*image)(x, y, 0) = r;
				(*image)(x, y, 1) = g;
				(*image)(x, y, 2) = b;
			}
		}

#endif
	}

	void DrawCircle(int center_x, int center_y, int radius, unsigned char r, unsigned char g, unsigned char b)
	{
#ifdef USE_CIMG_LIBRARY_FOR_DRAWING

		unsigned char color[3];

		color[0] = r;
		color[1] = g;
		color[2] = b;

		image->draw_circle(center_x, center_y, radius, color);

#else

		int y_top = center_y - radius;
		int y_bottom = center_y + radius;
		int current_width = 0;

		for (int y = y_top; y <= y_bottom; y++)
		{
			current_width = floor(sqrt(radius * radius - abs(center_y - y) * abs(center_y - y)));
			for (int x = center_x - current_width; x <= center_x + current_width; x++)
			{
				(*image)(x, y, 0) = r;
				(*image)(x, y, 1) = g;
				(*image)(x, y, 2) = b;
			}
		}

#endif
	}

	void Draw135Line(int start_x, int start_y, int length, unsigned char r, unsigned char g, unsigned char b)
	{
#ifdef USE_CIMG_LIBRARY_FOR_DRAWING

		unsigned char color[3];

		color[0] = r;
		color[1] = g;
		color[2] = b;

		image->draw_line(start_x, start_y, start_x + length, start_y + length, color);

#else

		for (int i = 0; i <= length; i++)
		{
			(*image)(start_x + i, start_y + i, 0) = r;
			(*image)(start_x + i, start_y + i, 1) = g;
			(*image)(start_x + i, start_y + i, 2) = b;
		}

#endif
	}

	void Save(const char* const fileName)
	{
		image->save(fileName);
	}

	virtual ~BasicImage()
	{
		delete image;
	}
};

int main()
{
	BasicImage image("1.bmp");
	image.WhiteToRed();
	image.BlackToGreen();
	image.DrawEquTriangle(50, 50, 40, 0, 0, 255);
	image.DrawCircle(50, 50, 15, 255, 255, 0);
	image.Draw135Line(0, 0, 100, 0, 255, 0);
	image.Display();
	image.Save("2.bmp");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
