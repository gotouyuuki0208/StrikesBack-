//==========================
// 
// �Q�[���S�̊Ǘ�[GameManager.h]
// Author Yuki Goto
//
//==========================
#include"GameManager.h"
#include"manager.h"

//==========================
//�R���X�g���N�^
//==========================
CGameManager::CGameManager():GameClear(GAME::NONE)
{

}

//==========================
//�f�X�g���N�^
//==========================
CGameManager::~CGameManager()
{

}

//==========================
//�Q�[���Ǘ�
//==========================
void CGameManager::SetGame(GAME game)
{
	GameClear = game;
}

CGameManager::GAME CGameManager::GetGame()
{
	return GameClear;
}