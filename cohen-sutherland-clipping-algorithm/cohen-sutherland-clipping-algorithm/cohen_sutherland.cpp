#include <SDL2/SDL.h>
#include "vector"
#include "vec3.h"

const int INSIDE = 0; //code 0000
const int LEFT = 1; //code 0001
const int RIGHT = 2; //code 0010
const int TOP = 8; //code 1000
const int BOTTOM = 4; //code 0100

double xmin = INT_MIN, xmax = INT_MAX, ymin = INT_MIN, ymax = INT_MAX;
namespace egc {
	std::vector<int> computeCScode(std::vector<vec3> clipWindow, const vec3 p)
	{
		std::vector<int> code;

		for (int i = 0; i < clipWindow.size(); i++) 
		{
			if (xmin > clipWindow[i].x) {
				xmin = clipWindow[i].x;
			}
			if (xmax < clipWindow[i].x) {
				xmax = clipWindow[i].x;
			}
			if (ymin > clipWindow[i].y) {
				ymin = clipWindow[i].y;
			}
			if (ymax < clipWindow[i].y) {
				ymax = clipWindow[i].y;
			}
		}

		if (p.y < ymin)
			code.at(0) = 1;
		else
			code.at(0) = 0;

		if (p.y > ymax)
			code.at(1) = 1;
		else
			code.at(1) = 0;

		if (p.x > xmax)
			code.at(2) = 1;
		else
			code.at(2) = 0;

		if (p.x < xmin)
			code.at(3) = 1;
		else
			code.at(3) = 0;

		return code;
	}

	bool simpleRejection(std::vector<int> code1, std::vector<int> code2)
	{
		for (int i = 0; i < code1.size(); i++)
		{
			if (code1[i] == 1 && code2[i] == 1)
				return true;
		}
		return false;
	}

	bool simpleAcceptance(std::vector<int> code1, std::vector<int> code2)
	{
		for (int i = 0; i < code1.size(); i++)
		{
			if (code1[i] == 1 || code2[i] == 1)
				return false;
		}
		return true;
	}

	void invert(vec3& p1, vec3& p2, std::vector<int>& code1, std::vector<int>& code2)
	{
		vec3 p;
		std::vector<int> code;

		p = p1;
		p1 = p2;
		p2 = p;

		code = code1;
		code1 = code2;
		code2 = code;

	}

	bool isInside(std::vector<int> code)
	{
		for (int i = 0; i < code.size(); i++)
		{
			if (code[i] != 0)
				return false;
		}
		return true;
	}
	
	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2)
	{
		std::vector<int> code1, code2;
		bool respins, finished = false, display;

		while (finished == false)
		{
			code1 = computeCScode(clipWindow, p1);
			code2 = computeCScode(clipWindow, p2);
			respins = simpleRejection(code1, code2); // test for simple rejection

			if (respins == true)
			{
				finished = true;
				break;
			}
			else
			{
				display = simpleAcceptance(code1, code2); // test for simple acceptance
				if (display == true)
				{
					finished = true;
					break;
				}
				else
				{
					if (isInside(code1) == true) // if it is inside the area
					{
						invert(p1, p2, code1, code2); // invert the points	
					}

					if (code1.at(0) == 1 && p1.y != p2.y) // eliminate the segment above the display area
					{
						p1.x = p1.x + (p2.x - p1.x) * (ymax - p1.y) / (p2.y - p1.y);
						p1.y = ymin;
					}
					else if (code1.at(1) == 1 && p1.y != p2.y) // eliminate the segment under the display area
					{
						p1.x = p1.x + (p2.x - p1.x) * (ymin - p1.y) / (p2.y - p1.y);
						p1.y = ymax;
					}
					else if (code1.at(2) == 1 && p1.x != p2.x) // eliminate the segment on the right of the display area 
					{
						p1.y = p1.y + (p2.y - p1.y) * (xmax - p1.x) / (p2.x - p1.x);
						p1.x = xmax;
					}
					else if (code1.at(3) == 1 && p1.x != p2.x) // eliminate the segment on the left of the display area 
					{
						p1.y = p1.y + (p2.y - p1.y) * (xmin - p1.x) / (p2.x - p1.x);
						p1.x = xmin;
					}
				}
			}
		}

		return 1;
	}
}