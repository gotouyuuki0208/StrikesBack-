//==========================
// 
// ��������Ǘ�[TutorialManager.h]
// Author Yuki Goto
//
//==========================
#ifndef _TUTORIALMANAGER_H_
#define _TUTORIALMANAGER_H_

//�O���錾
class CTutorialPopup;
class CTutorialBg;

//�N���X�̒�`
class CTutorialManager
{
public:
	
	//�����o�֐�
	CTutorialManager();//�R���X�g���N�^
	~CTutorialManager();//�f�X�g���N�^
	void ActionTutorialDisplay();//�s���̐�����\��
	void WeaponTutorialDisplay();//����̐�����\��
	void RecoveryTutorialDisplay();//�񕜂̐�����\��
	void TutorialDelete();//����̐���������
	void Reset();//��񃊃Z�b�g
private:
	//�����o�ϐ�
	bool m_Action;//�s������
	bool m_Weapon;//�������
	bool m_Recovery;//�񕜐���

	CTutorialPopup* m_pTutorialPopup;//�|�b�v�A�b�v�\������`���[�g���A���̏��
	CTutorialBg* m_pTutorialBg;//�w�i�̏��
};

#endif