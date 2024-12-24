//==========================
// 
// ����G[hitenemy.h]
// Author Yuki Goto
//
//==========================
#ifndef _HITENEMY_H_
#define _HITENEMY_H_

//include
#include "enemy.h"
#include "hpgauge3D.h"

//�N���X�̒�`
class CHitEnemy :public CEnemy
{
public:
	//�萔
	static const int PRIORITY;//�`�揇
	static const int NEAR_ACTION_COUNT;//�v���C���[���߂��Ƃ��ɂ���s���̒���
	static const int ATTACKFINISH_COOLTIME;//�U���I����̃N�[���^�C��
	static const float DUSH_DISTANCE;//���鋗��
	static const float DUSH_SPEED;//���鑬��
	static const float WALK_DISTANCE;//��������
	static const float WALK_SPEED;//��������

	//�����o�֐�
	CHitEnemy(int nPriority = PRIORITY);//�R���X�g���N�^
	~CHitEnemy() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CHitEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	
private:

	//�����o�֐�
	void Move();//�v���C���[�ւ̈ړ�
	void Count();//�J�E���g����
	void MoveAction();//�ړ����̍s���ݒ�
	void Attack();//�U������
	void ResetStak();//�X�^�b�N�̏���߂�
	void SetComboList();//�R���{���X�g�̐���
	void Push(MOTION_TYPE motion);//�f�[�^�̒ǉ�
	MOTION_TYPE Pop();//�f�[�^�̎��o��
	float ChangeDirection();//�����̕ύX
	void ColisionHitAttack();//����U���̓����蔻��

	//�����o�ϐ�
	CHPGauge3D* m_HPGauge;//HP�Q�[�W�̏��
	bool m_NearAction;//�v���C���[���߂��ɂ���Ƃ��̍s������
	bool Attackable;//�U���\����
	int m_NearCount;//�v���C���[���߂��ɂ���Ƃ��̍s���J�E���g
	int m_AttackCoolTime;//�U���̃N�[���^�C��
	int m_StackIdx;//TOP�̈ʒu
	MOTION_TYPE m_ComboList[3];//�U���̃R���{���X�g
	MOTION_TYPE m_ComboStack[3];//�U���R���{�̃X�^�b�N
	bool m_Attack;//�U������
	float m_Angle;//����
	int m_FlameCount;//�U���̃t���[���J�E���g
};
#endif