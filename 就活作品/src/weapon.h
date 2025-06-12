//==========================
// 
// 武器[weapon.h]
// Author Yuki Goto
//
//==========================
#ifndef _WEAPON_H_
#define _WEAPON_H_

//include
#include "objectX.h"
#include "modelparts.h"
#include "weaponpoint.h"
#include "collisionvisual.h"
#include "motionmodel.h"

//クラスの定義
class CWeapon :public CObjectX
{
public:
	//列挙型の定義
	enum class WEAPONTYPE
	{
		NONE = 0,
		BIG,//両手で持つ
		SMALL,//片手で持つ
	};

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CWeapon(int nPriority = PRIORITY);//コンストラクタ
	~CWeapon() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CWeapon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	void SetParent(CModelParts* Parent);//親モデルの設定
	void CollisionEnemy();//敵との当たり判定
	void SetAttackReset();//攻撃判定を戻す
	WEAPONTYPE GetWeaponType();//武器の種類を取得
	void SetWeaponType(WEAPONTYPE weapontype);//武器の種類を設定
	int GetModelIdx();//モデルの番号を取得
	void SetModelIdx(int num);//モデルの番号を設定
	void Reaction();//武器を所持出来るときの反応
	void Reset();//スケールをリセット
	void CreateVisual();//当たり判定を可視化する
	void GrabCharacter();//キャラクターに掴まれた
	void ReleseCharacter(D3DXVECTOR3 pos);//キャラクターが放した
	bool GetGrab();//掴まれてるか取得
	void SetDurability(int Num);//耐久値の設定
	int GetDurability();//耐久値の取得
	void SubDurability();//耐久値を減らす
	void CorrectInfo();//情報を戻す
	void ThrowAngle(CMotionModel* Charactar);//投げられる時の角度を求める
private:

	//メンバ関数
	void ColisionPlayer();//プレイヤーとの当たり判定
	void HitEnemy();//敵への攻撃時の判定
	void Move();//移動処理
	void CollisionFild();//地面との当たり判定
	void CollisionThrow();//武器を投げた時の当たり判定

	//メンバ変数
	CModelParts* m_Parent;//親モデル
	bool m_Attack;//衝突したか判定
	WEAPONTYPE m_weapontype;//武器の種類
	int m_ModelIdx;//モデルの番号
	CWeaponPoint* m_WeaponPoint;//武器の位置表示
	bool m_Transparent;//透明度の上下判定
	CCollisionVisual* m_visual;//当たり判定の可視化
	bool m_Garb;//キャラクターが持ってるか判定
	int m_Durability;//耐久値
	D3DXVECTOR3 m_RotKeep;//向きの保存
	D3DXVECTOR3 m_ScaleKeep;//拡大率の保存
	D3DXVECTOR3 m_ThrowAngle;
	bool m_Throw;
	D3DXMATRIX m_rot;
	D3DXMATRIX m_scale;
};
#endif