//==========================
// 
// �t�F�[�h����[fade.h]
// Author Yuki Goto
//
//==========================
#ifndef _FADE_H_
#define _FADE_H_

//include
#include"object2D.h"
#include"scene.h"

//�t�F�[�h�N���X�̒�`
class CFade :public CObject2D
{
public:
	//�t�F�[�h�̏��
	enum class FADE
	{
		FADE_NONE = 0,//�������Ă��Ȃ����
		FADE_IN,//�t�F�[�h�C�����
		FADE_OUT,//�t�F�[�h�A�E�g���
		FADE_MAX
	};

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CFade(int priority= PRIORITY);//�R���X�g���N�^
	~CFade() override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	void SetFade(CScene::MODE modenext);//�t�F�[�h�̐ݒ菈��
	FADE GetFade();//�t�F�[�h�̏�Ԏ擾
	static CFade* Create();//����
	void InGameFade();//�Q�[�����ł̃t�F�[�h
	float GetTransparency();//�����x�̎擾

private:
	FADE m_fade;//�t�F�[�h�̏��
	CScene::MODE g_modenext;//���̃V�[��
	float m_Transparency;//�F�̓����x
	bool m_InGame;//�Q�[����������
};

#endif 