//==========================
// 
// オブジェクト配置[edit.h]
// Author Yuki Goto
//
//==========================
#ifndef _EDIT_H_
#define _EDIT_H_

//include
#include"objectgame.h"
#include <list>

//オブジェクト配置クラスの定義
class CEdit
{
public:
	
	//定数
	static const float MOVE;//移動量
	static const float SCALE;//スケール

	//メンバ関数
	CEdit();//コンストラクタ
	~CEdit();//デストラクタ
	HRESULT Init();//初期設定
	void Update();//更新処理
	void Uninit();//終了処理
	void Load(int Stage);//配置情報を読み込む
	void Save(int Stage);//配置情報を書き出す
	void DeleteAll();//リストの全てのオブジェクトを削除
private:

	//保存する情報
	struct Keep
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 scale;
		D3DXVECTOR3 rot;
		int ObjectType;
	};

	//メンバ関数
	void Move();//移動
	void Scale();//スケール変更
	void ChangeObject();//オブジェクトを変更
	CObjectgame* SetType();//オブジェクトの種類を設定
	void ChangeType();//オブジェクトの種類を設定
	void Rotate();//向きを変える
	void KeepInfo();//情報を保存
	void SwitchEditMode();//編集モードの切り替え
	void StageChange();//ステージを変更

	void EnemyLoad(int Stage);//敵の配置情報を読み込む
	void EnemySave(int Stage);//敵の配置情報を書き出す
	void BuildingLoad(int Stage);//建物の配置情報を読み込む
	void BuildingSave(int Stage);//建物の配置情報を書き出す
	void WeaponLoad(int Stage);//武器の配置情報を読み込む
	void WeaponSave(int Stage);//武器の配置情報を書き出す
	void ItemLoad(int Stage);//アイテムの配置情報を読み込む
	void ItemSave(int Stage);//アイテムの配置情報を書き出す
	void FildLoad(int Stage);//フィールドの配置情報を読み込む
	void FildSave(int Stage);//フィールドの配置情報を書き出す

	//メンバ変数
	list<CObjectgame*> m_Object;//配置オブジェクトリスト
	list<CObjectgame*>::iterator m_Objectite;//配置オブジェクトリストイテレーター
	Keep m_EditObjectKeep;//編集中のオブジェクトを保存
	CObjectgame* m_EditObject;//現在編集しているオブジェクト
	D3DXVECTOR3 m_pos;//位置
	D3DXVECTOR3 m_scale;//スケール
	D3DXVECTOR3 m_rot;//向き
	bool m_EditMode;//編集モード(false:新規オブジェクト true:配置済みオブジェクト)
	int m_ObjectType;//オブジェクトの種類
	bool m_MoveDirection;//移動方向(false:Z移動 true:Y移動)
	bool m_SwitchInput;//入力方法(false:Press true:Trigger)
	bool m_move;//移動の編集(false:位置 true:向き)
	bool m_Camera;//カメラの位置
	bool m_ChangeScale;//スケール変更
};
#endif