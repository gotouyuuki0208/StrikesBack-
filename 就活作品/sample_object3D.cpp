//==========================
// 
// 3D�|���S���`��T���v��[sample_object3D.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sample_object3D.h"
#include "manager.h"
#include "texture.h"

//�ÓI�����o������
const int CSampleObject3D::PRIORITY = 0;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CSampleObject3D::CSampleObject3D(int nPriority):CObject3D(nPriority), m_nTexIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CSampleObject3D::~CSampleObject3D()
{

}

//==========================
//����������
//==========================
HRESULT CSampleObject3D::Init()
{
	//�����ݒ�
	CObject3D::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CSampleObject3D::Uninit()
{
	//�I������
	CObject3D::Uninit();
}

//==========================
//�X�V����
//==========================
void CSampleObject3D::Update()
{
	//�X�V����
	CObject3D::Update();
}

//==========================
//�`�揈��
//==========================
void CSampleObject3D::Draw()
{
	//�`�揈��
	CObject3D::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CSampleObject3D* CSampleObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CSampleObject3D* pSampleObject3D = DBG_NEW CSampleObject3D;

	//�ʒu�̐ݒ�
	pSampleObject3D->SetPos(pos);

	//�傫���̐ݒ�
	pSampleObject3D->SetSize(size);

	//����������
	pSampleObject3D->Init();

	//�e�N�X�`���ݒ�
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pSampleObject3D->m_nTexIdx = pTex->Regist("data\\TEXTURE\\blood.png");
	pSampleObject3D->BindTexture(pTex->GetAdress(pSampleObject3D->m_nTexIdx));*/

	return pSampleObject3D;
}