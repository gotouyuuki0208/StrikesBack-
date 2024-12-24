//==========================
// 
// �T���h�o�b�O[punchingbug.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "punchingbag.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
//�ÓI�����o������
const int CPunchingBag::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CPunchingBag::CPunchingBag(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CPunchingBag::~CPunchingBag()
{

}

//==========================
//����������
//==========================
HRESULT CPunchingBag::Init()
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
void  CPunchingBag::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CPunchingBag::Update()
{
	//�X�V����
	CObjectX::Update();
}

//==========================
//�`�揈��
//==========================
void CPunchingBag::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CPunchingBag* CPunchingBag::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CPunchingBag* pPunchingBag = DBG_NEW CPunchingBag;

	//�ʒu�̐ݒ�
	pPunchingBag->SetPos(pos);

	//�X�P�[���̐ݒ�
	pPunchingBag->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pPunchingBag->m_nModelIdx = pModel->Regist("data\\MODEL\\punchingbag.x");
	pPunchingBag->BindModel(pModel->GetMeshAdress(pPunchingBag->m_nModelIdx),
		pModel->GetBuffMatAdress(pPunchingBag->m_nModelIdx),
		pModel->GetNumMatAdress(pPunchingBag->m_nModelIdx),
		pModel->GetTexIdx(pPunchingBag->m_nModelIdx));

	//����������
	pPunchingBag->Init();

	return pPunchingBag;
}