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
	void SetMovable();//�s���\�ɂ���
	bool GetMovable();//�ړ��\���擾
	CPlayer* GetPlayer();//�v���C���[�̏����擾
	ENEMY_TYPE GetEnemyType();//�G�̎�ނ��擾
	void SetEnemyType(ENEMY_TYPE EnemyType);//�G�̎�ނ�ݒ�
	void ReleaseGrab(D3DXVECTOR3 rot);//�͂܂�Ă��Ȃ���ԂɕύX
	void BeGrabbed(D3DXMATRIX mtx);//�͂܂�鏈��
	void Move();//�ړ�����
	bool JudgeDush();//�_�b�V������
	void Dush();//�_�b�V���ړ�����
	bool JudgeWalk();//��������
	void Walk();//�����ړ�����
	bool JudgeStop();//��~����
	float ChangeDirection();//�����̕ύX
	bool GetAttackable();//�U���\������
	void ChangeAttackable();//�U���\�����ύX
	bool JudgeAttackRange();//�U���͈͂Ƀv���C���[�����邩����	
	void ChangePlayMotion(bool play);//���[�V�����̍Đ������ύX
	void ResetDamageNum();//��e�񐔏�����
	int GetDamageNum();//��e�񐔎擾
	void AddDamegeNum();//�_���[�W�񐔂𑝂₷
	void HitPlayer(int PartsNum);//�v���C���[�ւ̉���U���̓����蔻��
	void ResetAttack();//�U����������Z�b�g
	void AttackMove();//�U�����̈ړ�
	void SetCoolTime(int time);//�U���̃N�[���^�C����ݒ�
	
private:

	//�����o�֐�
	void CollisionFild();//�n�ʂƂ̓����蔻��
	void GetPlayerInfo();//�v���C���[�̏����擾

	//�����o�ϐ�
	D3DXMATRIX m_Mtx;//���[���h�}�g���b�N�X
	ENEMY_TYPE m_EnemyType;//�G�̎��
	CPlayer* m_player;//�v���C���[�̏��
	bool m_Movable;//�s���\����
	float m_Angle;//����
	bool Attackable;//�U���\����
	bool m_PlayMotion;//���[�V�����Đ�����
	int m_DamageNum;//�_���[�W�񐔃J�E���g
	int m_AttackCoolTime;//�U���̃N�[���^�C��
	bool m_Attack;//�U������
};
#endif