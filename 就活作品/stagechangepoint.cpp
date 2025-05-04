//==========================
// 
// �X�e�[�W�J�ڈʒu[stagechangepoint.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "stagechangepoint.h"
#include "texture.h"
#include "manager.h"
#include "player.h"

//�ÓI�����o������
const int CStageChangePoint::PRIORITY = 3;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CStageChangePoint::CStageChangePoint(int nPriority) :CFild(nPriority),m_GoalPoint(nullptr)
{

}

//==========================
//�f�X�g���N�^
//==========================
CStageChangePoint::~CStageChangePoint()
{

}

//==========================
//����������
//==========================
HRESULT CStageChangePoint::Init()
{
	//�����ݒ�
	CFild::Init();

	//UI�𐶐�
	m_GoalPoint = CGoalPoint::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 45.0f, GetPos().z), D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	return S_OK;
}

//==========================
//�I������
//==========================
void CStageChangePoint::Uninit()
{
	if (m_GoalPoint != nullptr)
	{
		m_GoalPoint->Uninit();
		m_GoalPoint = nullptr;
	}

	//�I������
	CFild::Uninit();
}

//==========================
//�X�V����
//==========================
void  CStageChangePoint::Update()
{
	//�X�V����
	CFild::Update();
	
	//�v���C���[�Ƃ̓����蔻��
	ColisionPlayer();

}

//==========================
//�`�揈��
//==========================
void CStageChangePoint::Draw()
{

#ifdef _DEBUG
	//�`�揈��
	CFild::Draw();
#endif
}

//==========================
//�I�u�W�F�N�g2D����
//==========================
CStageChangePoint* CStageChangePoint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CStageChangePoint* pStageChangePoint = DBG_NEW CStageChangePoint;

	//�ʒu�̐ݒ�
	pStageChangePoint->SetPos(pos);

	//�傫���̐ݒ�
	pStageChangePoint->SetSize(size);

	//�F�̐ݒ�
	pStageChangePoint->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	
	//����������
	pStageChangePoint->Init();

	//���a�̐ݒ�
	pStageChangePoint->SetRadius(15.0f);

	//�^�C�v�ݒ�
	pStageChangePoint->SetType(TYPE::FILD);
	pStageChangePoint->SetFild(FILDTYPE::STAGECHANGE);

	return pStageChangePoint;
}

//==========================
//�v���C���[�Ƃ̓����蔻��
//==========================
void CStageChangePoint::ColisionPlayer()
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

		CCollision* pCollision = CManager::GetInstance()->GetCollision();

		bool Colision = pCollision->Sphere(GetPos(), pPlayer->GetPos(), GetRadius(), pPlayer->GetRadius());

		if (Colision)
		{
			CManager::GetInstance()->GetStageManager()->SetStage();//�X�e�[�W�t���O�𗧂Ă�
			CManager::GetInstance()->GetStageManager()->DeleteObj(*this);//�I�u�W�F�N�g�Ǘ����X�g�������
			Uninit();//�I������
		}

		break;
	}
}