//==========================
// 
// �v���C���[����[player.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//include
#include "motionmodel.h"
#include "weapon.h"
#include "enemy.h"
#include "collisionvisual.h"

//�O���錾
class CEnemy;

//�N���X�̒�`
class CPlayer :public CMotionModel
{
public:

	enum class STATE
	{
		NEUTRAL=0,//�ҋ@
		ATTACK,//�U��
		MOVE,//�ړ�
		GUARD,//�K�[�h
		MAX,
	};

	//�萔
	static const int PRIORITY;//�`�揇
	static const int INPUT_START_FLAME;//���͎�t�J�n�t���[����
	static const int INPUT_FINISH_FLAME;//���͎�t�I���t���[����
	static const int RESET_FLAME;//�R���{�̏�񃊃Z�b�g�t���[����
	static const int MAX_LIFE;//�����̍ő�l
	static const float MOVE_VALUE;//�ړ�
	static const float DASH_VALUE;//�_�b�V��
	static const float JUMP_VALUE;//�W�����v
	static const float GRAVITY_VALUE;//�d��
	static const float INERTIA_VALUE;//����
	static const float ROT_VALUE;//����
	static const float CHARA_WIDTH;//�L�����N�^�[��X�T�C�Y
	static const float CHARA_HEIGHT;//�L�����N�^�[��Y�T�C�Y

	//�����o�֐�
	CPlayer(int nPriority = PRIORITY);//�R���X�g���N�^
	~CPlayer() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	void Damage(int damage);//�_���[�W����
	void DamageBlow(D3DXVECTOR3 pos);//������я���
	int GetLife();//���C�t���擾
	void SetLife(int Life);//���C�t��ݒ�
	void AddItem();//�A�C�e���̐��𑝂₷
	int GetInputFrame();//���͎�t���Ԃ��擾
	STATE GetState();//��Ԃ��擾
	void GetBoss(CEnemy* boss);//�{�X���擾
	bool GetHaveWeapon();//���폊������
private:

	//�����o�֐�
	void Attack();//�U������
	void AttackWeapon();//����ł̍U��
	void CollisionEnemy();//�G�Ƃ̓����蔻��
	void CollisionFild();//�n�ʂƂ̓����蔻��
	void CollisionHitEnemy();//�G������Ƃ��̓����蔻��
	void CollisionJihankiAttack();//���̋@�ɍU�����̓����蔻��
	void CollisionWeaponEnemy();//�G�𕐊�ŉ���Ƃ��̓����蔻��
	void ColisionDeleveryAttack();//�z�B���̍U�������蔻��
	void ColisionDelevery();//�z�B���̓����蔻��
	void GrabAttack();//�͂ݍU���̏���
	void GrabEnemy();//�G��͂ޏ���
	void Guard();//�K�[�h����
	void Input();//���͏���
	void InputMove();//�ړ��̓��͏���
	void InputAttack();//�U���̓��͏���
	void Move();//�ړ�����
	void Push(MOTION_TYPE motion);//�f�[�^�̒ǉ�
	MOTION_TYPE Pop();//�f�[�^�̎��o��
	void PickUpWeapon();//������E��
	void Recovery();//�񕜃A�C�e�����g�p
	void ReleaseEnemy();//�G�����
	void ReleaseWeapon();//����������
	void ResetStak();//�X�^�b�N�̏���߂�
	void SetComboList();//�R���{���X�g�̐���
	void SetState(STATE state);//��Ԃ̐ݒ�
	void CorrectionAngle();//�p�x�̕␳

	//�����o�ϐ�
	bool m_Jump;//�W�����v�̔���
	bool m_grab;//�͂ݔ���
	bool m_Attack;//�U������
	CWeapon* m_weapon;//�����Ă镐��
	CEnemy* m_GrabEnemy;//�͂�ł���G
	CEnemy* m_boss;//�{�X
	STATE m_state;//���݂̏��
	MOTION_TYPE m_ComboList[3];//�U���̃R���{���X�g
	MOTION_TYPE m_ComboStack[3];//�U���R���{�̃X�^�b�N
	int m_FlameCount;//�t���[�����̃J�E���g
	int m_StackIdx;//TOP�̈ʒu
	int m_CountAttack;//�R���{���ɍU���𓖂Ă���
	int m_Life;//����
	bool m_testdeth;
	int m_DamageCount;//
	int m_RecoveryItemStock;//�A�C�e���̃X�g�b�N��
	bool m_WeaponType;//����̎��(false:���� true:�Ў�)
	CCollisionVisual* m_Visual;//�����蔻��̏��
	bool m_VisualCor;//�����蔻��̐F�̐ݒ�
	D3DXVECTOR3 m_DamageMove;//��e���̐�����Ԉړ��l
	bool m_Damage;//�_���[�W��Ԃ̔���
};
#endif