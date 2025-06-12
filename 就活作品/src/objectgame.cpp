//==========================
// 
// �Q�[���I�u�W�F�N�g[objectgame.h]
// Author Yuki Goto
//
//==========================

//include
#include"objectgame.h"

//==========================
// �R���X�g���N�^
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
// �f�X�g���N�^
//==========================
CObjectgame::~CObjectgame()
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CObjectgame::Init(void)
{
	return S_OK;
}

//==========================
// �I������
//==========================
void CObjectgame::Uninit(void)
{

}

//==========================
// �X�V����
//==========================
void CObjectgame::Update(void)
{

}

//==========================
// �`�揈��
//==========================
void CObjectgame::Draw(void)
{

}

//==========================
//�ʒu�擾
//==========================
D3DXVECTOR3& CObjectgame::GetPos(void)
{
	return m_pos;
}

//==========================
//�ʒu�ݒ�
//==========================
void CObjectgame::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==========================
//�ʒu�擾
//==========================
D3DXVECTOR3& CObjectgame::GetRot(void)
{
	return m_rot;
}

//==========================
//�ʒu�ݒ�
//==========================
void CObjectgame::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==========================
//�̂̈ʒu�擾
//==========================
D3DXVECTOR3& CObjectgame::GetPosOld(void)
{
	return m_posold;
}

//==========================
//�̂̈ʒu�ݒ�
//==========================
void CObjectgame::SetPosOld(D3DXVECTOR3 posord)
{
	m_posold = posord;
}

//==========================
//�ړ��l�擾
//==========================
D3DXVECTOR3& CObjectgame::GetMove(void)
{
	return m_posmove;
}

//==========================
//�ړ��l�ݒ�
//==========================
void CObjectgame::SetMove(D3DXVECTOR3 move)
{
	m_posmove = move;
}

//==========================
//�����̈ړ��l�擾
//==========================
D3DXVECTOR3& CObjectgame::GetRotMove()
{
	return m_rotmove;
}

//==========================
//�����̈ړ��l�ݒ�
//==========================
void CObjectgame::SetRotMove(D3DXVECTOR3 rot)
{
	m_rotmove = rot;
}

//==========================
//�}�g���b�N�X�擾
//==========================
D3DXMATRIX& CObjectgame::GetMtxWorld()
{
	return m_mtxWorld;
}

//==========================
//�}�g���b�N�X�̐ݒ�
//==========================
void CObjectgame::SetMtxWorld(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}

//==========================
//���a�̐ݒ�
//==========================
void CObjectgame::SetRadius(float radius)
{
	m_radius = radius;
}

//==========================
//���a�̎擾
//==========================
float CObjectgame::GetRadius()
{
	return m_radius;
}

//==========================
//�g�嗦�̐ݒ�
//==========================
void CObjectgame::SetScale(D3DXVECTOR3 scale)
{
	m_scale = scale;
}

//==========================
//�g�嗦�̐ݒ�
//==========================
D3DXVECTOR3& CObjectgame::GetScale()
{
	return m_scale;
}

//==========================
//�����̕␳
//==========================
float CObjectgame::RevisionRot(float objectiverot, float currentrot, float Cur)
{
	float difference = objectiverot - currentrot;//�ړI�̌����ƌ��݂̌����̍��������߂�

	if (-D3DX_PI > difference)
	{//������3.14�𒴂��Ă���Ƃ�
		difference += D3DX_PI * 2;
	}
	else if (D3DX_PI < difference)
	{
		difference -= D3DX_PI * 2;
	}

	//�����ݒ�
	float rot = difference * Cur;

	return rot;
}

//==========================
//�����̐��K��
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
//�x�N�g���̎Z�o
//==========================
float CObjectgame::VectorCalculation(float purpose,float current)
{
	float Vector = purpose - current;

	return Vector;
}
