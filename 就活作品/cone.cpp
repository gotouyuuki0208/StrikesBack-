//==========================
// 
// 自転車[bicycle.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "cone.h"
#include "manager.h"

//静的メンバ初期化
const int CCone::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CCone::CCone(int nPriority) :
	CBigWeapon(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CCone::~CCone()
{

}

//==========================
//初期化処理
//==========================
HRESULT CCone::Init()
{
	//初期設定
	CBigWeapon::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CCone::Uninit()
{
	//終了処理
	CBigWeapon::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CCone::Update()
{
	//更新処理
	CBigWeapon::Update();

	SetRot(D3DXVECTOR3(1.57f, GetRot().y, GetRot().z));
}

//==========================
//描画処理
//==========================
void CCone::Draw()
{
	//描画処理
	CBigWeapon::Draw();
}

//==========================
//オブジェクト生成
//==========================
CCone* CCone::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CCone* pBigWeapon = DBG_NEW CCone;

	//位置の設定
	pBigWeapon->SetPos(pos);

	//スケールの設定
	pBigWeapon->SetScale(scale);

	//向きの設定
	pBigWeapon->SetRot(rot);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBigWeapon->SetModelIdx(pModel->Regist("data\\MODEL\\cone.x"));
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
	pBigWeapon->SetBigWeapon(BIGWEAPON::CONE);

	//半径の設定
	pBigWeapon->SetRadius(15.0f);

	//当たり判定の可視化
	//pBigWeapon->CreateVisual();

	//耐久値を設定
	pBigWeapon->SetDurability(15);

	return pBigWeapon;
}