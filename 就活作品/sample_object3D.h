//==========================
// 
// 3D�|���S���`��T���v��[sample_object3D.h]
// Author Yuki Goto
//
//==========================
#ifndef _SAMPLE_OBJECT3D_H_
#define _SAMPLE_OBJECT3D_H_

//include
#include "object3D.h"

//�N���X�̒�`
class CSampleObject3D :public CObject3D
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CSampleObject3D(int nPriority = PRIORITY);//�R���X�g���N�^
	~CSampleObject3D() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CSampleObject3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//�I�u�W�F�N�g����
private:
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
};
#endif