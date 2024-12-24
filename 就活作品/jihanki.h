//==========================
// 
// 自販機[jihanki.h]
// Author Yuki Goto
//
//==========================
#ifndef _JIHANKI_H_
#define _JIHANKI_H_

//include
#include "objectX.h"
#include "collisionvisual.h"

//クラスの定義
class CJihanki :public CObjectX
{
public:
	//定数
	static const int PRIORITY;//描画順
	static const int MAX_LIFE;//寿命の最大値

	//メンバ関数
	CJihanki(int nPriority = PRIORITY);//コンストラクタ
	~CJihanki() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CJihanki* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//オブジェクト生成
	void Damage(int Damage);//ダメージ処理
	void DamageVisual(D3DXVECTOR3 pos,float radius);//攻撃の当たり判定
	void DamageParticle();//被弾時にパーティクルを出す処理
private:
	//メンバ関数
	void ColisionPlayer();//プレイヤーとの当たり判定

	//メンバ変数
	int m_nModelIdx;//テクスチャの番号
	int m_Life;//寿命
	CCollisionVisual* m_visual[2];//当たり判定の可視化
};
#endif