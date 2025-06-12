//==========================
// 
// �v���C���[HP�Q�[�W�̘g[playergaugeframe.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYERGAUGEFRAME_H_
#define _PLAYERGAUGEFRAME_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CPlayerHPGaugeFrame :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CPlayerHPGaugeFrame(int nPriority = PRIORITY);//�R���X�g���N�^
	~CPlayerHPGaugeFrame() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CPlayerHPGaugeFrame* Create(D3DXVECTOR3 pos, float vertical, float width);//�I�u�W�F�N�g����
	void SetVtx();//���_���̐ݒ�
private:
	//�����o�ϐ�
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
};
#endif