//==========================
// 
// 武器敵[weaponenemy.h]
// Author Yuki Goto
//
//==========================
#ifndef _WEAPONENEMY_H_
#define _WEAPONENEMY_H_

//include
#include "enemy.h"
#include "hpgauge3D.h"

//クラスの定義
class CWeaponEnemy :public CEnemy
{
public:
	//定数
	static const int PRIORITY;//描画順
	static const int NEAR_ACTION_COUNT;//プレイヤーが近いときにする行動の長さ
	static const int ATTACKFINISH_COOLTIME;//攻撃終了後のクールタイム
	static const float DUSH_DISTANCE;//走る距離
	static const float DUSH_SPEED;//走る速さ
	static const float WALK_DISTANCE;//歩く距離
	static const float WALK_SPEED;//歩く速さ

	//メンバ関数
	CWeaponEnemy(int nPriority = PRIORITY);//コンストラクタ
	~CWeaponEnemy() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CWeaponEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
private:

	//メンバ関数
	void Move();//プレイヤーへの移動
	void Count();//カウントする
	void MoveAction();//移動時の行動設定
	void Attack();//攻撃処理
	void ResetStak();//スタックの情報を戻す
	void SetComboList();//コンボリストの生成
	void Push(MOTION_TYPE motion);//データの追加
	MOTION_TYPE Pop();//データの取り出し
	float ChangeDirection();//向きの変更
	void ColisionWeaponAttack();//殴り攻撃の判定

//メンバ変数
	CHPGauge3D* m_HPGauge;//HPゲージの情報
	bool m_NearAction;//プレイヤーが近くにいるときの行動判定
	bool Attackable;//攻撃可能判定
	int m_NearCount;//プレイヤーが近くにいるときの行動カウント
	int m_AttackCoolTime;//攻撃のクールタイム
	int m_StackIdx;//TOPの位置
	MOTION_TYPE m_ComboList[3];//攻撃のコンボリスト
	MOTION_TYPE m_ComboStack[3];//攻撃コンボのスタック
	bool m_Attack;//攻撃判定
	float m_Angle;//向き
	int m_FlameCount;//攻撃のフレームカウント
};
#endif