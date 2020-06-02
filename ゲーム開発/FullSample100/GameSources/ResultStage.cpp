/*!
@file ResultStage.cpp
@brief リザルトステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	リザルトステージクラス実体
	//--------------------------------------------------------------------------------------
	void ResultStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	//点滅するスプライト作成
	void ResultStage::CreatePushSprite() {
		auto ptrScore = AddGameObject<ScoreSprite>(1,
			L"NUMBER_TX",
			true,
			Vec2(250.0f, 100.0f),
			Vec3(0.0f, 300.0f, 0.0f));
		ptrScore->SetScore(static_cast<float>(m_SelectNum));
		SetSharedGameObject(L"TestScoreSprite", ptrScore);
	}

	void ResultStage::CreateSprite() {
		CreateSharedObjectGroup(L"ResultSprite");
		//配置する位置（全体）
		Vec3 DefultPos(0.0f,0.0f,0.0f);
		for (int i = 0; i < static_cast<int>(ResultStageMenuKey::Max); i++) {
			Vec2 createScale(100.0f, 100.0f);
			Vec3 createPos(Vec3(0.0f, -i * 150.0f, 0.0f) + DefultPos);
			wstring txKey;
			switch (static_cast<ResultStageMenuKey>(i))
			{
				//「次のステージへ」の画像
			case ResultStageMenuKey::NextStage:
				txKey = L"TONEXTSTAGE_TX";
				break;
				// 「ステージセレクトへ」の画像
			case ResultStageMenuKey::Select:
				txKey = L"TOSTAGESELECT_TX";
				break;
				// 「リトライ」の画像
			case ResultStageMenuKey::Retry:
				txKey = L"TORETRY_TX";
				break;
				// 「タイトルへ」の画像
			case ResultStageMenuKey::Title:
				txKey = L"TOTITLE_TX";
				break;
			default:
				//エラー
				txKey = L"SKY_TX";
				createScale = Vec2(100.0f);
				break;
			}
			auto ptrSprite = AddGameObject<Sprite>(txKey, createScale, createPos);
			m_ResultSpriteDefultScale.push_back(ptrSprite->GetComponent<Transform>()->GetScale());
			m_ResultSpritePos.push_back(createPos);
			GetSharedObjectGroup(L"ResultSprite")->IntoGroup(ptrSprite);
		}

		auto ptrCursol = AddGameObject<Sprite>(L"SPARK_TX");
		ptrCursol->SetPosition(DefultPos + Vec3(-(m_ResultSpriteDefultScale[static_cast<int>(ResultStageMenuKey::Select)].x + ptrCursol->GetScale().x) * 0.5f, 0.0f,0.0f));
		SetSharedGameObject(L"ResultCursor", ptrCursol);
	}

	void ResultStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreatePushSprite();
			CreateSprite();
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"Nanika", XAUDIO2_LOOP_INFINITE, 0.1f);
		}
		catch (...) {
			throw;
		}
	}

	void ResultStage::OnUpdate() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		StageSelectKeyInput();
		bool start =
			CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START ||
			CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B ||
			KeyState.m_bPressedKeyTbl[VK_SPACE];

		UpdateCursor();

		if (start) {
			ChangeStageSceneSelected();
		}
	}

	void ResultStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void ResultStage::StageSelectKeyInput() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (CntlVec[0].bConnected) {
			if (!m_InputOnce) {
				if (CntlVec[0].fThumbLY >= 0.9f) {
					m_SelectNum--;
					m_InputOnce = true;
				}
				else if (CntlVec[0].fThumbLY <= -0.9f) {
					m_SelectNum++;
					m_InputOnce = true;
				}
			}
			else {
				auto elapsedTime = App::GetApp()->GetElapsedTime();
				m_Time += elapsedTime;
				if (m_Time > 0.3f) {
					m_InputOnce = false;
					m_Time = 0.0f;
				}
			}
			if (CntlVec[0].fThumbLY <= 0.05f && CntlVec[0].fThumbLY >= -0.05f) {
				m_InputOnce = false;
				m_Time = 0.0f;
			}
		}
		else if (!(KeyState.m_bPressedKeyTbl[VK_UP] && KeyState.m_bPressedKeyTbl[VK_DOWN])) {
			if (KeyState.m_bPressedKeyTbl[VK_DOWN]) {
				m_SelectNum++;
			}
			if (KeyState.m_bPressedKeyTbl[VK_UP]) {
				m_SelectNum--;
			}
		}

		if (m_SelectNum <= 0) {
			m_SelectNum = static_cast<int>(ResultStageMenuKey::Max);
		}
		m_MenuKey = ResultStageMenuKey(m_SelectNum % static_cast<int>(ResultStageMenuKey::Max));
	}

	void ResultStage::UpdateCursor() {
		GetSharedGameObject<ScoreSprite>(L"TestScoreSprite")->SetScore(static_cast<float>(m_MenuKey));
		auto ptrCursor = GetSharedGameObject<Sprite>(L"ResultCursor");
		auto ptrTrans = ptrCursor->GetComponent<Transform>();
		ptrTrans->SetPosition(m_ResultSpritePos[static_cast<int>(m_MenuKey)] + Vec3(-(m_ResultSpriteDefultScale[static_cast<int>(m_MenuKey)].x + ptrTrans->GetScale().x) * 0.5f, 0.0f, 0.0f));
	}

	void ResultStage::ChangeStageSceneSelected() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		switch (m_MenuKey)
		{
		case ResultStageMenuKey::Select:
			ptrScene->ChangeScene(SceneKey::Select);
			break;
		case ResultStageMenuKey::Retry:
			ptrScene->ChangeScene(SceneKey::Game);
			break;
		case ResultStageMenuKey::Title:
			ptrScene->ChangeScene(SceneKey::Title);
			break;
		default:
			break;
		}
	}
}
//end basecross
