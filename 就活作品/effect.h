//==========================
// 
// �G�t�F�N�g����[effect.h]
// Author Yuki Goto
//
//==========================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//include
#include"billboard.h"

//�v���C���[�N���X�̒�`
class CEffect :public CBillBoard
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	CEffect(int nPriority = PRIORITY);//�R���X�g���N�^
	~CEffect() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR cor,float Vertical, float Width);//����
	
private:
	//�����o�ϐ�
	static int m_nTexIdx;//�e�N�X�`��ID
	int m_nLife;//����
	float cor;//�F
	float m_Vertical;//�c
	float m_Width;//��
};
#endif 
