//==========================
// 
// �{�X��HP�Q�[�W[bosshpgauge.h]
// Author Yuki Goto
//
//==========================
#ifndef _BOSSHPGAUGE_H_
#define _BOSSHPGAUGE_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CBossHPGauge :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBossHPGauge(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBossHPGauge() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBossHPGauge* Create(D3DXVECTOR3 pos, float vertical, float width);//�I�u�W�F�N�g����
	void SetHP(int hp);//hp��ݒ�
private:

	//�����o�֐�
	void SetVtx();//���_���̐ݒ�
	void SwitchCor();//�F�̕ύX
	void SetLength();//�Q�[�W�̒�����ݒ�

	//�����o�ϐ�
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
	int m_HP;//HP�̐��l
	int m_MaxHP;//�ő�HP�̐��l
	float m_Targetlength;//�ړI�̒���
	float m_length;//����
	float m_Ratio;//HP�̊���
};
#endif