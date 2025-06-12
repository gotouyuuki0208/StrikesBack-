//==========================
// 
// �p�[�e�B�N������[particle.h]
// Author Yuki Goto
//
//==========================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//include
#include"billboard.h"

//�v���C���[�N���X�̒�`
class CParticle :public CBillBoard
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CParticle(int priority = PRIORITY);//�R���X�g���N�^
	~CParticle() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CParticle* Create(D3DXVECTOR3 pos, D3DXCOLOR cor,int life,float Width, float Vertical, float speed);//����

private:

	//�����o�֐�
	D3DXVECTOR3 m_posmove;//�ʒu�̈ړ���
	D3DXVECTOR3 m_rotmove;//�����̈ړ���
	int m_nLife;//����
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
	float m_cor;//�F
	float m_Width;//��
	float m_Vertical;//�c
	float m_speed;//���x
};
#endif 
