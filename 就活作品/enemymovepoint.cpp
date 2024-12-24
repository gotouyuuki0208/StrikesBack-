//==========================
// 
// �G�̈ړ��n�_[enemymovepoint.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "enemymovepoint.h"
#include "manager.h"
#include "texture.h"

//�ÓI�����o������
const int CEnemyMovePoint::PRIORITY = 0;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CEnemyMovePoint::CEnemyMovePoint(int nPriority) :
	CFild(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CEnemyMovePoint::~CEnemyMovePoint()
{

}

//==========================
//����������
//==========================
HRESULT CEnemyMovePoint::Init()
{
	//�����ݒ�
	CFild::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CEnemyMovePoint::Uninit()
{
	//�I������
	CFild::Uninit();
}

//==========================
//�X�V����
//==========================
void CEnemyMovePoint::Update()
{
	//�X�V����
	CFild::Update();
}

//==========================
//�`�揈��
//==========================
void CEnemyMovePoint::Draw()
{
#ifdef _DEBUG

	//�`�揈��
	CFild::Draw();

#endif

}

//==========================
//�I�u�W�F�N�g����
//==========================
CEnemyMovePoint* CEnemyMovePoint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CEnemyMovePoint* pEnemyMovePoint = DBG_NEW CEnemyMovePoint;

	//�ʒu�̐ݒ�
	pEnemyMovePoint->SetPos(D3DXVECTOR3(pos.x, 0.5f, pos.z));

	//�傫���̐ݒ�
	pEnemyMovePoint->SetSize(size);

	//�傫���̐ݒ�
	pEnemyMovePoint->SetRot(rot);

	//�F�̐ݒ�
	pEnemyMovePoint->SetCor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//����������
	pEnemyMovePoint->Init();

	//�e�N�X�`���ݒ�
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pEnemyMovePoint->m_nTexIdx = pTex->Regist("data\\TEXTURE\\blood.png");
	pEnemyMovePoint->BindTexture(pTex->GetAdress(pEnemyMovePoint->m_nTexIdx));*/

	//�^�C�v�ݒ�
	pEnemyMovePoint->SetType(TYPE::FILD);
	pEnemyMovePoint->SetFild(FILDTYPE::ENEMYMOVEPOINT);

	return pEnemyMovePoint;
}