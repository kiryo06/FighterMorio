#pragma once
/*
class Vector3
{
public:
	/// <summary>
	/// ベクトルの足し算
	/// </summary>
	/// <returns></returns>
	bool AddVecter(Vector3& v1, Vector3& v2);
	/// <summary>
	/// ベクトル同士の引き算
	/// </summary>
	/// <returns></returns>
	bool SudVecter(Vector3& v1, Vector3& v2);
	/// <summary>
	/// ベクトルのスカラー倍
	/// </summary>
	/// <returns></returns>
	bool ScaleVector(Vector3& vec, float size);
	/// <summary>
	/// ベクトルの長さ
	/// </summary>
	/// <returns></returns>
	float GetVectorLength();
	/// <summary>
	/// ベクトルの正規化
	/// </summary>
	/// <returns></returns>
	bool NormalizeVector();
private:
	float x;
	float y;
	float z;
};
//*/


struct Vector
{
	float x;
	float y;
	float z;
};

Vector AddVector(Vector& v1, Vector& v2);
Vector SubVector(Vector& v1, Vector& v2);
Vector ScaleVector(Vector& vec, float size);
Vector NormalizeVector(Vector& vec);
float GetVectorLength(Vector& vec);
Vector NormalizeVector(Vector& vec);