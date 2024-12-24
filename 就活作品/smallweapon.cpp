//==========================
// 
// 片手武器[smallweapon.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "smallweapon.h"
#include "manager.h"

//静的メンバ初期化
const int CSmallWeapon::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CSmallWeapon::CSmallWeapon(int nPriority) :
	CWeapon(nPriority),
	m_SmallWeapontype(SMALLWEAPON::NONE)
{

}

//==========================
//デストラクタ
//==========================
CSmallWeapon::~CSmallWeapon()
{

}

//==========================
//初期化処理
//==========================
HRESULT CSmallWeapon::Init()
{
	//サイズ設定
	//SetSize();

	//初期設定
	CWeapon::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CSmallWeapon::Uninit()
{
	//終了処理
	CWeapon::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CSmallWeapon::Update()
{
	//更新処理
	CWeapon::Update();
}

//==========================
//描画処理
//==========================
void CSmallWeapon::Draw()
{
	//描画処理
	CWeapon::Draw();
}

//==========================
//オブジェクト生成
//==========================
CSmallWeapon* CSmallWeapon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, const char ModelName[256])
{
	//インスタンス生成
	CSmallWeapon* pSmallWeapon = DBG_NEW CSmallWeapon;

	//位置の設定
	pSmallWeapon->SetPos(pos);

	//スケールの設定
	pSmallWeapon->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pSmallWeapon->SetModelIdx(pModel->Regist(ModelName));
	pSmallWeapon->BindModel(pModel->GetMeshAdress(pSmallWeapon->GetModelIdx()),
		pModel->GetBuffMatAdress(pSmallWeapon->GetModelIdx()),
		pModel->GetNumMatAdress(pSmallWeapon->GetModelIdx()),
		pModel->GetTexIdx(pSmallWeapon->GetModelIdx()));

	//初期化処理
	pSmallWeapon->Init();

	//タイプを設定
	pSmallWeapon->SetType(TYPE::WEAPON);

	//武器の種類を設定
	pSmallWeapon->SetWeaponType(WEAPONTYPE::SMALL);

	//半径の設定
	pSmallWeapon->SetRadius(15.0f);

	//当たり判定の可視化
	pSmallWeapon->CreateVisual();

	return pSmallWeapon;
}

//==========================
//片手武器の種類を設定
//==========================
void CSmallWeapon::SetSmallWeapon(SMALLWEAPON type)
{
	m_SmallWeapontype = type;
}

//==========================
//片手武器の種類を取得
//==========================
CSmallWeapon::SMALLWEAPON CSmallWeapon::GetSmallWeapon()
{
	return m_SmallWeapontype;
}