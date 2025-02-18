#include "GroundRectangle_HitJudgement.h"
#include <cmath>
#include "DxLib.h"
#include "Map.h"
#include "Camera.h"

GroundRectangle_HitJudgement::GroundRectangle_HitJudgement():
	m_camera(),
	m_map(),
	w(25),
	h(32),
	fallSpeed(0.0f),
	workSpeed(0.0f),
	pos(VGet(256.0f + h * 0.5f, 992, 0)),
	dir(VGet(0, 0, 0)),
	velocity(VGet(0, 0, 0)),
	isGround(false),
	isHitTop(false),
	isLeft(false),
	isRight(false),
	mapChip(0),
	HitBox(0),
	m_kChipNumY(MapDataFile::kChipNumY),
	m_kChipNumX(MapDataFile::kChipNumX),
	m_k1ChipNumY(MapDataFile::k1ChipNumY),
	m_k1ChipNumX(MapDataFile::k1ChipNumX),
	m_k2ChipNumY(MapDataFile::k2ChipNumY),
	m_k2ChipNumX(MapDataFile::k2ChipNumX)
{

}

GroundRectangle_HitJudgement::~GroundRectangle_HitJudgement()
{
}

void GroundRectangle_HitJudgement::Init(int mapNumber)
{
	switch (mapNumber)
	{
	case 0:
		mapChip = 0;
		break;
	case 1:
		mapChip = 1;
		break;
	case 2:
		mapChip = 2;
		break;
	}

	if (mapChip == 0)
	{
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				PrototypeChipData0[hChip][wChip].chipKind = MapDataFile::mapChipData[hChip][wChip];
				PrototypeChipData0[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData0[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData0[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData0[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
	}

	if (mapChip == 1)
	{
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				PrototypeChipData1[hChip][wChip].chipKind = MapDataFile::mapChipData1[hChip][wChip];
				PrototypeChipData1[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData1[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData1[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData1[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
	}

	if (mapChip == 2)
	{
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				PrototypeChipData2[hChip][wChip].chipKind = MapDataFile::mapChipData2[hChip][wChip];
				PrototypeChipData2[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData2[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData2[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData2[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
	}
}


bool GroundRectangle_HitJudgement::IsHitBoxWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip)
{
	if (mapChip == 0)
	{
		// ↓デバック用
		const auto& chip = PrototypeChipData0[hChip][wChip];
		// マップチップが当たらない種類なら早期return
		if (chip.chipKind == 0)
		{
			return false;
		}
		// 当たっているかどうか調べる
		float futurePosLeft = checkPos.x - w * 0.5f;
		float futurePosRight = checkPos.x + w * 0.5f;
		float futurePosTop = checkPos.y - h * 0.5f;
		float futurePosBottom = checkPos.y + h * 0.5f;
		float targetLeft = chip.pos.x - chip.w * 0.5f;
		float targetRight = chip.pos.x + chip.w * 0.5f;
		float targetTop = chip.pos.y - chip.h * 0.5f;
		float targetBottom = chip.pos.y + chip.h * 0.5f;
		// 矩形同士の当たり判定
		if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
			(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
			((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
				(targetTop > futurePosTop && targetTop < futurePosBottom)))
		{
			return true;
		}
		return false;
	}

	if (mapChip == 1)
	{
		// ↓デバック用
		const auto& chip = PrototypeChipData1[hChip][wChip];
		// マップチップが当たらない種類なら早期return
		if (chip.chipKind == 0)
		{
			return false;
		}
		// 当たっているかどうか調べる
		float futurePosLeft = checkPos.x - w * 0.5f;
		float futurePosRight = checkPos.x + w * 0.5f;
		float futurePosTop = checkPos.y - h * 0.5f;
		float futurePosBottom = checkPos.y + h * 0.5f;
		float targetLeft = chip.pos.x - chip.w * 0.5f;
		float targetRight = chip.pos.x + chip.w * 0.5f;
		float targetTop = chip.pos.y - chip.h * 0.5f;
		float targetBottom = chip.pos.y + chip.h * 0.5f;
		// 矩形同士の当たり判定
		if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
			(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
			((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
				(targetTop > futurePosTop && targetTop < futurePosBottom)))
		{
			return true;
		}
		return false;
	}
	if (mapChip == 2)
	{
		// ↓デバック用
		const auto& chip = PrototypeChipData2[hChip][wChip];
		// マップチップが当たらない種類なら早期return
		if (chip.chipKind == 0)
		{
			return false;
		}
		// 当たっているかどうか調べる
		float futurePosLeft = checkPos.x - w * 0.5f;
		float futurePosRight = checkPos.x + w * 0.5f;
		float futurePosTop = checkPos.y - h * 0.5f;
		float futurePosBottom = checkPos.y + h * 0.5f;
		float targetLeft = chip.pos.x - chip.w * 0.5f;
		float targetRight = chip.pos.x + chip.w * 0.5f;
		float targetTop = chip.pos.y - chip.h * 0.5f;
		float targetBottom = chip.pos.y + chip.h * 0.5f;
		// 矩形同士の当たり判定
		if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
			(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
			((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
				(targetTop > futurePosTop && targetTop < futurePosBottom)))
		{
			return true;
		}
		return false;
	}
}

void GroundRectangle_HitJudgement::CheckIsTopHit(int mapNumber)
{
	// 1ドット上にずらして当たれば頭上がぶつかっている （小数点無視）
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) - 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;

	if (mapChip == 0)
	{
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				isHit = IsHitBoxWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			// 以前ぶつかっていないのにぶつかるならfallSpeedをゼロにし、即落下するように
			if (!isHitTop)
			{
				isHitTop = true;
				fallSpeed = 0.0f;

				// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
				pos.y = floorf(pos.y);
			}
		}
		else
		{
			isHitTop = false;
		}
	}

	if (mapChip == 1)
	{
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				isHit = IsHitBoxWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			// 以前ぶつかっていないのにぶつかるならfallSpeedをゼロにし、即落下するように
			if (!isHitTop)
			{
				isHitTop = true;
				fallSpeed = 0.0f;

				// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
				pos.y = floorf(pos.y);
			}
		}
		else
		{
			isHitTop = false;
		}
	}

	if (mapChip == 2)
	{
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				isHit = IsHitBoxWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			// 以前ぶつかっていないのにぶつかるならfallSpeedをゼロにし、即落下するように
			if (!isHitTop)
			{
				isHitTop = true;
				fallSpeed = 0.0f;

				// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
				pos.y = floorf(pos.y);
			}
		}
		else
		{
			isHitTop = false;
		}
	}
}

void GroundRectangle_HitJudgement::CheckIsGround(int mapNumber)
{
	// 1ドット下にずらして当たれば地面に足がぶつかっている （小数点無視）
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) + 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;

	if (mapChip == 0)
	{
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				isHit = IsHitBoxWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			isGround = true;
			// fallSpeedをゼロにし、急激な落下を防ぐ
			fallSpeed = 0.0f;

			// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
			pos.y = floorf(pos.y);	// ちょうど地面に付く位置に
		}
		else
		{
			isGround = false;
		}
	}

	if (mapChip == 1)
	{
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				isHit = IsHitBoxWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			isGround = true;
			// fallSpeedをゼロにし、急激な落下を防ぐ
			fallSpeed = 0.0f;

			// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
			pos.y = floorf(pos.y);	// ちょうど地面に付く位置に
		}
		else
		{
			isGround = false;
		}
	}

	if (mapChip == 2)
	{
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				isHit = IsHitBoxWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			isGround = true;
			// fallSpeedをゼロにし、急激な落下を防ぐ
			fallSpeed = 0.0f;

			// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
			pos.y = floorf(pos.y);	// ちょうど地面に付く位置に
		}
		else
		{
			isGround = false;
		}
	}
}

void GroundRectangle_HitJudgement::CheckIsLeft(int mapNumber)
{
}

void GroundRectangle_HitJudgement::CheckIsRight(int mapNumber)
{
}
