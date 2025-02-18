#include "Map.h"
#include "DxLib.h"
#include "Camera.h"
#include <cassert>

#define BACKCOLOR 0x87cefa

Map::Map():
	m_kChipWidth(MapDataFile::kChipWidth),
	m_kChipHeight(MapDataFile::kChipHeight),
	m_kChipNumY(MapDataFile::kChipNumY),
	m_kChipNumX(MapDataFile::kChipNumX),
	m_k1ChipNumY(MapDataFile::k1ChipNumY),
	m_k1ChipNumX(MapDataFile::k1ChipNumX),
	m_k2ChipNumY(MapDataFile::k2ChipNumY),
	m_k2ChipNumX(MapDataFile::k2ChipNumX),
	m_WallGraph(0),
	m_HardBlockGraph(0),
	m_SkyBackGroundGraph(0),
	m_dokanGraph(0),
	m_WorldGraph(0),
	m_CastleGraph(0)
{
}

Map::~Map()
{
	DeleteGraph(m_WallGraph);
	DeleteGraph(m_HardBlockGraph);
	DeleteGraph(m_SkyBackGroundGraph);
	DeleteGraph(m_dokanGraph);
	DeleteGraph(m_WorldGraph);
	DeleteGraph(m_CastleGraph);
}

void Map::Init(int mapNumber)
{
	m_WallGraph = LoadGraph("data/image/WorldMap.png");				// 16 * 16
	m_HardBlockGraph = LoadGraph("data/image/HardBlock.png");		// 32 * 32
	m_SkyBackGroundGraph = LoadGraph("data/image/BackGround.png");	// 960 * 1920
	m_dokanGraph = LoadGraph("data/image/dokan.png");
	m_WorldGraph = LoadGraph("data/image/OverWorld.png");
	m_CastleGraph = LoadGraph("data/image/Castle.png");
	switch (mapNumber)
	{
	case 0:
		// デバック
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData[hChip][wChip];
				PrototypeChipData[hChip][wChip].w = m_kChipWidth;
				PrototypeChipData[hChip][wChip].h = m_kChipHeight;
				PrototypeChipData[hChip][wChip].pos.x = wChip * m_kChipWidth;
				PrototypeChipData[hChip][wChip].pos.y = hChip * m_kChipHeight;
			}
		}
		break;
	case 1:
		// 1-1
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				PrototypeChipData1[hChip][wChip].chipKind = MapDataFile::mapChipData1[hChip][wChip];
				PrototypeChipData1[hChip][wChip].w = m_kChipWidth;
				PrototypeChipData1[hChip][wChip].h = m_kChipHeight;
				PrototypeChipData1[hChip][wChip].pos.x = wChip * m_kChipWidth;
				PrototypeChipData1[hChip][wChip].pos.y = hChip * m_kChipHeight;
			}
		}
		break;
	case 2:
		// 1-2
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				PrototypeChipData2[hChip][wChip].chipKind = MapDataFile::mapChipData2[hChip][wChip];
				PrototypeChipData2[hChip][wChip].w = m_kChipWidth;
				PrototypeChipData2[hChip][wChip].h = m_kChipHeight;
				PrototypeChipData2[hChip][wChip].pos.x = wChip * m_kChipWidth;
				PrototypeChipData2[hChip][wChip].pos.y = hChip * m_kChipHeight;
			}
		}
		break;
	}
}


