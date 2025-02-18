#pragma once
#include "MapData.h"
#include <list>

class Map;
class Camera;
class Kuribou;
class SystemEngineer;
class Player
{
public:
	Player();
	~Player();
	/// <summary>
	/// プレイヤーの初期化
	/// </summary>
	/// <param name="mapNumber">マップ番号</param>
	void Init(int mapNumber, SystemEngineer* pSE);
	/// <summary>
	/// プレイヤーの更新
	/// </summary>
	/// <param name="Kuribou">敵キャラクターのリスト</param>
	/// <param name="mapNumber">マップ番号</param>
	void Update(Camera* camera, std::list<Kuribou*>& Kuribou, int mapNumber);
	/// <summary>
	/// 現在のプレイヤー位置とマップの衝突判定を行い、修正されたvelocity（移動ベクトル）を返す
	/// </summary>
	/// <param name="mapNumber">マップ番号</param>
	/// <returns>修正された移動ベクトル</returns>
	VECTOR CheckPlayerHitWithMap(int mapNumber);
	/// <summary>
	/// プレイヤーとマップの衝突判定
	/// </summary>
	/// <param name="mapNumber">マップ番号</param>
	/// <param name="checkPos">チェックする位置</param>
	/// <param name="hChip">マップチップの高さ</param>
	/// <param name="wChip">マップチップの幅</param>
	/// <returns>衝突しているかどうか</returns>
	bool IsHitPlayerWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip);
	/// <summary>
	/// プレイヤーと敵の衝突判定
	/// </summary>
	/// <param name="Kuribou">敵キャラクター</param>
	/// <param name="checkPos">チェックする位置</param>
	/// <returns>衝突しているかどうか</returns>
	bool IsHitPlayerAndEnemy(Kuribou* Kuribou, const VECTOR& checkPos);
	/// <summary>
	/// プレイヤーと敵の側面衝突判定
	/// </summary>
	/// <param name="Kuribou">敵キャラクター</param>
	/// <param name="checkPos">チェックする位置</param>
	/// <returns>側面衝突しているかどうか</returns>
	bool IsHitPlayerAndEnemySide(Kuribou* Kuribou, const VECTOR& checkPos);
	/// <summary>
	/// 頭上に障害物があるか確認
	/// </summary>
	/// <param name="mapNumber">マップ番号</param>
	void CheckIsTopHit(int mapNumber);
	/// <summary>
	/// 地面に足がついているか確認
	/// </summary>
	/// <param name="mapNumber">マップ番号</param>
	void CheckIsGround(int mapNumber);
	/// <summary>
	/// 敵の左側に衝突しているか確認
	/// </summary>
	/// <param name="Kuribou">敵キャラクター</param>
	bool CheckIsEnemyTopHit(Kuribou* Kuribou);
	/// <summary>
	/// 敵の右側に衝突しているか確認
	/// </summary>
	/// <param name="Kuribou">敵キャラクター</param>
	bool ChickIsEnemyLeftHit(Kuribou* Kuribou);
	/// <summary>
	/// プレイヤー描画
	/// </summary>
	/// <param name="mapNumber">マップ番号</param>
	/// <param name="camera">カメラオブジェクト</param>
	bool ChickIsEnemyRightHit(Kuribou* Kuribou);
	/// <summary>
	/// プレイヤー描画
	/// </summary>
	/// <param name="mapNumber">マップ番号</param>
	/// <param name="camera">カメラオブジェクト</param>
	void Draw(int mapNumber, Camera* camera);
	//  bool IsHitMapChipKind(auto chip, const VECTOR& checkPos);
	/// <summary>
	/// プレイヤーの位置を取得
	/// </summary>
	/// <returns>プレイヤーの位置</returns>
	VECTOR GetPlayerPos() const { return pos; }
	/// <summary>
	/// プレイヤーの方向を取得
	/// </summary>
	/// <returns>プレイヤーの方向</returns>
	VECTOR GetPlayerDir() const { return dir; }
	/// <summary>
	/// プレイヤーが敵に衝突したかどうかを設定
	/// </summary>
	/// <param name="isdeath">衝突したかどうかのフラグ</param>
	/// <returns>設定されたフラグ</returns>
	int GetPlayerDeath() const { return playerDeath; }
	bool GetDeath() const { return isDeath; }
	bool GetClear() const { return isClear; }
	void SetStop(bool isStop) { m_IsStop = isStop; }
private:
	Map* m_pMap;
	Camera* m_pCamera;
	SystemEngineer* m_pSystemEngineer;
	float w, h;					// プレイヤーの幅と高さ
	float fallSpeed;			// 落下速度
	VECTOR pos;                 // プレイヤーの位置
	VECTOR dir;					// 方向ベクトル
	VECTOR velocity;            // 移動ベクトル
	bool isGround;              // 地面に足がついているかどうか
	bool isHitTop;              // 頭上に障害物があるかどうか
	int playerDeath;			// プレイヤーが死んだ回数
	bool isDeath;				// プレイヤーが死んだかどうか
	bool isClear;				// プレイヤーがクリアしたかどうか
	bool GameoverJump;
	bool GameOverInversion;
	bool m_IsLeft;
	bool m_IsRight;
	bool m_IsStop;
	int m_FrameCounter;
	int mapChip;                // マップチップ
	int _isHit;                 // 衝突フラグ
	int m_PlayerPosXback;
	int m_PlayerGraph;			// プレイヤーグラフィック
	int m_GoolGraph;
	float m_RunSpeed;
	int m_Graph_;
	int m_kChipNumY;
	int m_kChipNumX;
	int m_k1ChipNumY;
	int m_k1ChipNumX;
	int m_k2ChipNumY;
	int m_k2ChipNumX;
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData1[MapDataFile::k1ChipNumY][MapDataFile::k1ChipNumX] = {};
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData2[MapDataFile::k2ChipNumY][MapDataFile::k2ChipNumX] = {};
};
