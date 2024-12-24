//==========================
// 
// ゲーム画面の処理[game.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAME_H_
#define _GAME_H_

//include
#include"scene.h"
#include"edit.h"
#include"player.h"
#include"boss.h"
#include"playerhpgauge.h"
#include"bosshpgauge.h"

//ゲームクラスの定義
class CGame :public CScene
{
public:

	//メンバ関数
	CGame();//コンストラクタ
	~CGame() override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
private:

	//メンバ関数
	void DebugSelect();//デバッグの種類を選択
	void UseEdit();//配置ツールの使用
	void ChangeStage();//ステージの切り替え
	void DisplayUI();//UI表示

	//メンバ変数
	CEdit* m_Edit;//オブジェクト配置クラスの情報
	CPlayer* m_player;//プレイヤーの情報
	CBoss* m_Boss;//ボスの情報
	CPlayerHPGauge* m_PlalyerHPGauge;//プレイヤーのHPゲージの情報
	CBossHPGauge* m_BossHPGauge;//ボスのHPゲージの情報
	int m_playerlife;
};

#endif 