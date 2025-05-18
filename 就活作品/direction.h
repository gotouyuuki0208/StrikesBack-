//==========================
// 
// ボス戦演出の管理[direction.h]
// Author Yuki Goto
//
//==========================
#ifndef _DIRECTION_H_
#define _DIRECTION_H_

//前方宣言
class CDirectionBg;
class CBoss;

//クラスの定義
class CDirection
{
public:

	//メンバ関数
	CDirection();//コンストラクタ
	~CDirection();//デストラクタ
	void Update();//更新処理
	bool GetEnd();//終了判定を取得
	void GetBossInfo();//ボスの情報を取得
private:
	//メンバ関数
	void UpdateBg();//背景更新
	void BossEndMotion();//ボスのモーションが終了したか判定

	//メンバ変数
	CDirectionBg* m_Bg[2];//背景の情報
	CBoss* m_boss;//ボスの情報
	bool m_ExistenceBg;//画面内に背景があるか判定
	bool m_End;//演出終了判定
	bool m_BossMotionEnd;//ボスのモーション終了判定
};

#endif