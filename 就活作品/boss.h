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
#include "weapon.h"
#include "bosshpgauge.h"

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
	static const float DUSH_DISTANCE;//走る距離
	static const float WALK_DISTANCE;//歩く距離
	static const float GUARD_DISTANCE;//守る距離
	static const float DUSH_SPEED;//走る速さ
	static const float WALK_SPEED;//歩く速さ
	
	//メンバ関数
	CBoss(int nPriority = PRIORITY);//コンストラクタ
	~CBoss() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBoss* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	void GrabChangeWeapon(CWeapon* weapon);//掴む武器を変える
private:

	//メンバ関数
	void Move();//プレイヤーへの移動
	void WeaponMove();//武器攻撃の移動処理
	void Attack();//攻撃処理
	void FindNearbyWeapons();//近い武器を探す
	float ChangeDirection();//向きの変更
	void ColisionHitAttack();//攻撃の当たり判定
	void ColisionWeaponAttack();//武器攻撃の当たり判定
	bool JudgeAttackable();//攻撃可能か判定
	void ChoiceAttack();//攻撃の種類を選択
	void ColisionWeapon();//武器との当たり判定
	bool MeasureDistance();//距離を測る
	void ResetStak();//スタックの情報を戻す
	void SetComboList();//コンボリストの生成
	void Push(MOTION_TYPE motion);//データの追加
	MOTION_TYPE Pop();//データの取り出し
	int RandomNum();//ランダムな数値を取得
	void Guard();//ガード処理
	void PlayerNearAction();//プレイヤーが近いときの行動
	void Count();//カウントする
	void MoveAction();//移動時の行動
	void ReleseWeapon();//武器を離す
	void MotionUpdate();
	void SetWeaponMotion(MOTION_TYPE motion);//武器所持時のモーションを設定

	//メンバ変数
	CWeapon* m_weapon;//武器の情報
	CBossHPGauge* m_BossHPGauge;
	bool m_Attack;//攻撃したか判定
	bool Attackable;//攻撃可能か判定
	int m_AttackCoolTime;//攻撃のクールタイム
	int m_FlameCount;//攻撃フレームのカウント
	int m_AttackNum;//攻撃回数
	MOTION_TYPE m_ComboList[3];//攻撃のコンボリスト
	MOTION_TYPE m_ComboStack[3];//攻撃コンボのスタック
	int m_StackIdx;//TOPの位置
	float m_Angle;//向き
	int m_NearCount;//プレイヤーが近づいた時の行動のカウント
	bool m_NearAction;//プレイヤーが近づいた時の行動をしているか判定
};
#endif