//==========================
// 
// ���̋@[jihanki.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "jihanki.h"
#include "manager.h"
#include "model.h"
#include "player.h"
#include "drink.h"
#include "particle.h"

//�ÓI�����o������
const int CJihanki::PRIORITY = 2;//�`�揇
const int CJihanki::MAX_LIFE = 3;//�����̍ő�l
//==========================
//�R���X�g���N�^
//==========================
CJihanki::CJihanki(int nPriority) :
CObjectX(nPriority),//���R���X�g���N�^
m_nModelIdx(0),//���f���̔ԍ�
m_Life(MAX_LIFE),//����
m_visual{}//�����蔻��̉���
{

}

//==========================
//�f�X�g���N�^
//==========================
CJihanki::~CJihanki()
{

}

//==========================
//����������
//==========================
HRESULT CJihanki::Init()
{
	//�T�C�Y�ݒ�
	//SetSize();

	//�����ݒ�
	CObjectX::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CJihanki::Uninit()
{
	//�I������
	CObjectX::Uninit();

	for (int i = 0; i < 2; i++)
	{
		if (m_visual[i] != nullptr)
		{
			m_visual[i]->Uninit();
			m_visual[i] = nullptr;
		}
	}

	Release();
}

//==========================
//�X�V����
//==========================
void CJihanki::Update()
{
	//�X�V����
	CObjectX::Update();

	ColisionPlayer();
}

//==========================
//�`�揈��
//==========================
void CJihanki::Draw()
{
	//�`�揈��
	CObjectX::Draw();

	for (int i = 0; i < 2; i++)
	{
		if (m_visual[i] != nullptr)
		{
			//m_visual[i]->Draw();
		}
	}

}

//==========================
//�I�u�W�F�N�g����
//==========================
CJihanki* CJihanki::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CJihanki* pJihanki = DBG_NEW CJihanki;

	//�ʒu�̐ݒ�
	pJihanki->SetPos(pos);

	//�X�P�[���̐ݒ�
	pJihanki->SetScale(scale);

	//�����̐ݒ�
	pJihanki->SetRot(rot);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pJihanki->m_nModelIdx = pModel->Regist("data\\MODEL\\jihanki.x");
	pJihanki->BindModel(pModel->GetMeshAdress(pJihanki->m_nModelIdx),
		pModel->GetBuffMatAdress(pJihanki->m_nModelIdx),
		pModel->GetNumMatAdress(pJihanki->m_nModelIdx),
		pModel->GetTexIdx(pJihanki->m_nModelIdx));

	//����������
	pJihanki->Init();

	//�^�C�v��ݒ�
	pJihanki->SetType(TYPE::JIHANKI);
	
	//���a��ݒ�
	pJihanki->SetRadius(20.0f);

	//�����蔻�������
	//pJihanki->m_visual[0] = CCollisionVisual::Create(pJihanki->GetPos(), pJihanki->GetRadius());
	
	return pJihanki;
}

//==========================
//�v���C���[�Ƃ̓����蔻��
//==========================
void CJihanki::ColisionPlayer()
{
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

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

		bool Colision = pCollision->Sphere(GetPos(),
			pPlayer->GetPos(),
			GetRadius(),
			pPlayer->GetRadius());

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
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x + NormalizeVec.x * floor((GetRadius() + pPlayer->GetRadius())),
				GetPos().y,
				GetPos().z + NormalizeVec.z * floor((GetRadius() + pPlayer->GetRadius()))));

			CManager::GetInstance()->GetTutorial()->RecoveryTutorialDisplay();
		}

		break;
	}
}

//==========================
//�_���[�W����
//==========================
void CJihanki::Damage(int Damage)
{
	m_Life -= Damage;

	DamageParticle();

	if (m_Life <= 0)
	{
		CManager::GetInstance()->GetStageManager()->DeleteObj(*this);
		Uninit();
		CDrink::Create(GetPos(), D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	}
}

//==========================
//�U���̓����蔻��
//==========================
void CJihanki::DamageVisual(D3DXVECTOR3 pos, float radius)
{
	if (m_visual[1] == nullptr)
	{
		//m_visual[1] = CCollisionVisual::Create(pos, radius);
	}
}

//==========================
//��e���Ƀp�[�e�B�N�����o������
//==========================
void CJihanki::DamageParticle()
{
	for (int i = 0; i < 50; i++)
	{
		CParticle::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 30.0f, GetPos().z),
			D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
			10,
			0.5f,
			0.5f,
			10.0f);

	}
}