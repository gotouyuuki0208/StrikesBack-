//==========================
// 
// ���[�V�������郂�f���̕`��T���v��[sample_MotionModel.h]
// Author Yuki Goto
//
//==========================
#ifndef _SAMPLE_MOTIONMODEL_H_
#define _SAMPLE_MOTIONMODEL_H_

//include
#include "motionmodel.h"

//�N���X�̒�`
class CSampleMotionModel :public CMotionModel
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CSampleMotionModel(int nPriority = PRIORITY);//�R���X�g���N�^
	~CSampleMotionModel() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CSampleMotionModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
private:
};
#endif