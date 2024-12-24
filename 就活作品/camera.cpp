//==========================
// 
// �J��������[camera.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"camera.h"
#include"manager.h"

//�ÓI�����o�ϐ�������
const float CCamera::Y_DISTANCE = 75.0f;//����
const float CCamera::Z_DISTANCE = -200.0f;//����
//==========================
// �R���X�g���N�^
//==========================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, Y_DISTANCE, Z_DISTANCE);//���_
	m_posR = D3DXVECTOR3(0.0f, Y_DISTANCE, 0.0f);//�����_
	m_targetposV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;//�ړI�̎��_
	m_targetposR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
	m_PosVY = 0.0f;
	m_PosRY = 0.0f;
	m_nFlame = 0;
	m_fShapeScale = 0;
}

//==========================
// �f�X�g���N�^
//==========================
CCamera::~CCamera()
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(-100.0f, 10.0f, -200.0f);//���_
	m_posR = D3DXVECTOR3(-50.0f, 70.0f, 0.0f);//�����_
	//m_posV = D3DXVECTOR3(0.0f, Y_DISTANCE, Z_DISTANCE);//���_
	//m_posR = D3DXVECTOR3(0.0f, Y_DISTANCE, 0.0f);//�����_
	//m_posR = D3DXVECTOR3(0.0f, 80.0f, 0.0f);//�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�����
	m_targetposV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;//�ړI�̎��_
	m_targetposR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړI�̒����_
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
	m_PosVY = 0.0f;
	m_PosRY = 0.0f;
	m_nFlame = 0;
	m_fShapeScale = 0;

	return S_OK;
}

//==========================
// �I������
//==========================
void CCamera::Uninit()
{

}

//==========================
// �X�V����
//==========================
void CCamera::Update()
{

	//���͏���
	Input();

	/*m_posR.x += (m_targetposR.x - m_posR.x) * 0.75f;
	m_posV.x += (m_targetposV.x - m_posV.x) * 0.75f;

	m_posR.z += (m_targetposR.z - m_posR.z) * 0.75f;
	m_posV.z += (m_targetposV.z - m_posV.z) * 0.75f;*/

}

#define PLOJECTION (1)//���e���@�؂�ւ�
//==========================
// �J�����̐ݒ�
//==========================
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

#if PLOJECTION
	//�v���W�F�N�V�����}�g���b�N�X���쐬(���ߓ��e)
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),							//����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//��ʂ̃A�X�y�N�g��
		10.0f,											//Z�l�̍ŏ��l
		25000.0f);										//Z�l�̍ő�l

#else

	D3DXMATRIX MatScale;

	//�v���W�F�N�V�����}�g���b�N�X���쐬(���s���e)
	D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_HEIGHT,
		(float)SCREEN_WIDTH,
		10.0f,
		1000.0f);
	D3DXMatrixIdentity(&MatScale);
	D3DXMatrixScaling(&MatScale, 1.0f, 5.0f, 1.0f);
	D3DXMatrixMultiply(&m_mtxProjection, &m_mtxProjection, &MatScale);
#endif



	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
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

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,						//���_
		&posR,						//�����_
		&m_vecU);					//������x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}

//==========================
//�J�����h��ݒ�
//==========================
void CCamera::SetShape(int flame, int scale)
{
	m_nFlame = flame;
	m_fShapeScale = scale;
}

//==========================
//�J�����̈ړ�
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
//�J�����̏c�ړ�
//==========================
void CCamera::VerticalMove(D3DXVECTOR3 pos)
{
	m_posR.y = pos.y;
	m_posR.z = pos.z;

	m_posV.y = pos.y + Y_DISTANCE;
	m_posV.z = pos.z + Z_DISTANCE;
}

//==========================
//�����_�̎擾
//==========================
D3DXVECTOR3& CCamera::GetPosR()
{
	return m_posR;
}

//==========================
//�C���Q�[���ȊO�̃J����
//==========================
void CCamera::OutGame(D3DXVECTOR3 pos)
{
	m_posV = D3DXVECTOR3(-100.0f, 10.0f, -200.0f);//���_
	m_posR = D3DXVECTOR3(-50.0f, 70.0f, 0.0f);//�����_
}

//==========================
//�����̎擾
//==========================
D3DXVECTOR3& CCamera::GetRot()
{
	return m_rot;
}

