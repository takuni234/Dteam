/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	FixedBox::FixedBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	FixedBox::~FixedBox() {}

	//初期化
	void FixedBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"FixedBox");
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"SKY_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

	}
	//--------------------------------------------------------------------------------------
//	class IncreaseBox : public GameObject;
//--------------------------------------------------------------------------------------
//構築と破棄

	IncreaseBox::IncreaseBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}

	IncreaseBox::~IncreaseBox() {}

	//初期化
	void IncreaseBox::OnCreate() {
		check = 0;
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		//タグをつける
		AddTag(L"FixedBox");
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"SKY_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetDiffuse(Col4(1, 0, 0, 1));



	}
	//int IncreaseBox::checkkansu() {
	//	return check;
	//}
	void IncreaseBox::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Bullet")) {
				SetDrawActive(false);
				SetUpdateActive(false);
				auto posTarget = GetComponent<Transform>()->GetPosition();
				GetStage()->AddGameObject<ColdBox>(Vec3(0.2), Vec3(0), Vec3(posTarget));

		}

		check = 1;
	}

	//--------------------------------------------------------------------------------------
//	class ColdBox : public GameObject;
//--------------------------------------------------------------------------------------
//構築と破棄

	ColdBox::ColdBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}

	ColdBox::~ColdBox() {}

	//初期化
	void ColdBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"FixedBox");
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"SKY_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetDiffuse(Col4(0.5, 0.5, 0.5, 1));



	}

	//--------------------------------------------------------------------------------------
	//	class FixedSphere : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	FixedSphere::FixedSphere(const shared_ptr<Stage>& StagePtr,
		const float Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	FixedSphere::~FixedSphere() {}

	//初期化
	void FixedSphere::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//CollisionSphere衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"FixedSphere");
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetTextureResource(L"SKY_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

	}

	//--------------------------------------------------------------------------------------
	//	class FixedCapsule : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	FixedCapsule::FixedCapsule(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	FixedCapsule::~FixedCapsule() {}

	//初期化
	void FixedCapsule::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//CAPSULE衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"FixedCapsule");
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CAPSULE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		ptrDraw->SetTextureResource(L"SKY_TX");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
	}

	//--------------------------------------------------------------------------------------
	//	class IncreaseObject: public GameObject;
	//--------------------------------------------------------------------------------------
	IncreaseObject::IncreaseObject(const shared_ptr<Stage>& StagePtr ,const Vec3& Position):GameObject(StagePtr),m_Position(Position) ,count(0),x(0),z(0){}
	IncreaseObject::~IncreaseObject(){}
	void IncreaseObject::OnCreate(){

	}
	void IncreaseObject::OnUpdate() {
		if (count != 4) {
			//for (int i = 0; i < 5; i++) {
			if (time == 60) {	
				//randomx = rand() % 3-1;
				//randomz = rand() % 3-1;
				//if (!(randomx == 0 && randomz == 0)) {
				//	x = x + randomx;
					//z = z + randomz;
				//}
				
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x+0)*0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0)*0.2));
				z ++;

				count++;
				//time = 0;
			}	

			if (time == 120) {

				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1)*0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1)*0.2));

				z++;

				count++;
				//time = 0;
			}
			if (time == 180) {

				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2)* 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				z++;

				count++;
				//time = 0;
			}
			if (time == 240) {

				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 0) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -1) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -2) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 3) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -3)* 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 0) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -1) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + 2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + 3) * 0.2));
				GetStage()->AddGameObject<IncreaseBox>(Vec3(0.2), Vec3(0), Vec3((m_Position.x + -2) * 0.2, (m_Position.y + 0) - 0.4, (m_Position.z + -3) * 0.2));
				z++;

				count++;
				//time = 0;
			}

			time++;

			//}
		}

	}

	//--------------------------------------------------------------------------------------
///	スコア表示のスプライト
//--------------------------------------------------------------------------------------
	ScoreSprite::ScoreSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Score(0.0f)
	{}

	void ScoreSprite::OnCreate() {
		float xPiecesize = 1.0f / (float)m_NumberOfDigits;
		float helfSize = 0.5f;

		//インデックス配列
		vector<uint16_t> indices;
		for (UINT i = 0; i < m_NumberOfDigits; i++) {
			float vertex0 = -helfSize + xPiecesize * (float)i;
			float vertex1 = vertex0 + xPiecesize;
			//0
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, helfSize, 0), Vec2(0.0f, 0.0f))
			);
			//1
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, helfSize, 0), Vec2(0.1f, 0.0f))
			);
			//2
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, -helfSize, 0), Vec2(0.0f, 8.0f))
			);
			//3
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, -helfSize, 0), Vec2(0.1f, 8.0f))
			);
			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 2);
		}

		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		GetStage()->SetSharedGameObject(L"ScoreSprite", GetThis<ScoreSprite>());
	}

	void ScoreSprite::OnUpdate() {
		vector<VertexPositionTexture> newVertices;
		UINT num;
		int verNum = 0;
		for (UINT i = m_NumberOfDigits; i > 0; i--) {
			UINT base = (UINT)pow(10, i);
			num = ((UINT)m_Score) % base;
			num = num / (base / 10);
			Vec2 uv0 = m_BackupVertices[verNum].textureCoordinate;
			uv0.x = (float)num / 10.0f;
			auto v = VertexPositionTexture(
				m_BackupVertices[verNum].position,
				uv0
			);
			newVertices.push_back(v);

			Vec2 uv1 = m_BackupVertices[verNum + 1].textureCoordinate;
			uv1.x = uv0.x + 0.1f;
			v = VertexPositionTexture(
				m_BackupVertices[verNum + 1].position,
				uv1
			);
			newVertices.push_back(v);

			Vec2 uv2 = m_BackupVertices[verNum + 2].textureCoordinate;
			uv2.x = uv0.x;

			v = VertexPositionTexture(
				m_BackupVertices[verNum + 2].position,
				uv2
			);
			newVertices.push_back(v);

			Vec2 uv3 = m_BackupVertices[verNum + 3].textureCoordinate;
			uv3.x = uv0.x + 0.1f;

			v = VertexPositionTexture(
				m_BackupVertices[verNum + 3].position,
				uv3
			);
			newVertices.push_back(v);

			verNum += 4;
		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
	}


}



//end basecross
