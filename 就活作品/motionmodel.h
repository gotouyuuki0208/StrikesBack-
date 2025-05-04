//==========================
// 
// ���[�V�������郂�f���̕`�揈��[motionmodel.h]
// Author Yuki Goto
//
//==========================
#ifndef _MOTIONMODEL_H_
#define _MOTIONMODEL_H_

//include
#include "objectgame.h"
#include "modelparts.h"
#include "shadow.h"

//�N���X�̒�`
class CMotionModel :public CObjectgame
{
public:

	//�萔
	static const int PRIORITY;//�`�揇
	static const int MAX_PARTS = 20;//�p�[�c��
	static const int MAX_KEYSET = 20;//�L�[�Z�b�g�̐�
	static const int MAX_MOTION = 25;//���[�V�����̐�

	//�L�[�f�[�^
	struct KEY
	{
		D3DXVECTOR3 pos;//�ʒu
		D3DXVECTOR3 rot;//����
	};

	//�L�[���
	struct KEYSET
	{
		int nFrame;//�t���[��
		KEY aKey[MAX_PARTS];
	};

	//���[�V�������
	struct MOTION
	{
		int Loop;//���[�v���邩
		int nKeyNum;//�L�[�̑���
		KEYSET aKeySet[MAX_KEYSET];
	};

	enum class MOTION_TYPE
	{
		NEUTRAL = 0,//�ҋ@
		MOVE,//�ړ�
		ATTACK,//�U��
		ATTACK2,//�U��2����
		ATTACK3,//�U��3����
		WEAPONNEUTRAL,//�������������Ԃ̑ҋ@
		WEAPONATTACK,//����U��
		WEAPONATTACK2,//����U��2����
		WEAPONATTACK3,//����U��3����
		DUSH,//����
		GUARD,//�K�[�h
		DAMAGE,//�_���[�W
		SMALLWEAPONNEUTRAL,//�Ў蕐�����������Ԃ̑ҋ@
		SMALLWEAPONATTACK,//�Ў蕐��U��
		SMALLWEAPONATTACK2,//�Ў蕐��U��2����
		SMALLWEAPONATTACK3,//�Ў蕐��U��3����
		DAMAGEBLOW,//�������
		SMALLWEAPONGUARD,//�Ў蕐�폊�����K�[�h
		WEAPONMOVE,//�������������Ԃ̈ړ�
		AVOIDANCE_BACK,//���ɉ��
		MAX
	};

	//�����o�֐�
	CMotionModel(int nPriority = PRIORITY);//�R���X�g���N�^
	~CMotionModel() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CMotionModel* Create();//���f������
	void LoadFile(const char name[256],D3DXVECTOR3 scale);//�t�@�C����ǂݍ���
	void SetMotion(MOTION_TYPE MotionType);//���[�V������ݒ�
	MOTION_TYPE GetMotion();//���݂̃��[�V�������擾
	D3DXMATRIX& GetPartsMtx(int PartsNum);//���f���p�[�c�̃}�g���b�N�X���擾
	int GetKeyNum();//���݂̃L�[�ԍ��擾
	void SetDamageCor();//��e���̐F�ɐݒ�
	CModelParts* GetParts(int PartsNum);//�p�[�c�̏����擾
	void SetParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelParts* parents, int ModelPartsNum, D3DXVECTOR3 scale);//�p�[�c�̐���
	void CreateMtx();//�s��̐���
	MOTION_TYPE GetOldMotion();//�O�̃��[�V�������擾
	void SetOldMotion(MOTION_TYPE motion);//�O�̃��[�V������ۑ�
	void DeleteParts(int num);//�p�[�c�̍폜
	bool GetPartsExistence(int PartsNum);//�p�[�c�����݂��邩����
	void Motion();//���[�V��������
	void PartsDraw();//�p�[�c�̕`��
	D3DXVECTOR3& CalMotionPos(int PartsNum);//���[�V�������̃p�[�c�̈ʒu�����߂�
	D3DXVECTOR3& CalMotionRot(int PartsNum);//���[�V�������̃p�[�c�̌��������߂�
	void KeepFirstPos(D3DXVECTOR3 pos, int PartsNum);//�ŏ��̈ʒu��ۑ�
	void KeepFirstRot(D3DXVECTOR3 rot, int PartsNum);//�ŏ��̌�����ۑ�
	bool ExceedMaxFlame();//���[�V�����̃J�E���^�[���Đ��t���[���𒴂���������
	void CalParts();//�p�[�c�̍X�V�ɕK�v�Ȑ��l���v�Z
	void MotionCountUpdate();//�J�E���^�[�̍X�V
	void UpdateMotionInfo();//���[�V�����̏����X�V
	void SubTransparency(float col);//�����x�����炷
private:

	//�����o�ϐ�
	CModelParts* m_PartsList[MAX_PARTS];//�p�[�c�̏��
	CShadow* m_Shadow;//�e�̏��
	MOTION m_MotionInfo[MAX_MOTION];//���[�V�����̏��
	KEY m_FirstMotion[MAX_PARTS];//�ŏ��̈ʒu�ƌ���
	MOTION_TYPE m_MotionType;//���݂̃��[�V�����̎��
	MOTION_TYPE m_oldMotion;//�O�̃��[�V����
	int m_nCurKey;//���݂̃L�[�ԍ�
	int m_nCntMotion;//���[�V�����J�E���^�[
	int m_CurMotion;//���݂̃��[�V�����ԍ�
	int m_PartsNum;//���f���p�[�c��ǂݍ��񂾉�
};
#endif 