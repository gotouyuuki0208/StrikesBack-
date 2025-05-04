//==========================
// 
// �G�̏�ԊǗ�[enemystate.h]
// Author Yuki Goto
//
//==========================
#ifndef _ENEMYSTATE_H_
#define _ENEMYSTATE_H_

//include
#include"characterstate.h"

//�O���錾
class CWeakEnemy;
class CEenemyAttackStateMachine;
class CAttackEenemyState;

//==============================================================================
//�G�̏�ԃN���X
//==============================================================================
class CEnemyStateBase :public CStateBase
{
public:
	//�����o�֐�
	CEnemyStateBase();//�R���X�g���N�^
	~CEnemyStateBase();//�f�X�g���N�^
	void SetOwner(CWeakEnemy* enemy);//�X�e�[�g�̏����҂�ݒ�
	CWeakEnemy* GetOwner();//�X�e�[�g�̏��L�҂��擾
protected:

	//�����o�ϐ�
	CWeakEnemy* m_pEnemy;//�G�̏��
};

//==============================================================================
//����ԃN���X
//==============================================================================
class CEnemyMovabeState :public CEnemyStateBase
{
public:
	//�����o�֐�
	CEnemyMovabeState();//�R���X�g���N�^
	~CEnemyMovabeState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};


//==============================================================================
//�ҋ@��ԃN���X
//==============================================================================
class CEnemyNeutralState :public CEnemyStateBase
{
public:
	//�����o�֐�
	CEnemyNeutralState();//�R���X�g���N�^
	~CEnemyNeutralState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�ړ���ԃN���X
//==============================================================================
class CEnemyMoveState :public CEnemyStateBase
{
public:
	//�����o�֐�
	CEnemyMoveState();//�R���X�g���N�^
	~CEnemyMoveState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�_���[�W��ԃN���X
//==============================================================================
class CEnemyDamageState :public CEnemyStateBase
{
public:
	//�萔
	static const int DAMEGE_FLAME;//�_���[�W��Ԃ��I������܂ł̃t���[����

	//�����o�֐�
	CEnemyDamageState();//�R���X�g���N�^
	~CEnemyDamageState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��

private:

	//�����o�ϐ�
	int m_DmageCount;//�_���[�W���󂯂Ă���̃t���[����
};

//==============================================================================
//�_�b�V����ԃN���X
//==============================================================================
class CEnemyDushState :public CEnemyStateBase
{
public:
	//�����o�֐�
	CEnemyDushState();//�R���X�g���N�^
	~CEnemyDushState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//������я�ԃN���X
//==============================================================================
class CEnemyDamageBrrowState :public CEnemyStateBase
{
public:
	//�萔
	static const int BRROW_FLAME;//�_���[�W��Ԃ��I������܂ł̃t���[����

	//�����o�֐�
	CEnemyDamageBrrowState();//�R���X�g���N�^
	~CEnemyDamageBrrowState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��

private:

	//�����o�ϐ�
	int m_DmageCount;//�_���[�W���󂯂Ă���̃t���[����
};

//==============================================================================
//�U����ԃN���X
//==============================================================================
class CEnemyAttackState :public CEnemyStateBase
{
public:
	
	//�����o�֐�
	CEnemyAttackState();//�R���X�g���N�^
	~CEnemyAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
	void ChangeCombo();//�R���{������擾
	void ResetInfo();//����������
	void ChangeAttack(CAttackEenemyState* State);//�U����ύX
	int GetFrame();//�U���t���[�������擾
private:

	//�����o�ϐ�
	int m_FlameCount;//�U���̃t���[����
	bool m_Combo;//�R���{����
	CEenemyAttackStateMachine* m_EenemyAttackStateMachine;//�U���̏�ԊǗ�
};

#endif