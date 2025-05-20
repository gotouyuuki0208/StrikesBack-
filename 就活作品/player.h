//==========================
// 
// プレイヤー処理[player.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//include
#include "character.h"
#include "playerstate.h"

//前方宣言
class CEnemy;
class CWeapon;
class CStateMachine;

//クラスの定義
class CPlayer :public CCharacter
{
public:

	//定数
	static const int PRIORITY;//描画順
	static const int MAX_LIFE;//寿命の最大値
	static const float MOVE_VALUE;//移動
	static const float AVOIDANCE_VALUE;//回避の移動値
	static const float DASH_VALUE;//ダッシュ
	static const float JUMP_VALUE;//ジャンプ
	static const float GRAVITY_VALUE;//重力
	static const float INERTIA_VALUE;//慣性
	static const float ROT_VALUE;//向き
	static const float CHARA_WIDTH;//キャラクターのXサイズ
	static const float CHARA_HEIGHT;//キャラクターのYサイズ

	//メンバ関数
	CPlayer(int nPriority = PRIORITY);//コンストラクタ
	~CPlayer() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成

	void AddItem();//アイテムの数を増やす
	void GetBoss(CEnemy* boss);//ボスを取得
	bool GetHaveWeapon();//武器所持判定
	void DeleteWeapon();//武器を消す
	void ChangeState(CPlayerStateBase* NewState);//状態を変更
	void AttackMove();//攻撃時の移動処理
	void Move();//移動処理
	void InputMove();//移動の入力処理
	void CorrectionAngle();//角度の補正
	void Avoidance();//回避
	void PickUpWeapon();//武器を拾う
	void ReleaseWeapon();//武器を手放す
	bool GetWeaponType();//武器の種類を取得
	void ThrowWeapon();//武器を投げる
	void hit(D3DXVECTOR3 pos,int damage);//攻撃被弾処理
	void ResetDamageNum();//被弾回数初期化
	int GetDamageNum();//被弾回数取得
	void HitEnemy(int PartsNum);//敵を殴るときの当たり判定
	void WeaponHitEnemy();//敵を武器で殴るときの当たり判定
	void CollisionJihankiAttack();//自販機に攻撃時の当たり判定
	void RecoveryLife();//ライフの回復
	bool GetWeaponBreak();//武器が壊れたか取得
	void BreakReset();//武器破壊判定をリセット
	void StageChangeState();//ステージ変更時のステートの変更
private:
	
	//メンバ関数
	void CollisionEnemy();//敵との当たり判定
	void CollisionFild();//地面との当たり判定
	void SetWeaponMotion(MOTION_TYPE motion);//武器所持時のモーションを設定
	void MotionUpdate();//モーションの更新
	void Damage();//ダメージ処理
	void WeaponDamage();//武器の耐久を減らす

	//メンバ変数
	bool m_grab;//掴み判定
	CWeapon* m_weapon;//持ってる武器
	CEnemy* m_boss;//ボス
	CStateMachine* m_StateMachine;//状態管理
	int m_RecoveryItemStock;//アイテムのストック数
	bool m_WeaponType;//武器の種類(false:両手 true:片手)
	bool m_VisualCor;//当たり判定の色の設定
	float LeftStickAngle;//左スティックの角度
	int m_DamageNum;//ダメージ回数カウント
	bool m_Attack;//攻撃がヒットしたか判定
	bool m_breakweapon;//武器が壊れた判定
};

#endif