#pragma once
#include "game.h"
class TitlePlayMovie
{
public:
	TitlePlayMovie();
	~TitlePlayMovie();
	void Init();
	void Update();
	void Draw();
	void SetPlaySwitch(bool isPlay) { IsPlay = isPlay; }
private:
	int MovieGraphHandle;		// 動画ハンドル
	bool IsPlay;
};

