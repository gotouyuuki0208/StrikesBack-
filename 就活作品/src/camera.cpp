//==========================
// 
// カメラ処理[camera.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"camera.h"
#include"manager.h"

//静的メンバ変数初期化
const float CCamera::Y_DISTANCE = 75.0f;//距離
const float CCamera::Z_DISTANCE = -200.0f;//距離
//==========================
// コンストラクタ
//==========================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, Y_DISTANCE, Z_DISTANCE);//視点
	m_posR = D3DXVECTOR3(0.0f, Y_DISTANCE, 0.0f);//注視点
	m_targetposV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;//目的の視点
	m_targetposR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//目的の注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//上方向
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
	m_PosVY = 0.0f;
	m_PosRY = 0.0f;
	m_nFlame = 0;
	m_fShapeScale = 0;
	m_DrectionFlame = 0;
	m_NowFlame = 0;
}

//==========================
// デストラクタ
//==========================
CCamera::~CCamera()
{

}

//==========================
// 初期設定
//==========================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(-100.0f, Y_DISTANCE, Z_DISTANCE);//視点
	m_posR = D3DXVECTOR3(-50.0f, Y_DISTANCE, 0.0f);//注視点
	//m_posV = D3DXVECTOR3(0.0f, Y_DISTANCE, Z_DISTANCE);//視点
	//m_posR = D3DXVECTOR3(0.0f, Y_DISTANCE, 0.0f);//注視点
	//m_posR = D3DXVECTOR3(0.0f, 80.0f, 0.0f);//注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//上方向
	m_targetposV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;//目的の視点
	m_targetposR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//目的の注視点
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
	m_PosVY = 0.0f;
	m_PosRY = 0.0f;
	m_nFlame = 0;
	m_fShapeScale = 0;

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CCamera::Uninit()
{
	
}

//==========================
// 更新処理
//==========================
void CCamera::Update()
{
	//入力処理
	Input();
}

#define PLOJECTION (1)//投影方法切り替え
//==========================
// カメラの設定
//==========================
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

#if PLOJECTION
	//プロジェクションマトリックスを作成(遠近投影)
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),							//視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//画面のアスペクト比
		10.0f,											//Z値の最小値
		25000.0f);										//Z値の最大値

#else

	D3DXMATRIX MatScale;

	//プロジェクションマトリックスを作成(平行投影)
	D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_HEIGHT,
		(float)SCREEN_WIDTH,
		10.0f,
		1000.0f);
	D3DXMatrixIdentity(&MatScale);
	D3DXMatrixScaling(&MatScale, 1.0f, 5.0f, 1.0f);
	D3DXMatrixMultiply(&m_mtxProjection, &m_mtxProjection, &MatScale);
#endif



	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 adjust = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_nFlame > 0)
	{
		m_nFlame--;
		random_device rnd;
		adjust.x = (float)(rnd() % m_fShapeScale);
		adjust.y = (float)(rnd() % m_fShapeScale);
	}

	D3DXVECTOR3 posV = m_posV + adjust;
	D3DXVECTOR3 posR = m_posR + adjust;

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,						//視点
		&posR,						//注視点
		&m_vecU);					//上方向ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}

//==========================
//カメラ揺れ設定
//==========================
void CCamera::SetShape(int flame, int scale)
{
	m_nFlame = flame;
	m_fShapeScale = scale;
}

