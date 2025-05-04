//==========================
// 
// �O�Ղ̕`�揈��[trajectory.h]
// Author Yuki Goto
//
//==========================
#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

//include
#include "objectMesh.h"

//�N���X�̒�`
class CTrajectory :public CObjectMesh
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CTrajectory(int nPriority = PRIORITY);//�R���X�g���N�^
	~CTrajectory() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CTrajectory* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Width, int Vertical);//���f������
	void SetNewPos(D3DXVECTOR3 pos);//�V�������_���W�̈ʒu��ݒ�
private:

	//�����o�֐�
	void SetVertexPos();//���_���W�̐ݒ�
	void InitVtxPos();//���_���̏����ݒ�

	//�����o�ϐ�
	D3DXVECTOR3 m_NewPos;//�V�������_���W�̈ʒu
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
};
#endif 