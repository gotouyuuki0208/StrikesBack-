//==========================
// 
// モーションするモデルの描画処理[motionmodel.h]
// Author Yuki Goto
//
//==========================
#ifndef _MOTIONMODEL_H_
#define _MOTIONMODEL_H_

//include
#include "objectgame.h"
#include "modelparts.h"
#include "shadow.h"

//クラスの定義
class CMotionModel :public CObjectgame
{
public:

	//定数
	static const int PRIORITY;//描画順
	static const int MAX_PARTS = 20;//パーツ数
	static const int MAX_KEYSET = 20;//キーセットの数
	static const int MAX_MOTION = 25;//モーションの数

	//キーデータ
	struct KEY
	{
		D3DXVECTOR3 pos;//位置
		D3DXVECTOR3 rot;//向き
	};

	//キー情報
	struct KEYSET
	{
		int nFrame;//フレーム
		KEY aKey[MAX_PARTS];
	};

	//モーション情報
	struct MOTION
	{
		int Loop;//ループするか
		int nKeyNum;//キーの総数
		KEYSET aKeySet[MAX_KEYSET];
	};

	enum class MOTION_TYPE
	{
		NEUTRAL = 0,//待機
		MOVE,//移動
		ATTACK,//攻撃
		ATTACK2,//攻撃2発目
		ATTACK3,//攻撃3発目
		WEAPONNEUTRAL,//武器を持った状態の待機
		WEAPONATTACK,//武器攻撃
		WEAPONATTACK2,//武器攻撃2発目
		WEAPONATTACK3,//武器攻撃3発目
		DUSH,//走る
		GUARD,//ガード
		DAMAGE,//ダメージ
		SMALLWEAPONNEUTRAL,//片手武器を持った状態の待機
		SMALLWEAPONATTACK,//片手武器攻撃
		SMALLWEAPONATTACK2,//片手武器攻撃2発目
		SMALLWEAPONATTACK3,//片手武器攻撃3発目
		DAMAGEBLOW,//吹き飛び
		SMALLWEAPONGUARD,//片手武器所持時ガード
		WEAPONMOVE,//武器を持った状態の移動
		AVOIDANCE_BACK,//後ろに回避
		MAX
	};

	//メンバ関数
	CMotionModel(int nPriority = PRIORITY);//コンストラクタ
	~CMotionModel() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CMotionModel* Create();//モデル生成
	void LoadFile(const char name[256],D3DXVECTOR3 scale);//ファイルを読み込む
	void SetMotion(MOTION_TYPE MotionType);//モーションを設定
	MOTION_TYPE GetMotion();//現在のモーションを取得
	D3DXMATRIX& GetPartsMtx(int PartsNum);//モデルパーツのマトリックスを取得
	int GetKeyNum();//現在のキー番号取得
	void SetDamageCor();//被弾時の色に設定
	CModelParts* GetParts(int PartsNum);//パーツの情報を取得
	void SetParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelParts* parents, int ModelPartsNum, D3DXVECTOR3 scale);//パーツの生成
	void CreateMtx();//行列の生成
	MOTION_TYPE GetOldMotion();//前のモーションを取得
	void SetOldMotion(MOTION_TYPE motion);//前のモーションを保存
	void DeleteParts(int num);//パーツの削除
	bool GetPartsExistence(int PartsNum);//パーツが存在するか判定
	void Motion();//モーション処理
	void PartsDraw();//パーツの描画
	D3DXVECTOR3& CalMotionPos(int PartsNum);//モーション中のパーツの位置を求める
	D3DXVECTOR3& CalMotionRot(int PartsNum);//モーション中のパーツの向きを求める
	void KeepFirstPos(D3DXVECTOR3 pos, int PartsNum);//最初の位置を保存
	void KeepFirstRot(D3DXVECTOR3 rot, int PartsNum);//最初の向きを保存
	bool ExceedMaxFlame();//モーションのカウンターが再生フレームを超えたか判定
	void CalParts();//パーツの更新に必要な数値を計算
	void MotionCountUpdate();//カウンターの更新
	void UpdateMotionInfo();//モーションの情報を更新
	void SubTransparency(float col);//透明度を減らす
private:

	//メンバ変数
	CModelParts* m_PartsList[MAX_PARTS];//パーツの情報
	CShadow* m_Shadow;//影の情報
	MOTION m_MotionInfo[MAX_MOTION];//モーションの情報
	KEY m_FirstMotion[MAX_PARTS];//最初の位置と向き
	MOTION_TYPE m_MotionType;//現在のモーションの種類
	MOTION_TYPE m_oldMotion;//前のモーション
	int m_nCurKey;//現在のキー番号
	int m_nCntMotion;//モーションカウンター
	int m_CurMotion;//現在のモーション番号
	int m_PartsNum;//モデルパーツを読み込んだ回数
};
#endif 