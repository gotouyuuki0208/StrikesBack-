//==========================
// 
// ゲーム全体管理[GameManager.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//include
#include"player.h"

//前方宣言
class CDirection;
class CHitEnemy;

//クラスの定義
class CGameManager
{
public:

	//ゲームの状況
	enum class GAME
	{
		NONE = 0,	//ゲーム中
		CLEAR,		//ゲームクリア
		OVER,		//ゲームオーバー
	};

	//メンバ関数
	CGameManager();					//コンストラクタ
	~CGameManager();				//デストラクタ
	void Init();					//初期化処理
	void Uninit();					//終了処理
	void Update();					//更新処理
	void SetGame(GAME game);		//ゲームのクリア情報を設定
	GAME GetGame();					//ゲームのクリア情報を取得
	void ChangePlayGame(bool play);	//キャラクター操作の判定を変更
	bool GetPlayGame();				//遊べる状態か取得
	void SetDirection();			//演出中に変更
	bool GetDirection();			//演出中か取得
	int GetWave();					//現在のウェーブを取得
	void AddWave();					//ウェーブを増やす
	void AddActiveEnemy();			//行動してる敵の数を増やす
	void SubActiveEnemy();			//行動してる敵の数を減らす
	int GetActiveEnemy();				//行動中の敵の数を取得
private:

	//メンバ関数
	void SetTutorial();		//チュートリアルの設定
	void StartTutorial();	//ゲーム開始時の操作説明表示
	void EndTutorial();		//操作説明表示の終了
	void GetPlayerInfo();	//プレイヤーの情報を取得
	void SetCamera();		//カメラの設定
	void StartBossBattle();	//ボス戦開始時の演出
	void CmeraLookOn();		//カメラのロックオン
	void WaveUpdate();		//ウェーブの更新
	void JudgeEnemyBeing(); //敵が存在してるか判定

	//メンバ変数
	CPlayer* m_player;			//プレイヤーの情報
	CDirection* m_direction;	//演出の情報
	CHitEnemy* Enemy;

	GAME m_GameClear;			//ゲームのクリア情報
	bool m_Direction;			//演出中か判定
	bool m_PlayGame;			//ゲームを遊べるか判定(false:遊べない true:遊べる)
	bool m_GameStartTutorial;	//ゲームの開始時の操作説明を表示したか判定
	int m_count;				//フレーム数カウント
	bool m_CameraLookOn;		//カメラが敵をロックオンするか
	int m_NowWave;				//現在のウェーブ
	int m_ActiveEnemy;			//現在行動してる敵の数
	bool m_EnemyBeing;			//敵が存在してる
};

#endif