//==========================
// 
// ステージ管理[drawdebug.h]
// Author Yuki Goto
//
//==========================
#ifndef _STAGEMANAGER_H_
#define _STAGEMANAGER_H_

#include"darkbg.h"

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
	void StageReset();
private:

	//メンバ変数
	STAGE m_Stage;//ステージの番号
	bool m_Change;//ステージが切り替わったか判定
	CDarkBg* m_DarkBg;
	int m_Rast;
};

#endif