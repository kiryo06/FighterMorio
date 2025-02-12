#include "Camera.h"
#include <cmath>
#include "DxLib.h"
#include "Player.h"
#include "Screen.h"
#include "game.h"
namespace
{
	// カメラ範囲
	const float CameraScopeRangeRight = 500.0f;
	const float CameraScopeRangeLeft = -10.0f;
	const float CameraScopeRangeH = 300.0f;
	const float CameraScopeRangeTop = 320.0f;
	const float CameraScopeRangeBottom = 900.0f;
	const float CameraLerpRate = 0.9f;
}

VECTOR VLerp(VECTOR start, VECTOR end, float t)
{
	VECTOR ret;
	ret.x = std::lerp(start.x, end.x, t);
	ret.y = std::lerp(start.y, end.y, t);
	ret.z = std::lerp(start.z, end.z, t);
	return ret;
}

Camera::Camera():
	pos(VGet(0, 0, 0)),
	drawOffset(VGet(0, 0, 0))
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update(Player* player)
{
	VECTOR aimCameraPos = CalculateAimCameraPos(player->GetPlayerPos());
	// 目標ポジションに、Lerpを使ってカメラポジションを近づける
	pos = VLerp(pos, aimCameraPos, CameraLerpRate);
	ClampCameraPos();
	UpdateDrawOffset();
}

VECTOR Camera::CalculateAimCameraPos(const VECTOR& playerPos)
{
	// プレイヤーの位置が、カメラの中央から一定以上離れたら
	// カメラの「目標」ポジションをその範囲内に留める
	VECTOR aimCameraPos = pos;
	if (playerPos.x > pos.x + (CameraScopeRangeRight * 1.0f))
	{
		aimCameraPos.x = playerPos.x - (CameraScopeRangeRight * 1.0f);
	}
	/*else if (playerPos.x < pos.x - (CameraScopeRangeLeft * 5.0f))
	{
		aimCameraPos.x = playerPos.x + (CameraScopeRangeLeft * 5.0f);
	}*/
	if (playerPos.y > pos.y + (CameraScopeRangeH * 0.5f))
	{
		aimCameraPos.y = playerPos.y - (CameraScopeRangeH * 0.5f);
	}
	else if (playerPos.y < pos.y - (CameraScopeRangeH * 0.5f))
	{
		aimCameraPos.y = playerPos.y + (CameraScopeRangeH * 0.5f);
	}
	return aimCameraPos;
}

void Camera::ClampCameraPos()
{
	// 地面の一定より下にカメラが移動しないように後で固定
	if (pos.y > CameraScopeRangeBottom)
	{
		pos.y = CameraScopeRangeBottom;
	}
	// 空も同じく止める
	if (pos.y < CameraScopeRangeTop)
	{
		pos.y = CameraScopeRangeTop;
	}
	// 止める
	if (pos.x < 20)
	{
		pos.x = 20;
	}
}

void Camera::UpdateDrawOffset()
{
	drawOffset.x = pos.x * -1 + (ScreenWidth * 0.01f);
	drawOffset.y = pos.y * -1 + (ScreenHeight * 0.55f);
}