//==========================
//カメラの移動
//==========================
void CCamera::Move(D3DXVECTOR3 pos)
{
	m_posV.y = Y_DISTANCE;
	m_posV.x = pos.x + (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	m_posV.z = pos.z + (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	m_posR.x = m_posV.x - (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	m_posR.z = m_posV.z - (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
}

//==========================
//カメラの縦移動
//==========================
void CCamera::VerticalMove(D3DXVECTOR3 pos)
{
	m_posR.y = pos.y;
	m_posR.z = pos.z;

	m_posV.y = pos.y + Y_DISTANCE;
	m_posV.z = pos.z + Z_DISTANCE;
}

//==========================
//注視点の取得
//==========================
D3DXVECTOR3& CCamera::GetPosR()
{
	return m_posR;
}

//==========================
//視点の取得
//==========================
D3DXVECTOR3& CCamera::GetPosV()
{
	return m_posV;
}

//==========================
//インゲーム以外のカメラ
//==========================
void CCamera::OutGame(D3DXVECTOR3 pos)
{
	m_posV = D3DXVECTOR3(-100.0f, 10.0f, -200.0f);//視点
	m_posR = D3DXVECTOR3(-50.0f, 70.0f, 0.0f);//注視点
}

//==========================
//向きの取得
//==========================
D3DXVECTOR3& CCamera::GetRot()
{
	return m_rot;
}

//==========================
//位置の取得
//==========================
D3DXVECTOR3& CCamera::GetPos()
{
	return m_posV;
}

//==========================
//カメラの追従変更後の位置を設定
//==========================
void CCamera::SetTargetPos(D3DXVECTOR3 pos,int flame)
{
	//演出終了のフレーム数
	m_DrectionFlame = flame;

	//移動後の注視点の位置
	m_targetposR.x = pos.x;
	m_targetposR.z = pos.z;

	//移動後の視点の位置
	m_targetposV.x = pos.x;
	m_targetposV.z = pos.z + Z_DISTANCE;
}

//==========================
//カメラの位置を設定
//==========================
void CCamera::SetPos(D3DXVECTOR3 pos)
{
	//注視点の位置
	m_posR.x = pos.x;
	m_posR.z = pos.z;

	//視点の位置
	m_posV.x = pos.x;
	m_posV.z = pos.z + Z_DISTANCE;
}

//==========================
//カメラの位置を設定
//==========================
void CCamera::SetEditPos(D3DXVECTOR3 pos, D3DXVECTOR3 objectpos)
{
	//注視点の位置
	m_posR.x = objectpos.x;
	m_posR.z = objectpos.z;

	//視点の位置
	m_posV.y = pos.y;
	m_posV.x = objectpos.x;
	m_posV.z = objectpos.z + Z_DISTANCE;

}

//==========================
//ターゲットの位置へ移動
//==========================
void CCamera::TarGetMove()
{
	//フレーム数をカウント
	m_NowFlame++;

	//現在値を求める
	D3DXVECTOR3 posV = D3DXVECTOR3(0.0f, m_posV.y, 0.0f);
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, m_posR.y, 0.0f);

	//相対値を求める
	float Cur = (float)m_NowFlame / (float)m_DrectionFlame;

	//位置の差分を求める
	D3DXVECTOR3 diffposV = m_targetposV - m_posV;
	D3DXVECTOR3 diffposR = m_targetposR - m_posR;

	//現在値を求める
	posV.x = m_posV.x + (diffposV.x * Cur);
	posV.z = m_posV.z + (diffposV.z * Cur);

	posR.x = m_posR.x + (diffposR.x * Cur);
	posR.z = m_posR.z + (diffposR.z * Cur);

	//位置の設定
	m_posV = posV;
	m_posR = posR;
}

//==========================
//演出が終了したか取得
//==========================
bool CCamera::FinishDirection()
{
	if ((int)m_targetposR.z == (int)m_posR.z)
	{
		//フレーム数を初期化
		m_DrectionFlame = 0;
		m_NowFlame = 0;

		return true;
	}

	return false;
}

//==========================
//カメラのロックオン
//==========================
void CCamera::LockOn(D3DXVECTOR3 playerpos, D3DXVECTOR3 enemypos)
{
	D3DXVECTOR3 PlayerPos = playerpos;
	D3DXVECTOR3 TargetPos = enemypos;

	//ベクトルを算出
	D3DXVECTOR3 pos = TargetPos - PlayerPos;

	//ベクトルを正規化
	D3DXVec3Normalize(&pos, &pos);

	m_rot.y = atan2f(pos.x, pos.z) / D3DX_PI;
	
	m_posV.x = PlayerPos.x + pos.x *Z_DISTANCE;
	m_posV.z = PlayerPos.z + pos.z * Z_DISTANCE;
	m_posR.x = enemypos.x;
	m_posR.z = enemypos.z;
}

//==========================
// カメラの入力処理
//==========================
void CCamera::Input(void)
{
	if (!CManager::GetInstance()->GetGameManager()->GetPlayGame()
		|| CManager::GetInstance()->GetScene()==nullptr
		/*|| CManager::GetInstance()->GetGameManager()->GetDirection()*/)
	{//操作説明表示中
		return;
	}

	float angle = CManager::GetInstance()->GetJoypad()->GetRightAngle();

	//視点操作
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_Z)
		|| angle>0.1f)
	{
		if (CManager::GetInstance()->GetScene()->GetScene() == CScene::MODE::GAME)
		{
			m_rot.y += 0.005f;
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_C)
		|| angle <= -0.1f)
	{
		if (CManager::GetInstance()->GetScene()->GetScene() == CScene::MODE::GAME)
		{
			m_rot.y -= 0.005f;
		}
	}
}