//==========================
// 
// �Q�[���S�̊Ǘ�[GameManager.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//�N���X�̒�`
class CGameManager
{
public:

	enum class GAME
	{
		NONE = 0,
		CLEAR,
		OVER,
	};
	

	//�����o�֐�
	CGameManager();//�R���X�g���N�^
	~CGameManager();//�f�X�g���N�^
	void SetGame(GAME game);
	GAME GetGame();
private:

	//�����o�ϐ�
	GAME GameClear;//

};

#endif