//==========================
// 
// 壁[wall.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"wall.h"
#include"model.h"
#include"manager.h"

//静的メンバ初期化
const int CWall::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CWall::CWall(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CWall::~CWall()
{

}

//==========================
//初期化処理
//==========================
HRESULT CWall::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CWall::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CWall::Update()
{
	//更新処理
	CObjectX::Update();

	int rot = static_cast<int>(GetRot().y);

	if (rot == 1 || rot == -1)
	{
		//プレイヤーとの当たり判定
		ColisionPlayerWide();
	}
	else
	{
		//プレイヤーとの当たり判定
		ColisionPlayer();
	}
}

//==========================
//描画処理
//==========================
void CWall::Draw()
{
	if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		//描画処理
		CBuilding::Draw();
	}
}

//==========================
//オブジェクト生成
//==========================
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CWall* pConveni = DBG_NEW CWall;

	//位置の設定
	pConveni->SetPos(pos);

	//向きの設定
	pConveni->SetRot(rot);

	//スケールの設定
	pConveni->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\wall.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//初期化処理
	pConveni->Init();

	//タイプを設定
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::WALL);

	return pConveni;
}