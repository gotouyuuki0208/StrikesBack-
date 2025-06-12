//==========================
// 
// ステージ管理[drawdebug.h]
// Author Yuki Goto
//
//==========================
#ifndef _STAGEMANAGER_H_
#define _STAGEMANAGER_H_

//include
#include<list>
#include"objectgame.h"

//前方宣言
class CPlayer;
class CDarkBg;

//クラスの定義
class CStageManager
{
public:
	enum class STAGE
	{
		STAGE_NONE = 0,
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
	void StageReset();//ステージをリセット
	void Load();//ステージのオブジェクト生成
	void DeleteAll();//全てのオブジェクトを削除
	void DeleteObj(CObjectgame& obj);//オブジェクトを削除
	void ChangeStage();//ステージの切り替え
private:

	//メンバ関数
	void JsonBuildingLoad();
	void JsonEnemyLoad();
	void JsonFildLoad();
	void JsonWeaponLoad();
	void JsonItemLoad();

	//メンバ変数
	list<CObjectgame*> m_Obj;//オブジェクトリスト
	list<CObjectgame*>::iterator m_ObjIte;//オブジェクトリストイテレーター
	CDarkBg* m_DarkBg;//暗転のための黒ポリゴン
	CPlayer* m_player;//プレイヤーの情報
	STAGE m_Stage;//ステージの番号
	bool m_Change;//ステージが切り替わったか判定
	int m_Rast;//最終ステージの番号
};

#endif