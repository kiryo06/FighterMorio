//#include "Input.h"
//#include <DxLib.h>
//#include <stdexcept>
//
//// カッコに何も入ってないときは0で初期化されてる
//Input::Input()
//{
//	// 入力と名前の対応表を作る
//	inputTable_["next"] = { {PeripheralType::keybd, KEY_INPUT_RETURN},
//							{PeripheralType::pad1, PAD_INPUT_A} };
//	inputTable_["pause"] = { {PeripheralType::keybd, KEY_INPUT_P},
//							{PeripheralType::pad1, PAD_INPUT_START} };
//}
//
//void Input::Update()
//{
//	// 前回のフレームの入力を取っておく
//	last_ = current_;
//
//	char keyState[256];
//	int padInput = GetJoypadInputState(DX_INPUT_PAD1);
//	// 入力をとる
//	GetHitKeyStateAll(keyState);
//	// テーブルに記憶されたすべての入力をチェックする
//	for (const auto& keyValue : inputTable_)
//	{
//		// 出てきたキーイベントに対し、
//		const auto& key = keyValue.first;
//		current_[key] = false;
//		// それぞれの入力形式でチェックする
//		for (const auto& input : keyValue.second)
//		{
//			switch (input.periType)
//			{
//			case PeripheralType::keybd:
//				current_[keyValue.first] = current_[key] || keyState[input.id];
//				break;
//			case PeripheralType::pad1:
//				current_[keyValue.first] = current_[key] || (input.id & padInput);
//				break;
//			default:
//				break;
//			}
//		}
//	}
//}
//
//bool Input::IsTrigger(std::string key) const
//{
//	if (!inputTable_.contains(key))
//	{
//		throw std::runtime_error("キーが存在しない");
//	}
//
//	// idが前回押されていなくて、現在押されている時にtrueを返す
//	// []演算子ではなく、at(key)を使うこと！！！！！
//	return (current_.at(key) && !last_.at(key));
//}
