#pragma once
class SystemEngineer
{
public:
	SystemEngineer();
	~SystemEngineer();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 描画設定処理
	/// </summary>
	void DrawSetUp();
	/// <summary>
	/// スコアを設定
	/// </summary>
	/// <param name="score">設定するスコア</param>
	/// <returns>設定されたスコア</returns>
	void SetScore(bool score){ IsScore = score; }
	/// <summary>
	/// スコアを取得
	/// </summary>
	/// <returns>現在のスコア</returns>
	int GetScore() const { return m_Score; }
	/// <summary>
	/// タイマーを取得
	/// </summary>
	/// <returns>現在のタイマー値</returns>
	int GetTimer() const { return m_Timer; }
	void SetBGM(bool bgm) { m_Bgm = bgm; }
	void SetStop(bool isStop) { m_IsStop = isStop; }
private:
	bool IsScore;					// スコアフラグ
	int m_Score;					// スコア
	int m_Timer;					// タイマー	
	int m_FrameCounter;				// カウンタ
	int m_fontHandle;				// フォントの情報
	int dsad;
	bool m_Bgm;
	bool m_IsStop;
};

