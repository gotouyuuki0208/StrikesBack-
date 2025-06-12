//==========================
// 
// ボス戦開始時の黒背景処理[directionbg.h]
// Author Yuki Goto
//
//==========================
#ifndef _DIRECTIONBG_H_
#define _DIRECTIONBG_H_

//include
#include "object2D.h"

//クラスの定義
class CDirectionBg :public CObject2D
{
public:
	//定数
	static const int PRIORITY;

	//メンバ関数
	CDirectionBg(int nPriority = PRIORITY);//コンストラクタ
	~CDirectionBg()override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	static CDirectionBg* Create(D3DXVECTOR3 pos);//オブジェクト2D生成
	void EnterScreen();//画面に入る
	void ExitScreen();//画面から出る
private:

	//メンバ変数
	D3DXVECTOR3 m_FirstPos;//最初にいた位置
	int m_CountFlame;//フレーム数カウント用
	bool m_Delete;//画面にでたら消す判定
};

#endif 
