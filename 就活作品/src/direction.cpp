//==========================
// 
// �{�X�퉉�o�̊Ǘ�[direction.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"direction.h"
#include"manager.h"
#include"directionbg.h"
#include"boss.h"

//========================
//�R���X�g���N�^
//========================
CDirection::CDirection():
	m_ExistenceBg(true),
	m_End(false),
	m_boss(nullptr),//�{�X�̏��
	m_BossMotionEnd(false)
{
	//�w�i�𐶐�
	m_Bg[0] = CDirectionBg::Create({ SCREEN_WIDTH / 2, -50.0f, 0.0f });
	m_Bg[1] = CDirectionBg::Create({ SCREEN_WIDTH / 2, SCREEN_HEIGHT + 50.0f, 0.0f });
}

//========================
//�f�X�g���N�^
//========================
CDirection::~CDirection()
{

}

//========================
//�X�V����
//========================
void CDirection::Update()
{
	//�w�i�̍X�V
	UpdateBg();

	//�{�X�̃��[�V�������I������������
	BossEndMotion();

	if (m_BossMotionEnd)
	{//�{�X�̃��[�V�������I������

		//�J�����̏����擾
		CCamera* pCamera = CManager::GetInstance()->GetCamera();

		//�^�[�Q�b�g�̈ʒu�ֈړ�
		pCamera->TarGetMove();

		if (pCamera->FinishDirection())
		{//�J�����̈ړ����I��
			m_End = true;
		}
	}
}

//========================
//�w�i�X�V
//========================
void CDirection::UpdateBg()
{
	if (m_ExistenceBg)
	{
		for (int i = 0; i < 2; i++)
		{
			//��ʓ��ɓ���
			m_Bg[i]->EnterScreen();
		}
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			//��ʊO�ɏo��
			m_Bg[i]->ExitScreen();
		}
	}

}

//========================
//�I��������擾
//========================
bool CDirection::GetEnd()
{
	return m_End;
}

//========================
//�{�X�̃��[�V�������I������������
//========================
void CDirection::BossEndMotion()
{
	if (m_boss->GetMotion() == CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL)
	{//�ҋ@���[�V�������Đ����Ă���

		//�{�X�̃��[�V�������I������
		m_BossMotionEnd = true;

		//�w�i������
		m_ExistenceBg = false;
	}
}

//==========================
//�{�X�̏����擾
//==========================
void CDirection::GetBossInfo()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CBoss::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//�I�u�W�F�N�g���G�l�~�[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		if (pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE::BOSS)
		{//�I�u�W�F�N�g���{�X�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		CBoss* pBoss = (CBoss*)pObj;

		//�{�X�̏����擾
		m_boss = pBoss;

		break;
	}

	//�J�����̈ʒu��ύX
	CManager::GetInstance()->GetCamera()->SetPos(m_boss->GetPos());
}