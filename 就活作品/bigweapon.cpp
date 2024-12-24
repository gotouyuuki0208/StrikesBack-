//==========================
// 
// �傫������[bigweapon.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bigweapon.h"
#include "manager.h"

//�ÓI�����o������
const int CBigWeapon::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBigWeapon::CBigWeapon(int nPriority):
	CWeapon(nPriority),
	m_BigWeapontype(BIGWEAPON::NONE)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBigWeapon::~CBigWeapon()
{

}

//==========================
//����������
//==========================
HRESULT CBigWeapon::Init()
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
void  CBigWeapon::Uninit()
{
	//�I������
	CWeapon::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CBigWeapon::Update()
{
	//�X�V����
	CWeapon::Update();
}

//==========================
//�`�揈��
//==========================
void CBigWeapon::Draw()
{
	//�`�揈��
	CWeapon::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBigWeapon* CBigWeapon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, const char ModelName[256])
{
	//�C���X�^���X����
	CBigWeapon* pBigWeapon = DBG_NEW CBigWeapon;

	//�ʒu�̐ݒ�
	pBigWeapon->SetPos(pos);

	//�X�P�[���̐ݒ�
	pBigWeapon->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBigWeapon->SetModelIdx(pModel->Regist(ModelName));
	pBigWeapon->BindModel(pModel->GetMeshAdress(pBigWeapon->GetModelIdx()),
		pModel->GetBuffMatAdress(pBigWeapon->GetModelIdx()),
		pModel->GetNumMatAdress(pBigWeapon->GetModelIdx()),
		pModel->GetTexIdx(pBigWeapon->GetModelIdx()));

	//����������
	pBigWeapon->Init();

	//�^�C�v��ݒ�
	pBigWeapon->SetType(TYPE::WEAPON);

	//����̎�ނ�ݒ�
	pBigWeapon->SetWeaponType(WEAPONTYPE::BIG);

	//���a�̐ݒ�
	pBigWeapon->SetRadius(15.0f);

	//�����蔻��̉���
	pBigWeapon->CreateVisual();

	return pBigWeapon;
}

//==========================
//���蕐��̎�ނ�ݒ�
//==========================
void CBigWeapon::SetBigWeapon(BIGWEAPON type)
{
	m_BigWeapontype = type;
}

//==========================
//���蕐��̎�ނ��擾
//==========================
CBigWeapon::BIGWEAPON CBigWeapon::GetBigWeapon()
{
	return m_BigWeapontype;
}