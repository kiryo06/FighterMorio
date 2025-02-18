#pragma once
#include "MapData.h"
class Camera;
class Map
{
public:
	Map();
	~Map();
	/// <summary>
	/// 1-1_マップ情報初期化
	/// </summary>
	/// <param name="mapdata"></param>
	void Init(int mapNumber);
//	void Update_1();
//	void Update_2();
	void Draw(int mapNumber, Camera* camera);
private:
	int m_kChipWidth;				// マップチップの大きさ横軸
	int m_kChipHeight;				// マップチップの大きさ縦軸
	int m_kChipNumY;				// デバック用マップチップ、縦軸の数
	int m_kChipNumX;				// デバック用マップチップ、横軸の数
	int m_k1ChipNumY;				// 1-1マップチップ、縦軸の数
	int m_k1ChipNumX;				// 1-1マップチップ、横軸の数
	int m_k2ChipNumY;				// 1-2マップチップ、縦軸の数
	int m_k2ChipNumX;				// 1-2マップチップ、横軸の数
	int m_WallGraph;				// 構成マップチップ
	int m_HardBlockGraph;			// 壊れないマップチップの画像
	int m_SkyBackGroundGraph;		// 空の背景画像
	int m_dokanGraph;				// 土管のグラフィック
	int m_WorldGraph;				// ワールドの当たり判定のないもの
	int m_CastleGraph;				// 城(ゴール)
	// 原型チップデバック用データ
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// 原型チップ1-1データ
	MapDataFile::ChipData PrototypeChipData1[MapDataFile::k1ChipNumY][MapDataFile::k1ChipNumX] = {};
	// 原型チップ1-2データ
	MapDataFile::ChipData PrototypeChipData2[MapDataFile::k2ChipNumY][MapDataFile::k2ChipNumX] = {};
};