#pragma once
#include "Object.h"

enum CollitionType {
	kBox,
	kCircle,
	kPoint,

};

/// <summary>
/// “–‚½‚è”»’è
/// </summary>
namespace CL {

	/// <summary>
	/// BoxToBox
	/// </summary>
	bool BtB(Object* obj1, Object* obj2);

	/// <summary>
	/// BoxToPoint
	/// </summary>
	bool BtP(Object* obj, Vector2 point);

	/// <summary>
	/// CircleToPoint
	/// </summary>
	bool CTP(Object* obj, Vector2 point);

}
