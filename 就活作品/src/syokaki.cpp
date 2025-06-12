//==========================
// 
// �o�b�g[bat.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "syokaki.h"
#include "manager.h"

//�ÓI�����o������
const int CSyokaki::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CSyokaki::CSyokaki(int nPriority) :
	CSmallWeapon(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CSyokaki::~CSyokaki()
{

}

//==========================
//����������
//==========================
HRESULT CSyokaki::Init()
{
	//�����ݒ�
	CSmallWeapon::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CSyokaki::Uninit()
{
	//�I������
	CSmallWeapon::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CSyokaki::Update()
{
	//�X�V����
	CSmallWeapon::Update();

	SetRot(D3DXVECTOR3(1.57f, GetRot().y, GetRot().z));
}

//==========================
//�`�揈��
//==========================
void CSyokaki::Draw()
{
	//�`�揈��
	CSmallWeapon::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CSyokaki* CSyokaki::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CSyokaki* pSmallWeapon = DBG_NEW CSyokaki;

	//�ʒu�̐ݒ�
	pSmallWeapon->SetPos(pos);

	//�X�P�[���̐ݒ�
	pSmallWeapon->SetScale(scale);

	//�����̐ݒ�
	pSmallWeapon->SetRot(D3DXVECTOR3(1.57f, rot.y, rot.z));

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pSmallWeapon->SetModelIdx(pModel->Regist("data\\MODEL\\syokaki.x"));
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
	pSmallWeapon->SetSmallWeapon(SMALLWEAPON::SYOKAKI);

	//���a�̐ݒ�
	pSmallWeapon->SetRadius(15.0f);

	//�����蔻��̉���
	//pSmallWeapon->CreateVisual();

	//�ϋv�l��ݒ�
	pSmallWeapon->SetDurability(9);

	return pSmallWeapon;
}