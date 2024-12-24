//==========================
// 
// ����[weapon.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "weapon.h"
#include "manager.h"
#include "model.h"
#include "enemy.h"
#include"player.h"

//�ÓI�����o������
const int CWeapon::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CWeapon::CWeapon(int nPriority) :
CObjectX(nPriority),//���R���X�g���N�^
//m_nModelIdx(0),//���f���̔ԍ�
m_Attack(false),//�U������
m_weapontype(WEAPONTYPE::NONE),//����̎��
m_Parent(nullptr),//�e���f��
m_ModelIdx(0),//���f���̔ԍ�
m_WeaponPoint(nullptr),//����̈ʒu�\��
m_Transparent(false),//�����x�̏㉺����
m_visual(nullptr),//�����蔻��̉���
m_Garb(false),//�L�����N�^�[�������Ă邩����
m_Durability(0)//�ϋv�l
{
	
}

//==========================
//�f�X�g���N�^
//==========================
CWeapon::~CWeapon()
{

}

//==========================
//����������
//==========================
HRESULT CWeapon::Init()
{
	//�T�C�Y�ݒ�
	SetSize();

	//�����ݒ�
	CObjectX::Init();
	
	//UI�𐶐�
	m_WeaponPoint = CWeaponPoint::Create(D3DXVECTOR3(GetPos().x, GetPos().y + GetVtxMax().y + 15.0f, GetPos().z), D3DXVECTOR3(5.0f, 5.0f, 0.0f));
	
	return S_OK;
}

//==========================
//�I������
//==========================
void  CWeapon::Uninit()
{
	//�I������
	CObjectX::Uninit();

	if (m_WeaponPoint != nullptr)
	{
		m_WeaponPoint->Uninit();
		m_WeaponPoint = nullptr;
	}

	if (m_visual != nullptr)
	{
		m_visual->Uninit();
		m_visual = nullptr;
	}

	Release();
}

//==========================
//�X�V����
//==========================
void CWeapon::Update()
{
	if (m_Garb)
	{//�͂܂�Ă�Ƃ�
		return;
	}

	ColisionPlayer();

	//�X�V����
	CObjectX::Update();

	
}

//==========================
//�`�揈��
//==========================
void CWeapon::Draw()
{
	if (m_Garb)
	{//�͂܂�Ă�Ƃ�
		return;
	}

	//�`�揈��
	CObjectX::Draw();

	if (m_visual != nullptr)
	{
		//m_visual->Draw();
	}
}

//==========================
//�I�u�W�F�N�g����
//==========================
CWeapon* CWeapon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CWeapon* pWeapon = DBG_NEW CWeapon;

	//�ʒu�̐ݒ�
	pWeapon->SetPos(pos);

	//�����̐ݒ�
	pWeapon->SetRot(D3DXVECTOR3(1.57f, 0.0f, 0.0f));

	//�X�P�[���̐ݒ�
	pWeapon->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pWeapon->m_ModelIdx = pModel->Regist("data\\MODEL\\bat.x");
	pWeapon->BindModel(pModel->GetMeshAdress(pWeapon->m_ModelIdx),
		pModel->GetBuffMatAdress(pWeapon->m_ModelIdx),
		pModel->GetNumMatAdress(pWeapon->m_ModelIdx),
		pModel->GetTexIdx(pWeapon->m_ModelIdx));

	//����������
	pWeapon->Init();

	//�^�C�v��ݒ�
	pWeapon->SetType(TYPE::WEAPON);
	
	return pWeapon;
}

//==========================
//�e�̐ݒ�
//==========================
void CWeapon::SetParent(CModelParts* Parent)
{
	m_Parent = Parent;
}

//==========================
//�G�Ƃ̓����蔻��
//==========================
void CWeapon::CollisionEnemy()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//�I�u�W�F�N�g���G�l�~�[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = (CEnemy*)pObj;

		bool Colision = ColisionSphere(D3DXVECTOR3(GetMtxWorld()._41, GetMtxWorld()._42 + 5.0f, GetMtxWorld()._43),
			D3DXVECTOR3(pEnemy->GetPartsMtx(0)._41, pEnemy->GetPartsMtx(0)._42, pEnemy->GetPartsMtx(0)._43),
			10.0f,
			30.0f);

		if (Colision
			&&!m_Attack)
		{
			//pEnemy->Damage(D3DXVECTOR3(GetMtxWorld()._41, GetMtxWorld()._42, GetMtxWorld()._43),1);
			m_Attack = true;
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}
}

