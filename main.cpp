#include <Novice.h>

const char kWindowTitle[] = "BGM";

// ゲームのシーンを定義
enum Scene {
    SCENE1, // シーン1
    SCENE2, // シーン2
    SCENE3, // シーン3
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // ライブラリ初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力用
    char keys[256] = { 0 };     // 今のキー状態
    char preKeys[256] = { 0 };  // 1フレーム前のキー状態

    // サウンドデータ読み込み
    int bgmScene1 = Novice::LoadAudio("./Resources/Sounds/title.mp3");   // シーン1用
    int bgmScene2 = Novice::LoadAudio("./Resources/Sounds/ketei.mp3");  // シーン2用
    int bgmScene3 = Novice::LoadAudio("./Resources/Sounds/cancel.mp3"); // シーン3用

    int playHandle = -1; // 再生中サウンドのハンドル
    int scene = SCENE1;  // 最初はシーン1から開始

    // ================= メインループ =================
    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();

        // 入力を更新（前のフレームの状態をコピー → 今の状態を取得）
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // ================= 更新処理 =================
        switch (scene) {
        case SCENE1:
            // サウンドが再生されていなければ再生開始
            if (!Novice::IsPlayingAudio(playHandle)) {
                playHandle = Novice::PlayAudio(bgmScene1, false, 1.0f);
            }
            // Spaceキーでシーン2へ移動
            if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE]) {
                scene = SCENE2;              // SCENE2に遷移
                Novice::StopAudio(playHandle); // 再生中の音を止める
            }
            break;

        case SCENE2:
            // Enterキーを押したら bgmScene2 を再生
            if (preKeys[DIK_RETURN] == 0 && keys[DIK_RETURN]) {
                playHandle = Novice::PlayAudio(bgmScene2, false, 1.0f);
            }

            // Spaceキーでシーン3へ移動
            if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE]) {
                scene = SCENE3;              // SCENE3に遷移
                Novice::StopAudio(playHandle); // 再生中の音を止める
            }
            break;

        case SCENE3:
            // Enterキーを押したら bgmScene3 を再生
            if (preKeys[DIK_RETURN] == 0 && keys[DIK_RETURN]) {
                playHandle = Novice::PlayAudio(bgmScene3, false, 1.0f);
            }

            // Spaceキーでシーン1へ戻る
            if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE]) {
                scene = SCENE1;              // SCENE1に遷移
                Novice::StopAudio(playHandle); // 再生中の音を止める
            }
            break;
        }

        // ================= 描画処理 =================
        switch (scene) {
        case SCENE1:
            // 紫色の背景
            Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xffaaaaff, kFillModeSolid);
            break;
        case SCENE2:
            // 緑色の背景
            Novice::DrawBox(0, 0, 1280, 720, 0.0f, GREEN, kFillModeSolid);
            Novice::ScreenPrintf(10, 40, "Press ENTER to play bgmScene2");
            break;
        case SCENE3:
            // 青色の背景
            Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLUE, kFillModeSolid);
            break;
        }

        // デバッグ情報を表示
        Novice::ScreenPrintf(10, 0, "Scene: %d", scene);
        Novice::ScreenPrintf(10, 20, "SPACE: change scene / ESC: exit");

        Novice::EndFrame();

        // ESCキーで終了
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE]) {
            break;
        }
    }

    // ライブラリ終了処理
    Novice::Finalize();
    return 0;
}