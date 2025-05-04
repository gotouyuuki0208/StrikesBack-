//==========================
// 
// 殴る敵[hitenemy.h]
// Author Yuki Goto
//
//==========================
#ifndef _HITENEMY_H_
#define _HITENEMY_H_

//include
#include "weakenemy.h"
#include "hpgauge3D.h"

//クラスの定義
class CHitEnemy :public CWeakEnemy
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CHitEnemy(int nPriority = PRIORITY);//コンストラクタ
	~CHitEnemy() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CHitEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	
private:

	//メンバ変数
	CHPGauge3D* m_HPGauge;//HPゲージの情報
};
#endif