#include "Collition.h"

bool CL::BtB(Object* obj1, Object* obj2) {

	if (obj2->GetCorner(0).x < obj1->GetCorner(1).x && obj1->GetCorner(0).x < obj2->GetCorner(1).x &&
		obj2->GetCorner(2).y < obj1->GetCorner(1).y && obj1->GetCorner(2).y < obj2->GetCorner(1).y) {
		return true;
	}
	else {
		return false;
	}

}

bool CL::BtP(Object* obj, Vector2 point) {

	if (obj->GetCorner(0).x < point.x && obj->GetCorner(1).x > point.x && obj->GetCorner(1).y > point.y && obj->GetCorner(2).y < point.y) {
		return true;
	}
	else {
		return false;
	}

}
