//==========================
// 
// 操作説明管理[TutorialManager.h]
// Author Yuki Goto
//
//==========================
#ifndef _TUTORIALMANAGER_H_
#define _TUTORIALMANAGER_H_

//前方宣言
class CTutorialPopup;
class CTutorialBg;

//クラスの定義
class CTutorialManager
{
public:
	
	//メンバ関数
	CTutorialManager();//コンストラクタ
	~CTutorialManager();//デストラクタ
	void ActionTutorialDisplay();//行動の説明を表示
	void WeaponTutorialDisplay();//武器の説明を表示
	void RecoveryTutorialDisplay();//回復の説明を表示
	void TutorialDelete();//武器の説明を消す
	void Reset();//情報リセット
private:
	//メンバ変数
	bool m_Action;//行動説明
	bool m_Weapon;//武器説明
	bool m_Recovery;//回復説明

	CTutorialPopup* m_pTutorialPopup;//ポップアップ表示するチュートリアルの情報
	CTutorialBg* m_pTutorialBg;//背景の情報
};

#endif