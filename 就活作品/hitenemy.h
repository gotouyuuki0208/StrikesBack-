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
	void Attack();//�U������
	
	void ColisionHitAttack();//����U���̓����蔻��

	//�����o�ϐ�
	CHPGauge3D* m_HPGauge;//HP�Q�[�W�̏��
	bool m_NearAction;//�v���C���[���߂��ɂ���Ƃ��̍s������
	
	int m_NearCount;//�v���C���[���߂��ɂ���Ƃ��̍s���J�E���g
	int m_AttackCoolTime;//�U���̃N�[���^�C��
	bool m_Attack;//�U������
	int m_FlameCount;//�U���̃t���[���J�E���g
};
#endif