#pragma once
#include <map>
#include <string>
#include <vector>

/// <summary>
/// 入力系をつかさどるクラス
/// </summary>
class Input
{
private:

	/// <summary>
	/// 周辺機器種別
	/// </summary>
	enum class PeripheralType
	{
		keybd, // キーボード
		pad1 // パッド1
	};
	// 入力情報定義用
	struct InputState
	{
		PeripheralType periType;
		int id; // 入力のID
	};

	using InputTable_t = std::map < std::string, std::vector<InputState>>;
	using InputRecord_t = std::map < std::string, bool>;

	// 名前と実際の入力の対応表
	InputTable_t inputTable_;
	// 押されたかどうかを記録していくもの
	InputRecord_t current_;
	InputRecord_t last_;

public:
	Input();

	/// <summary>
	/// 入力状態を更新
	/// </summary>
	void Update();

	/// <summary>
	/// 押した瞬間を検出
	/// </summary>
	/// <param name="id">入力コード</param>
	/// <returns>true:押した瞬間 false:押してないor押しっぱなし</returns>
	bool IsTrigger(std::string key) const;
};

