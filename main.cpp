#include <Novice.h>
#include <cstdio>

const char kWindowTitle[] = "Clock Timer";

enum Scene {
	TITLE,
	GAME1,// ゲーム本編（ステージ1）
	CLEAR,// クリア画面
};
int scene = TITLE;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Novice::Initialize(kWindowTitle, 1280, 720);

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// 数字画像をロード
	int numberGrahs[10] = {};
	for (int i = 0; i < 10; i++) {
		char filePath[64];
		snprintf(filePath, sizeof(filePath), "./Resources/%d.png", i); // 安全な関数
		numberGrahs[i] = Novice::LoadTexture(filePath);
	}
	const int graphWidth = 71;
	int frame = 0;// フレームカウント
	int seconds = 0; // 秒数

	int LIVEs = 20;
	

	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();

		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// 更新処理
		///
		switch (scene)
		{
		case TITLE:
			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
				scene = GAME1;
				frame = 0; // タイマーをリセット
				seconds = 0;
			}
			break;

		case GAME1:
			frame++;
			seconds = frame / 60; // ここの値を変更

			if (seconds >= 60) {
				scene = CLEAR;
			}
			

			if(preKeys[DIK_BACKSPACE] == 0 && keys[DIK_BACKSPACE] != 0)
			{
				LIVEs -= 1;
			}
			break;

		case CLEAR:
			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
				scene = TITLE;
			}
			break;
		}

		///
		/// 描画処理
		///
		switch (scene)
		{
		case TITLE:
			Novice::ScreenPrintf(50, 50, "TITLE SCREEN");
			Novice::ScreenPrintf(50, 70, "Press SPACE to start the game.");
			break;

		case GAME1: {
			// 桁ごとに分解
			int numbersArray[2];
			numbersArray[0] = seconds / 10; // 十の位
			numbersArray[1] = seconds % 10; // 一の位

			for (int i = 0; i < 2; i++) {
				Novice::DrawSprite(
					graphWidth * i, 0,
					numberGrahs[numbersArray[i]],
					0.5f, 0.5f, 0.0f, WHITE
				);
			}
			Novice::ScreenPrintf(50, 70, "Seconds: %d", LIVEs);
			Novice::ScreenPrintf(50, 50, "Seconds: %d", seconds);
			break;
		}
		case CLEAR:
			Novice::ScreenPrintf(500, 350, "GAME CLEAR!");
			Novice::ScreenPrintf(450, 370, "Press SPACE to return to title.");
			break;
		}

		Novice::EndFrame();

		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	Novice::Finalize();
	return 0;
}