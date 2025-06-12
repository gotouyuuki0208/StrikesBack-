//==========================
// 
// ボスのHPゲージの枠[bossgaugeframe.h]
// Author Yuki Goto
//
//==========================
#ifndef _BOSSGAUGEFRAME_H_
#define _BOSSGAUGEFRAME_H_

//include
#include "object2D.h"

//クラスの定義
class CBossGaugeFrame :public CObject2D
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CBossGaugeFrame(int nPriority = PRIORITY);//コンストラクタ
	~CBossGaugeFrame() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBossGaugeFrame* Create(D3DXVECTOR3 pos, float vertical, float width);//オブジェクト生成
private:

	//メンバ関数
	void SetVtx();//頂点情報の設定

	//メンバ変数
	int m_nTexIdx;//テクスチャの番号
};
#endif