#include "SystemEngineer.h"
#include "DxLib.h"

namespace
{
	constexpr int kAddScore = 100;						// スコア加算値
	constexpr int kTimer = 500;							// タイマー
	constexpr int kTimerX = 1000;						// タイマー表示位置X
	constexpr int kTimerY = 30;							// タイマー表示位置Y
	constexpr int kScoreX = 1000;						// スコア表示位置X
	constexpr int kScoreY = 60;							// スコア表示位置Y
	constexpr const char* kFontName = "MS ゴシック";	// フォント名
	constexpr int kFontSize = 25;						// フォントサイズ
	constexpr const char* kBGMFile = "data/Sound/BGM_3_Maker.mp3";			// BGMファイル
}

SystemEngineer::SystemEngineer():
	IsScore(false),
	m_Score(0),
	m_Timer(kTimer),
	m_FrameCounter(0),
	m_fontHandle(0),
	dsad(0),
	m_Bgm(false),
	m_IsStop(false)
{
}

SystemEngineer::~SystemEngineer()
{
	DeleteFontToHandle(m_fontHandle);
	delete kBGMFile;
}

void SystemEngineer::Init()
{
	m_fontHandle = CreateFontToHandle("kFontName", kFontSize, -1, DX_FONTTYPE_ANTIALIASING);
	if (!m_Bgm)
	{
		PlayMusic(kBGMFile, DX_PLAYTYPE_LOOPBIT);
	}
	PlayMusic(kBGMFile, DX_PLAYTYPE_LOOPBIT);
	//PlayMusicByMemImage(void kBGMFile, )
}

void SystemEngineer::Update()
{
	if (m_Bgm)
	{
		StopMusic();
	}
	if (m_IsStop)
	{
		return;
	}
	m_FrameCounter++;
	if (m_FrameCounter >= 60)
	{
		m_Timer--;
		m_FrameCounter -= 60;
	}
	if (IsScore)
	{
		dsad += kAddScore;
		IsScore = false;
	}
	if (m_Score < dsad)
	{
		m_Score += 3;
		if (m_Score > dsad)
		{
			m_Score = dsad;
		}
		return;
	}
}

void SystemEngineer::Draw()
{
	DrawSetUp();
}

void SystemEngineer::DrawSetUp()
{
	// 残り時間の表示
	if (m_Timer >= 0 && m_Timer < 10)
	{
		//DrawFormatString(kTimerX, kTimerY, 0x556b2f, "残り時間:00%d", m_Timer, true);
		DrawFormatStringToHandle(kTimerX, kTimerY, 0x556b2f, m_fontHandle, "残り時間:00%d", m_Timer);
	}
	else if (m_Timer >= 10 && m_Timer < 100)
	{
		//DrawFormatString(kTimerX, kTimerY, 0x556b2f, "残り時間:0%d", m_Timer, true);
		DrawFormatStringToHandle(kTimerX, kTimerY, 0x556b2f, m_fontHandle, "残り時間:0%d", m_Timer);
	}
	else if (m_Timer >= 100 && m_Timer < 1000)
	{
		//DrawFormatString(kTimerX, kTimerY, 0x556b2f, "残り時間:%d", m_Timer, true);
		DrawFormatStringToHandle(kTimerX, kTimerY, 0x556b2f, m_fontHandle, "残り時間:%d", m_Timer);
	}
	// スコアの表示
	if (m_Score >= 0 && m_Score < 10)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff8c00, "スコア:00000%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff8c00, m_fontHandle, "スコア:00000%d", m_Score, true);
	}
	else if (m_Score >= 10 && m_Score < 100)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff8c00, "スコア:0000%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff8c00, m_fontHandle, "スコア:0000%d", m_Score, true);
	}
	else if (m_Score >= 100 && m_Score < 1000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff8c00, "スコア:000%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff8c00, m_fontHandle, "スコア:000%d", m_Score, true);
	}
	else if (m_Score >= 1000 && m_Score < 10000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff8c00, "スコア:00%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff8c00, m_fontHandle, "スコア:00%d", m_Score, true);
	}
	else if (m_Score >= 10000 && m_Score < 100000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff8c00, "スコア:0%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff8c00, m_fontHandle, "スコア:0%d", m_Score, true);
	}
	else if (m_Score >= 100000 && m_Score < 1000000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff8c00, "スコア:%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff8c00, m_fontHandle, "スコア:%d", m_Score, true);
	}
	else
	{
		DrawString(kScoreX, kScoreY, "スコア:oversukoa",0xff8c00,true);
	}
#ifdef _DEBUG
	DrawFormatString(kScoreX, 90, 0xff0000, "スコア:%d", m_Score, true);
#endif // _DEBUG
}
