//==========================
// 
// �Ў蕐��[smallweapon.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "smallweapon.h"
#include "manager.h"

//�ÓI�����o������
const int CSmallWeapon::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CSmallWeapon::CSmallWeapon(int nPriority) :
	CWeapon(nPriority),
	m_SmallWeapontype(SMALLWEAPON::NONE)
{

}

//==========================
//�f�X�g���N�^
//==========================
CSmallWeapon::~CSmallWeapon()
{

}

//==========================
//����������
//==========================
HRESULT CSmallWeapon::Init()
{
	//�T�C�Y�ݒ�
	//SetSize();

	//�����ݒ�
	CWeapon::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CSmallWeapon::Uninit()
{
	//�I������
	CWeapon::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CSmallWeapon::Update()
{
	//�X�V����
	CWeapon::Update();
}

//==========================
//�`�揈��
//==========================
void CSmallWeapon::Draw()
{
	//�`�揈��
	CWeapon::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CSmallWeapon* CSmallWeapon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, const char ModelName[256])
{
	//�C���X�^���X����
	CSmallWeapon* pSmallWeapon = DBG_NEW CSmallWeapon;

	//�ʒu�̐ݒ�
	pSmallWeapon->SetPos(pos);

	//�X�P�[���̐ݒ�
	pSmallWeapon->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pSmallWeapon->SetModelIdx(pModel->Regist(ModelName));
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

	//���a�̐ݒ�
	pSmallWeapon->SetRadius(15.0f);

	//�����蔻��̉���
	pSmallWeapon->CreateVisual();

	return pSmallWeapon;
}

//==========================
//�Ў蕐��̎�ނ�ݒ�
//==========================
void CSmallWeapon::SetSmallWeapon(SMALLWEAPON type)
{
	m_SmallWeapontype = type;
}

//==========================
//�Ў蕐��̎�ނ��擾
//==========================
CSmallWeapon::SMALLWEAPON CSmallWeapon::GetSmallWeapon()
{
	return m_SmallWeapontype;
}