//==========================
//���ォ��ʂ�
//==========================
void CCamera::Overhead(D3DXVECTOR3 pos)
{
	m_posR.x = pos.x;
	m_posR.z = pos.z;

	m_posV.x = pos.x;
	m_posV.z = pos.z + Z_DISTANCE;

	m_posV.y = 1000.0f;
}

//==========================
// �J�����̓��͏���
//==========================
void CCamera::Input(void)
{
	if (CManager::GetInstance()->GetTutorial()->GetTutorial())
	{//��������\����
		return;
	}
	
	//�J�����̕��s�ړ�
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_H))
	{
		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_T))
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI + 2.355f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI + 2.355f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI + 2.355f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI + 2.355f) * 2.0f;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_G))
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI + 0.785f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI + 0.785f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI + 0.785f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI + 0.785f) * 2.0f;
		}
		else
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI + 1.57f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI + 1.57f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI + 1.57f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI + 1.57f) * 2.0f;
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_F))
	{
		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_T))
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI - 2.355f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI - 2.355f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI - 2.355f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI - 2.355f) * 2.0f;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_G))
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI - 0.785f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI - 0.785f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI - 0.785f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI - 0.785f) * 2.0f;
		}
		else
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI - 1.57f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI - 1.57f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI - 1.57f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI - 1.57f) * 2.0f;
		}
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_T))
	{
		m_PosRY += 1.0f;
		m_posR.y = 0.0f + m_PosRY;

		m_PosVY += 1.0f;
		m_posV.y = Y_DISTANCE + m_PosVY;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_G))
	{
		m_PosRY -= 1.0f;
		m_posR.y = 0.0f + m_PosRY;

		m_PosVY -= 1.0f;
		
		m_posV.y = Y_DISTANCE + m_PosVY;
	}

	/*else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_Q))
	{
		m_posV.x += sinf(m_rot.y * D3DX_PI) * -2.0f;
		m_posV.z += cosf(m_rot.y * D3DX_PI) * -2.0f;
		m_posR.x += sinf(m_rot.y * D3DX_PI) * -2.0f;
		m_posR.z += cosf(m_rot.y * D3DX_PI) * -2.0f;
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_E))
	{
		m_posV.x += sinf(m_rot.y * D3DX_PI) * 2.0f;
		m_posV.z += cosf(m_rot.y * D3DX_PI) * 2.0f;
		m_posR.x += sinf(m_rot.y * D3DX_PI) * 2.0f;
		m_posR.z += cosf(m_rot.y * D3DX_PI) * 2.0f;
	}*/

	float angle = CManager::GetInstance()->GetJoypad()->GetRightAngle();

	//���_����
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_Z)
		|| angle>0.1f)
	{
		if (CManager::GetInstance()->GetScene()->GetScene() == CScene::MODE::GAME)
		{
			m_rot.y += 0.005f;
			m_posV.x = m_posR.x + (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
			m_posV.z = m_posR.z + (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_C)
		|| angle <= -0.1f)
	{
		if (CManager::GetInstance()->GetScene()->GetScene() == CScene::MODE::GAME)
		{
			m_rot.y -= 0.005f;
			m_posV.x = m_posR.x + (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
			m_posV.z = m_posR.z + (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
		}

	}
	/*else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_Y))
	{
		m_PosVY += 1.0f;
		m_posV.x = m_posR.x + (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
		m_posV.y = Y_DISTANCE + m_PosVY;
		m_posV.z = m_posR.z + (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_N))
	{
		m_PosVY -= 1.0f;
		m_posV.x = m_posR.x + (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
		m_posV.y = Y_DISTANCE + m_PosVY;
		m_posV.z = m_posR.z + (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	}*/

	//�����_����
	/*if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_T))
	{
		m_PosRY += 2.0f;
		m_posR.y = 0.0f + m_PosRY;
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_B))
	{
		m_PosRY -= 2.0f;
		m_posR.y = 0.0f + m_PosRY;
	}*/
	/*if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_Q))
	{
		m_rot.y -= 0.01f;
		m_posR.x = m_posV.x - (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
		m_posR.z = m_posV.z - (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_E))
	{
		m_rot.y += 0.01f;
		m_posR.x = m_posV.x - (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
		m_posR.z = m_posV.z - (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	}*/

}