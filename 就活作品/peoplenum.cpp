//==========================
// 
// �^�C�g�����S[PeopleNum.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"peoplenum.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int CPeopleNum::PRIORITY = 4;//�`��D��x
int  CPeopleNum::m_nTexIdx = 0;//�e�N�X�`��ID
//========================
//�R���X�g���N�^
//========================
CPeopleNum::CPeopleNum(int nPriority) :CObject2D(nPriority)
{

}

//========================
//�f�X�g���N�^
//========================
CPeopleNum::~CPeopleNum()
{

}

//========================
//�����ݒ�
//========================
HRESULT CPeopleNum::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void CPeopleNum::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void CPeopleNum::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void CPeopleNum::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
CPeopleNum* CPeopleNum::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CPeopleNum* pPeopleNum = DBG_NEW CPeopleNum;

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pPeopleNum->m_nTexIdx = pTex->Regist("data\\TEXTURE\\People.png");
	pPeopleNum->BindTexture(pTex->GetAdress(pPeopleNum->m_nTexIdx));

	//�ʒu�̐ݒ�
	pPeopleNum->SetPos(pos);

	//�T�C�Y�ݒ�
	pPeopleNum->SetSize(50.0f, 50.0f);

	//�F��ݒ�
	pPeopleNum->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�����ݒ�
	pPeopleNum->Init();

	return pPeopleNum;
}