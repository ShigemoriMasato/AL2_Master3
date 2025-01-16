#include "Collition.h"
#include <cmath>

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

bool CL::BTC(Object* obj1, Object* obj2) {
	Vector2 circleDistance;
	circleDistance.x = abs(obj2->GetPos().x - obj1->GetPos().x - obj1->GetSize().x / 2);
	circleDistance.y = abs(obj2->GetPos().y - obj1->GetPos().y - obj1->GetSize().y / 2);

	if (circleDistance.x > (obj1->GetSize().x / 2 + obj2->GetSize().x * 2 * obj2->GetScale().x)) {
		return false;
	}
	if (circleDistance.y > (obj1->GetSize().y / 2 + obj2->GetSize().x * 2 * obj2->GetScale().x)) {
		return false;
	}

	if (circleDistance.x <= (obj1->GetSize().x / 2)) {
		return true;
	}
	if (circleDistance.y <= (obj1->GetSize().y / 2)) {
		return true;
	}

	float cornerDistance_sq = (circleDistance.x - obj1->GetSize().x / 2) * (circleDistance.x - obj1->GetSize().x / 2) + (circleDistance.y - obj1->GetSize().y / 2) * (circleDistance.y - obj1->GetSize().y / 2);

	return (cornerDistance_sq <= (obj2->GetSize().x * 2 * obj2->GetScale().x * obj2->GetSize().x * 2 * obj2->GetScale().x));
}

bool CL::CTC(Object* obj1, Object* obj2) {
 	float distance = sqrt((obj1->GetPos().x - obj2->GetPos().x) * (obj1->GetPos().x - obj2->GetPos().x) + (obj1->GetPos().y - obj2->GetPos().y) * (obj1->GetPos().y - obj2->GetPos().y));
	if (distance < obj1->GetSize().x + obj2->GetSize().x) {
		return true;
	}
	else {
		return false;
	}
}
