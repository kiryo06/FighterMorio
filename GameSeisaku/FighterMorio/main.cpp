#include "DxLib.h"
#include "game.h"
#include "SceneManager.h"
#include "resource.h"
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	AllocConsole();        // Debug用コンソール
	FILE* out = 0; 
	freopen_s(&out, "CON", "w", stdout); // stdout
	FILE* in = 0; 
	freopen_s(&in, "CON", "r", stdin);   // stdin
#endif
	// フルスクリーンでなく、ウィンドウモードで開くようにする
	ChangeWindowMode(Game::kDefaultWindowMode);

	SetWindowIconID(IDI_ICON1);
	SetWindowText("FighterMorio");

	// 画面のサイズを変更する。第三引数は色に使う情報量(ビット)
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kScreenBitNum);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* pSceneManager = new SceneManager();
	pSceneManager->Init();

	// ゲームループ
	while (ProcessMessage() == 0) // Windowsが行う処理を待つ必要がある
	{
		// 今回のループが始まった時間を覚えておく
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面全体をクリアする
		ClearDrawScreen();

		// ここにゲームの処理を書く
		pSceneManager->Update();
		pSceneManager->Draw();
		// 画面の切り替わりを待つ
		ScreenFlip();

		//リフレッシュ処理(-1ならエラー)
		if (ProcessMessage() < 0) { break; }

		//Debug.
#ifdef _DEBUG

		printf("ssa\n"); 

#endif // DEBUG
		//ループ終了処理
		if (CheckHitKey(KEY_INPUT_ESCAPE)) { break; }

		// 60FPSに固定
		while (GetNowHiPerformanceCount() - time < 16667);
	}

	WaitKey();				// キー入力待ち

	//終了処理

	DxLib_End();//Dxlib終了処理

#ifdef _DEBUG	//コンソールDebug用
	fclose(out); fclose(in); FreeConsole();//コンソール解放
#endif
	return 0;//プログラム終了
}