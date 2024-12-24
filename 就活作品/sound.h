//==========================
// 
// �T�E���h����[sound.h]
// Author Yuki Goto
//
//==========================
#ifndef _SOUND_H_
#define _SOUND_H_

// �T�E���h�N���X�̒�`
class CSound
{
public:
	//�T�E���h�ꗗ
	typedef enum
	{
		SOUND_LABEL_INGAME = 0,		// BGM0
		SOUND_LABEL_TITLE,			// BGM1
		SOUND_LABEL_RESULT,			// BGM2
		SOUND_LABEL_SE_WEAOPNATTACK,		// ����U��
		SOUND_LABEL_SE_ATTACK,			// ����
		SOUND_LABEL_SE_RECOVERY,	// ��
		SOUND_LABEL_SE_START,	// �X�^�[�g
		SOUND_LABEL_SE_GUARD,	// �X�^�[�g
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//�����o�֐�
	CSound();//�R���X�g���N�^
	~CSound();//�f�X�g���N�^
	HRESULT Init(HWND hWnd);//����������
	void Uninit();//�I������
	HRESULT PlaySound(SOUND_LABEL label);// �Z�O�����g�Đ�(�Đ����Ȃ��~)
	void Stop(SOUND_LABEL label);// �Z�O�����g��~(���x���w��)
	void Stop();// �Z�O�����g��~(�S��)

private:
	// �T�E���h���̍\���̒�`
	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	//�����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);// �`�����N�̃`�F�b�N
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);// �`�����N�f�[�^�̓ǂݍ���

	//�����o�ϐ�
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX]= {				// �T�E���h�̏��
	{"data/BGM/ingame.wav", -1},		// BGM0
	{"data/BGM/title.wav", -1},		// BGM1
	{"data/BGM/result.wav", -1},		// BGM2
	{"data/SE/weaponattack.wav", 0},			// �e���ˉ�
	{"data/SE/attack.wav", 0},			// ������
	{"data/SE/recovery.wav", 0},	// ���S��
	{"data/SE/start.wav", 0},	// �A�C�e���擾��
	{"data/SE/guard.wav", 0},	// �A�C�e���擾��
	};			
};

#endif 
