//==========================
// 
// 2D�|���S���`��T���v��[sample_object2D.h]
// Author Yuki Goto
//
//==========================
#ifndef _SAMPLE_OBJECT2D_H_
#define _SAMPLE_OBJECT2D_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CSampleObject2D :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CSampleObject2D(int nPriority = PRIORITY);//�R���X�g���N�^
	~CSampleObject2D() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CSampleObject2D* Create(D3DXVECTOR3 pos, float vertical, float width);//�I�u�W�F�N�g����
private:
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
};
#endif