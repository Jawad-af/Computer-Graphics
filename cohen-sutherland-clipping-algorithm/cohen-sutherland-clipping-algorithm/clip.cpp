#include "clip.h"

namespace egc {

	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p) {
		std::vector<int> code;
		//TO DO - compute the code for the point given as argument
		// check above 
		if (p.y < clipWindow.at(0).y && p.y < clipWindow.at(1).y)
			code.push_back(1);
		else code.push_back(0);

		// check bellow
		if (p.y > clipWindow.at(2).y && p.y > clipWindow.at(3).y)
			code.push_back(1);
		else code.push_back(0);

		// check left
		if (p.x < clipWindow.at(0).x && p.x < clipWindow.at(3).x)
			code.push_back(1);
		else code.push_back(0);

		// check right
		if (p.x > clipWindow.at(1).x && p.x > clipWindow.at(2).x)
			code.push_back(1);
		else code.push_back(0);

		return code;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE REJECTION case
		for (int i = 0; i < 4; i++)
			if (cod1.at(i) == 1 && cod2.at(i) == 1)
				return true;
		return false;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE ACCEPTANCE case
		for (int i = 0; i < 4; i++)
			if (cod1[i] == 1 || cod2[i] == 1)
				return false;
		return true;
	}

	void invert(float& x1, float& y1, float& x2, float& y2, std::vector<int>& cod1, std::vector<int>& cod2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
		std::swap(cod1, cod2);
	}

	bool isInside(std::vector<int> cod)
	{
		for (int i = 0; i < 4; i++)
			if (cod[i])
				return false;
		return true;
	}

	//function returns -1 if the line segment cannot be clipped
	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		//TO DO - implement the Cohen-Sutherland line clipping algorithm - consult the laboratory work
		bool finish = false;
		while (!finish)
		{
			std::vector<int> cod1 = computeCSCode(clipWindow, p1);
			std::vector<int> cod2 = computeCSCode(clipWindow, p2);
		
			bool rejected = simpleRejection(cod1, cod2);
			if (rejected)
			{
				return -1;
			}
			else
			{
				bool display = simpleAcceptance(cod1, cod2);
				if (display)
					finish = true;
				else
				{
					int xMin = clipWindow.at(0).x;
					int yMin = clipWindow.at(0).y;
					int xMax = clipWindow.at(2).x;
					int yMax = clipWindow.at(2).y;

					if (!isInside(cod1))
					{
						if (cod1.at(0) == 1 && p2.y != p1.y)
						{
							p1.x = p1.x + ((p2.x - p1.x) * ((yMin - p1.y) / (p2.y - p1.y)));
							p1.y = yMin;
						}
						else if (cod1.at(1) == 1 && p2.y != p1.y)
						{
							p1.x = p1.x + (p2.x - p1.x) * ((yMax - p1.y) / (p2.y - p1.y));
							p1.y = yMax;
						}
						else if (cod1.at(2) == 1 && p2.x != p1.x)
						{
							p1.x = xMin;
							p1.y = p1.y + ((p2.y - p1.y) * ((xMin - p1.x) / (p2.x - p1.x)));
						}
						else if (cod1.at(3) == 1 && p2.x != p1.x)
						{
							p1.x = xMax;
							p1.y = p1.y + ((p2.y - p1.y) * ((xMax - p1.x) / (p2.x - p1.x)));
						}
					}

					if (!isInside(cod2))
					{
						if (cod2.at(0) == 1 && p2.y != p1.y)
						{
							p2.x = p1.x + ((p2.x - p1.x) * ((yMin - p1.y) / (p2.y - p1.y)));
							p2.y = yMin;
						}
						else if (cod2.at(1) == 1 && p2.y != p1.y)
						{
							p2.x = p1.x + (p2.x - p1.x) * ((yMax - p1.y) / (p2.y - p1.y));
							p2.y = yMax;
						}
						else if (cod2.at(2) == 1 && p2.x != p1.x)
						{
							p2.x = xMin;
							p2.y = p1.y + ((p2.y - p1.y) * ((xMin - p1.x) / (p2.x - p1.x)));
						}
						else if (cod2.at(3) == 1 && p2.x != p1.x)
						{
							p2.x = xMax;
							p2.y = p1.y + ((p2.y - p1.y) * ((xMax - p1.x) / (p2.x - p1.x)));
						}
					}
					finish = true;
				}
			}

		}
		return 0;
	}
}

