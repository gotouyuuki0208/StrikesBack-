//==========================
// 
// パーティクル処理[particle.h]
// Author Yuki Goto
//
//==========================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//include
#include"billboard.h"

//プレイヤークラスの定義
class CParticle :public CBillBoard
{
public:

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CParticle(int priority = PRIORITY);//コンストラクタ
	~CParticle() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CParticle* Create(D3DXVECTOR3 pos, D3DXCOLOR cor,int life,float Width, float Vertical, float speed);//生成

private:

	//メンバ関数
	D3DXVECTOR3 m_posmove;//位置の移動量
	D3DXVECTOR3 m_rotmove;//向きの移動量
	int m_nLife;//寿命
	int m_nTexIdx;//テクスチャの番号
	float m_cor;//色
	float m_Width;//横
	float m_Vertical;//縦
	float m_speed;//速度
};
#endif 
