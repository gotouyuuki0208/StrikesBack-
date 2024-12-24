//==========================
// 
// �f�o�b�O[debug.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "debug.h"

//==========================
// �R���X�g���N�^
//==========================
CDebug::CDebug():
m_TestPlayer(false),
m_TestBoss(false),
m_TestBattle(false),
m_UseEdit(false)
{

}

//==========================
// �f�X�g���N�^
//==========================
CDebug::~CDebug()
{

}

//==========================
//�f�o�b�O�������Z�b�g
//==========================
void CDebug::Reset()
{
	FinishPlayerTest();
	FinishBossTest();
	FinishEdit();
}

//==========================
//�v���C���[�̃e�X�g
//==========================
bool CDebug::GetPlayerTest()
{
	return m_TestPlayer;
}

//==========================
//�v���C���[�̃e�X�g�J�n
//==========================
void CDebug::StartPlayerTest()
{
	m_TestPlayer = true;
}

//==========================
//�v���C���[�̃e�X�g�I��
//==========================
void CDebug::FinishPlayerTest()
{
	m_TestPlayer = false;
}

//==========================
//�{�X�̃e�X�g
//==========================
bool CDebug::GetBossTest()
{
	return m_TestBoss;
}

//==========================
//�{�X�̃e�X�g�J�n
//==========================
void CDebug::StartBossTest()
{
	m_TestBoss = true;
}

//==========================
//�{�X�̃e�X�g�I��
//==========================
void CDebug::FinishBossTest()
{
	m_TestBoss = false;
}

//==========================
//�o�g���̃e�X�g
//==========================
bool CDebug::GetBattleTest()
{
	return m_TestBattle;
}
//==========================
//�o�g���̃e�X�g�J�n
//==========================
void CDebug::StartBattleTest()
{
	m_TestBattle = true;
}

//==========================
//�o�g���̃e�X�g�I��
//==========================
void CDebug::FinishBattleTest()
{
	m_TestBattle = false;
}

//==========================
//�o�g���̃e�X�g
//==========================
bool CDebug::GetEdit()
{
	return m_UseEdit;
}
//==========================
//�o�g���̃e�X�g�J�n
//==========================
void CDebug::StartEdit()
{
	m_UseEdit = true;
}

//==========================
//�o�g���̃e�X�g�I��
//==========================
void CDebug::FinishEdit()
{
	m_UseEdit = false;
}