//==========================
// 
// ��[sky.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sky.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CSky::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CSky::CSky(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CSky::~CSky()
{

}

//==========================
//����������
//==========================
HRESULT CSky::Init()
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
void  CSky::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CSky::Update()
{
	//�X�V����
	CObjectX::Update();
}

//==========================
//�`�揈��
//==========================
void CSky::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//�J�����O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	
	//�`�揈��
	CObjectX::Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================
//�I�u�W�F�N�g����
//==========================
CSky* CSky::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CSky* pSky = DBG_NEW CSky;

	//�ʒu�̐ݒ�
	pSky->SetPos(pos);

	//�X�P�[���̐ݒ�
	pSky->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pSky->m_nModelIdx = pModel->Regist("data\\MODEL\\sky.x");
	pSky->BindModel(pModel->GetMeshAdress(pSky->m_nModelIdx),
		pModel->GetBuffMatAdress(pSky->m_nModelIdx),
		pModel->GetNumMatAdress(pSky->m_nModelIdx),
		pModel->GetTexIdx(pSky->m_nModelIdx));

	//����������
	pSky->Init();

	return pSky;
}