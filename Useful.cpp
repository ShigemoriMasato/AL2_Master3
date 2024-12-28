#include "Useful.h"
#include <Novice.h>

Vector2 UF::Normalize(Vector2 vector) {
	Vector2 ans = {
		vector.x * vector.x / (vector.x * vector.x + vector.y * vector.y),
		vector.y * vector.y / (vector.x * vector.x + vector.y * vector.y)
	};

	return ans;
}

float UF::Normalize(float value, float length) {
	return value * value / length;
}

Vector2 UF::NormalizeLength(Vector2 vector, float length) {
	Vector2 ans = {
		vector.x * vector.x / length,
		vector.y * vector.y / length
	};

	return ans;
}

float UF::GetSign(float value) {
	if (value < 0) {
		return -1;
	}
	else {
		return 1;
	}
}

Vector2 UF::Multiply(Vector2 vector1, Vector2 vector2) {
	Vector2 ans = {
		vector1.x * vector2.x,
		vector1.y * vector2.y
	};

	return ans;
}

float UF::AbsoluteValue(float value) {
	if (value < 0) {
		value *= -1;
	}

	return value;
}

float UF::SerchMax(float value1, float value2, float value3, float value4, float value5, float value6, float value7, float value8, float value9, float value10) {
	float ans = value1;

	if (ans < value2) {
		ans = value2;
	}

	if (ans < value3) {
		ans = value3;
	}

	if (ans < value4) {
		ans = value4;
	}

	if (ans < value5) {
		ans = value5;
	}

	if (ans < value6) {
		ans = value6;
	}

	if (ans < value7) {
		ans = value7;
	}

	if (ans < value8) {
		ans = value8;
	}

	if (ans < value9) {
		ans = value9;
	}

	if (ans < value10) {
		ans = value10;
	}

	return ans;
}

Vector2 UF::GetMousePos() {
	int x = 0;
	int y = 0;
	Novice::GetMousePosition(&x, &y);
	Vbuffer = { float(x), float(y) };
	return Vbuffer;
}