void Map::Draw(int mapNumber, Camera* camera)
{
	switch (mapNumber)
	{
	case 0:
		// デバック
		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
			{
				auto leftTop = static_cast<int>(PrototypeChipData[hChip][wChip].pos.x - PrototypeChipData[hChip][wChip].w * 0.5f);			// 左上の座標を渡す
				auto leftBottom = static_cast<int>(PrototypeChipData[hChip][wChip].pos.y - PrototypeChipData[hChip][wChip].h * 0.5f);		// 左下の座標を渡す
				auto rightTop = static_cast<int>(PrototypeChipData[hChip][wChip].pos.x + PrototypeChipData[hChip][wChip].w * 0.5f);			// 右上の座標を渡す
				auto rightBottom = static_cast<int>(PrototypeChipData[hChip][wChip].pos.y + PrototypeChipData[hChip][wChip].h * 0.5f);		// 右下の座標を渡す


				leftTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// 左上の座標の補正
				leftBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// 左下の座標の補正
				rightTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// 右上の座標の補正
				rightBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// 右下の座標の補正

				// 0は当たり判定がないので0を空色で描画
				if (PrototypeChipData[hChip][wChip].chipKind == 0)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, 0x222222, TRUE);
				}
				// １は当たり判定チップ、1を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 1)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 16, 16, 16, m_WallGraph, TRUE);
				}
				// 2は当たり判定チップ、2を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 2)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 272, 64, 48, 48, m_WallGraph, TRUE);
				}
				// 3は当たり判定チップ、3を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 3)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 272, 144, 16, 16, m_WallGraph, TRUE);
				}
				// 4は当たり判定チップ、4を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 4)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 32, 32, m_HardBlockGraph, TRUE);
				}
				// 5は当たり判定チップ、5を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 5)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30, 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 6は当たり判定チップ、6を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 6)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 7は当たり判定チップ、7を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 7)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30, 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 8は当たり判定チップ、8を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 8)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 9は当たり判定がないチップ、9を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 9)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 10は当たり判定がないチップ、10を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 10)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 11は当たり判定がないチップ、11を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 11)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 12は当たり判定がないチップ、12を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 12)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 13は当たり判定がないチップ、13を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 13)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 14は当たり判定がないチップ、14を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 14)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 15は当たり判定がないチップ、15を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 15)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 16は当たり判定がないチップ、16を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 16)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 17は当たり判定がないチップ、17を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 17)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 64, 16, 16, m_WorldGraph, TRUE);
				}
				// 18は当たり判定がないチップ、18を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 18)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 19は当たり判定がないチップ、19を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 19)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 20は当たり判定がないチップ、20を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 20)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 21は当たり判定がないチップ、21を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 21は当たり判定がないチップ、21を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 22は当たり判定がないチップ、22を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 22)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 23は当たり判定がないチップ、23を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 23)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 24は当たり判定がないチップ、24を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 24)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 25は当たり判定がないチップ、25を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 25)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 26は当たり判定がないチップ、26を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 26)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 27は当たり判定がないチップ、27を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 27)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 28は当たり判定がないチップ、28を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 28)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 29は当たり判定がないチップ、29を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 29)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 30は当たり判定がないチップ、30を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 30)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 31は当たり判定がないチップ、31を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 31)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 32は当たり判定がないチップ、32を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 32)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 33は当たり判定がないチップ、33を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 33)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 34は当たり判定がないチップ、34を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 34)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 35は当たり判定がないチップ、35を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 35)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 36は当たり判定がないチップ、36を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 36)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 37は当たり判定がないチップ、37を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 37)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 38は当たり判定がないチップ、38を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 38)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 39は当たり判定がないチップ、39を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 39)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 40は当たり判定がないチップ、40を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 40)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 41は当たり判定がないチップ、41を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 41)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 42は当たり判定がないチップ、42を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 42)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 43は当たり判定がないチップ、43を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 43)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 44は当たり判定がないチップ、44を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 44)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 45は当たり判定がないチップ、45を描画
				if (PrototypeChipData[hChip][wChip].chipKind == 45)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 0, 16, 16, m_CastleGraph, TRUE);
				}
			}
		}
		break;
	case 1:
		// 1-1

		/*DrawRectExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight,0, 0, 3840, 1920, m_SkyBackGroundGraph, TRUE);*/

		for (int hChip = 0; hChip < MapDataFile::k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::k1ChipNumX; wChip++)
			{
				auto leftTop = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.x - PrototypeChipData1[hChip][wChip].w * 0.5f);			// 左上の座標を渡す
				auto leftBottom = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.y - PrototypeChipData1[hChip][wChip].h * 0.5f);			// 左下の座標を渡す
				auto rightTop = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.x + PrototypeChipData1[hChip][wChip].w * 0.5f);			// 右上の座標を渡す
				auto rightBottom = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.y + PrototypeChipData1[hChip][wChip].h * 0.5f);		// 右下の座標を渡す

				leftTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// 左上の座標の補正
				leftBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// 左下の座標の補正
				rightTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// 右上の座標の補正
				rightBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// 右下の座標の補正



				// 0は当たり判定がないので0を空色で描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 0)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
				}
				// -１は当たり判定チップ、-1を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == -1)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 1, 16, 16, m_WallGraph, TRUE);
				}
				// １は当たり判定チップ、1を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 1)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 16, 16, 16, m_WallGraph, TRUE);
				}
				// 2は当たり判定チップ、2を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 2)
				{
					DrawRectExtendGraph(leftTop,leftBottom,rightTop,rightBottom,272, 64, 48, 48, m_WallGraph, TRUE);
				}
				// 3は当たり判定チップ、3を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 3)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 272, 144, 16, 16, m_WallGraph, TRUE);
				}
				// 4は当たり判定チップ、4を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 4)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 32, 32, m_HardBlockGraph, TRUE);
				}
				// 5は当たり判定チップ、5を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 5)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30 , 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 6は当たり判定チップ、6を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 6)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 7は当たり判定チップ、7を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 7)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30 , 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 8は当たり判定チップ、8を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 8)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 9は当たり判定がないチップ、9を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 9)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 10は当たり判定がないチップ、10を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 10)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 11は当たり判定がないチップ、11を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 11)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 12は当たり判定がないチップ、12を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 12)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 13は当たり判定がないチップ、13を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 13)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 14は当たり判定がないチップ、14を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 14)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 15は当たり判定がないチップ、15を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 15)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 16は当たり判定がないチップ、16を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 16)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 17は当たり判定がないチップ、17を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 17)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 64, 16, 16, m_WorldGraph, TRUE);
				}
				// 18は当たり判定がないチップ、18を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 18)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 19は当たり判定がないチップ、19を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 19)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 20は当たり判定がないチップ、20を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 20)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 21は当たり判定がないチップ、21を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 21は当たり判定がないチップ、21を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 22は当たり判定がないチップ、22を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 22)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 23は当たり判定がないチップ、23を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 23)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 24は当たり判定がないチップ、24を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 24)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 25は当たり判定がないチップ、25を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 25)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 26は当たり判定がないチップ、26を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 26)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 27は当たり判定がないチップ、27を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 27)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 28は当たり判定がないチップ、28を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 28)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 29は当たり判定がないチップ、29を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 29)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 30は当たり判定がないチップ、30を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 30)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 31は当たり判定がないチップ、31を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 31)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 32は当たり判定がないチップ、32を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 32)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,16, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 33は当たり判定がないチップ、33を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 33)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,32, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 34は当たり判定がないチップ、34を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 34)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,48, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 35は当たり判定がないチップ、35を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 35)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,64, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 36は当たり判定がないチップ、36を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 36)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 37は当たり判定がないチップ、37を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 37)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,16, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 38は当たり判定がないチップ、38を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 38)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,32, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 39は当たり判定がないチップ、39を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 39)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,48, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 40は当たり判定がないチップ、40を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 40)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,64, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 41は当たり判定がないチップ、41を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 41)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 42は当たり判定がないチップ、42を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 42)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,16, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 43は当たり判定がないチップ、43を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 43)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,32, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 44は当たり判定がないチップ、44を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 44)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,48, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 45は当たり判定がないチップ、45を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 45)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,64, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 46は当たり判定がないチップ、46を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 46)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 32, 16, 16, m_WorldGraph, TRUE);
				}
				// 47は当たり判定がないチップ、47を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 47)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 32, 16, 16, m_WorldGraph, TRUE);
				}
				// 48は当たり判定がないチップ、48を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 48)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 32, 16, 16, m_WorldGraph, TRUE);
				}
				// 49は当たり判定がないチップ、49を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 49)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 48, 16, 16, m_WorldGraph, TRUE);
				}
				// 50は当たり判定がないチップ、50を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 50)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 48, 16, 16, m_WorldGraph, TRUE);
				}
				// 51は当たり判定がないチップ、51を描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 51)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 48, 16, 16, m_WorldGraph, TRUE);
				}
			}
		}
		break;
	case 2:
		// 1-2

		/*DrawRectExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight,0, 0, 3840, 1920, m_SkyBackGroundGraph, TRUE);*/

		for (int hChip = 0; hChip < MapDataFile::k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::k2ChipNumX; wChip++)
			{
				auto leftTop = static_cast<int>(PrototypeChipData2[hChip][wChip].pos.x - PrototypeChipData2[hChip][wChip].w * 0.5f);			// 左上の座標を渡す
				auto leftBottom = static_cast<int>(PrototypeChipData2[hChip][wChip].pos.y - PrototypeChipData2[hChip][wChip].h * 0.5f);			// 左下の座標を渡す
				auto rightTop = static_cast<int>(PrototypeChipData2[hChip][wChip].pos.x + PrototypeChipData2[hChip][wChip].w * 0.5f);			// 右上の座標を渡す
				auto rightBottom = static_cast<int>(PrototypeChipData2[hChip][wChip].pos.y + PrototypeChipData2[hChip][wChip].h * 0.5f);		// 右下の座標を渡す

				leftTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// 左上の座標の補正
				leftBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// 左下の座標の補正
				rightTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// 右上の座標の補正
				rightBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// 右下の座標の補正


				// 0は当たり判定がないので0を空色で描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 0)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
				}
				// -１は当たり判定チップ、-1を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == -1)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 1, 16, 16, m_WallGraph, TRUE);
				}
				// １は当たり判定チップ、1を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 1)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 16, 16, 16, m_WallGraph, TRUE);
				}
				// 2は当たり判定チップ、2を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 2)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 272, 64, 48, 48, m_WallGraph, TRUE);
				}
				// 3は当たり判定チップ、3を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 3)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 272, 144, 16, 16, m_WallGraph, TRUE);
				}
				// 4は当たり判定チップ、4を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 4)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 32, 32, m_HardBlockGraph, TRUE);
				}
				// 5は当たり判定チップ、5を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 5)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30, 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 6は当たり判定チップ、6を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 6)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 7は当たり判定チップ、7を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 7)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30, 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 8は当たり判定チップ、8を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 8)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +○,-○ は切り取り位置を変えている
				}
				// 9は当たり判定がないチップ、9を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 9)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 10は当たり判定がないチップ、10を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 10)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 11は当たり判定がないチップ、11を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 11)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 12は当たり判定がないチップ、12を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 12)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 13は当たり判定がないチップ、13を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 13)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 14は当たり判定がないチップ、14を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 14)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 15は当たり判定がないチップ、15を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 15)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 16は当たり判定がないチップ、16を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 16)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 17は当たり判定がないチップ、17を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 17)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 64, 16, 16, m_WorldGraph, TRUE);
				}
				// 18は当たり判定がないチップ、18を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 18)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 19は当たり判定がないチップ、19を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 19)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 20は当たり判定がないチップ、20を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 20)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 21は当たり判定がないチップ、21を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 21は当たり判定がないチップ、21を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 22は当たり判定がないチップ、22を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 22)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 23は当たり判定がないチップ、23を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 23)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 24は当たり判定がないチップ、24を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 24)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 25は当たり判定がないチップ、25を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 25)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 26は当たり判定がないチップ、26を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 26)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 27は当たり判定がないチップ、27を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 27)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 28は当たり判定がないチップ、28を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 28)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 29は当たり判定がないチップ、29を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 29)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 30は当たり判定がないチップ、30を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 30)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 31は当たり判定がないチップ、31を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 31)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 32は当たり判定がないチップ、32を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 32)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 33は当たり判定がないチップ、33を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 33)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 34は当たり判定がないチップ、34を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 34)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 35は当たり判定がないチップ、35を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 35)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 36は当たり判定がないチップ、36を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 36)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 37は当たり判定がないチップ、37を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 37)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 38は当たり判定がないチップ、38を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 38)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 39は当たり判定がないチップ、39を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 39)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 40は当たり判定がないチップ、40を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 40)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 41は当たり判定がないチップ、41を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 41)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 42は当たり判定がないチップ、42を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 42)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 43は当たり判定がないチップ、43を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 43)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 44は当たり判定がないチップ、44を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 44)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 45は当たり判定がないチップ、45を描画
				if (PrototypeChipData2[hChip][wChip].chipKind == 45)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 0, 16, 16, m_CastleGraph, TRUE);
				}
			}
		}
		break;
	}
}
