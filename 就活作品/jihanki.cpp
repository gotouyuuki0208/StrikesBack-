//==========================
// 
// 自販機[jihanki.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "jihanki.h"
#include "manager.h"
#include "model.h"
#include "player.h"
#include "drink.h"
#include "particle.h"

//静的メンバ初期化
const int CJihanki::PRIORITY = 2;//描画順
const int CJihanki::MAX_LIFE = 3;//寿命の最大値
//==========================
//コンストラクタ
//==========================
CJihanki::CJihanki(int nPriority) :
CObjectX(nPriority),//基底コンストラクタ
m_nModelIdx(0),//モデルの番号
m_Life(MAX_LIFE),//寿命
m_visual{}//当たり判定の可視化
{

}

//==========================
//デストラクタ
//==========================
CJihanki::~CJihanki()
{

}

//==========================
//初期化処理
//==========================
HRESULT CJihanki::Init()
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
void  CJihanki::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	for (int i = 0; i < 2; i++)
	{
		if (m_visual[i] != nullptr)
		{
			m_visual[i]->Uninit();
			m_visual[i] = nullptr;
		}
	}

	Release();
}

//==========================
//更新処理
//==========================
void CJihanki::Update()
{
	//更新処理
	CObjectX::Update();

	ColisionPlayer();
}

//==========================
//描画処理
//==========================
void CJihanki::Draw()
{
	//描画処理
	CObjectX::Draw();

	for (int i = 0; i < 2; i++)
	{
		if (m_visual[i] != nullptr)
		{
			//m_visual[i]->Draw();
		}
	}

}

//==========================
//オブジェクト生成
//==========================
CJihanki* CJihanki::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CJihanki* pJihanki = DBG_NEW CJihanki;

	//位置の設定
	pJihanki->SetPos(pos);

	//スケールの設定
	pJihanki->SetScale(scale);

	//向きの設定
	pJihanki->SetRot(rot);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pJihanki->m_nModelIdx = pModel->Regist("data\\MODEL\\jihanki.x");
	pJihanki->BindModel(pModel->GetMeshAdress(pJihanki->m_nModelIdx),
		pModel->GetBuffMatAdress(pJihanki->m_nModelIdx),
		pModel->GetNumMatAdress(pJihanki->m_nModelIdx),
		pModel->GetTexIdx(pJihanki->m_nModelIdx));

	//初期化処理
	pJihanki->Init();

	//タイプを設定
	pJihanki->SetType(TYPE::JIHANKI);
	
	//半径を設定
	pJihanki->SetRadius(20.0f);

	//当たり判定を可視化
	//pJihanki->m_visual[0] = CCollisionVisual::Create(pJihanki->GetPos(), pJihanki->GetRadius());
	
	return pJihanki;
}

//==========================
//プレイヤーとの当たり判定
//==========================
void CJihanki::ColisionPlayer()
{
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

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

		bool Colision = pCollision->Sphere(GetPos(),
			pPlayer->GetPos(),
			GetRadius(),
			pPlayer->GetRadius());

		if (Colision)
		{
			D3DXVECTOR3 Vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きベクトル
			D3DXVECTOR3 NormalizeVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//正規化したベクトル

			//向きベクトルを算出
			Vector.x = VectorCalculation(pPlayer->GetPos().x, GetPos().x);
			Vector.z = VectorCalculation(pPlayer->GetPos().z, GetPos().z);

			//ベクトルを正規化
			D3DXVec3Normalize(&NormalizeVec, &Vector);

			//位置を変更
			pPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x + NormalizeVec.x * floor((GetRadius() + pPlayer->GetRadius())),
				GetPos().y,
				GetPos().z + NormalizeVec.z * floor((GetRadius() + pPlayer->GetRadius()))));

			CManager::GetInstance()->GetTutorial()->RecoveryTutorialDisplay();
		}

		break;
	}
}

//==========================
//ダメージ処理
//==========================
void CJihanki::Damage(int Damage)
{
	m_Life -= Damage;

	DamageParticle();

	if (m_Life <= 0)
	{
		CManager::GetInstance()->GetStageManager()->DeleteObj(*this);
		Uninit();
		CDrink::Create(GetPos(), D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	}
}

//==========================
//攻撃の当たり判定
//==========================
void CJihanki::DamageVisual(D3DXVECTOR3 pos, float radius)
{
	if (m_visual[1] == nullptr)
	{
		//m_visual[1] = CCollisionVisual::Create(pos, radius);
	}
}

//==========================
//被弾時にパーティクルを出す処理
//==========================
void CJihanki::DamageParticle()
{
	for (int i = 0; i < 50; i++)
	{
		CParticle::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 30.0f, GetPos().z),
			D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
			10,
			0.5f,
			0.5f,
			10.0f);

	}
}