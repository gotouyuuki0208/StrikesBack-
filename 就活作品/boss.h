//==========================
// 
// ボス[boss.h]
// Author Yuki Goto
//
//==========================
#ifndef _BOSS_H_
#define _BOSS_H_

//include
#include "enemy.h"

//前方宣言
class CWeapon;
class CBossHPGauge;
class CBossStateBase;
class CStateMachine;

//クラスの定義
class CBoss :public CEnemy
{
public:
	//定数
	static const int PRIORITY;//描画順
	static const int GUARD_PROBABILITY;//プレイヤーが素手の時ガードする確率
	static const int NEAR_ACTION_COUNT;//プレイヤーが近いときにする行動の長さ
	static const int HITATTACK_PROBABILITY;//プレイヤーが近いときに殴る確率
	static const int WEAPONATTACK_PROBABILITY;//武器が近いときに武器攻撃する確率
	static const int ATTACKFINISH_COOLTIME;//攻撃終了後のクールタイム
	static const float GUARD_DISTANCE;//守る距離
	
	//メンバ関数
	CBoss(int nPriority = PRIORITY);//コンストラクタ
	~CBoss() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBoss* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	void GrabChangeWeapon(CWeapon* weapon);//掴む武器を変える
	bool GetWeapon();//武器を所持しているか判定
	void ChangeState(CBossStateBase* NewState);//状態を変更
	void ChoiceAttack();//攻撃の種類を選択
	bool GetNextAttack();//次の攻撃方法を取得
	void WeaponMove();//武器攻撃の移動処理
	bool GetWeaponType();//武器のタイプを取得
	void hit(D3DXVECTOR3 pos, int damage, MOTION_TYPE hitmotion);//攻撃被弾処理
	bool JudgeGuard();//ガードする距離にいるか判定
	void PlayerNearAction();//プレイヤーが近いときの行動
	bool GetGuard();//ガードするか取得
	void GuardReset();//ガードの情報をリセット
private:

	//メンバ関数
	void FindNearbyWeapons();//近い武器を探す
	bool MeasureDistance();//距離を測る
	int RandomNum();//ランダムな数値を取得
	void ColisionWeapon();//武器との当たり判定
	void MotionUpdate();//モーションの更新
	void ReleseWeapon();//武器を離す
	void WeaponDamage();//武器の耐久値を減らす
	void ColisionWeaponAttack();//武器攻撃の当たり判定
	void InitHaveWeapon();//最初に武器を持たせる

	//メンバ変数
	CWeapon* m_weapon;//武器の情報
	CWeapon* m_HaveWeapon;//持ってる武器
	CStateMachine* m_StateMachine;//状態管理
	int m_FlameCount;//攻撃フレームのカウント
	int m_NearCount;//プレイヤーが近づいた時の行動のカウント
	bool m_NearAction;//プレイヤーが近づいた時の行動をしているか判定
	bool m_NextAttack;//次の攻撃(false:素手 true:武器)
	bool m_Guard;//ガード判定

};
#endif