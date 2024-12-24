//==========================
// 
// ���]��[bicycle.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bicycle.h"
#include "manager.h"

//�ÓI�����o������
const int CBicycle::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBicycle::CBicycle(int nPriority) :
	CBigWeapon(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBicycle::~CBicycle()
{

}

//==========================
//����������
//==========================
HRESULT CBicycle::Init()
{
	//�����ݒ�
	CBigWeapon::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBicycle::Uninit()
{
	//�I������
	CBigWeapon::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CBicycle::Update()
{
	//�X�V����
	CBigWeapon::Update();
}

//==========================
//�`�揈��
//==========================
void CBicycle::Draw()
{
	//�`�揈��
	CBigWeapon::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBicycle* CBicycle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CBicycle* pBigWeapon = DBG_NEW CBicycle;

	//�ʒu�̐ݒ�
	pBigWeapon->SetPos(pos);

	//�X�P�[���̐ݒ�
	pBigWeapon->SetScale(scale);

	//�����̐ݒ�
	pBigWeapon->SetRot(rot);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBigWeapon->SetModelIdx(pModel->Regist("data\\MODEL\\bicycle.x"));
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
	pBigWeapon->SetBigWeapon(BIGWEAPON::BICYCLE);

	//���a�̐ݒ�
	pBigWeapon->SetRadius(15.0f);

	//�����蔻��̉���
	//pBigWeapon->CreateVisual();

	//�ϋv�l��ݒ�
	pBigWeapon->SetDurability(15);

	return pBigWeapon;
}