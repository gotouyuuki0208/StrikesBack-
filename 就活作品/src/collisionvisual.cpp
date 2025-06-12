//==========================
// 
// �����蔻�����[collisionvisual.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "collisionvisual.h"
#include "manager.h"

//==========================
//�R���X�g���N�^
//==========================
CCollisionVisual::CCollisionVisual():
m_pMesh(nullptr),//���b�V��(���_���)�ւ̃|�C���^
m_radius(0.0f),//���a
m_pos(0.0f,0.0f,0.0f),//�ʒu
m_rot(0.0f, 0.0f, 0.0f),//����
m_mtxWorld()//���[���h�}�g���b�N�X
{
	m_cor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//==========================
//�f�X�g���N�^
//==========================
CCollisionVisual::~CCollisionVisual()
{

}

//==========================
//����������
//==========================
HRESULT CCollisionVisual::Init()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾
	D3DXCreateSphere(pDevice, m_radius, 10, 7, &m_pMesh, NULL);//���̃��b�V������

	SetColNomal();//�ʏ�̐F�ɐݒ�

	return S_OK;
}

//==========================
//�I������
//==========================
void  CCollisionVisual::Uninit()
{
	//���b�V���̔j��
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	delete this;
}

//==========================
//�X�V����
//==========================
void CCollisionVisual::Update()
{

}

//==========================
//�`�揈��
//==========================
void CCollisionVisual::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL Mat{};//�}�e���A��

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�g���b�N�X���擾
	pDevice->GetMaterial(&matDef);

	//�@���̒�����1�ɂ���
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//�F�̐ݒ�
	Mat.MatD3D.Diffuse = m_cor;

	//�}�e���A���̐ݒ�
	pDevice->SetMaterial(&Mat.MatD3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�`��
	m_pMesh->DrawSubset(0);

	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//==========================
//�I�u�W�F�N�g����
//==========================
CCollisionVisual* CCollisionVisual::Create(D3DXVECTOR3 pos, float radius)
{
	//�C���X�^���X����
	CCollisionVisual* pVisualization = DBG_NEW CCollisionVisual;

	//�ʒu�̐ݒ�
	pVisualization->m_pos = pos;

	//���a�̐ݒ�
	pVisualization->m_radius = radius;
	
	//����������
	pVisualization->Init();

	return pVisualization;
}

//==========================
//�ʒu�̐ݒ�
//==========================
void CCollisionVisual::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==========================
//�ʏ�̐F�ɐݒ�
//==========================
void CCollisionVisual::SetColNomal()
{
	m_cor = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.3f);
}

//==========================
//�Փ˂��Ă���Ƃ��̐F�ɐݒ�
//==========================
void CCollisionVisual::SetColCollision()
{
	m_cor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);
}

//==========================
//���a���擾
//==========================
float CCollisionVisual::GetRadius()
{
	return m_radius;
}

//==========================
//�ʒu���擾
//==========================
D3DXVECTOR3& CCollisionVisual::GetPos()
{
	return m_pos;
}