#include "SceneChange.h"
#include "DxLib.h"

SceneChange::SceneChange():
	w(32),
	h(32),
	x(0),
	y(0),
	X(0),
	Y(0),
	ChangeDeath(false),
	ChangeClear(false),
	isSceneChange(false),
	m_FrameCounter(0)
{
}

SceneChange::~SceneChange()
{
}

void SceneChange::Init()
{
	if (ChangeClear)
	{
		y = 640;
	}
}

void SceneChange::Update()
{
	// クリアー時
	if (ChangeClear)
	{
		m_FrameCounter += 3;
		while (m_FrameCounter > 0)
		{
			if (m_FrameCounter >= 1)
			{
				y -= 64;
				if (y <= 0)
				{
					Y += 64;
					y = 640;
					x += 64;
					if (x >= 1324)
					{
						isSceneChange = true;
					}
				}
				m_FrameCounter -= 1;
			}
		}
	}
	// ゲームオーバー時
	if (ChangeDeath)
	{
		m_FrameCounter+= 3;
		while (m_FrameCounter > 0)
		{
			if (m_FrameCounter >= 1)
			{
				x += 64;
				if (x >= 1280)
				{
					X += 64;
					x = 0;
					y += 64;
					if (y >= 704)
					{
						isSceneChange = true;
					}
				}
				m_FrameCounter -= 1;
			}
		}
	}
}

void SceneChange::Draw()
{
	if (ChangeClear)
	{
		DrawBox(0, 0, Y, 640, 0x333333, TRUE);
		DrawBox(x, y, x + 64, 640, 0x333333, TRUE);
	}
	if (ChangeDeath)
	{
		DrawBox(0, 0, 1280, X, 0x333333, TRUE);
		DrawBox(0, y, x, y + 64, 0x333333, TRUE);
	}
}
