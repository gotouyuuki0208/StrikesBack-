//==========================
// 
// �I�u�W�F�N�g�Ǘ�[object.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//�I�u�W�F�N�g�N���X�̒�`
class CObject
{
public:

	//�I�u�W�F�N�g�̃^�C�v
	enum class TYPE
	{
		NONE = 0,//����
		FADE,	 //�t�F�[�h
		ENEMY,	 //�G
		PLAYER,	 //�v���C���[
		FILD,	 //�t�B�[���h
		WEAPON,	 //����
		BLOCK,	 //�u���b�N
		BUILDING,//����
		JIHANKI, //���̋@
		DELIVERY,//�z�B��
		MAX,
	};

	//�萔
	static const int PRIORITY = 6;		//�`�揇
	static const int MAX_OBJECT = 2000;	//�I�u�W�F�N�g�̍ő吔

	//�����o�֐�
	
	CObject(int nPriority = PRIORITY);					//�`��D��ݒ�
	virtual~CObject();									//�f�X�g���N�^
	virtual HRESULT Init() = 0;							//����������
	virtual void Uninit() = 0;							//�I������
	virtual void Update() = 0;							//�X�V����
	virtual void Draw() = 0;							//�`�揈��
	static void ReleaseAll();							//�S�I�u�W�F�N�g���
	static void UpdateAll();							//�S�I�u�W�F�N�g�X�V
	static void DrawAll();								//�S�I�u�W�F�N�g�`��
	static CObject* GetObj(CObject*Object,int priority);//�I�u�W�F�N�g�擾
	static void ReleseDeath();							//���S�t���O�������Ă�I�u�W�F�N�g�폜
	TYPE GetType();										//�^�C�v�擾
	void SetType(TYPE type);							//�^�C�v�ݒ�
	CObject* GetNextObj();								//���̃I�u�W�F�N�g���擾
	CObject* GetPrevObj();								//�O�̃I�u�W�F�N�g���擾
protected:

	//�����o�֐�
	void Release();	//�������g�̉��	

private:

	//�����o�֐�
	void SwitchDeath();	 //���S�t���O�̐؂�ւ�
	void DisengageList();//���X�g����؂藣��

	//�����o�ϐ�
	static CObject* m_apObject[PRIORITY][MAX_OBJECT];//�I�u�W�F�N�g�Ǘ�
	static CObject* m_pTop[PRIORITY];				 //�擪�̃I�u�W�F�N�g
	static CObject* m_pCur[PRIORITY];				 //�Ō���̃|�C���^
	CObject* m_pPrev;								 //�O�̃I�u�W�F�N�g�̃|�C���^
	CObject* m_pNext;								 //���̃I�u�W�F�N�g�̃|�C���^
	bool m_bDeath;									 //���S����t���O
	static int m_nNumAll;							 //�I�u�W�F�N�g����
	int m_nID;										 //�������g��ID
	TYPE m_Type;									 //�I�u�W�F�N�g�^�C�v
	int m_nPriority;								 //�`��D��x
};

#endif