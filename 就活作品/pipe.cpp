//==========================
// 
// �S�p�C�v[pipe.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "pipe.h"
#include "manager.h"

//�ÓI�����o������
const int CPipe::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CPipe::CPipe(int nPriority) :
	CSmallWeapon(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CPipe::~CPipe()
{

}

//==========================
//����������
//==========================
HRESULT CPipe::Init()
{
	//�����ݒ�
	CSmallWeapon::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CPipe::Uninit()
{
	//�I������
	CSmallWeapon::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CPipe::Update()
{
	//�X�V����
	CSmallWeapon::Update();
}

//==========================
//�`�揈��
//==========================
void CPipe::Draw()
{
	//�`�揈��
	CSmallWeapon::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CPipe* CPipe::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CPipe* pSmallWeapon = DBG_NEW CPipe;

	//�ʒu�̐ݒ�
	pSmallWeapon->SetPos(pos);

	//�X�P�[���̐ݒ�
	pSmallWeapon->SetScale(scale);

	//�����̐ݒ�
	pSmallWeapon->SetRot(rot);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pSmallWeapon->SetModelIdx(pModel->Regist("data\\MODEL\\iron_pipe.x"));
	pSmallWeapon->BindModel(pModel->GetMeshAdress(pSmallWeapon->GetModelIdx()),
		pModel->GetBuffMatAdress(pSmallWeapon->GetModelIdx()),
		pModel->GetNumMatAdress(pSmallWeapon->GetModelIdx()),
		pModel->GetTexIdx(pSmallWeapon->GetModelIdx()));

	//����������
	pSmallWeapon->Init();

	//�^�C�v��ݒ�
	pSmallWeapon->SetType(TYPE::WEAPON);

	//����̎�ނ�ݒ�
	pSmallWeapon->SetWeaponType(WEAPONTYPE::SMALL);
	pSmallWeapon->SetSmallWeapon(SMALLWEAPON::PIPE);

	//���a�̐ݒ�
	pSmallWeapon->SetRadius(15.0f);

	//�����蔻��̉���
	//pSmallWeapon->CreateVisual();

	//�ϋv�l��ݒ�
	pSmallWeapon->SetDurability(9);

	return pSmallWeapon;
}