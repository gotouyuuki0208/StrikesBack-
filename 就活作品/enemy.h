//==========================
// 
// エネミー[enemy.h]
// Author Yuki Goto
//
//==========================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//include
#include"character.h"

//前方宣言
class CPlayer;
class CFild;
class CEnemyMovePoint;
class CStateMachine;
class CEnemyStateBase;

//クラスの定義
class CEnemy :public CCharacter
{
public:

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
	static const float DUSH_DISTANCE;//走る距離
	static const float DUSH_SPEED;//走る速さ
	static const float STOP_DISTANCE;//歩く距離
	static const float WALK_SPEED;//歩く速さ

	//メンバ関数
	CEnemy(int nPriority = PRIORITY);//コンストラクタ
	~CEnemy() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	void JudgeMovable();//行動出来るか判定
	float ChangeDirection();//向きの変更
	bool JudgeDush();//ダッシュ判定
	void Dush();//ダッシュ移動処理
	bool JudgeWalk();//歩き判定
	void Walk();//歩き移動処理
	bool JudgeStop();//停止判定
	bool GetAttackable();//攻撃可能か判定
	void ChangeAttackable();//攻撃可能判定を変更
	bool JudgeAttacKRange();//攻撃範囲にプレイヤーがいるか判定
	void AttackMove();//攻撃時の移動
	void Move();//移動処理
	void ChangeState(CEnemyStateBase* NewState);//状態を変更
	void ChangePlayMotion();//モーションの再生判定を変更
	

	void Damage(int damage);//ダメージを受けたときの処理
	void BeGrabbed(D3DXMATRIX mtx);//掴まれる処理
	void ReleaseGrab(D3DXVECTOR3 rot);//掴まれていない状態に変更
	void SetEnemyType(ENEMY_TYPE EnemyType);//敵の種類を設定

	ENEMY_TYPE GetEnemyType();//敵の種類を取得
	CFild* GetFild();//乗っている地面の情報
	CPlayer* GetPlayer();//プレイヤーの情報を取得
	bool GetMovable();//移動可能か取得
	void SetMovable();//行動可能にする
	
	void Patrol();//移動地点を巡回
private:

	//メンバ関数
	void ColisionEnemy();//敵同士の当たり判定
	void CollisionFild();//地面との当たり判定
	
	void GetPlayerInfo();//プレイヤーの情報を取得
	void GetMovePoint();//移動地点を取得

	//メンバ変数
	//ATTACK_STATE m_AttackState;//攻撃方法
	D3DXMATRIX m_Mtx;//ワールドマトリックス
	ENEMY_TYPE m_EnemyType;//敵の種類
	CPlayer* m_player;//プレイヤーの情報
	bool m_Movable;//行動可能判定
	CStateMachine* m_StateMachine;//状態管理
	CEnemyMovePoint* m_Point[POINT];//移動地点の情報
	float m_Angle;//向き
	int m_CurPoint;//現在の移動地点
	bool Attackable;//攻撃可能判定
	bool m_PlayMotion;//モーション再生判定
};
#endif