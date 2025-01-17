#pragma once
#include "Object.h"

enum CollitionType {
	kBox,
	kCircle,
	kPoint,

};

/// <summary>
/// 当たり判定
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

	/// <summary>
	/// BoxToCircle
	/// </summary>
	bool BTC(Object* obj1, Object* obj2);

	/// <summary>
	/// CircleToCircle
	/// </summary>
	/// <param name="obj1"></param>
	/// <param name="obj2"></param>
	/// <returns></returns>
	bool CTC(Object* obj1, Object* obj2);

}
