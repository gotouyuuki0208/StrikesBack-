//==========================
// 
// 雑魚敵[weakenemy.h]
// Author Yuki Goto
//
//==========================
#ifndef _WEAKENEMY_H_
#define _WEAKENEMY_H_

//include
#include"enemy.h"

//前方宣言
class CEnemyStateBase;
class CStateMachine;
class CEnemyMovePoint;
class CHPGauge3D;

//クラスの定義
class CWeakEnemy :public CEnemy
{
public:

	//定数
	static const int PRIORITY;//描画順
	static const int POINT = 10;//移動地点の数

	//メンバ関数
	CWeakEnemy(int nPriority = PRIORITY);//コンストラクタ
	~CWeakEnemy() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CWeakEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成

	void ChangeState(CEnemyStateBase* NewState);//状態を変更
	bool Hit(D3DXVECTOR3 pos, int damage, MOTION_TYPE HitMotion);//攻撃被弾処理
	void SubPartsCol();//パーツの透明度を減らす
	void Patrol();//移動地点を巡回
	bool GetPatrol();
	void SetEndPatrol();
private:

	//メンバ関数
	void ColisionEnemy();//敵同士の当たり判定
	void GetMovePoint();//移動地点を取得

	//メンバ変数
	CStateMachine* m_StateMachine;//状態管理
	CEnemyMovePoint* m_Point[POINT];//移動地点の情報
	int m_CurPoint;//現在の移動地点
	float m_Color;
	bool m_Patrol;//移動地点を移動するか判定
};
#endif