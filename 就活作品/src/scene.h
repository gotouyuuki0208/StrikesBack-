//==========================
// 
// �V�[���Ǘ�[scene.h]
// Author Yuki Goto
//
//==========================
#ifndef _SCENE_H_
#define _SCENE_H_

//�V�[���N���X�̒�`
class CScene
{
public:
	//��ʂ̎��
	enum class MODE
	{
		TITLE = 0,//�^�C�g��
		GAME,//�Q�[��
		RESULT,//���U���g
		MAX,
	};

	//�����o�֐�
	CScene();//�R���X�g���N�^
	virtual ~CScene();//�f�X�g���N�^
	virtual HRESULT Init();//����������
	virtual void Uninit();//�I������
	virtual void Update();//�X�V����
	virtual void Draw();//�`�揈��
	static CScene* Create(MODE mode);//����
	MODE GetScene();//���݂̃V�[�����擾
private:
	MODE m_mode;//���݂̃��[�h
};

#endif 