//==========================
// 
// �X�e�[�W�J�ڈʒu[stagechangepoint.h]
// Author Yuki Goto
//
//==========================
#ifndef _STAGECHANGEPOINT_H_
#define _STAGECHANGEPOINT_H_

//include
#include "fild.h"
#include "goalpoint.h"

//�N���X�̒�`
class CStageChangePoint :public CFild
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CStageChangePoint(int nPriority = PRIORITY);//�R���X�g���N�^
	~CStageChangePoint() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CStageChangePoint* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//�I�u�W�F�N�g����
private:

	//�����o�֐�
	void ColisionPlayer();//�v���C���[�Ƃ̓����蔻��

	//�����o�ϐ�
	CGoalPoint* m_GoalPoint;//�X�e�[�W�J�ڈʒu�̈ʒu�\��
};
#endif