//==========================
// 
// ��������Ǘ�[TutorialManager.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"manager.h"
#include"TutorialManager.h"
#include"TutorialPopup.h"
#include"tutorialbg.h"

//==========================
//�R���X�g���N�^
//==========================
CTutorialManager::CTutorialManager():
m_Action(false),//�s������
m_Weapon(false),//�������
m_Recovery(false),//�񕜐���
m_pTutorialPopup(nullptr),//�|�b�v�A�b�v�\������`���[�g���A���̏��
m_pTutorialBg(nullptr)//�w�i�̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CTutorialManager::~CTutorialManager()
{

}

//==========================
//�s���̐�����\��
//==========================
void CTutorialManager::ActionTutorialDisplay()
{
	if (m_Action)
	{//���łɍs�����������Ă���

		return;
	}

	//�w�i�̐���
	m_pTutorialBg = CTutorialBg::Create();

	//�|�b�v�A�b�v�\���𐶐�
	m_pTutorialPopup = CTutorialPopup::Create();

	//�s��������������ԂɕύX
	m_Action = true;

	//�v���C���[�𑀍�ł��Ȃ��悤�ɕύX
	CManager::GetInstance()->GetGameManager()->ChangePlayGame(false);
}

//==========================
//����̐�����\��
//==========================
void CTutorialManager::WeaponTutorialDisplay()
{
	if (m_Weapon)
	{//���łɕ�����������Ă���

		return;
	}

	//�w�i�̐���
	m_pTutorialBg = CTutorialBg::Create();

	//�|�b�v�A�b�v�\���𐶐�
	m_pTutorialPopup = CTutorialPopup::Create();

	//���������������ԂɕύX
	m_Weapon = true;

	//�v���C���[�𑀍�ł��Ȃ��悤�ɕύX
	CManager::GetInstance()->GetGameManager()->ChangePlayGame(false);
}

//==========================
//�񕜂̐�����\��
//==========================
void CTutorialManager::RecoveryTutorialDisplay()
{
	if (m_Recovery)
	{//���łɉ񕜐��������Ă���

		return;
	}

	//�w�i�̐���
	m_pTutorialBg = CTutorialBg::Create();

	//�|�b�v�A�b�v�\���𐶐�
	m_pTutorialPopup = CTutorialPopup::Create();

	//�񕜐�����������ԂɕύX
	m_Recovery = true;

	//�v���C���[�𑀍�ł��Ȃ��悤�ɕύX
	CManager::GetInstance()->GetGameManager()->ChangePlayGame(false);
}

//==========================
//����������
//==========================
void CTutorialManager::TutorialDelete()
{

	if (m_pTutorialPopup != nullptr)
	{//�|�b�v�A�b�v�\��������Ă��Ȃ�

		//�L�[���͂��ꂽ���Ƃ�ʒm
		m_pTutorialPopup->KeyInput();
		m_pTutorialPopup = nullptr;

		//�w�i�폜
		m_pTutorialBg->Uninit();
		m_pTutorialPopup = nullptr;

		//�v���C���[�𑀍�ł���悤�ɂɕύX
		CManager::GetInstance()->GetGameManager()->ChangePlayGame(true);
	}
}
