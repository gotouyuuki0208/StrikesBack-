//==========================
// 
// サウンド処理[sound.h]
// Author Yuki Goto
//
//==========================
#ifndef _SOUND_H_
#define _SOUND_H_

// サウンドクラスの定義
class CSound
{
public:
	//サウンド一覧
	typedef enum
	{
		SOUND_LABEL_INGAME = 0,		// BGM0
		SOUND_LABEL_TITLE,			// BGM1
		SOUND_LABEL_RESULT,			// BGM2
		SOUND_LABEL_SE_WEAOPNATTACK,		// 武器攻撃
		SOUND_LABEL_SE_ATTACK,			// 殴り
		SOUND_LABEL_SE_RECOVERY,	// 回復
		SOUND_LABEL_SE_START,	// スタート
		SOUND_LABEL_SE_GUARD,	// スタート
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//メンバ関数
	CSound();//コンストラクタ
	~CSound();//デストラクタ
	HRESULT Init(HWND hWnd);//初期化処理
	void Uninit();//終了処理
	HRESULT PlaySound(SOUND_LABEL label);// セグメント再生(再生中なら停止)
	void Stop(SOUND_LABEL label);// セグメント停止(ラベル指定)
	void Stop();// セグメント停止(全て)

private:
	// サウンド情報の構造体定義
	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDINFO;

	//メンバ関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);// チャンクのチェック
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);// チャンクデータの読み込み

	//メンバ変数
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX]= {				// サウンドの情報
	{"data/BGM/ingame.wav", -1},		// BGM0
	{"data/BGM/title.wav", -1},		// BGM1
	{"data/BGM/result.wav", -1},		// BGM2
	{"data/SE/weaponattack.wav", 0},			// 弾発射音
	{"data/SE/attack.wav", 0},			// 爆発音
	{"data/SE/recovery.wav", 0},	// 死亡音
	{"data/SE/start.wav", 0},	// アイテム取得音
	{"data/SE/guard.wav", 0},	// アイテム取得音
	};			
};

#endif 
