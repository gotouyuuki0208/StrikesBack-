//==========================
// 
// 殴る敵[hitenemy.h]
// Author Yuki Goto
//
//==========================
#ifndef _HITENEMY_H_
#define _HITENEMY_H_

//include
#include "enemy.h"
#include "hpgauge3D.h"

//クラスの定義
class CHitEnemy :public CEnemy
{
public:
	//定数
	static const int PRIORITY;//描画順
	static const int NEAR_ACTION_COUNT;//プレイヤーが近いときにする行動の長さ
	static const int ATTACKFINISH_COOLTIME;//攻撃終了後のクールタイム
	
	
	

	//メンバ関数
	CHitEnemy(int nPriority = PRIORITY);//コンストラクタ
	~CHitEnemy() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CHitEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	
private:

	//メンバ関数
	void Move();//プレイヤーへの移動
	void Count();//カウントする
	void Attack();//攻撃処理
	
	void ColisionHitAttack();//武器攻撃の当たり判定

	//メンバ変数
	CHPGauge3D* m_HPGauge;//HPゲージの情報
	bool m_NearAction;//プレイヤーが近くにいるときの行動判定
	
	int m_NearCount;//プレイヤーが近くにいるときの行動カウント
	int m_AttackCoolTime;//攻撃のクールタイム
	bool m_Attack;//攻撃判定
	int m_FlameCount;//攻撃のフレームカウント
};
#endif