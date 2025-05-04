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
#include"boss.h"

//クラスの定義
class CGameManager
{
public:

	enum class GAME
	{
		NONE = 0,
		CLEAR,
		OVER,
	};
	

	//メンバ関数
	CGameManager();//コンストラクタ
	~CGameManager();//デストラクタ
	void a();
	void SetGame(GAME game);//ゲームのクリア情報を設定
	GAME GetGame();//ゲームのクリア情報を取得
	void Init();//初期化処理
	void Uninit();//終了処理
	void SetDirection();//演出の設定
	bool GetDirection();//演出中か取得
	void GetBossInfo();//ボスの情報を取得
	bool GetChange();//切り替わり判定を取得
	void SetChange();//切り替わり判定をリセット
private:

	//メンバ関数
	void GetPlayerInfo();//プレイヤーの情報を取得
	void SetCamera();//カメラが追従する対象を設定
	void StartBossBattle();//ボス戦開始時の演出

	//メンバ変数
	GAME GameClear;//ゲームのクリア情報
	CPlayer* m_player;//プレイヤーの情報
	CBoss* m_boss;//ボスの情報
	bool m_Direction;//演出中か判定
	bool m_StageChamge;//ステージが切り替わったか判定
	int m_count;
};

#endif