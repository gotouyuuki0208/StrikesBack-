//==========================
// 
// 配達員[deliveryperson.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "deliveryperson.h"
#include "manager.h"
#include "model.h"
#include"drink.h"

//静的メンバ初期化
const int CDeliveryPerson::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CDeliveryPerson::CDeliveryPerson(int nPriority):
CMotionModel(nPriority),//基底コンストラクタ
m_life(3),//寿命
m_Move(true)//移動判定
{

}

//==========================
//デストラクタ
//==========================
CDeliveryPerson::~CDeliveryPerson()
{

}

//==========================
//初期化処理
//==========================
HRESULT CDeliveryPerson::Init()
{
	//初期設定
	CMotionModel::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CDeliveryPerson::Uninit()
{
	//終了処理
	CMotionModel::Uninit();
}

//==========================
//更新処理
//==========================
void CDeliveryPerson::Update()
{
	if (m_Move)
	{//移動出来る時
		move();//移動処理
	}
	//更新処理
	CMotionModel::Update();
	CMotionModel::Motion();
}

//==========================
//描画処理
//==========================
void CDeliveryPerson::Draw()
{
	//描画処理
	CMotionModel::Draw();
}

//==========================
//オブジェクト生成
//==========================
CDeliveryPerson* CDeliveryPerson::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CDeliveryPerson* pDeliveryPerson = DBG_NEW CDeliveryPerson;

	//位置の設定
	pDeliveryPerson->SetPos(pos);

	//初期化処理
	pDeliveryPerson->Init();

	//半径の設定
	pDeliveryPerson->SetRadius(15.0f);

	//ファイルを読み込む
	pDeliveryPerson->LoadFile("data\\MOTION\\motion_player_15.txt", scale);
	
	//タイプ設定
	pDeliveryPerson->SetType(TYPE::DELIVERY);
	
	return pDeliveryPerson;
}

//==========================
//移動処理
//==========================
void CDeliveryPerson::move()
{
	SetPos(D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z + 1.0f));
}

//==========================
//ダメージ処理
//==========================
void CDeliveryPerson::Damage(int Damage)
{
	m_life -= Damage;

	if (m_life <= 0)
	{
		Uninit();
		CDrink::Create(GetPos(), D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	}
}

//==========================
//移動可能状態にする
//==========================
void CDeliveryPerson::Movable()
{
	m_Move = true;
}

//==========================
//移動不可能状態にする
//==========================
void CDeliveryPerson::Immovable()
{
	m_Move = false;
}