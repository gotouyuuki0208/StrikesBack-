//==========================
// 
// 3D���f���`��T���v��[sample_objectX.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sample_objectX.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CSampleObjectX::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CSampleObjectX::CSampleObjectX(int nPriority):CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CSampleObjectX::~CSampleObjectX()
{

}

//==========================
//����������
//==========================
HRESULT CSampleObjectX::Init()
{
	//�T�C�Y�ݒ�
	//SetSize();

	//�����ݒ�
	CObjectX::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CSampleObjectX::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CSampleObjectX::Update()
{
	//�X�V����
	CObjectX::Update();
}

//==========================
//�`�揈��
//==========================
void CSampleObjectX::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CSampleObjectX* CSampleObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CSampleObjectX* pSampleObjectX = DBG_NEW CSampleObjectX;

	//�ʒu�̐ݒ�
	pSampleObjectX->SetPos(pos);

	//�X�P�[���̐ݒ�
	pSampleObjectX->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pSampleObjectX->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pSampleObjectX->BindModel(pModel->GetMeshAdress(pSampleObjectX->m_nModelIdx),
		pModel->GetBuffMatAdress(pSampleObjectX->m_nModelIdx),
		pModel->GetNumMatAdress(pSampleObjectX->m_nModelIdx),
		pModel->GetTexIdx(pSampleObjectX->m_nModelIdx));

	//����������
	pSampleObjectX->Init();

	return pSampleObjectX;
}