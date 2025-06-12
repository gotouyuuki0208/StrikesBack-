//==========================
// 
// �A�C�e��[item.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "item.h"
#include "manager.h"
#include "model.h"
#include"player.h"
#include"collision.h"

//�ÓI�����o������
const int CItem::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CItem::CItem(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CItem::~CItem()
{

}

//==========================
//����������
//==========================
HRESULT CItem::Init()
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
void  CItem::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CItem::Update()
{
	//�X�V����
	CObjectX::Update();

	//�v���C���[�Ƃ̓����蔻��
	ColisionPlayer();
}

//==========================
//�`�揈��
//==========================
void CItem::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CItem* pItem = DBG_NEW CItem;

	//�ʒu�̐ݒ�
	pItem->SetPos(pos);

	//�X�P�[���̐ݒ�
	pItem->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pItem->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pItem->BindModel(pModel->GetMeshAdress(pItem->m_nModelIdx),
		pModel->GetBuffMatAdress(pItem->m_nModelIdx),
		pModel->GetNumMatAdress(pItem->m_nModelIdx),
		pModel->GetTexIdx(pItem->m_nModelIdx));

	//����������
	pItem->Init();

	return pItem;
}

//==========================
//���f���̔ԍ����擾
//==========================
int CItem::GetModelIdx()
{
	return m_nModelIdx;
}

//==========================
//���f���̔ԍ���ݒ�
//==========================
void CItem::SetModelIdx(int Idx)
{
	m_nModelIdx = Idx;
}

//==========================
//�v���C���[�Ƃ̓����蔻��
//==========================
void CItem::ColisionPlayer()
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

		bool Colision = Collision::Sphere(GetPos(),
			pPlayer->GetPos(),
			GetRadius(),
			pPlayer->GetRadius());

		if (Colision)
		{
			Uninit();
			pPlayer->RecoveryLife();//��
			
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_RECOVERY);
		}

		break;
	}
}