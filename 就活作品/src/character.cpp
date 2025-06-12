//==========================
// 
// キャラクター[character.h]
// Author Yuki Goto
//
//==========================
#include"character.h"

const int CCharacter::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CCharacter::CCharacter(int nPriority):
CMotionModel(nPriority),//基底コンストラクタ
m_state(STATE::NEUTRAL),//現在の状態
m_nLife(0),//寿命
m_Damage(false),//ダメージ状態判定
m_DamageMove(D3DXVECTOR3(0.0f,0.0f,0.0f)),//吹き飛び用の移動値
m_visual(nullptr)//当たり判定の可視化
{

}

//==========================
//デストラクタ
//==========================
CCharacter::~CCharacter()
{

}

//==========================
//初期化処理
//==========================
HRESULT CCharacter::Init()
{
	//初期設定
	CMotionModel::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CCharacter::Uninit()
{
	if (m_visual != nullptr)
	{
		m_visual->Uninit();
		m_visual = nullptr;
	}

	//終了処理
	CMotionModel::Uninit();
}

//==========================
//更新処理
//==========================
void CCharacter::Update()
{
	//更新処理
	CMotionModel::Update();
}

//==========================
//描画処理
//==========================
void CCharacter::Draw()
{
	//描画処理
	CMotionModel::Draw();
}

//==========================
//被弾時の吹き飛び処理
//==========================
void CCharacter::DamegeBlow(D3DXVECTOR3 pos)
{
	if (GetState() != STATE::GUARD)
	{
		SetMotion(MOTION_TYPE::DAMAGEBLOW);
	}

	float angle = atan2f(GetPos().x - pos.x, GetPos().z - pos.z);
	m_DamageMove = D3DXVECTOR3(sinf(angle) * 15.0f, GetMove().y, cosf(angle) * 15.0f);
}

//==========================
//寿命の設定
//==========================
void CCharacter::SetLife(int life)
{
	m_nLife = life;
}

//==========================
//寿命の取得
//==========================
int CCharacter::GetLife()
{
	return m_nLife;
}

//==========================
//ダメージ判定の取得
//==========================
bool CCharacter::GetDamage()
{
	return m_Damage;
}

//==========================
//ダメージ判定の変更
//==========================
void CCharacter::SetDamage(bool damege)
{
	m_Damage = damege;
}

//==========================
//状態の設定
//==========================
void CCharacter::SetState(STATE state)
{
	m_state = state;
}

//==========================
//状態の取得
//==========================
CCharacter::STATE CCharacter::GetState()
{
	return m_state;
}

//==========================
//被弾時の当たり判定の可視化
//==========================
void CCharacter::DamageVisual(int PartsNum, float Radius)
{
	GetParts(PartsNum)->CreateVisual(D3DXVECTOR3(GetParts(PartsNum)->GetMtxWorld()._41, GetParts(PartsNum)->GetMtxWorld()._42, GetParts(PartsNum)->GetMtxWorld()._43), Radius);
}

//==========================
//当たり判定の可視化処理
//==========================
void CCharacter::SetVisual()
{
	if (m_visual == nullptr)
	{
		//m_visual = CCollisionVisual::Create(GetPos(), GetRadius());
	}
}

//==========================
//吹き飛び用の移動値設定
//==========================
void CCharacter::SetDamegeBlow(D3DXVECTOR3 move)
{
	m_DamageMove = move;
}

//==========================
//吹き飛び用の移動値取得
//==========================
D3DXVECTOR3& CCharacter::GetDamegeBlow()
{
	return m_DamageMove;
}