//==========================
// 
// エネミー[enemy.h]
// Author Yuki Goto
//
//==========================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//include
#include "motionmodel.h"
#include "collisionvisual.h"
#include "enemymovepoint.h"
#include "player.h"

//前方宣言
class CPlayer;

//クラスの定義
class CEnemy :public CMotionModel
{
public:
	enum class ATTACK_STATE
	{
		USUALLY = 0,//通常
		GRAB,//掴む
		ATTACK,//攻撃
		WEAPONATTACK,//武器攻撃
		MAX,
	};

	enum class STATE
	{
		USUALLY = 0,//通常
		ATTACK,//攻撃
		GUARD,//ガード
		GRAB,//掴まれる
		MAX,
	};

	enum class ENEMY_TYPE
	{
		NONE = 0,
		BOSS,//ボス
		HitEnemy,//素手雑魚
		WeaponEnemy,//武器雑魚
	};

	//定数
	static const int PRIORITY;//描画順
	static const int POINT=10;//移動地点の数

	//メンバ関数
	CEnemy(int nPriority = PRIORITY);//コンストラクタ
	~CEnemy() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	void Damage(int damage);//ダメージを受けたときの処理
	void BeGrabbed(D3DXMATRIX mtx);//掴まれる処理
	void ReleaseGrab(D3DXVECTOR3 rot);//掴まれていない状態に変更
	void DamegeBlow(D3DXVECTOR3 pos);//被弾時の吹き飛び処理
	void SetAttackState(ATTACK_STATE state);//攻撃方法の設定
	ATTACK_STATE GetAttackState();//攻撃方法の取得
	void SetLife(int life);//寿命の設定
	int GetLife();//寿命の取得
	bool GetDamage();//ダメージ判定の取得
	void SetDamage();//ダメージ判定の変更
	void SetState(STATE state);//状態の設定
	STATE GetState();//状態の取得
	void SetEnemyType(ENEMY_TYPE EnemyType);//敵の種類を設定
	ENEMY_TYPE GetEnemyType();//敵の種類を取得
	void DamageVisual(int PartsNum,float Radius);//被弾時の当たり判定の可視化
	void SetVisual();//当たり判定の可視化処理
	CFild* GetFild();//乗っている地面の情報
	CPlayer* GetPlayer();//プレイヤーの情報を取得
	bool GetMovable();//移動可能か取得
	void SetMovable();//行動可能にする
	void judgeMovable();//行動出来るか判定
	void Patrol();//移動地点を巡回
private:

	//メンバ関数
	void ColisionEnemy();//敵同士の当たり判定
	void CollisionFild();//地面との当たり判定
	void Move();//移動処理
	void GetPlayerInfo();//プレイヤーの情報を取得
	void GetMovePoint();//移動地点を取得

	//メンバ変数
	ATTACK_STATE m_AttackState;//攻撃方法
	STATE m_state;//現在の状態
	D3DXMATRIX m_Mtx;//ワールドマトリックス
	int m_nLife;//寿命
	bool m_Damage;//ダメージ状態判定
	D3DXVECTOR3 m_DamageMove;//吹き飛び用の移動値
	ENEMY_TYPE m_EnemyType;//敵の種類
	CCollisionVisual* m_visual;//当たり判定の可視化
	CPlayer* m_player;//プレイヤーの情報
	bool m_Movable;//行動可能判定

	CEnemyMovePoint* m_Point[POINT];//移動地点の情報

	int m_CurPoint;//現在の移動地点
};
#endif