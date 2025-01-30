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
#include "collisionvisual.h"
#include "enemymovepoint.h"
#include "player.h"

//�O���錾
class CPlayer;

//�N���X�̒�`
class CEnemy :public CCharacter
{
public:
	enum class ATTACK_STATE
	{
		USUALLY = 0,//�ʏ�
		GRAB,//�͂�
		ATTACK,//�U��
		WEAPONATTACK,//����U��
		MAX,
	};

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

	//�����o�֐�
	CEnemy(int nPriority = PRIORITY);//�R���X�g���N�^
	~CEnemy() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	void Damage(int damage);//�_���[�W���󂯂��Ƃ��̏���
	void BeGrabbed(D3DXMATRIX mtx);//�͂܂�鏈��
	void ReleaseGrab(D3DXVECTOR3 rot);//�͂܂�Ă��Ȃ���ԂɕύX
	void SetAttackState(ATTACK_STATE state);//�U�����@�̐ݒ�
	ATTACK_STATE GetAttackState();//�U�����@�̎擾
	void SetEnemyType(ENEMY_TYPE EnemyType);//�G�̎�ނ�ݒ�
	ENEMY_TYPE GetEnemyType();//�G�̎�ނ��擾
	CFild* GetFild();//����Ă���n�ʂ̏��
	CPlayer* GetPlayer();//�v���C���[�̏����擾
	bool GetMovable();//�ړ��\���擾
	void SetMovable();//�s���\�ɂ���
	void judgeMovable();//�s���o���邩����
	void Patrol();//�ړ��n�_������
private:

	//�����o�֐�
	void ColisionEnemy();//�G���m�̓����蔻��
	void CollisionFild();//�n�ʂƂ̓����蔻��
	void Move();//�ړ�����
	void GetPlayerInfo();//�v���C���[�̏����擾
	void GetMovePoint();//�ړ��n�_���擾

	//�����o�ϐ�
	ATTACK_STATE m_AttackState;//�U�����@
	D3DXMATRIX m_Mtx;//���[���h�}�g���b�N�X
	ENEMY_TYPE m_EnemyType;//�G�̎��
	CPlayer* m_player;//�v���C���[�̏��
	bool m_Movable;//�s���\����

	CEnemyMovePoint* m_Point[POINT];//�ړ��n�_�̏��

	int m_CurPoint;//���݂̈ړ��n�_
};
#endif