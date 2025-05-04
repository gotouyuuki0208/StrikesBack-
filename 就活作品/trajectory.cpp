//==========================
// 
// �O�Ղ̕`�揈��[trajectory.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "trajectory.h"
#include "manager.h"
#include "texture.h"

//�ÓI�����o������
const int CTrajectory::PRIORITY = 3;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CTrajectory::CTrajectory(int nPriority) :
	CObjectMesh(nPriority),
	m_nTexIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CTrajectory::~CTrajectory()
{

}

//==========================
//����������
//==========================
HRESULT CTrajectory::Init()
{
	//�����ݒ�
	CObjectMesh::Init();

	//���_���̏�����
	InitVtxPos();

	//���_���W�̐ݒ�
	//SetVertexPos();

	return S_OK;
}

//==========================
//�I������
//==========================
void CTrajectory::Uninit()
{
	//�I������
	CObjectMesh::Uninit();
}

//==========================
//�X�V����
//==========================
void CTrajectory::Update()
{
	//���_���W�̐ݒ�
	SetVertexPos();

	//�X�V����
	CObjectMesh::Update();
}

//==========================
//�`�揈��
//==========================
void CTrajectory::Draw()
{
	//�`�揈��
	CObjectMesh::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CTrajectory* CTrajectory::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Width, int Vertical)
{
	//�C���X�^���X����
	CTrajectory* pTrajectory = DBG_NEW CTrajectory;

	//�ʒu�̐ݒ�
	pTrajectory->SetPos(pos);

	//�T�C�Y�̐ݒ�
	pTrajectory->SetSize(size);

	//���̕�����
	pTrajectory->SetWidthDiv(Width);

	//�c�̕�����
	pTrajectory->SetVerticalDiv(Vertical);

	//�ŏ��̒��_�̈ʒu��ݒ�
	pTrajectory->m_NewPos = pos;

	//�����ݒ�
	pTrajectory->Init();

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pTrajectory->m_nTexIdx = pTex->Regist("data\\TEXTURE\\effect.png");
	pTrajectory->BindTexture(pTex->GetAdress(pTrajectory->m_nTexIdx));

	return pTrajectory;
}

//==========================
//���_���W�̐ݒ�
//==========================
void CTrajectory::SetVertexPos()
{
	if (GetVtxBuff() == nullptr)
	{
		return;
	}

	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@���擾

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̉��̈ʒu
	int WidthPos = 0;

	//���_�̏c�̈ʒu
	int VerticalPos = 0;

	//���_�̏c�����Z�o
	float Height = (GetSize().y * 2) / GetVerticalDiv();

	int a = GetNumVtx();
	//���_���W���ړ�
	for (int i = 0; i < GetNumVtx(); i++)
	{
		if (WidthPos == (VerticalPos + GetWidthDiv()))
		{//���_�̉������Ō�ɂȂ���
			VerticalPos += (GetVerticalDiv() + 1);
		}
		else
		{
			int ChangeNum = i + 1;
			pVtx[i].pos = pVtx[ChangeNum].pos;
		}

		WidthPos++;
	}

	//�V�������W������
	for (int i = 0; i <= GetVerticalDiv(); i++)
	{
		int VtxNum = i * (GetVerticalDiv() + 1) + GetWidthDiv();
		pVtx[VtxNum].pos = D3DXVECTOR3(m_NewPos.x, m_NewPos.y + (GetSize().y + (-Height * i)), m_NewPos.z);
	}

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//==========================
//���_���̏����ݒ�
//==========================
void CTrajectory::InitVtxPos()
{
	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@���擾

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̏c�����Z�o
	float Height = (GetSize().y * 2) / GetVerticalDiv();

	//�V�������W������
	for (int i = 0; i < GetNumVtx(); i++)
	{
		pVtx[i].pos = D3DXVECTOR3(m_NewPos.x, m_NewPos.y + (GetSize().y + (-Height * i)), m_NewPos.z);
	}

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//==========================
//�V�������_���W�̈ʒu��ݒ�
//==========================
void CTrajectory::SetNewPos(D3DXVECTOR3 pos)
{
	m_NewPos = pos;
}