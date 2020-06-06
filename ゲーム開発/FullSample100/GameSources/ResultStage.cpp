/*!
@file ResultStage.cpp
@brief ���U���g�X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void ResultStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	//�_�ł���X�v���C�g�쐬
	void ResultStage::CreatePushSprite() {
		//�X�R�A
		auto ptrScore = AddGameObject<ScoreSprite>(1,
			L"NUMBER_TX",
			true,
			Vec2(70.0f, 140.0f),
			Vec3(120.0f, 200.0f, 0.0f));
		ptrScore->SetScore(static_cast<float>(m_SelectNum));
		SetSharedGameObject(L"ResultScoreSprite", ptrScore);
		//�X�e�[�W���Ŏ擾�\�ȍő�X�R�A
		auto ptrMaxScore = AddGameObject<ScoreSprite>(1,
			L"NUMBER_TX",
			true,
			Vec2(70.0f, 140.0f),
			Vec3(300.0f, 200.0f, 0.0f));
		ptrMaxScore->SetScore(static_cast<float>(m_SelectNum));
		SetSharedGameObject(L"MaxResultScoreSprite", ptrMaxScore);
		//�X�e�[�W�̔w�i
		auto ptrSprite = AddGameObject<Sprite>(L"RESULT_BACKGROUND_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f));
		ptrSprite->SetDrawLayer(-3);
		//UI �t���[��
		ptrSprite = AddGameObject<Sprite>(L"RESULT_FRAME1_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f));
		ptrSprite->SetDrawLayer(-2);
		//UI �t���[��
		ptrSprite = AddGameObject<Sprite>(L"RESULT_FRAME2_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f, 200.0f,0.0));
		ptrSprite->SetDrawLayer(-1);
		//�u�������l���v
		ptrSprite = AddGameObject<Sprite>(L"SCORE_TX", Vec2(600.0f, 200.0f), Vec3(-200.0f, 200.0f,0.0));
		ptrSprite->SetDrawLayer(0);
		//�u/�v
		ptrSprite = AddGameObject<Sprite>(L"SLASH_TX", Vec2(840.0f, 280.0f), Vec3(210.0f, 200.0f,0.0));
		ptrSprite->SetDrawLayer(0);
	}

	void ResultStage::CreateSprite() {
		CreateSharedObjectGroup(L"ResultSprite");
		//�z�u����ʒu�i�S�́j
		Vec3 DefultPos(0.0f,0.0f,0.0f);
		for (int i = 0; i < static_cast<int>(ResultStageMenuKey::Max); i++) {
			Vec2 createScale(450.0f, 150.0f);
			Vec3 createPos(Vec3(0.0f, -i * 100.0f, 0.0f) + DefultPos);
			wstring txKey;
			switch (static_cast<ResultStageMenuKey>(i))
			{
				//�u���̃X�e�[�W�ցv�̉摜
			case ResultStageMenuKey::NextStage:
				txKey = L"TONEXTSTAGE_TX";
				break;
				// �u�X�e�[�W�Z���N�g�ցv�̉摜
			case ResultStageMenuKey::Select:
				txKey = L"TOSTAGESELECT_TX";
				break;
				// �u���g���C�v�̉摜
			case ResultStageMenuKey::Retry:
				txKey = L"TORETRY_TX";
				break;
				// �u�^�C�g���ցv�̉摜
			case ResultStageMenuKey::Title:
				txKey = L"TOTITLE_TX";
				break;
			default:
				//�G���[
				txKey = L"SKY_TX";
				createScale = Vec2(100.0f);
				break;
			}
			auto ptrSprite = AddGameObject<Sprite>(txKey, createScale, createPos);
			m_ResultSpriteDefultScale.push_back(ptrSprite->GetComponent<Transform>()->GetScale());
			m_ResultSpritePos.push_back(createPos);
			GetSharedObjectGroup(L"ResultSprite")->IntoGroup(ptrSprite);
		}

		auto ptrCursol = AddGameObject<Sprite>(L"LEFTARROWCURSOL_TX", Vec2(50.0f));
		ptrCursol->SetPosition(DefultPos + Vec3(-(m_ResultSpriteDefultScale[static_cast<int>(ResultStageMenuKey::Select)].x + ptrCursol->GetScale().x) * 0.5f, 0.0f,0.0f));
		SetSharedGameObject(L"ResultCursor", ptrCursol);
	}

	void ResultStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreatePushSprite();
			CreateSprite();
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"REISCUE_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
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
		//BGM�̃X�g�b�v
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
		else if (!(KeyState.m_bPressedKeyTbl['W'] && KeyState.m_bPressedKeyTbl['S'])) {
			if (KeyState.m_bPressedKeyTbl['S']) {
				m_SelectNum++;
			}
			if (KeyState.m_bPressedKeyTbl['W']) {
				m_SelectNum--;
			}
		}

		if (m_SelectNum <= 0) {
			m_SelectNum = static_cast<int>(ResultStageMenuKey::Max);
		}
		m_MenuKey = ResultStageMenuKey(m_SelectNum % static_cast<int>(ResultStageMenuKey::Max));
	}

	void ResultStage::UpdateCursor() {
		GetSharedGameObject<ScoreSprite>(L"ResultScoreSprite")->SetScore(static_cast<float>(m_MenuKey));
		GetSharedGameObject<ScoreSprite>(L"MaxResultScoreSprite")->SetScore(static_cast<float>(m_MenuKey));
		auto ptrCursor = GetSharedGameObject<Sprite>(L"ResultCursor");
		auto ptrTrans = ptrCursor->GetComponent<Transform>();
		ptrTrans->SetPosition(m_ResultSpritePos[static_cast<int>(m_MenuKey)] + Vec3((m_ResultSpriteDefultScale[static_cast<int>(m_MenuKey)].x + ptrTrans->GetScale().x) * 0.5f, 0.0f, 0.0f));
	}

	void ResultStage::ChangeStageSceneSelected() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		switch (m_MenuKey)
		{
		case ResultStageMenuKey::NextStage:
			ptrScene->ChangeScene(SceneKey::Game);
			break;
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
