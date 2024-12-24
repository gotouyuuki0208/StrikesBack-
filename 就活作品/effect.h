//==========================
// 
// エフェクト処理[effect.h]
// Author Yuki Goto
//
//==========================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//include
#include"billboard.h"

//プレイヤークラスの定義
class CEffect :public CBillBoard
{
public:
	//定数
	static const int PRIORITY;

	//メンバ関数
	CEffect(int nPriority = PRIORITY);//コンストラクタ
	~CEffect() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR cor,float Vertical, float Width);//生成
	
private:
	//メンバ変数
	static int m_nTexIdx;//テクスチャID
	int m_nLife;//寿命
	float cor;//色
	float m_Vertical;//縦
	float m_Width;//横
};
#endif 
