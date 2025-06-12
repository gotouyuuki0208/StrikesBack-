//==========================
// 
// ����[building.h]
// Author Yuki Goto
//
//==========================
#ifndef _BUILDING_H_
#define _BUILDING_H_

//include
#include "objectX.h"

//�N���X�̒�`
class CBuilding :public CObjectX
{
public:
	enum class BUILDING_TYPE
	{
		NONE = 0,
		BUILDING,//�r��
		APARTMENT,//�A�p�[�g
		CONVENI,//�R���r�j
		HOUSE,//��
		HOUSEWHITE,//������
		POLE,//�d��
		SHINGOKI,//�M���@
		FENCE,//�t�F���X
		GARDEN,//��
		CONSTRUCTION,//�H������
		SCHOOL,//�w�Z
		BPARKING,//���֏�
		CORRIDORFLOOR,//�L���̏�
		CORRIDORWALL,//�L���̕�
		SHOERACK,//���ʔ�
		ROOMDOOR,//�����̃h�A
		BOARD,//�f����
		ENTRANCE,//���փh�A
		GYMFRONT,//�̈�ِ���
		GYMWALL,//�̈�ٕ�
		GYMENTRANCE,//�̈�ٓ���
		GYMWALLTOP,//�̈�ٕǏ㕔
		BASKETGOAL,//�o�X�P�b�g�S�[��
		WALL,//��
		GYMDOOR,//�̈�كh�A
		GYMCEILING,
		CEXIT,//�L���o��
		CORRIDORCEILING,//�L���V��
		ILLUMINATION,//�Ɩ�
		WAVEWALL,//�E�F�[�u�ŏ������
		MAX,
	};

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBuilding(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBuilding() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBuilding* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	BUILDING_TYPE GetBuildingType();//�����̎�ނ��擾
	void SetBuildingType(BUILDING_TYPE type);//�����̎�ނ�ݒ�
	int GetModelIdx();//���f���̔ԍ����擾
	void SetModelIdx(int Idx);//���f���̔ԍ���ݒ�
	void ColisionPlayer();//�v���C���[�Ƃ̓����蔻��
	void ColisionPlayerWide();//���f�����������̎��̓����蔻��
	void ColisionEnemy();//�G�Ƃ̓����蔻��
	void ColisionEnemyWide();//���f�����������̎��̓G�Ƃ̓����蔻��
private:
	

	//�����o�ϐ�
	int m_nModelIdx;//���f���̔ԍ�
	BUILDING_TYPE m_Building_Type;//�����̎��
};
#endif