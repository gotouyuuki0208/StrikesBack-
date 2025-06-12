//==========================
// 
// 2D�|���S���`��T���v��[sample_object2D.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sample_object2D.h"
#include "texture.h"
#include "manager.h"

//�ÓI�����o������
const int CSampleObject2D::PRIORITY = 3;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CSampleObject2D::CSampleObject2D(int nPriority):CObject2D(nPriority),m_nTexIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CSampleObject2D::~CSampleObject2D()
{

}

//==========================
//����������
//==========================
HRESULT CSampleObject2D::Init()
{
	//�����ݒ�
	CObject2D::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CSampleObject2D::Uninit()
{
	//�I������
	CObject2D::Uninit();
}

//==========================
//�X�V����
//==========================
void  CSampleObject2D::Update()
{
	//�A�j���[�V����
	//CObject2D::Animetion(2.0f, 5, 10);

	//�X�V����
	CObject2D::Update();
}

//==========================
//�`�揈��
//==========================
void CSampleObject2D::Draw()
{
	//�`�揈��
	CObject2D::Draw();
}

//==========================
//�I�u�W�F�N�g2D����
//==========================
CSampleObject2D* CSampleObject2D::Create(D3DXVECTOR3 pos,float vertical, float width)
{
	//�C���X�^���X����
	CSampleObject2D* pSampleObject2D = DBG_NEW CSampleObject2D;

	//�ʒu�̐ݒ�
	pSampleObject2D->SetPos(pos);

	//�傫���̐ݒ�
	pSampleObject2D->SetSize(vertical, width);

	//����������
	pSampleObject2D->Init();
	
	//�F�̐ݒ�
	pSampleObject2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�e�N�X�`���̐ݒ�
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pSampleObject2D->m_nTexIdx = pTex->Regist("data\\TEXTURE\\runningman102.png");
	pSampleObject2D->BindTexture(pTex->GetAdress(pSampleObject2D->m_nTexIdx));*/

	//�e�N�X�`���̑傫���ݒ�
	//pSampleObject2D->SetTexSize(2.0f, 5, 0);

	return pSampleObject2D;
}