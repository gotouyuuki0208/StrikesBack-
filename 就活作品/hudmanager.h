//==========================
// 
// HUD�̊Ǘ�[hudmanager.h]
// Author Yuki Goto
//
//==========================
#ifndef _HUDMANAGER_H_
#define _HUDMANAGER_H_

//�O���錾
class CPlayerHPGauge;//�G���G��HP�Q�[�W�N���X
class CBossHPGauge;//�{�X��HP�Q�[�W�N���X

//�N���X�̒�`
class CHudManager
{
public:

	//�����o�֐�
	CHudManager();//�R���X�g���N�^
	~CHudManager();//�f�X�g���N�^
	void ChangePlayerHP(int hp);//�v���C���[HP���ύX���ꂽ
	void ChangeBossHP(int hp);//�{�X��HP���ύX���ꂽ
	void CreatePlayerHPGauge();//�v���C���[�̃Q�[�W�𐶐�
	void CreateBossHPGauge();//�{�X�̃Q�[�W�𐶐�
	void Reset();//���Z�b�g
	void DisplayUI();//�{��������UI�\��
private:

	//�����o�ϐ�
	CPlayerHPGauge* m_pPlayerHPGauge;//�v���C���[��HP�Q�[�W�̏��
	CBossHPGauge* m_pBossHPGauge;//�{�X��HP�Q�[�W�̏��
};

#endif