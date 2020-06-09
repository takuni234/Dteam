/*!
@file StageSelect.cpp
@brief �X�e�[�W�Z���N�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g�N���X����
	//--------------------------------------------------------------------------------------
	void StageSelect::CreateViewLight() {
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

	void StageSelect::CreateSelectSprite() {
		//�u�X�e�[�W�v�̃e�L�X�g
		auto ptrStageTx = AddGameObject<Sprite>(L"STAGE_TX", Vec2(600.0f, 200.0f), Vec3(-70.0f,300.0f,0.0f));
		//�u0�`9�v
		auto ptrScore = AddGameObject<ScoreSprite>(1,
			L"NUMBERCOLOR_TX",
			true,
			Vec2(65.0f, 130.0f),
			Vec3(130.0f, 300.0f, 0.0f));
		ptrScore->SetScore(static_cast<int>(App::GetApp()->GetScene<Scene>()->GetCurrentSceneKey()));
		SetSharedGameObject(L"ScoreSprite", ptrScore);
		//�X�e�[�W�̃X�N���[���V���b�g
		auto ptrSprite = AddGameObject<Sprite>(L"Stage1_TX", Vec2(1280.0f, 800.0f) * 0.5f, Vec3(0.0f));
		SetSharedGameObject(L"StageTXSprite", ptrSprite);

		auto ptrBGSprite = AddGameObject<Sprite>(L"STAGESELECT_BACKGROUND_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f));
		ptrBGSprite->SetDrawLayer(-3);

		//Right�I���J�[�\��
		auto ptrRArrowCursol = AddGameObject<Sprite>(L"RIGHTARROWCURSOL_TX", m_ArrowCursorScale, Vec3(500.0f,0.0f,0.0f));
		SetSharedGameObject(L"RArrowCursorSprite", ptrRArrowCursol);
		//Left�I���J�[�\��
		auto ptrLArrowCursol = AddGameObject<Sprite>(L"RIGHTARROWCURSOL_TX", m_ArrowCursorScale, Vec3(0.0f,0.0f,XM_PI), Vec3(-500.0f,0.0f,0.0f));
		SetSharedGameObject(L"LArrowCursorSprite", ptrLArrowCursol);

		//�u�~�o�Ώہv
		ptrSprite = AddGameObject<Sprite>(L"SURVIVOR_UI_TX", Vec2(100.0f, 100.0f), Vec3(430.0f, 300.0f, 0.0));

		// �X�e�[�W���ɂ��鑍�l���̕\��
		ptrScore = AddGameObject<ScoreSprite>(1,
			L"NUMBER_TX",
			true,
			Vec2(65.0f, 130.0f),
			Vec3(530.0f, 300.0f, 0.0f));
		ptrScore->SetScore(0);
		SetSharedGameObject(L"StageMaxScoreSprite", ptrScore);
	}

	void StageSelect::OnCreate() {
		try {
			m_SelectKey = App::GetApp()->GetScene<Scene>()->GetCurrentSceneKey();
			m_SelectNum = static_cast<int>(m_SelectKey);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateSelectSprite();
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"REISCUE_BGM", XAUDIO2_LOOP_INFINITE, 0.07f);
		}
		catch (...) {
			throw;
		}
	}

	void StageSelect::OnUpdate() {
		//���͂���l��ύX
		StageSelectKeyInput();
		//�e�N�X�`�����X�V
		UpdateSpriteTX();
		//�V�[���J��
		ChangeStageSceneSelected();
	}

	void StageSelect::StageSelectKeyInput() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		int currentNum = m_SelectNum;
		auto elapsedTime = App::GetApp()->GetElapsedTime();

		if (CntlVec[0].bConnected) {
			if (!m_InputOnce) {
				if (CntlVec[0].fThumbLX >= 0.9f) {
					m_SelectNum++;
					m_InputOnce = true;
				}
				else if (CntlVec[0].fThumbLX <= -0.9f) {
					m_SelectNum--;
					m_InputOnce = true;
				}
			}
			else {
				m_InputTime += elapsedTime;
				if (m_InputTime > 0.3f) {
					m_InputOnce = false;
					m_InputTime = 0.0f;
				}
			}
			if (CntlVec[0].fThumbLX <= 0.05f && CntlVec[0].fThumbLX >= -0.05f) {
				m_InputOnce = false;
				m_InputTime = 0.0f;
			}
		}
		else if (!(KeyState.m_bPushKeyTbl['A'] && KeyState.m_bPushKeyTbl['D'])) {
			if (!m_InputOnce) {
				if (KeyState.m_bPushKeyTbl['D']) {
					m_SelectNum++;
					m_InputOnce = true;
				}
				if (KeyState.m_bPushKeyTbl['A']) {
					m_SelectNum--;
					m_InputOnce = true;
				}
			}
			else {
				m_InputTime += elapsedTime;
				if (m_InputTime > 0.3f) {
					m_InputOnce = false;
					m_InputTime = 0.0f;
				}
			}
			if (KeyState.m_bUpKeyTbl['A'] && KeyState.m_bUpKeyTbl['D']) {
				m_InputOnce = false;
				m_InputTime = 0.0f;
			}
		}
		//�I���L�[���ς������
		if (currentNum < m_SelectNum) {
			auto ptrSprite = GetSharedGameObject<Sprite>(L"RArrowCursorSprite");
			ptrSprite->SetScale(m_ArrowCursorScale * 0.8f);
			ptrSprite->SetTextureKey(L"CHOICE_RIGHTARROWCURSOL_TX");
			m_RCursorTime = 0.0f;
		}
		else if(m_RCursorTime >= 0.1f) {
			auto ptrSprite = GetSharedGameObject<Sprite>(L"RArrowCursorSprite");
			ptrSprite->SetScale(m_ArrowCursorScale);
			ptrSprite->SetTextureKey(L"RIGHTARROWCURSOL_TX");
		}
		else {
			m_RCursorTime += elapsedTime;
		}
		//�I���L�[���ς������
		if (currentNum > m_SelectNum) {
			auto ptrSprite = GetSharedGameObject<Sprite>(L"LArrowCursorSprite");
			ptrSprite->SetScale(m_ArrowCursorScale * 0.8f);
			ptrSprite->SetTextureKey(L"CHOICE_RIGHTARROWCURSOL_TX");
			m_LCursorTime = 0.0f;
		}
		else if(m_LCursorTime >= 0.1f) {
			auto ptrSprite = GetSharedGameObject<Sprite>(L"LArrowCursorSprite");
			ptrSprite->SetScale(m_ArrowCursorScale);
			ptrSprite->SetTextureKey(L"RIGHTARROWCURSOL_TX");
		}
		else {
			m_LCursorTime += elapsedTime;
		}

		if (m_SelectNum <= 0) {
			m_SelectNum = static_cast<int>(SelectKey::Max);
		}
		m_SelectKey = SelectKey(m_SelectNum % static_cast<int>(SelectKey::Max));
	}

	void StageSelect::OnDestroy() {
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void StageSelect::UpdateSpriteTX() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		ptrScene->SetCurrentSceneKey(m_SelectKey);
		switch (m_SelectKey)
		{
		case SelectKey::Stage1:
			GetSharedGameObject<Sprite>(L"StageTXSprite")->SetTextureKey(L"Stage1_TX");
			ptrScene->SetLimitTime(90.0f); // Stage1.csv�ł̐�������
			ptrScene->SetStageCSVKey(L"Stage1.csv");
			SetCSVKey();
			break;
		case SelectKey::Stage2:
			GetSharedGameObject<Sprite>(L"StageTXSprite")->SetTextureKey(L"Stage2_TX");
			ptrScene->SetLimitTime(120.0f);
			ptrScene->SetStageCSVKey(L"Stage2.csv");
			SetCSVKey();
			break;
		case SelectKey::Stage3:
			GetSharedGameObject<Sprite>(L"StageTXSprite")->SetTextureKey(L"Stage3_TX");
			ptrScene->SetLimitTime(200.0f);
			ptrScene->SetStageCSVKey(L"SaveData25.csv");
			SetCSVKey();
			break;
		default:
			break;
		}
		//�I������Ă���CSV�t�@�C����ǂݍ���
		m_CsvFile.ReadCsv();
		int RescurCount = GetObjCountInCSV(L"RescurTarget_1") + GetObjCountInCSV(L"RescurTarget_2");
		auto ptrScoreSprite = GetSharedGameObject<ScoreSprite>(L"StageMaxScoreSprite");
		ptrScoreSprite->SetScore(float(RescurCount));
		ptrScoreSprite = GetSharedGameObject<ScoreSprite>(L"ScoreSprite");
		ptrScoreSprite->SetScore(float(static_cast<int>(m_SelectKey) + 1.0f));
	}

	void StageSelect::ChangeStageSceneSelected() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		bool start = false;

		if (CntlVec[0].bConnected) {
			start = CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B;
		}
		else {
			start = KeyState.m_bPressedKeyTbl[VK_SPACE];
		}
		if (start) {
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::Game);
		}
	}

	void StageSelect::SetCSVKey() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		wstring detadir;
		App::GetApp()->GetDataDirectory(detadir);
		m_CsvFile.SetFileName(detadir + ptrScene->GetStageCSVKey()); // �V�[���N���X�ɕۑ�����Ă���X�e�[�W��ǂݍ���
	}

	int StageSelect::GetObjCountInCSV(const wstring& key) {
		int count = 0;
		vector<wstring> LineVec;
		m_CsvFile.GetSelect(LineVec, 0, key);
		for (auto& v : LineVec) {
			count++;
		}
		return count;
	}
}
//end basecross
