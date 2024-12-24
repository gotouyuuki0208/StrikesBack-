//==========================
// 
// ��������Ǘ�[TutorialManager.h]
// Author Yuki Goto
//
//==========================
#ifndef _TUTORIALMANAGER_H_
#define _TUTORIALMANAGER_H_

//�N���X�̒�`
class CTutorial
{
public:
	
	//�����o�֐�
	CTutorial();//�R���X�g���N�^
	~CTutorial();//�f�X�g���N�^
	bool GetTutorial();//������\�����Ă��邩���擾
	void StartTutorial();//�������J�n
	void FinishTutorial();//�������I��
	void SetAction();//�s��������\��������ԂɕύX
	void SetWeapon();//���������\��������ԂɕύX
	void SetRecovery();//�񕜐�����\��������ԂɕύX
	bool GetAction();//�s��������\��������ԂɎ擾
	bool GetWeapon();//���������\��������ԂɎ擾
	bool GetRecovery();//�񕜐�����\��������ԂɎ擾
private:
	//�����o�ϐ�
	bool m_Tutorial;//�����\������
	bool m_Action;//�s������
	bool m_Weapon;//�������
	bool m_Recovery;//�񕜐���
};

#endif