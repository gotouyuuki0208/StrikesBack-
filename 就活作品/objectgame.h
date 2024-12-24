//==========================
// 
// �Q�[���I�u�W�F�N�g[objectgame.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECTGAME_H_
#define _OBJECTGAME_H_

//ibclude
#include "object.h"

//�I�u�W�F�N�g�N���X�̒�`
class CObjectgame:public CObject
{
public:

	//�萔
	static const int PRIORITY = 5;

	//�����o�֐�
	CObjectgame(int nPriority = PRIORITY);//�`��D��ݒ�
	~CObjectgame()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	D3DXVECTOR3& GetPos();//�ʒu�擾
	void SetPos(D3DXVECTOR3 pos);//�ʒu�ݒ�
	D3DXVECTOR3& GetRot();//�����擾
	void SetRot(D3DXVECTOR3 rot);//�����ݒ�
	D3DXVECTOR3& GetRotMove();//�����擾
	void SetRotMove(D3DXVECTOR3 rot);//�����ݒ�
	D3DXVECTOR3& GetPosOld();//�̂̈ʒu�擾
	void SetPosOld(D3DXVECTOR3 posord);//�̂̈ʒu�ݒ�
	D3DXVECTOR3& GetMove();//�ړ��l�擾
	void SetMove(D3DXVECTOR3 move);//�ړ��l�ݒ�
	D3DXMATRIX& GetMtxWorld();//�}�g���b�N�X�擾
	void SetMtxWorld(D3DXMATRIX mtxWorld);//�}�g���b�N�X�̐ݒ�
	float GetRadius();//���a�̎擾
	void SetRadius(float radius);//���a�̐ݒ�
	D3DXVECTOR3& GetScale();//�g�嗦�̐ݒ�
	void SetScale(D3DXVECTOR3 scale);//�g�嗦�̐ݒ�
	bool ColisionSphere(D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, float myradius, float partnerradius);//���̔���
	float RevisionRot(float objectiverot ,float currentrot,float Cur);//�����̕␳
	float NormalizeAngle(float angle);//�����̐��K��
	float VectorCalculation(float current, float purpose);//�x�N�g���̎Z�o
private:
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;//�ʒu
	D3DXVECTOR3 m_posmove;//�ʒu�̈ړ���
	D3DXVECTOR3 m_rot;//����
	D3DXVECTOR3 m_posold;//�O�̈ʒu
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X
	float m_radius;//���a
	D3DXVECTOR3 m_scale;//�g�嗦
	D3DXVECTOR3 m_rotmove;//�����̈ړ���
};

#endif
