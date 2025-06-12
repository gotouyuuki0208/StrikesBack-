//==========================
// 
// 矢印表示[arrowUI.h]
// Author Yuki Goto
//
//==========================
#ifndef _ARROWUI_H_
#define _ARROWUI_H_

//include
#include "object3D.h"

//前方宣言
class CArrowPoint;

//クラスの定義
class CArrowUI :public CObject3D
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CArrowUI(int nPriority = PRIORITY);//コンストラクタ
	~CArrowUI() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CArrowUI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//オブジェクト生成
private:

	//メンバ関数
	void JudgeDraw();//描画するか判定
	void ChangeDirection();//向きの変更

	//メンバ変数
	int m_nTexIdx;//テクスチャの番号
	bool m_Draw;//描画判定
	CArrowPoint* m_ArrowPoint;
};
#endif