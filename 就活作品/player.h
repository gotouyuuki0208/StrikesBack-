//==========================
// 
// �v���C���[����[player.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//include
#include "character.h"
#include "playerstate.h"

//�O���錾
class CEnemy;
class CWeapon;
class CStateMachine;

//�N���X�̒�`
class CPlayer :public CCharacter
{
public:

	//�萔
	static const int PRIORITY;//�`�揇
	static const int MAX_LIFE;//�����̍ő�l
	static const float MOVE_VALUE;//�ړ�
	static const float AVOIDANCE_VALUE;//����̈ړ��l
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

	void AddItem();//�A�C�e���̐��𑝂₷
	void GetBoss(CEnemy* boss);//�{�X���擾
	bool GetHaveWeapon();//���폊������
	void DeleteWeapon();//���������
	void ChangeState(CPlayerStateBase* NewState);//��Ԃ�ύX
	void AttackMove();//�U�����̈ړ�����
	void Move();//�ړ�����
	void InputMove();//�ړ��̓��͏���
	void CorrectionAngle();//�p�x�̕␳
	void Avoidance();//���
	void PickUpWeapon();//������E��
	void ReleaseWeapon();//����������
	bool GetWeaponType();//����̎�ނ��擾
	void ThrowWeapon();//����𓊂���
	void hit(D3DXVECTOR3 pos,int damage);//�U����e����
	void ResetDamageNum();//��e�񐔏�����
	int GetDamageNum();//��e�񐔎擾
	void HitEnemy(int PartsNum);//�G������Ƃ��̓����蔻��
	void WeaponHitEnemy();//�G�𕐊�ŉ���Ƃ��̓����蔻��
	void CollisionJihankiAttack();//���̋@�ɍU�����̓����蔻��
	void RecoveryLife();//���C�t�̉�
	bool GetWeaponBreak();//���킪��ꂽ���擾
	void BreakReset();//����j�󔻒�����Z�b�g
	void StageChangeState();//�X�e�[�W�ύX���̃X�e�[�g�̕ύX
private:
	
	//�����o�֐�
	void CollisionEnemy();//�G�Ƃ̓����蔻��
	void CollisionFild();//�n�ʂƂ̓����蔻��
	void SetWeaponMotion(MOTION_TYPE motion);//���폊�����̃��[�V������ݒ�
	void MotionUpdate();//���[�V�����̍X�V
	void Damage();//�_���[�W����
	void WeaponDamage();//����̑ϋv�����炷

	//�����o�ϐ�
	bool m_grab;//�͂ݔ���
	CWeapon* m_weapon;//�����Ă镐��
	CEnemy* m_boss;//�{�X
	CStateMachine* m_StateMachine;//��ԊǗ�
	int m_RecoveryItemStock;//�A�C�e���̃X�g�b�N��
	bool m_WeaponType;//����̎��(false:���� true:�Ў�)
	bool m_VisualCor;//�����蔻��̐F�̐ݒ�
	float LeftStickAngle;//���X�e�B�b�N�̊p�x
	int m_DamageNum;//�_���[�W�񐔃J�E���g
	bool m_Attack;//�U�����q�b�g����������
	bool m_breakweapon;//���킪��ꂽ����
};

#endif