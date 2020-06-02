/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 10.0f, -5.0f);
		const Vec3 at(0.0f);
		//OpeningCameraView�p�̃r���[
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		//MyCamera�p�̃r���[
		m_PlayerCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<PlayerCamera>();
		ptrMyCamera->SetEye(eye);
		ptrMyCamera->SetAt(at);
		m_PlayerCameraView->SetCamera(ptrMyCamera);
		//������Ԃł�m_OpeningCameraView���g��
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect::openingCamera;
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetMyLighting();
	}

	//�X�R�A�X�v���C�g�쐬
	void GameStage::CreateScoreSprite() {
		auto ptrScore = AddGameObject<ScoreSprite>(3,
			L"NUMBER_TX",
			true,
			Vec2(250.0f, 100.0f),
			Vec3(0.0f, 300.0f, 0.0f));
		ptrScore->SetScore(m_TotalTime);
	}

	void GameStage::CreateHPSprite() {
		auto ptrHP = AddGameObject<Sprite>(L"SKY_TX");
		SetSharedGameObject(L"PlayerHPSprite", ptrHP);
	}

	void GameStage::CreateObjectB_CSV() {
		auto group = CreateSharedObjectGroup(L"RescurTargetGroup");
		//CSV�̍s�P�ʂ̔z��
		vector<wstring> LineVec;
		//0�Ԗڂ̃J������L"TilingFixedBox"�ł���s�𔲂��o��
		ObjCsvfile.GetSelect(LineVec, 0, L"Tx_Box(Clone)");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');

			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);
			Vec3 Scale(
				(float)_wtof(torkns[4].c_str()),
				(float)_wtof(torkns[5].c_str()),
				(float)_wtof(torkns[6].c_str())
			);
			Vec3 Rot;
			//��]��XM_PIDIV2�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (torkns[7] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[7].c_str());
			Rot.y = (torkns[8] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[8].c_str());
			Rot.z = (torkns[9] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[9].c_str());

			Vec3 Rot2(Rot.x - 45 / 3.1415f, Rot.y / 3.1415f, Rot.z - 90 / 3.1415f);
			AddGameObject<Rock>(Vec3(Pos.x, Pos.y - 0.5f, Pos.z), Scale, Rot);
		}

		ObjCsvfile.GetSelect(LineVec, 0, L"Cube");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');

			Vec3 col_Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);
			Vec3 col_Scale(
				(float)_wtof(torkns[4].c_str()),
				(float)_wtof(torkns[5].c_str()),
				(float)_wtof(torkns[6].c_str())
			);
			Vec3 col_Rot;
			//��]��XM_PIDIV2�̕�����ɂȂ��Ă���ꍇ������
			col_Rot.x = (torkns[7] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[7].c_str());
			col_Rot.y = (torkns[8] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[8].c_str());
			col_Rot.z = (torkns[9] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[9].c_str());

			//Vec3 Rot2(Rot.x - 45 / 3.1415f, Rot.y / 3.1415f, Rot.z - 90 / 3.1415f);
			AddGameObject<CollisionBox>(Vec3(col_Pos.x, col_Pos.y - 0.5f, col_Pos.z), col_Scale,  col_Rot); //-1 * (* 13.74f )
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"Wall");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');

			Vec3 col_Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);
			Vec3 col_Scale(
				(float)_wtof(torkns[4].c_str()),
				(float)_wtof(torkns[5].c_str()),
				(float)_wtof(torkns[6].c_str())
			);

			AddGameObject<TransparentBox>(
				Vec3(col_Scale), 
				Vec3(0.0f),
				Vec3(col_Pos));
		}

		ObjCsvfile.GetSelect(LineVec, 0, L"Player");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			PlayerPos.x = (float)_wtof(torkns[1].c_str());
			PlayerPos.y = (float)_wtof(torkns[2].c_str());
			PlayerPos.z = (float)_wtof(torkns[3].c_str());

		}

		ObjCsvfile.GetSelect(LineVec, 0, L"RescurTarget_1");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);

			group->IntoGroup(AddGameObject<RescurTarget_1>(Vec3(Pos), Vec3(0.25f), Vec3(0)));
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"RescurTarget_2");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);

			group->IntoGroup(AddGameObject<RescurTarget_2>(Vec3(Pos), Vec3(0.25f), Vec3(0)));
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"maguma");
		for (auto& v : LineVec) {
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);

			magumaPos = Pos;
			AddGameObject<IncreaseObject2>(Pos);
			//AddGameObject<Enemy>(Vec3(Pos), Vec3(0.25f), Vec3(0));
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"Obj_Rock");
		for (auto& v : LineVec) {
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);

			AddGameObject<ObjRock>(Pos, Vec3(1), Vec3(0), L"HOTROCK_TX", false);

			//AddGameObject<Enemy>(Vec3(Pos), Vec3(0.25f), Vec3(0));
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"Obj_Cinder");
		for (auto& v : LineVec) {
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);

			AddGameObject<Obj_Cinder>(Pos,Pos.x);

			//AddGameObject<Enemy>(Vec3(Pos), Vec3(0.25f), Vec3(0));
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"Goal");
		for (auto& v : LineVec) {
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()-1),
				(float)_wtof(torkns[3].c_str())
			);
			GoalPos = Pos;
			//AddGameObject<Enemy>(Vec3(Pos), Vec3(0.25f), Vec3(0));
		}
	}

	void GameStage::SetBackGroundColor(Col4 color) {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		ptrScene->SetClearColor(color);
	}

	void GameStage::SetBackGroundPlayerPosColor(Col4 posZeroCol, Col4 posMaxCol, float posSizeMax) {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrTrans = ptrPlayer->GetComponent<Transform>();
		auto playerPosCol = ptrTrans->GetPosition().y / posSizeMax;
		Col4 ZeroCol = posZeroCol - posZeroCol * playerPosCol;
		Col4 MaxCol = posMaxCol * playerPosCol;
		SetBackGroundColor(ZeroCol + MaxCol);
	}

	//�J�����}���̍쐬
	void GameStage::CreateCameraman() {
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraman>();
		//�V�F�A�z���OpeningCameraman��ǉ�
		SetSharedGameObject(L"OpeningCameraman", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect::openingCamera;
		}

	}

	void GameStage::OnCreate() {
		try {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			wstring detadir;
			App::GetApp()->GetDataDirectory(detadir);
			ObjCsvfile.SetFileName(detadir + ptrScene->GetStageCSVKey()); // �V�[���N���X�ɕۑ�����Ă���X�e�[�W��ǂݍ���
			//ObjCsvfile.SetFileName(detadir + L"TestStage2.csv");// SaveDataStage4.csv");// SaveData.csv");// GameStageA.csv");
			ObjCsvfile.ReadCsv();

			CreateObjectB_CSV();

			//SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			//auto ground = AddGameObject<FixedBox>(Vec3(100.0f, 1.0f, 100.0f), Vec3(0.0f), Vec3(0.0f, -0.5f, 0.0f));
			//ground->AddTag(L"Ground");
			//SetSharedGameObject(L"Stage", ground);

			auto goalObj = AddGameObject<GoalObject>(Vec3(1.0f), Vec3(0.0f, XM_PIDIV2, 0.0f), Vec3(GoalPos),2);
			SetSharedGameObject(L"Goal", goalObj);

			auto player = AddGameObject<Player>(Vec3(0.25f), Vec3(0.0f), PlayerPos);// Vec3(0.0f, 1.0f, 0.0f));
			SetSharedGameObject(L"Player", player);
			CreateHPSprite();
			//�J�����}���̍쐬
			CreateCameraman();

			//AddGameObject<Enemy>(Vec3(4, 2, -7), Vec3(0.25f), Vec3(0));
			//AddGameObject<RescurNomalTarget>(Vec3(3.7f, 5, 4.4f), Vec3(0.25f), Vec3(0));
			//AddGameObject<RescurTarget_1>(Vec3(-2,5 , -2), Vec3(0.25f), Vec3(0));
			//AddGameObject<IncreaseObject>(magumaPos);

			//AddGameObject<TransparentBox>(Vec3(10.0f, 80.0f, 10.0f), Vec3(0.0f), Vec3(0.0f, 0.0f, 0.0f));
			CreateScoreSprite();
			//BGM
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"ERUPTION_WAV", XAUDIO2_LOOP_INFINITE, 0.1f);
			CreateSharedObjectGroup(L"PlayerBullet");
		}
		catch (...) {
			throw;
		}
	}


	void GameStage::OnUpdate() {		
		auto goal = GetSharedGameObject<GoalObject>(L"Goal");

		SetBackGroundPlayerPosColor(m_Color, m_Color1, 2.24f);
		if (GetThis<GameStage>()->GetCameraSelect() == CameraSelect::openingCamera) {
			return;
		}
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime -= elapsedTime;
		if (m_TotalTime <= 0) {
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::GameOver);
		}
		//�X�R�A���X�V����
		if (goal->Getflg()==false) {
			auto ptrScor = GetSharedGameObject<ScoreSprite>(L"ScoreSprite");
			ptrScor->SetScore(m_TotalTime);
			GameEndFlg = true;
		}
		if(goal->Getflg()&&GameEndFlg){
			AddGameObject<GameEndSplite>(Vec3(-740,0,0), Vec3(0), Vec3(0));
			GameEndFlg = false;
		}
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A&&goal->Getflg()) {
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::Title);
		}

	}
	void GameStage::StageChange() {
		auto goal = GetSharedGameObject<GoalObject>(L"Goal");
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A&&goal->Getflg()) {
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::Title);
		}

	}

	void GameStage::UpdateStage() {
		auto goal = GetSharedGameObject<GoalObject>(L"Goal");
		m_InputHandler.PushHandle(GetThis<GameStage>());
		if (m_IsUpdate) {
			Stage::UpdateStage();
		}
	}

	void GameStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void GameStage::ToPlayerCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCamera�ɕύX
		auto ptrMyCamera = dynamic_pointer_cast<PlayerCamera>(m_PlayerCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraView���g��
			SetView(m_PlayerCameraView);
			m_CameraSelect = CameraSelect::playerCamera;
		}
	}

	void GameStage::OnPushStart() {
		if (m_IsUpdate) {
			m_IsUpdate = false;
		}
		else {
			m_IsUpdate = true;
		}
	}

}
//end basecross
