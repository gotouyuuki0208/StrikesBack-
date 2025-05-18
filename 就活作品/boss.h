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

//�O���錾
class CWeapon;
class CBossHPGauge;
class CBossStateBase;
class CStateMachine;

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
	static const float GUARD_DISTANCE;//��鋗��
	
	//�����o�֐�
	CBoss(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBoss() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBoss* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	void GrabChangeWeapon(CWeapon* weapon);//�͂ޕ����ς���
	bool GetWeapon();//������������Ă��邩����
	void ChangeState(CBossStateBase* NewState);//��Ԃ�ύX
	void ChoiceAttack();//�U���̎�ނ�I��
	bool GetNextAttack();//���̍U�����@���擾
	void WeaponMove();//����U���̈ړ�����
	bool GetWeaponType();//����̃^�C�v���擾
	void hit(D3DXVECTOR3 pos, int damage, MOTION_TYPE hitmotion);//�U����e����
	bool JudgeGuard();//�K�[�h���鋗���ɂ��邩����
	void PlayerNearAction();//�v���C���[���߂��Ƃ��̍s��
	bool GetGuard();//�K�[�h���邩�擾
	void GuardReset();//�K�[�h�̏������Z�b�g
private:

	//�����o�֐�
	void FindNearbyWeapons();//�߂������T��
	bool MeasureDistance();//�����𑪂�
	int RandomNum();//�����_���Ȑ��l���擾
	void ColisionWeapon();//����Ƃ̓����蔻��
	void MotionUpdate();//���[�V�����̍X�V
	void ReleseWeapon();//����𗣂�
	void WeaponDamage();//����̑ϋv�l�����炷
	void ColisionWeaponAttack();//����U���̓����蔻��
	void InitHaveWeapon();//�ŏ��ɕ������������

	//�����o�ϐ�
	CWeapon* m_weapon;//����̏��
	CWeapon* m_HaveWeapon;//�����Ă镐��
	CStateMachine* m_StateMachine;//��ԊǗ�
	int m_FlameCount;//�U���t���[���̃J�E���g
	int m_NearCount;//�v���C���[���߂Â������̍s���̃J�E���g
	bool m_NearAction;//�v���C���[���߂Â������̍s�������Ă��邩����
	bool m_NextAttack;//���̍U��(false:�f�� true:����)
	bool m_Guard;//�K�[�h����

};
#endif