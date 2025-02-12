#include "Pad.h"
#include "DxLib.h"

namespace
{
	// 現在のフレームのパッド入力
	int padInput = 0;
	// ひとつ前のフレームのパッド入力
	int lastInput = 0;
}

namespace Pad
{
	void Update()
	{
		// 前のフレームに押されていたボタンの情報を覚えておく
		lastInput = padInput;
		// このフレームに押されているボタンの情報を取得する
		padInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

#if false

	// Press判定の取得
	// 戻り値:押されていたらtrue,押されていなかったらfalse
	// 引数:判定を行いたいボタン
	bool IsPress(int button)
	{
		if (padInput & button)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	// Trigger判定の取得
	bool IsTrigger(int button)
	{
		// 押されていなかったらそりゃfalse
		if (!(padInput & button))
		{
			return false;
		}

		// 前のフレームにボタンが押されていなければ押された瞬間だと判定できる
		// 前のフレームに押されているならそれもfalse
		if (lastInput & button)
		{
			return false;
		}
		else
		{
			// 厳選されたTriggerをお届け
			return true;
		}
	}

#else
	// Press判定の取得
	// 戻り値:押されていたらtrue,押されていなかったらfalse
	// 引数:判定を行いたいボタン
	bool IsPress(int button)
	{
		// 押されてたらtrueで戻り値もtrueだからこれでいいよね
		return (padInput & button);
	}

	// Trigger判定の取得
	bool IsTrigger(int button)
	{
		// 押されていればtrueそうでないならfalse
		// ちょっと分かりやすい
		bool isNow = (padInput & button);
		bool isLast = (lastInput & button);
		return (isNow && !isLast);
	}
#endif
}