#pragma once
// ゲーム中で使用する情報型を定義する場所

/// <summary>
/// 2Dベクトル
/// </summary>
struct Vector2
{
	float x, y;
};

// Vec2があるので別名を作っただけ
using Position2 = Vector2;

/// <summary>
/// サイズ(2Dゲームで使用するピクセルサイズ)
/// </summary>
struct Size
{
	int w, h;
};

