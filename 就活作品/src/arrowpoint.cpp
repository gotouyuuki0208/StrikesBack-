//==========================
// 
// 矢印表示が指し示す位置[arrowpoint.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "arrowpoint.h"
#include "manager.h"
#include "texture.h"

//静的メンバ初期化
const int CArrowPoint::PRIORITY = 0;//描画順

//==========================
//コンストラクタ
//==========================
CArrowPoint::CArrowPoint(int nPriority) :
	CFild(nPriority),
	m_player(nullptr)
{

}

//==========================
//デストラクタ
//==========================
CArrowPoint::~CArrowPoint()
{

}

//==========================
//初期化処理
//==========================
HRESULT CArrowPoint::Init()
{
	//初期設定
	CObject3D::Init();

	//プレイヤーの情報を取得
	GetPlayerinfo();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CArrowPoint::Uninit()
{
	if (m_player != nullptr)
	{
		m_player = nullptr;
	}

	//終了処理
	CObject3D::Uninit();
}

//==========================
//更新処理
//==========================
void CArrowPoint::Update()
{
	//更新処理
	CObject3D::Update();

	//プレイヤーがいるか判定
	//CollisionPlayer();
}

//==========================
//描画処理
//==========================
void CArrowPoint::Draw()
{
	//描画処理
	CObject3D::Draw();
}

//==========================
//オブジェクト生成
//==========================
CArrowPoint* CArrowPoint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンス生成
	CArrowPoint* pArrowPoint = DBG_NEW CArrowPoint;

	//位置の設定
	pArrowPoint->SetPos(pos);

	//大きさの設定
	pArrowPoint->SetSize(size);

	//色の設定
	pArrowPoint->SetCol({ 1.0f,1.0f,1.0f,1.0f });

	//初期化処理
	pArrowPoint->Init();

	//タイプ設定
	pArrowPoint->SetType(TYPE::FILD);
	pArrowPoint->SetFild(FILDTYPE::ARROWPOINT);

	return pArrowPoint;
}

//==========================
//プレイヤーの情報を取得
//==========================
void CArrowPoint::GetPlayerinfo()
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

		CPlayer* pPlayer = (CPlayer*)pObj;

		//プレイヤーの情報を取得
		m_player = pPlayer;

		break;
	}
}

//==========================
//プレイヤーが当たってるか判定
//==========================
void CArrowPoint::CollisionPlayer()
{
	if (m_player->GetPos().x <= GetPos().x + GetSize().x
		&& m_player->GetPos().x >= GetPos().x - GetSize().x
		&& m_player->GetPos().z <= GetPos().z + GetSize().z
		&& m_player->GetPos().z >= GetPos().z - GetSize().z)
	{//中にプレイヤーがいる

		//ウェーブを進める
		CManager::GetInstance()->GetGameManager()->AddWave();

		//終了処理
		Uninit();
	}
}