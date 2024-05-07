#include "clip.h"
#include "include\SDL.h"
#include "vec3.h"

#define MAX(a,b) ((a > b)? a : b)
#define MIN(a,b) ((a < b)? a : b)

namespace egc {

	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2){//, SDL_Renderer* renderer) {
		float tE, tL;
		float t, value;
		int PE = 0, PL = 0;	
		vec3 PtE, PtL;
		std::vector<vec3> normale;

		for (int i = 0; i < clipWindow.size() - 1; i++)
		{
			vec3 v = clipWindow.at(i + 1) - clipWindow.at(i);
			vec3 n = vec3(-v.y, v.x, 0);
			n.normalize();
			normale.push_back(n);
		}

		vec3 v1 = clipWindow.at(0) - clipWindow.at(clipWindow.size() - 1);
		vec3 n1 = vec3(-v1.y, v1.x, 0);
		n1.normalize();
		normale.push_back(n1);

		/*for (int i = 0; i < normale.size() - 1; i++)
		{
			SDL_RenderDrawLine(renderer, clipWindow.at(i).x, clipWindow.at(i).y, clipWindow.at(i + 1).x, clipWindow.at(i + 1).y);
		}
		SDL_RenderDrawLine(renderer, clipWindow.at(0).x, clipWindow.at(0).y, clipWindow.at(normale.size() - 1).x, clipWindow.at(normale.size() - 1).y);
		*/
		vec3 D = p2 - p1;

		if (p1 == p2)
		{
			return 0;
		}
		else
		{
			tE = 0; tL = 1;
			for (int i = 0; i < normale.size(); i++)
			{
				//PE = 0;
				//PL = 0;
				value = dotProduct(normale.at(i), D);
				if (value != 0)
				{
					t = -(dotProduct(normale.at(i), (p1 - clipWindow.at(i)))) / value;
					if (t >= 0 && t <= 1)
					{
						if (value < 0)
							PE = 1;
						if (value > 0)
							PL = 1;
						if (PE)
							tE = MAX(tE, t);
						if (PL)
							tL = MIN(tL, t);
					}
				}
			}
		}
		if (tE > tL)
			return -1;
		else
		{
			PtE = p1 + D * tE;
			PtL = p1 + D * tL;
			p1 = PtE;
			p2 = PtL;
			return 1;
		}
	}
}