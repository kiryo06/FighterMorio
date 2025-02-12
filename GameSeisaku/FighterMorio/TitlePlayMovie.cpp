#include "TitlePlayMovie.h"
#include "DxLib.h"

TitlePlayMovie::TitlePlayMovie():
    MovieGraphHandle(-1),
    IsPlay(false)
{
}

TitlePlayMovie::~TitlePlayMovie()
{
    DeleteGraph(MovieGraphHandle);
}

void TitlePlayMovie::Init()
{
    // 動画ファイルを開く
    MovieGraphHandle = LoadGraph("data/image/Title_2.mp4");
    PlayMovieToGraph(MovieGraphHandle,2);
    //PlayMovie("data/image/Title_2.mp4",0,0);
}

void TitlePlayMovie::Update()
{
    //// 動画の再生状態を更新
    //if (!IsPlay)
    //{
    //    if (MovieGraphHandle != -1 && GetMovieStateToGraph(MovieGraphHandle) == DX_MOVIEPLAYTYPE_BCANCEL)
    //    {
    //        // 再生が終了したら再生をリセット
    //        SeekMovieToGraph(MovieGraphHandle, 0);
    //        PlayMovieToGraph(MovieGraphHandle);
    //    }
    //}
}

void TitlePlayMovie::Draw()
{
    // 動画を描画
    DrawGraph(0, 0, MovieGraphHandle, TRUE);
   // DrawRectExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, );
   // DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, MovieGraphHandle, TRUE);
}
