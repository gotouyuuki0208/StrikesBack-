//==========================
// 
// 操作説明管理[TutorialManager.h]
// Author Yuki Goto
//
//==========================
#ifndef _TUTORIALMANAGER_H_
#define _TUTORIALMANAGER_H_

//クラスの定義
class CTutorial
{
public:
	
	//メンバ関数
	CTutorial();//コンストラクタ
	~CTutorial();//デストラクタ
	bool GetTutorial();//説明を表示しているかを取得
	void StartTutorial();//説明を開始
	void FinishTutorial();//説明を終了
	void SetAction();//行動説明を表示した状態に変更
	void SetWeapon();//武器説明を表示した状態に変更
	void SetRecovery();//回復説明を表示した状態に変更
	bool GetAction();//行動説明を表示した状態に取得
	bool GetWeapon();//武器説明を表示した状態に取得
	bool GetRecovery();//回復説明を表示した状態に取得
private:
	//メンバ変数
	bool m_Tutorial;//説明表示判定
	bool m_Action;//行動説明
	bool m_Weapon;//武器説明
	bool m_Recovery;//回復説明
};

#endif