#pragma once
#include "MapData.h"
class Map;
class Camera;
class GroundRectangle_HitJudgement
{
public:
	GroundRectangle_HitJudgement();
	~GroundRectangle_HitJudgement();
	/// <summary>
	/// 矩形の初期化
	/// </summary>
	void Init(int mapNumber);
	/// <summary>
	/// 矩形とマップの当たり判定
	/// </summary>
	/// <param name="isHitWithMapY">横軸の変数</param>
	/// <param name="isHitWithMapX">縦軸の変数</param>
	/// <returns></returns>
	bool IsHitBoxWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip);
	/// <summary>
	/// 頭上がぶつかっているか見る
	/// </summary>
	void CheckIsTopHit(int mapNumber);
	/// <summary>
	/// 地面に接地しているか見る
	/// </summary>
	void CheckIsGround(int mapNumber);
	/// <summary>
	/// 左の壁に接地しているか見る
	/// </summary>
	void CheckIsLeft(int mapNumber);
	/// <summary>
	/// 右の壁に接地しているか見る
	/// </summary>
	void CheckIsRight(int mapNumber);
	/// <summary>
	/// 矩形描画
	/// </summary>
	void Draw(int mapNumber, Camera* camera);
	VECTOR GetPlayerPos() { return pos; }
	VECTOR GetPlayerDir() { return dir; }
private:
	float w, h;					// 幅、高さ
	float fallSpeed;			// プレイヤーの落下速度。ジャンプ時は反転する
	float workSpeed;			// 移動速度
	VECTOR pos;					// 座標 横：中心　縦：中心
	VECTOR dir;					// 座標の移動方向
	VECTOR velocity;			// 速度の計算等
	bool isGround;				// プレイヤーが接地中か
	bool isHitTop;				// プレイヤーの頭が天井に当たっているか
	bool isLeft;				// 敵が左に当たったか
	bool isRight;				// 敵が右に当たったか
	int mapChip;				// マップの判別
	int HitBox;					// 当たっているかどうか
	int m_kChipNumY;			// マップの大きさ横軸デバック
	int m_kChipNumX;			// マップの大きさ縦軸デバック
	int m_k1ChipNumY;			// マップの大きさ横軸1-1
	int m_k1ChipNumX;			// マップの大きさ縦軸1-1
	int m_k2ChipNumY;			// マップの大きさ横軸1-2
	int m_k2ChipNumX;			// マップの大きさ縦軸1-2
	Map* m_map;
	Camera* m_camera;
	MapDataFile::ChipData PrototypeChipData0[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};			// デバック原型チップデータ
	MapDataFile::ChipData PrototypeChipData1[MapDataFile::k1ChipNumY][MapDataFile::k1ChipNumX] = {};		// 1-1原型チップデータ
	MapDataFile::ChipData PrototypeChipData2[MapDataFile::k2ChipNumY][MapDataFile::k2ChipNumX] = {};		// 1-2原型チップデータ
};