//==========================
// 
// �r���{�[�h��HP�Q�[�W[hpgauge3D.h]
// Author Yuki Goto
//
//==========================
#ifndef _HPGAUGE3D_H_
#define _HPGAUGE3D_H_

//include
#include "billboard.h"

//�N���X�̒�`
class CHPGauge3D :public CBillBoard
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CHPGauge3D(int nPriority = PRIORITY);//�R���X�g���N�^
	~CHPGauge3D() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CHPGauge3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int hp);//�I�u�W�F�N�g����
	void SetHP(int hp);//hp��ݒ�
	void EraseGauge();//�\�����Ȃ�
	void DrawGauge();//�\������
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
	bool m_Draw;//�`�攻��
};
#endif