//==========================
// 
// �`���[�g���A���̃|�b�v�A�b�v�\��[TutorialPopup.h]
// Author Yuki Goto
//
//==========================
#ifndef _TUTORIALPOPUP_H_
#define _TUTORIALPOPUP_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CTutorialPopup :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CTutorialPopup(int nPriority = PRIORITY);//�R���X�g���N�^
	~CTutorialPopup() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CTutorialPopup* Create(const char texname[256]);//�I�u�W�F�N�g����
	void KeyInput();//�L�[����
private:

	//�����o�֐�
	void MakeOpaque();//�s�����ɂ���
	void MakeTransparent();//�����ɂ���
	

	//�����o�ϐ�
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
	float m_transparency;//�����x
	bool m_input;//���͔���
};
#endif