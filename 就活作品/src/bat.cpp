//==========================
// 
// �o�b�g[bat.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bat.h"
#include "manager.h"

//�ÓI�����o������
const int CBat::PRIORITY =2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBat::CBat(int nPriority) :
	CSmallWeapon(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBat::~CBat()
{

}

//==========================
//����������
//==========================
HRESULT CBat::Init()
{
	//�����ݒ�
	CSmallWeapon::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBat::Uninit()
{
	//�I������
	CSmallWeapon::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CBat::Update()
{
	//�X�V����
	CSmallWeapon::Update();
}

//==========================
//�`�揈��
//==========================
void CBat::Draw()
{
	//�`�揈��
	CSmallWeapon::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBat* CBat::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CBat* pSmallWeapon = DBG_NEW CBat;

	//�ʒu�̐ݒ�
	pSmallWeapon->SetPos(pos);

	//�X�P�[���̐ݒ�
	pSmallWeapon->SetScale(scale);

	//�����̐ݒ�
	pSmallWeapon->SetRot(rot);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pSmallWeapon->SetModelIdx(pModel->Regist("data\\MODEL\\bat.x"));
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
	pSmallWeapon->SetSmallWeapon(SMALLWEAPON::BAT);

	//���a�̐ݒ�
	pSmallWeapon->SetRadius(15.0f);

	//�����蔻��̉���
	//pSmallWeapon->CreateVisual();

	//�ϋv�l��ݒ�
	pSmallWeapon->SetDurability(9);

	return pSmallWeapon;
}