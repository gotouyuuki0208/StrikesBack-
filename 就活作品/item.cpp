//==========================
// 
// アイテム[item.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "item.h"
#include "manager.h"
#include "model.h"
#include"player.h"
#include"collision.h"

//静的メンバ初期化
const int CItem::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CItem::CItem(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CItem::~CItem()
{

}

//==========================
//初期化処理
//==========================
HRESULT CItem::Init()
{
	//サイズ設定
	//SetSize();

	//初期設定
	CObjectX::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CItem::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CItem::Update()
{
	//更新処理
	CObjectX::Update();

	//プレイヤーとの当たり判定
	ColisionPlayer();
}

//==========================
//描画処理
//==========================
void CItem::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CItem* pItem = DBG_NEW CItem;

	//位置の設定
	pItem->SetPos(pos);

	//スケールの設定
	pItem->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pItem->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pItem->BindModel(pModel->GetMeshAdress(pItem->m_nModelIdx),
		pModel->GetBuffMatAdress(pItem->m_nModelIdx),
		pModel->GetNumMatAdress(pItem->m_nModelIdx),
		pModel->GetTexIdx(pItem->m_nModelIdx));

	//初期化処理
	pItem->Init();

	return pItem;
}

//==========================
//モデルの番号を取得
//==========================
int CItem::GetModelIdx()
{
	return m_nModelIdx;
}

//==========================
//モデルの番号を設定
//==========================
void CItem::SetModelIdx(int Idx)
{
	m_nModelIdx = Idx;
}

//==========================
//プレイヤーとの当たり判定
//==========================
void CItem::ColisionPlayer()
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

		bool Colision = Collision::Sphere(GetPos(),
			pPlayer->GetPos(),
			GetRadius(),
			pPlayer->GetRadius());

		if (Colision)
		{
			Uninit();
			pPlayer->RecoveryLife();//回復
			
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_RECOVERY);
		}

		break;
	}
}