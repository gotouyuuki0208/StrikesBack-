//==========================
// 
// ��������Ǘ�[TutorialManager.cpp]
// Author Yuki Goto
//
//==========================

#include"TutorialManager.h"

//==========================
//�R���X�g���N�^
//==========================
CTutorial::CTutorial() :
m_Tutorial(false),//�����\������
m_Action(false),//�s������
m_Weapon(false),//�������
m_Recovery(false)//�񕜐���
{

}


//==========================
//�f�X�g���N�^
//==========================
CTutorial::~CTutorial()
{

}

//==========================
//������\�����Ă��邩���擾
//==========================
bool CTutorial::GetTutorial()
{
	return m_Tutorial;
}

//==========================
//�������J�n
//==========================
void CTutorial::StartTutorial()
{
	m_Tutorial = true;
}

//==========================
//�������I��
//==========================
void CTutorial::FinishTutorial()
{
	m_Tutorial = false;
}

//==========================
//�s��������\��������ԂɕύX
//==========================
void CTutorial::SetAction()
{
	m_Action = true;
}

//==========================
//���������\��������ԂɕύX
//==========================
void CTutorial::SetWeapon()
{
	m_Weapon = true;
}

//==========================
//�񕜐�����\��������ԂɕύX
//==========================
void CTutorial::SetRecovery()
{
	m_Recovery = true;
}

//==========================
//�s��������\��������ԂɎ擾
//==========================
bool CTutorial::GetAction()
{
	return m_Action;
}

//==========================
//���������\��������ԂɎ擾
//==========================
bool CTutorial::GetWeapon()
{
	return m_Weapon;
}

//==========================
//�񕜐�����\��������ԂɎ擾
//==========================
bool CTutorial::GetRecovery()
{
	return m_Recovery;
}