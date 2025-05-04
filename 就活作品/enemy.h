//==========================
// 
// �G�l�~�[[enemy.h]
// Author Yuki Goto
//
//==========================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//include
#include"character.h"

//�O���錾
class CPlayer;
class CFild;
class CEnemyMovePoint;
class CStateMachine;
class CEnemyStateBase;

//�N���X�̒�`
class CEnemy :public CCharacter
{
public:

	enum class ENEMY_TYPE
	{
		NONE = 0,
		BOSS,//�{�X
		HitEnemy,//�f��G��
		WeaponEnemy,//����G��
	};

	//�萔
	static const int PRIORITY;//�`�揇
	static const int POINT=10;//�ړ��n�_�̐�
	static const float DUSH_DISTANCE;//���鋗��
	static const float DUSH_SPEED;//���鑬��
	static const float STOP_DISTANCE;//��������
	static const float WALK_SPEED;//��������

	//�����o�֐�
	CEnemy(int nPriority = PRIORITY);//�R���X�g���N�^
	~CEnemy() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	void JudgeMovable();//�s���o���邩����
	float ChangeDirection();//�����̕ύX
	bool JudgeDush();//�_�b�V������
	void Dush();//�_�b�V���ړ�����
	bool JudgeWalk();//��������
	void Walk();//�����ړ�����
	bool JudgeStop();//��~����
	bool GetAttackable();//�U���\������
	void ChangeAttackable();//�U���\�����ύX
	bool JudgeAttacKRange();//�U���͈͂Ƀv���C���[�����邩����
	void AttackMove();//�U�����̈ړ�
	void Move();//�ړ�����
	void ChangeState(CEnemyStateBase* NewState);//��Ԃ�ύX
	void ChangePlayMotion();//���[�V�����̍Đ������ύX
	

	void Damage(int damage);//�_���[�W���󂯂��Ƃ��̏���
	void BeGrabbed(D3DXMATRIX mtx);//�͂܂�鏈��
	void ReleaseGrab(D3DXVECTOR3 rot);//�͂܂�Ă��Ȃ���ԂɕύX
	void SetEnemyType(ENEMY_TYPE EnemyType);//�G�̎�ނ�ݒ�

	ENEMY_TYPE GetEnemyType();//�G�̎�ނ��擾
	CFild* GetFild();//����Ă���n�ʂ̏��
	CPlayer* GetPlayer();//�v���C���[�̏����擾
	bool GetMovable();//�ړ��\���擾
	void SetMovable();//�s���\�ɂ���
	
	void Patrol();//�ړ��n�_������
private:

	//�����o�֐�
	void ColisionEnemy();//�G���m�̓����蔻��
	void CollisionFild();//�n�ʂƂ̓����蔻��
	
	void GetPlayerInfo();//�v���C���[�̏����擾
	void GetMovePoint();//�ړ��n�_���擾

	//�����o�ϐ�
	//ATTACK_STATE m_AttackState;//�U�����@
	D3DXMATRIX m_Mtx;//���[���h�}�g���b�N�X
	ENEMY_TYPE m_EnemyType;//�G�̎��
	CPlayer* m_player;//�v���C���[�̏��
	bool m_Movable;//�s���\����
	CStateMachine* m_StateMachine;//��ԊǗ�
	CEnemyMovePoint* m_Point[POINT];//�ړ��n�_�̏��
	float m_Angle;//����
	int m_CurPoint;//���݂̈ړ��n�_
	bool Attackable;//�U���\����
	bool m_PlayMotion;//���[�V�����Đ�����
};
#endif