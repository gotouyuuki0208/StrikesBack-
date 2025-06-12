//==========================
// 
// �G���G[weakenemy.h]
// Author Yuki Goto
//
//==========================
#ifndef _WEAKENEMY_H_
#define _WEAKENEMY_H_

//include
#include"enemy.h"

//�O���錾
class CEnemyStateBase;
class CStateMachine;
class CEnemyMovePoint;
class CHPGauge3D;

//�N���X�̒�`
class CWeakEnemy :public CEnemy
{
public:

	//�萔
	static const int PRIORITY;//�`�揇
	static const int POINT = 10;//�ړ��n�_�̐�

	//�����o�֐�
	CWeakEnemy(int nPriority = PRIORITY);//�R���X�g���N�^
	~CWeakEnemy() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CWeakEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����

	void ChangeState(CEnemyStateBase* NewState);//��Ԃ�ύX
	bool Hit(D3DXVECTOR3 pos, int damage, MOTION_TYPE HitMotion);//�U����e����
	void SubPartsCol();//�p�[�c�̓����x�����炷
	void Patrol();//�ړ��n�_������
	bool GetPatrol();
	void SetEndPatrol();
private:

	//�����o�֐�
	void ColisionEnemy();//�G���m�̓����蔻��
	void GetMovePoint();//�ړ��n�_���擾

	//�����o�ϐ�
	CStateMachine* m_StateMachine;//��ԊǗ�
	CEnemyMovePoint* m_Point[POINT];//�ړ��n�_�̏��
	int m_CurPoint;//���݂̈ړ��n�_
	float m_Color;
	bool m_Patrol;//�ړ��n�_���ړ����邩����
};
#endif