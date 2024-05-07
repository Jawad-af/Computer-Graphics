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
		if (p.x < clipWindow.at(1).x && p.x < clipWindow.at(2).x)
			code.push_back(1);
		else code.push_back(0);

		return code;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE REJECTION case
		bool rejected = false;
		for (int i = 0; i < 4; i++)
			if (cod1.at(i) == cod2.at(i))
				rejected = true;
		return rejected;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE ACCEPTANCE case
		bool cod1Accepted = true;
		for (int i : cod1)
			if (i == 1)
				cod1Accepted = false;

		bool cod2Accepted = true;
		for (int i : cod2)
			if (i == 1)
				cod2Accepted = false;

		return cod1Accepted && cod2Accepted;
	}

	//function returns -1 if the line segment cannot be clipped
	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		//TO DO - implement the Cohen-Sutherland line clipping algorithm - consult the laboratory work

		return 0;
	}
}

