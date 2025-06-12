//==========================
// 
// 大きい武器[bigweapon.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bigweapon.h"
#include "manager.h"

//静的メンバ初期化
const int CBigWeapon::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CBigWeapon::CBigWeapon(int nPriority):
	CWeapon(nPriority),
	m_BigWeapontype(BIGWEAPON::NONE)
{

}

//==========================
//デストラクタ
//==========================
CBigWeapon::~CBigWeapon()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBigWeapon::Init()
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
void  CBigWeapon::Uninit()
{
	//終了処理
	CWeapon::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CBigWeapon::Update()
{
	//更新処理
	CWeapon::Update();
}

//==========================
//描画処理
//==========================
void CBigWeapon::Draw()
{
	//描画処理
	CWeapon::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBigWeapon* CBigWeapon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, const char ModelName[256])
{
	//インスタンス生成
	CBigWeapon* pBigWeapon = DBG_NEW CBigWeapon;

	//位置の設定
	pBigWeapon->SetPos(pos);

	//スケールの設定
	pBigWeapon->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBigWeapon->SetModelIdx(pModel->Regist(ModelName));
	pBigWeapon->BindModel(pModel->GetMeshAdress(pBigWeapon->GetModelIdx()),
		pModel->GetBuffMatAdress(pBigWeapon->GetModelIdx()),
		pModel->GetNumMatAdress(pBigWeapon->GetModelIdx()),
		pModel->GetTexIdx(pBigWeapon->GetModelIdx()));

	//初期化処理
	pBigWeapon->Init();

	//タイプを設定
	pBigWeapon->SetType(TYPE::WEAPON);

	//武器の種類を設定
	pBigWeapon->SetWeaponType(WEAPONTYPE::BIG);

	//半径の設定
	pBigWeapon->SetRadius(15.0f);

	//当たり判定の可視化
	pBigWeapon->CreateVisual();

	return pBigWeapon;
}

//==========================
//両手武器の種類を設定
//==========================
void CBigWeapon::SetBigWeapon(BIGWEAPON type)
{
	m_BigWeapontype = type;
}

//==========================
//両手武器の種類を取得
//==========================
CBigWeapon::BIGWEAPON CBigWeapon::GetBigWeapon()
{
	return m_BigWeapontype;
}