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
	void SetMovable();//行動可能にする
	bool GetMovable();//移動可能か取得
	CPlayer* GetPlayer();//プレイヤーの情報を取得
	ENEMY_TYPE GetEnemyType();//敵の種類を取得
	void SetEnemyType(ENEMY_TYPE EnemyType);//敵の種類を設定
	void ReleaseGrab(D3DXVECTOR3 rot);//掴まれていない状態に変更
	void BeGrabbed(D3DXMATRIX mtx);//掴まれる処理
	void Move();//移動処理
	bool JudgeDush();//ダッシュ判定
	void Dush();//ダッシュ移動処理
	bool JudgeWalk();//歩き判定
	void Walk();//歩き移動処理
	bool JudgeStop();//停止判定
	float ChangeDirection();//向きの変更
	bool GetAttackable();//攻撃可能か判定
	void ChangeAttackable();//攻撃可能判定を変更
	bool JudgeAttackRange();//攻撃範囲にプレイヤーがいるか判定	
	void ChangePlayMotion(bool play);//モーションの再生判定を変更
	void ResetDamageNum();//被弾回数初期化
	int GetDamageNum();//被弾回数取得
	void AddDamegeNum();//ダメージ回数を増やす
	void HitPlayer(int PartsNum);//プレイヤーへの殴り攻撃の当たり判定
	void ResetAttack();//攻撃判定をリセット
	void AttackMove();//攻撃時の移動
	void SetCoolTime(int time);//攻撃のクールタイムを設定
	
private:

	//メンバ関数
	void CollisionFild();//地面との当たり判定
	void GetPlayerInfo();//プレイヤーの情報を取得

	//メンバ変数
	D3DXMATRIX m_Mtx;//ワールドマトリックス
	ENEMY_TYPE m_EnemyType;//敵の種類
	CPlayer* m_player;//プレイヤーの情報
	bool m_Movable;//行動可能判定
	float m_Angle;//向き
	bool Attackable;//攻撃可能判定
	bool m_PlayMotion;//モーション再生判定
	int m_DamageNum;//ダメージ回数カウント
	int m_AttackCoolTime;//攻撃のクールタイム
	bool m_Attack;//攻撃判定
};
#endif