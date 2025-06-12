//==========================
// 
// �z�B��[deliveryperson.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "deliveryperson.h"
#include "manager.h"
#include "model.h"
#include"drink.h"

//�ÓI�����o������
const int CDeliveryPerson::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CDeliveryPerson::CDeliveryPerson(int nPriority):
CMotionModel(nPriority),//���R���X�g���N�^
m_life(3),//����
m_Move(true)//�ړ�����
{

}

//==========================
//�f�X�g���N�^
//==========================
CDeliveryPerson::~CDeliveryPerson()
{

}

//==========================
//����������
//==========================
HRESULT CDeliveryPerson::Init()
{
	//�����ݒ�
	CMotionModel::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CDeliveryPerson::Uninit()
{
	//�I������
	CMotionModel::Uninit();
}

//==========================
//�X�V����
//==========================
void CDeliveryPerson::Update()
{
	if (m_Move)
	{//�ړ��o���鎞
		move();//�ړ�����
	}
	//�X�V����
	CMotionModel::Update();
	CMotionModel::Motion();
}

//==========================
//�`�揈��
//==========================
void CDeliveryPerson::Draw()
{
	//�`�揈��
	CMotionModel::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CDeliveryPerson* CDeliveryPerson::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CDeliveryPerson* pDeliveryPerson = DBG_NEW CDeliveryPerson;

	//�ʒu�̐ݒ�
	pDeliveryPerson->SetPos(pos);

	//����������
	pDeliveryPerson->Init();

	//���a�̐ݒ�
	pDeliveryPerson->SetRadius(15.0f);

	//�t�@�C����ǂݍ���
	pDeliveryPerson->LoadFile("data\\MOTION\\motion_player_15.txt", scale);
	
	//�^�C�v�ݒ�
	pDeliveryPerson->SetType(TYPE::DELIVERY);
	
	return pDeliveryPerson;
}

//==========================
//�ړ�����
//==========================
void CDeliveryPerson::move()
{
	SetPos(D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z + 1.0f));
}

//==========================
//�_���[�W����
//==========================
void CDeliveryPerson::Damage(int Damage)
{
	m_life -= Damage;

	if (m_life <= 0)
	{
		Uninit();
		CDrink::Create(GetPos(), D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	}
}

//==========================
//�ړ��\��Ԃɂ���
//==========================
void CDeliveryPerson::Movable()
{
	m_Move = true;
}

//==========================
//�ړ��s�\��Ԃɂ���
//==========================
void CDeliveryPerson::Immovable()
{
	m_Move = false;
}