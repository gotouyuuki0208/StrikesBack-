//==========================
// 
// �{�X��HP�Q�[�W�̘g[bossgaugeframe.h]
// Author Yuki Goto
//
//==========================
#ifndef _BOSSGAUGEFRAME_H_
#define _BOSSGAUGEFRAME_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CBossGaugeFrame :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBossGaugeFrame(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBossGaugeFrame() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBossGaugeFrame* Create(D3DXVECTOR3 pos, float vertical, float width);//�I�u�W�F�N�g����
private:

	//�����o�֐�
	void SetVtx();//���_���̐ݒ�

	//�����o�ϐ�
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
};
#endif