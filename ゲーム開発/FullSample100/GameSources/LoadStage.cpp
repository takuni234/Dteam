/*!
@file LoadStage.cpp
@brief ���[�h�X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���[�h�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	bool LoadStage::m_Loaded = false;
	std::mutex LoadStage::mtx;

	//���\�[�X���[�h�p�̃X���b�h�i�X�^�e�B�b�N�֐��j
	void LoadStage::LoadResourceFunc() {
		mtx.lock();
		m_Loaded = false;
		mtx.unlock();

		wstring DataDir;
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = DataDir + L"water5.png";
		App::GetApp()->RegisterTexture(L"WATER_TX", strTexture);
		strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = DataDir + L"Fade.png";
		App::GetApp()->RegisterTexture(L"FADE_TX", strTexture);
		strTexture = DataDir + L"Pause.png";
		App::GetApp()->RegisterTexture(L"PAUSE_TX", strTexture);
		strTexture = DataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		strTexture = DataDir + L"number_color (1).png";
		App::GetApp()->RegisterTexture(L"NUMBERCOLOR_TX", strTexture);
		strTexture = DataDir + L"Ground.png";
		App::GetApp()->RegisterTexture(L"GROUND_TX", strTexture);
		strTexture = DataDir + L"Ground2.png";
		App::GetApp()->RegisterTexture(L"GROUND2_TX", strTexture);
		strTexture = DataDir + L"Survivor_UI.png";
		App::GetApp()->RegisterTexture(L"SURVIVOR_UI_TX", strTexture);
		strTexture = DataDir + L"spark.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX", strTexture);
		strTexture = DataDir + L"fire.png";
		App::GetApp()->RegisterTexture(L"FIRE_TX", strTexture);
		strTexture = DataDir + L"PushBButton.png";
		App::GetApp()->RegisterTexture(L"MESSAGE_TX", strTexture);
		strTexture = DataDir + L"�^�C�g�����S_7.png";
		App::GetApp()->RegisterTexture(L"TITLELOGO_TX", strTexture);
		strTexture = DataDir + L"gameover2.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);
		strTexture = DataDir + L"gameclear.png";
		App::GetApp()->RegisterTexture(L"GAMECREAR_TX", strTexture);
		strTexture = DataDir + L"title.png";
		App::GetApp()->RegisterTexture(L"TOTITLE_TX", strTexture);
		strTexture = DataDir + L"stage.png";
		App::GetApp()->RegisterTexture(L"STAGE_TX", strTexture);
		strTexture = DataDir + L"select.png";
		App::GetApp()->RegisterTexture(L"TOSTAGESELECT_TX", strTexture);
		strTexture = DataDir + L"retry.png";
		App::GetApp()->RegisterTexture(L"TORETRY_TX", strTexture);
		strTexture = DataDir + L"nextstage.png";
		App::GetApp()->RegisterTexture(L"TONEXTSTAGE_TX", strTexture);
		strTexture = DataDir + L"help.png";
		App::GetApp()->RegisterTexture(L"HELPTEXT_TX", strTexture);
		strTexture = DataDir + L"Tx_survivor.png";
		App::GetApp()->RegisterTexture(L"SURVIVOR_TX", strTexture);
		strTexture = DataDir + L"Tx_rescuecharacter2.png";
		App::GetApp()->RegisterTexture(L"RESCUECHARACTER_TX", strTexture);
		strTexture = DataDir + L"Tx_rock.png";
		App::GetApp()->RegisterTexture(L"ROCK_TX", strTexture);
		strTexture = DataDir + L"Tx_rock2.png";
		App::GetApp()->RegisterTexture(L"HOTROCK_TX", strTexture);
		strTexture = DataDir + L"Tx_tree.png";
		App::GetApp()->RegisterTexture(L"TREE_TX", strTexture);
		strTexture = DataDir + L"Tx_Ambulance3.png";
		App::GetApp()->RegisterTexture(L"GOAL_TX", strTexture);
		strTexture = DataDir + L"rightmark.png";
		App::GetApp()->RegisterTexture(L"RIGHTARROWCURSOL_TX", strTexture);
		strTexture = DataDir + L"leftmark.png";
		App::GetApp()->RegisterTexture(L"LEFTARROWCURSOL_TX", strTexture);
		strTexture = DataDir + L"choice_rightmark.png";
		App::GetApp()->RegisterTexture(L"CHOICE_RIGHTARROWCURSOL_TX", strTexture);
		strTexture = DataDir + L"resultbackground.png";
		App::GetApp()->RegisterTexture(L"TITLE_BACKGROUND_TX", strTexture);
		strTexture = DataDir + L"resultbackground.png";
		App::GetApp()->RegisterTexture(L"STAGESELECT_BACKGROUND_TX", strTexture);
		strTexture = DataDir + L"resultbackground.png";
		App::GetApp()->RegisterTexture(L"RESULT_BACKGROUND_TX", strTexture);
		strTexture = DataDir + L"resultbackground.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_BACKGROUND_TX", strTexture);
		strTexture = DataDir + L"score.png";
		App::GetApp()->RegisterTexture(L"SCORE_TX", strTexture);
		strTexture = DataDir + L"slash.png";
		App::GetApp()->RegisterTexture(L"SLASH_TX", strTexture);
		strTexture = DataDir + L"resultframe1.png";
		App::GetApp()->RegisterTexture(L"RESULT_FRAME1_TX", strTexture);
		strTexture = DataDir + L"resultframe2.png";
		App::GetApp()->RegisterTexture(L"RESULT_FRAME2_TX", strTexture);
		strTexture = DataDir + L"��X�L���[ 2020_06_10 14_26_17a.png";
		App::GetApp()->RegisterTexture(L"Stage1_TX", strTexture);
		strTexture = DataDir + L"��X�L���[ 2020_06_10 14_55_17a.png";
		App::GetApp()->RegisterTexture(L"Stage2_TX", strTexture);
		strTexture = DataDir + L"��X�L���[ 2020_06_10 15_00_41a.png";
		App::GetApp()->RegisterTexture(L"Stage3_TX", strTexture);
		strTexture = DataDir + L"Stage4.png";
		App::GetApp()->RegisterTexture(L"Stage4_TX", strTexture);
		strTexture = DataDir + L"HPgauge1.png";
		App::GetApp()->RegisterTexture(L"HPGAUGE1_TX", strTexture);
		strTexture = DataDir + L"HPgauge2.png";
		App::GetApp()->RegisterTexture(L"HPGAUGE2_TX", strTexture);
		strTexture = DataDir + L"volcanicash2.png";
		App::GetApp()->RegisterTexture(L"SMOKE_TX", strTexture);
		strTexture = DataDir + L"copyright.png";
		App::GetApp()->RegisterTexture(L"COPYRIGHT_TX", strTexture);
		
		auto modelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Survivor7.bmf");
		App::GetApp()->RegisterResource(L"SURVIVOR_1", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Survivor8.bmf");
		App::GetApp()->RegisterResource(L"SURVIVOR_2", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Rescuecharacter8.bmf");
		App::GetApp()->RegisterResource(L"RESCUECHARACTER_MESH", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"RescuecharacterGun.bmf");
		App::GetApp()->RegisterResource(L"RESCUECHARACTERGUN_MESH", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"RescuecharacterIceax.bmf");
		App::GetApp()->RegisterResource(L"RESCUECHARACTERICEAX_MESH", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Rock6.bmf");
		App::GetApp()->RegisterResource(L"HOTROCK_MESH", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Tree4.bmf");
		App::GetApp()->RegisterResource(L"TREE_MESH", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"ambulance5.bmf");
		App::GetApp()->RegisterResource(L"GOAL_MESH", modelMesh);

		//�T�E���h
		wstring strFolder = L"���f��/";
		wstring DataDirFolder = DataDir + strFolder;
		wstring DataWav = DataDirFolder + L"cursor.wav";
		App::GetApp()->RegisterWav(L"CURSOR_WAV", DataWav);
		DataWav = DataDirFolder + L"decision.wav";
		App::GetApp()->RegisterWav(L"DECISION_WAV", DataWav);
		DataWav = DataDirFolder + L"air_shot.wav";
		App::GetApp()->RegisterWav(L"ICEAX_ATTACK_WAV", DataWav);
		DataWav = DataDirFolder + L"Lava.wav";
		App::GetApp()->RegisterWav(L"ERUPTION_WAV", DataWav);
		DataWav = DataDirFolder + L"�΂��ӂ���.wav";
		App::GetApp()->RegisterWav(L"ROCK_DESTORY_WAV", DataWav);
		DataWav = DataDirFolder + L"left_foot.wav";
		App::GetApp()->RegisterWav(L"WALK_LEFT_WAV", DataWav);
		DataWav = DataDirFolder + L"right_foot.wav";
		App::GetApp()->RegisterWav(L"WALK_RIGHT_WAV", DataWav);
		DataWav = DataDirFolder + L"Water3.wav";
		App::GetApp()->RegisterWav(L"WATER_WAV", DataWav);
		DataWav = DataDirFolder + L"burn.wav";
		App::GetApp()->RegisterWav(L"BURN_WAV", DataWav);
		DataWav = DataDirFolder + L"hose2.wav";
		App::GetApp()->RegisterWav(L"HOSE_WAV", DataWav);
		//BGM
		wstring strMusic = DataDirFolder + L"nanika .wav";
		App::GetApp()->RegisterWav(L"Nanika", strMusic);
		strMusic = DataDirFolder + L"Reiscue.wav";
		App::GetApp()->RegisterWav(L"REISCUE_BGM", strMusic);
		mtx.lock();
		m_Loaded = true;
		mtx.unlock();

	}

	void LoadStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

	}

	//�X�v���C�g�̍쐬
	void LoadStage::CreateTitleSprite() {
		AddGameObject<Sprite>(L"WAIT_TX", Vec2(200.0f, 100.0f), Vec3(400.0f,-350.0f,0.0f));
		AddGameObject<SerialAnimeSprite>(L"LOADTEST_TX", true,
			Vec2(256.0f, 256.0f), Vec2(400.0f, -150.0f), 4, 1, 0.1f);
	}

	//������
	void LoadStage::OnCreate() {
		wstring DataDir;
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		App::GetApp()->GetDataDirectory(DataDir);
		//���҂����������̃e�N�X�`���݂̂����œo�^
		wstring strTexture = DataDir + L"wait.png";
		App::GetApp()->RegisterTexture(L"WAIT_TX", strTexture);
		strTexture = DataDir + L"movetest.png";
		App::GetApp()->RegisterTexture(L"MOVETEST_TX", strTexture);
		strTexture = DataDir + L"�^���N.png";
		App::GetApp()->RegisterTexture(L"LOADTEST_TX", strTexture);
		strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		//���̃��\�[�X��ǂݍ��ރX���b�h�̃X�^�[�g
		std::thread LoadThread(LoadResourceFunc);
		//�I���܂ł͑҂��Ȃ�
		LoadThread.detach();

		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateTitleSprite();
	}

	//�X�V
	void LoadStage::OnUpdate() {
		if (m_Loaded) {
			//���\�[�X�̃��[�h���I��������^�C�g���X�e�[�W�Ɉڍs
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::CopyrightInfo);
		}
	}


}
//end basecross