//==========================
//�U�������߂�
//==========================
void CWeapon::SetAttackReset()
{
	m_Attack = false;
}

//==========================
//����̎�ނ��擾
//==========================
CWeapon::WEAPONTYPE CWeapon::GetWeaponType()
{
	return m_weapontype;
}

//==========================
//����̎�ނ�ݒ�
//==========================
void CWeapon::SetWeaponType(WEAPONTYPE weapontype)
{
	m_weapontype = weapontype;
}

//==========================
//���f���̔ԍ����擾
//==========================
int CWeapon::GetModelIdx()
{
	return m_ModelIdx;
}

//==========================
//���f���̔ԍ���ݒ�
//==========================
void CWeapon::SetModelIdx(int num)
{
	m_ModelIdx = num;
}

//==========================
//����������o����Ƃ��̔���
//==========================
void CWeapon::Reaction()
{
	if (m_Transparent)
	{
		SetTransparent(GetTransparent() + 0.03f);//�����x��������
	}
	else
	{
		SetTransparent(GetTransparent() - 0.03f);//�����x��������
	}

	if (GetTransparent() > 1.0f)
	{
		m_Transparent = false;
	}
	else if (GetTransparent() < 0.8f)
	{
		m_Transparent = true;
	}
}

//==========================
//�X�P�[�������Z�b�g
//==========================
void CWeapon::Reset()
{
	m_Transparent = false;
	SetTransparent(1.0f);
}

//==========================
//�v���C���[�Ƃ̓����蔻��
//==========================
void CWeapon::ColisionPlayer()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CPlayer::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::PLAYER)
		{//�I�u�W�F�N�g���v���C���[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		bool Colision = ColisionSphere(GetPos(),
			pPlayer->GetPos(),
			GetRadius() - 1.0f,
			pPlayer->GetRadius() - 1.0f);

		if (Colision)
		{

			D3DXVECTOR3 Vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����x�N�g��
			D3DXVECTOR3 NormalizeVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���K�������x�N�g��

			//�����x�N�g�����Z�o
			Vector.x = VectorCalculation(pPlayer->GetPos().x, GetPos().x);
			Vector.z = VectorCalculation(pPlayer->GetPos().z, GetPos().z);

			//�x�N�g���𐳋K��
			D3DXVec3Normalize(&NormalizeVec, &Vector);

			//�ʒu��ύX
			pPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x + NormalizeVec.x * floor((GetRadius() - 1.0f + pPlayer->GetRadius())),
				GetPos().y,
				GetPos().z + NormalizeVec.z * floor((GetRadius()-1.0f + pPlayer->GetRadius()))));
		}

		Colision = ColisionSphere(GetPos(),
			pPlayer->GetPos(),
			GetRadius(),
			pPlayer->GetRadius());

		if (Colision)
		{
			Reaction();//�����x��ύX
		}
		else
		{
			Reset();//�����x�����Z�b�g
		}
		break;
	}
}

//==========================
//�����蔻�����������
//==========================
void CWeapon::CreateVisual()
{
	if (m_visual == nullptr)
	{
		//m_visual = CCollisionVisual::Create(GetPos(), GetRadius());
	}
}

//==========================
//�L�����N�^�[�ɒ͂܂ꂽ
//==========================
void CWeapon::GrabCharacter()
{
	m_Garb = true;

	m_WeaponPoint->Uninit();
	m_WeaponPoint = nullptr;
}

//==========================
//�L�����N�^�[��������
//==========================
void CWeapon::ReleseCharacter(D3DXVECTOR3 pos)
{
	//�ʒu��ύX
	SetPos(pos);
	//m_visual->SetPos(GetPos());

	//UI�𐶐�
	m_WeaponPoint = CWeaponPoint::Create(D3DXVECTOR3(GetPos().x, GetPos().y + GetVtxMax().y + 15.0f, GetPos().z), D3DXVECTOR3(5.0f, 5.0f, 0.0f));

	//������Ă��Ԃɂ���
	m_Garb = false;
}

//==========================
//�͂܂�Ă邩�擾
//==========================
bool CWeapon::GetGrab()
{
	return m_Garb;
}

//==========================
//�ϋv�l�̐ݒ�
//==========================
void CWeapon::SetDurability(int Num)
{
	m_Durability = Num;
}

//==========================
//�ϋv�l�̎擾
//==========================
int CWeapon::GetDurability()
{
	return m_Durability;
}

//==========================
//�ϋv�l�����炷
//==========================
void CWeapon::SubDurability()
{
	m_Durability--;
}