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
#include "weapon.h"
#include "enemy.h"
#include "collisionvisual.h"

//前方宣言
class CEnemy;

//クラスの定義
class CPlayer :public CCharacter
{
public:

	//定数
	static const int PRIORITY;//描画順
	static const int INPUT_START_FLAME;//入力受付開始フレーム数
	static const int INPUT_FINISH_FLAME;//入力受付終了フレーム数
	static const int RESET_FLAME;//コンボの情報リセットフレーム数
	static const int MAX_LIFE;//寿命の最大値
	static const float MOVE_VALUE;//移動
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
	void Damage(int damage);//ダメージ処理
	void AddItem();//アイテムの数を増やす
	int GetInputFrame();//入力受付時間を取得
	void GetBoss(CEnemy* boss);//ボスを取得
	bool GetHaveWeapon();//武器所持判定
	void DeleteWeapon();//武器を消す
private:
	
	//メンバ関数
	void Attack();//攻撃処理
	void Avoidance();//回避
	void AttackWeapon();//武器での攻撃
	void CollisionEnemy();//敵との当たり判定
	void CollisionFild();//地面との当たり判定
	void CollisionHitEnemy();//敵を殴るときの当たり判定
	void CollisionJihankiAttack();//自販機に攻撃時の当たり判定
	void CollisionWeaponEnemy();//敵を武器で殴るときの当たり判定
	void ColisionDeleveryAttack();//配達員の攻撃当たり判定
	void ColisionDelevery();//配達員の当たり判定
	void GrabAttack();//掴み攻撃の処理
	void GrabEnemy();//敵を掴む処理
	void Guard();//ガード処理
	void Input();//入力処理
	void InputMove();//移動の入力処理
	void InputAttack();//攻撃の入力処理
	void Move();//移動処理
	void Push(MOTION_TYPE motion);//データの追加
	MOTION_TYPE Pop();//データの取り出し
	void PickUpWeapon();//武器を拾う
	void Recovery();//回復アイテムを使用
	void ReleaseEnemy();//敵を放す
	void ReleaseWeapon();//武器を手放す
	void ResetStak();//スタックの情報を戻す
	void SetComboList();//コンボリストの生成
	void SetWeaponMotion(MOTION_TYPE motion);//武器所持時のモーションを設定
	void CorrectionAngle();//角度の補正
	void MotionUpdate();//モーションの更新
	void ThrowWeapon();//武器を投げる

	//メンバ変数
	bool m_grab;//掴み判定
	bool m_Attack;//攻撃判定
	CWeapon* m_weapon;//持ってる武器
	CEnemy* m_GrabEnemy;//掴んでいる敵
	CEnemy* m_boss;//ボス
	MOTION_TYPE m_ComboList[3];//攻撃のコンボリスト
	MOTION_TYPE m_ComboStack[3];//攻撃コンボのスタック
	int m_FlameCount;//フレーム数のカウント
	int m_StackIdx;//TOPの位置
	int m_CountAttack;//コンボ中に攻撃を当てた回数
	bool m_testdeth;
	int m_DamageCount;//
	int m_RecoveryItemStock;//アイテムのストック数
	int m_Avoidance;//回避フレーム
	bool m_WeaponType;//武器の種類(false:両手 true:片手)
	bool m_VisualCor;//当たり判定の色の設定
	float LeftStickAngle;//左スティックの角度
};

//class C :public CPlayer
#endif