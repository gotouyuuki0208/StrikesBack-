//==========================
// 
// バット[bat.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "syokaki.h"
#include "manager.h"

//静的メンバ初期化
const int CSyokaki::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CSyokaki::CSyokaki(int nPriority) :
	CSmallWeapon(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CSyokaki::~CSyokaki()
{

}

//==========================
//初期化処理
//==========================
HRESULT CSyokaki::Init()
{
	//初期設定
	CSmallWeapon::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CSyokaki::Uninit()
{
	//終了処理
	CSmallWeapon::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CSyokaki::Update()
{
	//更新処理
	CSmallWeapon::Update();

	SetRot(D3DXVECTOR3(1.57f, GetRot().y, GetRot().z));
}

//==========================
//描画処理
//==========================
void CSyokaki::Draw()
{
	//描画処理
	CSmallWeapon::Draw();
}

//==========================
//オブジェクト生成
//==========================
CSyokaki* CSyokaki::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CSyokaki* pSmallWeapon = DBG_NEW CSyokaki;

	//位置の設定
	pSmallWeapon->SetPos(pos);

	//スケールの設定
	pSmallWeapon->SetScale(scale);

	//向きの設定
	pSmallWeapon->SetRot(D3DXVECTOR3(1.57f, rot.y, rot.z));

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pSmallWeapon->SetModelIdx(pModel->Regist("data\\MODEL\\syokaki.x"));
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
	pSmallWeapon->SetSmallWeapon(SMALLWEAPON::SYOKAKI);

	//半径の設定
	pSmallWeapon->SetRadius(15.0f);

	//当たり判定の可視化
	//pSmallWeapon->CreateVisual();

	//耐久値を設定
	pSmallWeapon->SetDurability(9);

	return pSmallWeapon;
}