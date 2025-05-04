//==========================
// 
// ステージ遷移位置[stagechangepoint.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "stagechangepoint.h"
#include "texture.h"
#include "manager.h"
#include "player.h"

//静的メンバ初期化
const int CStageChangePoint::PRIORITY = 3;//描画順

//==========================
//コンストラクタ
//==========================
CStageChangePoint::CStageChangePoint(int nPriority) :CFild(nPriority),m_GoalPoint(nullptr)
{

}

//==========================
//デストラクタ
//==========================
CStageChangePoint::~CStageChangePoint()
{

}

//==========================
//初期化処理
//==========================
HRESULT CStageChangePoint::Init()
{
	//初期設定
	CFild::Init();

	//UIを生成
	m_GoalPoint = CGoalPoint::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 45.0f, GetPos().z), D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	return S_OK;
}

//==========================
//終了処理
//==========================
void CStageChangePoint::Uninit()
{
	if (m_GoalPoint != nullptr)
	{
		m_GoalPoint->Uninit();
		m_GoalPoint = nullptr;
	}

	//終了処理
	CFild::Uninit();
}

//==========================
//更新処理
//==========================
void  CStageChangePoint::Update()
{
	//更新処理
	CFild::Update();
	
	//プレイヤーとの当たり判定
	ColisionPlayer();

}

//==========================
//描画処理
//==========================
void CStageChangePoint::Draw()
{

#ifdef _DEBUG
	//描画処理
	CFild::Draw();
#endif
}

//==========================
//オブジェクト2D生成
//==========================
CStageChangePoint* CStageChangePoint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンス生成
	CStageChangePoint* pStageChangePoint = DBG_NEW CStageChangePoint;

	//位置の設定
	pStageChangePoint->SetPos(pos);

	//大きさの設定
	pStageChangePoint->SetSize(size);

	//色の設定
	pStageChangePoint->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	
	//初期化処理
	pStageChangePoint->Init();

	//半径の設定
	pStageChangePoint->SetRadius(15.0f);

	//タイプ設定
	pStageChangePoint->SetType(TYPE::FILD);
	pStageChangePoint->SetFild(FILDTYPE::STAGECHANGE);

	return pStageChangePoint;
}

//==========================
//プレイヤーとの当たり判定
//==========================
void CStageChangePoint::ColisionPlayer()
{
	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CPlayer::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::PLAYER)
		{//オブジェクトがプレイヤーではない
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		CCollision* pCollision = CManager::GetInstance()->GetCollision();

		bool Colision = pCollision->Sphere(GetPos(), pPlayer->GetPos(), GetRadius(), pPlayer->GetRadius());

		if (Colision)
		{
			CManager::GetInstance()->GetStageManager()->SetStage();//ステージフラグを立てる
			CManager::GetInstance()->GetStageManager()->DeleteObj(*this);//オブジェクト管理リストから消す
			Uninit();//終了処理
		}

		break;
	}
}