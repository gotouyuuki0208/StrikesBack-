//==========================
// 
// キャラクター[character.h]
// Author Yuki Goto
//
//==========================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//include
#include "motionmodel.h"
#include "collisionvisual.h"

//クラスの定義
class CCharacter :public CMotionModel
{
public:
	
	enum class STATE
	{
		NEUTRAL = 0,//通常
		ATTACK,//攻撃
		MOVE,//移動
		GUARD,//ガード
		AVOIDANCE,//回避
		GRAB,//掴まれる
		MAX,
	};

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CCharacter(int nPriority = PRIORITY);//コンストラクタ
	~CCharacter() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	void DamegeBlow(D3DXVECTOR3 pos);//被弾時の吹き飛び処理
	void SetLife(int life);//寿命の設定
	int GetLife();//寿命の取得
	bool GetDamage();//ダメージ判定の取得
	void SetDamage(bool damege);//ダメージ判定の変更
	void SetState(STATE state);//状態の設定
	STATE GetState();//状態の取得
	void DamageVisual(int PartsNum, float Radius);//被弾時の当たり判定の可視化
	void SetVisual();//当たり判定の可視化処理
	void SetDamegeBlow(D3DXVECTOR3 move);//吹き飛び用の移動値設定
	D3DXVECTOR3& GetDamegeBlow();//吹き飛び用の移動値取得
private:

	//メンバ変数
	STATE m_state;//現在の状態
	int m_nLife;//寿命
	bool m_Damage;//ダメージ状態判定
	D3DXVECTOR3 m_DamageMove;//吹き飛び用の移動値
	CCollisionVisual* m_visual;//当たり判定の可視化
};
#endif