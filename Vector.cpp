#include "Vector.h"
#include <assert.h>
#include <math.h>

Matrix3x3 M::Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {

	Matrix3x3 ans = { 0 };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			ans.m_[i][j] = matrix1.m_[i][0] * matrix2.m_[0][j] + matrix1.m_[i][1] * matrix2.m_[1][j] + matrix1.m_[i][2] * matrix2.m_[2][j];

		}
	}

	return ans;

}

Matrix3x3 M::Inverse(Matrix3x3 matrix) {

	float abc = matrix.m_[0][0] * matrix.m_[1][1] * matrix.m_[2][2] + matrix.m_[0][1] * matrix.m_[1][2] * matrix.m_[2][0] + matrix.m_[0][2] * matrix.m_[1][0] * matrix.m_[2][1] -
		matrix.m_[0][2] * matrix.m_[1][1] * matrix.m_[2][0] - matrix.m_[0][1] * matrix.m_[1][0] * matrix.m_[2][2] - matrix.m_[0][0] * matrix.m_[1][2] * matrix.m_[2][1];

	matrix = { {{matrix.m_[1][1] * matrix.m_[2][2] - matrix.m_[1][2] * matrix.m_[2][1],-matrix.m_[0][1] * matrix.m_[2][2] + 
		matrix.m_[0][2] * matrix.m_[2][1],matrix.m_[0][1] * matrix.m_[1][2] - matrix.m_[0][2] * matrix.m_[1][1]},
		{-matrix.m_[1][0] * matrix.m_[2][2] + matrix.m_[1][2] * matrix.m_[2][0],matrix.m_[0][0] * matrix.m_[2][2] - 
		matrix.m_[0][2] * matrix.m_[2][0],-matrix.m_[0][0] * matrix.m_[1][2] + matrix.m_[0][2] * matrix.m_[1][0]},
		{matrix.m_[1][0] * matrix.m_[2][1] - matrix.m_[1][1] * matrix.m_[2][0], -matrix.m_[0][0] * matrix.m_[2][1] + 
		matrix.m_[0][1] * matrix.m_[2][0],matrix.m_[0][0] * matrix.m_[1][1] - matrix.m_[0][1] * matrix.m_[1][0]}} };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix.m_[i][j] /= abc;
		}
	}

	return matrix;
}

Vector2 M::Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 ans{};

	ans.x = vector.x * matrix.m_[0][0] + vector.y * matrix.m_[1][0] + 1.0f * matrix.m_[2][0];
	ans.y = vector.x * matrix.m_[0][1] + vector.y * matrix.m_[1][1] + 1.0f * matrix.m_[2][1];
	float w = vector.x * matrix.m_[0][2] + vector.y * matrix.m_[1][2] + 1.0f * matrix.m_[2][2];
	assert(w != 0.0f);
	ans.x /= w;
	ans.y /= w;
	return ans;

}

Matrix3x3 M::MakeRotateMatrix(float theta) {

	return {
		{
			{cosf(theta), sinf(theta), 0},
			{-sinf(theta), cosf(theta), 0},
			{0, 0, 1}
		}
	};

}

Matrix3x3 M::MakeTransformMatrix(float x, float y) {

	return{
		{
			{1, 0, 0},
			{0, 1, 0},
			{x ,y, 1}
		}
	};

}

Matrix3x3 M::MakeScaleMatrix(float x, float y) {

	return {
		{
			{x, 0, 0},
			{0, y, 0},
			{0, 0, 1}
		}
	};

}
