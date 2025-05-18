//==========================
// 
// [darkbg.h]
// Author Yuki Goto
//
//==========================
#ifndef _DARKBG_H_
#define _DARKBG_H_

//include
#include"object2D.h"

//�N���X�̒�`
class CDarkBg :public CObject2D
{
public:
	
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
	CDarkBg(int priority = PRIORITY);//�R���X�g���N�^
	~CDarkBg() override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	void SetFade();//�t�F�[�h�̐ݒ菈��
	FADE GetFade();//�t�F�[�h�̏�Ԏ擾
	static CDarkBg* Create();//����
	float GetCol();//�����x�̎擾

private:

	//�����o�ϐ�
	FADE m_fade;//�t�F�[�h�̏��
	float m_cor;//�F�̓����x
};

#endif 