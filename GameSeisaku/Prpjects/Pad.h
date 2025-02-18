#pragma once

namespace Pad
{
	// プロトタイプ宣言

	// ///を関数の上で入力すると各要素の説明が書けるもののテンプレートが出る

	/// <summary>
	/// パッドの入力状態更新処理
	/// 1フレームに1回のみ呼び出す
	/// </summary>
	void Update();

	/// <summary>
	/// Press判定の取得
	/// パッドが1つの場合のみ対応
	/// </summary>
	/// <param name="button">判定を行いたいボタン</param>
	/// <returns>押されていたらtrue,押されていなかったらfalse</returns>
	bool IsPress(int button);

	/// <summary>
	/// Trigger判定(押された瞬間)の取得
	/// パッドが1つの場合のみ対応
	/// </summary>
	/// <param name="button">判定を行いたいボタン</param>
	/// <returns>押された瞬間ならtrue,それ以外はfalse</returns>
	bool IsTrigger(int button);
}