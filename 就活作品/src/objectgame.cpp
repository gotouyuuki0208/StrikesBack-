//==========================
// 
// ゲームオブジェクト[objectgame.h]
// Author Yuki Goto
//
//==========================

//include
#include"objectgame.h"

//==========================
// コンストラクタ
//==========================
CObjectgame::CObjectgame(int nPriority):
CObject(nPriority),
m_posmove({0.0f, 0.0f, 0.0f}),
m_pos({0.0f, 0.0f, 0.0f}),
m_posold({0.0f, 0.0f, 0.0f}),
m_rot({0.0f, 0.0f, 0.0f}),
m_radius(0.0f),
m_scale({ 1.0f, 1.0f, 1.0f }),
m_rotmove({0.0f, 0.0f, 0.0f})
{
	D3DXMatrixIdentity(&m_mtxWorld);	
}

//==========================
// デストラクタ
//==========================
CObjectgame::~CObjectgame()
{

}

//==========================
// 初期設定
//==========================
HRESULT CObjectgame::Init(void)
{
	return S_OK;
}

//==========================
// 終了処理
//==========================
void CObjectgame::Uninit(void)
{

}

//==========================
// 更新処理
//==========================
void CObjectgame::Update(void)
{

}

//==========================
// 描画処理
//==========================
void CObjectgame::Draw(void)
{

}

//==========================
//位置取得
//==========================
D3DXVECTOR3& CObjectgame::GetPos(void)
{
	return m_pos;
}

//==========================
//位置設定
//==========================
void CObjectgame::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==========================
//位置取得
//==========================
D3DXVECTOR3& CObjectgame::GetRot(void)
{
	return m_rot;
}

//==========================
//位置設定
//==========================
void CObjectgame::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==========================
//昔の位置取得
//==========================
D3DXVECTOR3& CObjectgame::GetPosOld(void)
{
	return m_posold;
}

//==========================
//昔の位置設定
//==========================
void CObjectgame::SetPosOld(D3DXVECTOR3 posord)
{
	m_posold = posord;
}

//==========================
//移動値取得
//==========================
D3DXVECTOR3& CObjectgame::GetMove(void)
{
	return m_posmove;
}

//==========================
//移動値設定
//==========================
void CObjectgame::SetMove(D3DXVECTOR3 move)
{
	m_posmove = move;
}

//==========================
//向きの移動値取得
//==========================
D3DXVECTOR3& CObjectgame::GetRotMove()
{
	return m_rotmove;
}

//==========================
//向きの移動値設定
//==========================
void CObjectgame::SetRotMove(D3DXVECTOR3 rot)
{
	m_rotmove = rot;
}

//==========================
//マトリックス取得
//==========================
D3DXMATRIX& CObjectgame::GetMtxWorld()
{
	return m_mtxWorld;
}

//==========================
//マトリックスの設定
//==========================
void CObjectgame::SetMtxWorld(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}

//==========================
//半径の設定
//==========================
void CObjectgame::SetRadius(float radius)
{
	m_radius = radius;
}

//==========================
//半径の取得
//==========================
float CObjectgame::GetRadius()
{
	return m_radius;
}

//==========================
//拡大率の設定
//==========================
void CObjectgame::SetScale(D3DXVECTOR3 scale)
{
	m_scale = scale;
}

//==========================
//拡大率の設定
//==========================
D3DXVECTOR3& CObjectgame::GetScale()
{
	return m_scale;
}

//==========================
//向きの補正
//==========================
float CObjectgame::RevisionRot(float objectiverot, float currentrot, float Cur)
{
	float difference = objectiverot - currentrot;//目的の向きと現在の向きの差分を求める

	if (-D3DX_PI > difference)
	{//差分が3.14を超えているとき
		difference += D3DX_PI * 2;
	}
	else if (D3DX_PI < difference)
	{
		difference -= D3DX_PI * 2;
	}

	//向き設定
	float rot = difference * Cur;

	return rot;
}

//==========================
//向きの正規化
//==========================
float CObjectgame::NormalizeAngle(float angle)
{
	if (angle >=D3DX_PI)
	{
		angle = -D3DX_PI;
	}
	else if (angle < -D3DX_PI)
	{
		angle = D3DX_PI;
	}

	return angle;
}

//==========================
//ベクトルの算出
//==========================
float CObjectgame::VectorCalculation(float purpose,float current)
{
	float Vector = purpose - current;

	return Vector;
}
