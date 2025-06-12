//==========================
// 
// �L�����N�^�[�̏�ԊǗ�[characterstate.h]
// Author Yuki Goto
//
//==========================
#ifndef _STATE_H_
#define _STATE_H_


//==============================================================================
//���N���X
//==============================================================================
class CStateBase
{
public:
	//�����o�֐�
	CStateBase();//�R���X�g���N�^
	~CStateBase();//�f�X�g���N�^
	virtual void Start();//�J�n
	virtual void Update();//�X�V
	virtual void Uninit();//�I��
};

//==============================================================================
//��ԊǗ��N���X
//==============================================================================
class CStateMachine
{
public:
	//�����o�֐�
	CStateMachine();//�R���X�g���N�^
	~CStateMachine();//�f�X�g���N�^
	void ChangeState(CStateBase* NewState);//��Ԃ̕ύX
	void Update();//�X�V
	CStateBase* GetState();//���݂̃X�e�[�g���擾

private:

	//�����o�ϐ�
	CStateBase* m_State = nullptr;//���݂̃X�e�[�g
};

#endif