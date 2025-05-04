//==========================
// 
// ステージ管理[drawdebug.h]
// Author Yuki Goto
//
//==========================
#ifndef _STAGEMANAGER_H_
#define _STAGEMANAGER_H_

//include
#include"darkbg.h"
#include<list>
#include"objectgame.h"
#include"player.h"
#include"boss.h"
#include"playerhpgauge.h"
#include"bosshpgauge.h"

//クラスの定義
class CStageManager
{
public:
	enum class STAGE
	{
		STAGE_FIRST,//ステージ1
		STAGE_SECOND,//ステージ2
		STAGE_BOSS,//ボスステージ
	};

	//メンバ関数
	CStageManager();//コンストラクタ
	~CStageManager();//デストラクタ
	void SetStage();//ステージを設定
	STAGE GetStage();//ステージを取得
	bool GetChange();//切り替わり判定を取得
	void ChangeReset();//切り替わり判定をリセット
	void Uninit();//終了処理
	bool ChangeObject();//オブジェクト変更タイミング
	void StageReset();//
	void Load();//ステージのオブジェクト生成
	void DeleteAll();//全てのオブジェクトを削除
	void DeleteObj(CObjectgame& obj);//オブジェクトを削除
	void ChangeStage();//ステージの切り替え
	void HPGaugeUpdate();//プレイヤーのHPゲージの更新
private:

	//メンバ関数
	void FildLoad();//フィールドの情報を読み込む
	void EnemyLoad();//敵の配置情報を読み込む
	void BuildingLoad();//建物の情報を読み込む
	void WeaponLoad();//武器の情報を読み込む
	void ItemLoad();//アイテムの情報を読み込む

	//メンバ変数
	STAGE m_Stage;//ステージの番号
	bool m_Change;//ステージが切り替わったか判定
	CDarkBg* m_DarkBg;//暗転のための黒ポリゴン
	int m_Rast;//最終ステージの番号
	list<CObjectgame*> m_Obj;//オブジェクトリスト
	list<CObjectgame*>::iterator m_ObjIte;//オブジェクトリストイテレーター

	CPlayer* m_player;//プレイヤーの情報
	CPlayerHPGauge* m_PlalyerHPGauge;//プレイヤーのHPゲージの情報

	int m_playerlife;
};

#endif