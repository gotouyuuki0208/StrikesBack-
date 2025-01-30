//==========================
// 
// �{�X[boss.h]
// Author Yuki Goto
//
//==========================
#ifndef _BOSS_H_
#define _BOSS_H_

//include
#include "enemy.h"
#include "weapon.h"
#include "bosshpgauge.h"

//�N���X�̒�`
class CBoss :public CEnemy
{
public:
	//�萔
	static const int PRIORITY;//�`�揇
	static const int GUARD_PROBABILITY;//�v���C���[���f��̎��K�[�h����m��
	static const int NEAR_ACTION_COUNT;//�v���C���[���߂��Ƃ��ɂ���s���̒���
	static const int HITATTACK_PROBABILITY;//�v���C���[���߂��Ƃ��ɉ���m��
	static const int WEAPONATTACK_PROBABILITY;//���킪�߂��Ƃ��ɕ���U������m��
	static const int ATTACKFINISH_COOLTIME;//�U���I����̃N�[���^�C��
	static const float DUSH_DISTANCE;//���鋗��
	static const float WALK_DISTANCE;//��������
	static const float GUARD_DISTANCE;//��鋗��
	static const float DUSH_SPEED;//���鑬��
	static const float WALK_SPEED;//��������
	
	//�����o�֐�
	CBoss(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBoss() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBoss* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	void GrabChangeWeapon(CWeapon* weapon);//�͂ޕ����ς���
private:

	//�����o�֐�
	void Move();//�v���C���[�ւ̈ړ�
	void WeaponMove();//����U���̈ړ�����
	void Attack();//�U������
	void FindNearbyWeapons();//�߂������T��
	float ChangeDirection();//�����̕ύX
	void ColisionHitAttack();//�U���̓����蔻��
	void ColisionWeaponAttack();//����U���̓����蔻��
	bool JudgeAttackable();//�U���\������
	void ChoiceAttack();//�U���̎�ނ�I��
	void ColisionWeapon();//����Ƃ̓����蔻��
	bool MeasureDistance();//�����𑪂�
	void ResetStak();//�X�^�b�N�̏���߂�
	void SetComboList();//�R���{���X�g�̐���
	void Push(MOTION_TYPE motion);//�f�[�^�̒ǉ�
	MOTION_TYPE Pop();//�f�[�^�̎��o��
	int RandomNum();//�����_���Ȑ��l���擾
	void Guard();//�K�[�h����
	void PlayerNearAction();//�v���C���[���߂��Ƃ��̍s��
	void Count();//�J�E���g����
	void MoveAction();//�ړ����̍s��
	void ReleseWeapon();//����𗣂�
	void MotionUpdate();
	void SetWeaponMotion(MOTION_TYPE motion);//���폊�����̃��[�V������ݒ�

	//�����o�ϐ�
	CWeapon* m_weapon;//����̏��
	CBossHPGauge* m_BossHPGauge;
	bool m_Attack;//�U������������
	bool Attackable;//�U���\������
	int m_AttackCoolTime;//�U���̃N�[���^�C��
	int m_FlameCount;//�U���t���[���̃J�E���g
	int m_AttackNum;//�U����
	MOTION_TYPE m_ComboList[3];//�U���̃R���{���X�g
	MOTION_TYPE m_ComboStack[3];//�U���R���{�̃X�^�b�N
	int m_StackIdx;//TOP�̈ʒu
	float m_Angle;//����
	int m_NearCount;//�v���C���[���߂Â������̍s���̃J�E���g
	bool m_NearAction;//�v���C���[���߂Â������̍s�������Ă��邩����
};
#endif