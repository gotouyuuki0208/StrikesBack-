//==========================
// 
// 当たり判定可視化[collisionvisual.h]
// Author Yuki Goto
//
//==========================
#ifndef _COLLISONVISUAL_H_
#define _COLLISONVISUAL_H_

//クラスの定義
class CCollisionVisual
{
public:
	
	//メンバ関数
	CCollisionVisual();//コンストラクタ
	~CCollisionVisual();//デストラクタ
	HRESULT Init();//初期化処理
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw();//描画処理
	static CCollisionVisual* Create(D3DXVECTOR3 pos, float radius);//オブジェクト生成
	void SetPos(D3DXVECTOR3 pos);//位置の設定
	void SetCorNomal();//通常の色に設定
	void SetCorCollision();//衝突しているときの色に設定
	float GetRadius();//半径を取得
	D3DXVECTOR3& GetPos();//位置を取得
private:
	//メンバ変数
	LPD3DXMESH m_pMesh;//メッシュ(頂点情報)へのポインタ
	float m_radius;//半径
	D3DXVECTOR3 m_pos;//位置
	D3DXVECTOR3 m_rot;//向き
	D3DXMATRIX m_mtxWorld;//ワールドマトリックス
	D3DXCOLOR m_cor;//色の設
};

#endif