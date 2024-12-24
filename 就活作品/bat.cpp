//==========================
// 
// バット[bat.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bat.h"
#include "manager.h"

//静的メンバ初期化
const int CBat::PRIORITY =2;//描画順

//==========================
//コンストラクタ
//==========================
CBat::CBat(int nPriority) :
	CSmallWeapon(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CBat::~CBat()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBat::Init()
{
	//初期設定
	CSmallWeapon::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CBat::Uninit()
{
	//終了処理
	CSmallWeapon::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CBat::Update()
{
	//更新処理
	CSmallWeapon::Update();
}

//==========================
//描画処理
//==========================
void CBat::Draw()
{
	//描画処理
	CSmallWeapon::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBat* CBat::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CBat* pSmallWeapon = DBG_NEW CBat;

	//位置の設定
	pSmallWeapon->SetPos(pos);

	//スケールの設定
	pSmallWeapon->SetScale(scale);

	//向きの設定
	pSmallWeapon->SetRot(rot);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pSmallWeapon->SetModelIdx(pModel->Regist("data\\MODEL\\bat.x"));
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
	pSmallWeapon->SetSmallWeapon(SMALLWEAPON::BAT);

	//半径の設定
	pSmallWeapon->SetRadius(15.0f);

	//当たり判定の可視化
	//pSmallWeapon->CreateVisual();

	//耐久値を設定
	pSmallWeapon->SetDurability(9);

	return pSmallWeapon;
}