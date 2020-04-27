/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Player::Player(const shared_ptr<Stage>& stage, const Vec3& scale, const Vec3& rot, const Vec3& pos)
		:GameObject(stage),
		m_Scale(scale),
		m_Rotation(rot),
		m_Position(pos),
		m_Speed(2.0f),
		m_IntervalTime(0.0f)
	{}
 
	Player::~Player() {}

	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		else {
			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (KeyState.m_bPushKeyTbl['W']) {
				//前
				ret.y = 1.0f;
			}
			else if (KeyState.m_bPushKeyTbl['A']) {
				//左
				ret.x = -1.0f;
			}
			else if (KeyState.m_bPushKeyTbl['S']) {
				//後ろ
				ret.y = -1.0f;
			}
			else if (KeyState.m_bPushKeyTbl['D']) {
				//右
				ret.x = 1.0f;
			}
		}
		return ret;
	}

	void Player::DrawStrings() {
		//文字列表示
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring fpsStr(L"FPS: ");
		fpsStr += Util::UintToWStr(fps);
		fpsStr += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		fpsStr += Util::FloatToWStr(ElapsedTime);
		fpsStr += L"\n";

		auto transPtr = GetComponent<Transform>();

		auto pos = transPtr->GetPosition();
		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Y=" + Util::FloatToWStr(pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Z=" + Util::FloatToWStr(pos.z, 6, Util::FloatModify::Fixed) + L"\n";
		
		auto rot = transPtr->GetRotation();
		wstring rotationStr(L"Rotation:\t");
		rotationStr += L"X=" + Util::FloatToWStr(rot.x, 6, Util::FloatModify::Fixed) + L",\t";
		rotationStr += L"Y=" + Util::FloatToWStr(rot.y, 6, Util::FloatModify::Fixed) + L",\t";
		rotationStr += L"Z=" + Util::FloatToWStr(rot.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring gravStr(L"GravityVelocoty:\t");
		auto gravVelocity = GetComponent<Gravity>()->GetGravityVelocity();
		gravStr += L"X=" + Util::FloatToWStr(gravVelocity.x, 6, Util::FloatModify::Fixed) + L",\t";
		gravStr += L"Y=" + Util::FloatToWStr(gravVelocity.y, 6, Util::FloatModify::Fixed) + L",\t";
		gravStr += L"Z=" + Util::FloatToWStr(gravVelocity.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring updatePerStr(L"UpdatePerformance:\t");
		updatePerStr += Util::FloatToWStr(GetStage()->GetUpdatePerformanceTime());
		updatePerStr += L"\tmillisecond\n";

		wstring drawPerStr(L"DrawPerformance:\t");
		drawPerStr += Util::FloatToWStr(GetStage()->GetDrawPerformanceTime());
		drawPerStr += L"\tmillisecond\n";

		wstring collPerStr(L"CollisionPerform:\t");
		collPerStr += Util::FloatToWStr(GetStage()->GetCollisionPerformanceTime(), 5);
		collPerStr += L"\tmillisecond\n";

		wstring collMiscStr(L"ColMiscPerform:\t");
		collMiscStr += Util::FloatToWStr(GetStage()->GetCollisionManager()->GetMiscPerformanceTime(), 5);
		collMiscStr += L"\tmillisecond\n";

		wstring collTernCountStr(L"CollisionCountOfTern:\t");
		collTernCountStr += Util::UintToWStr(GetStage()->GetCollisionManager()->GetCollisionCountOfTern());
		collTernCountStr += L"\n";
		wstring str = fpsStr + positionStr + rotationStr + gravStr + updatePerStr + drawPerStr + collPerStr + collMiscStr
			+ collTernCountStr;

		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

	void Player::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		auto gravPtr = AddComponent<Gravity>();

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		auto ptrCol = AddComponent<CollisionCapsule>();

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
		);

		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"RESCUECHARACTER_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"RESCUECHARACTER_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetTextureResource(L"RESCUECHARACTER_TX");

		ptrDraw->AddAnimation(L"Default", 200, 30, false, 60.0f);
		ptrDraw->AddAnimation(L"Walk", 0, 30,true, 60.0f);
		ptrDraw->AddAnimation(L"Push", 40, 30, true, 60.0f);
		ptrDraw->AddAnimation(L"Pull", 80, 30, true, 60.0f);
		ptrDraw->AddAnimation(L"Shot", 120, 30, true, 60.0f);
		ptrDraw->AddAnimation(L"Break", 160, 30, true, 60.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//カメラを得る
		auto ptrCamera = dynamic_pointer_cast<PlayerCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCameraである
			//MyCameraに注目するオブジェクト（プレイヤー）の設定
			ptrCamera->SetTargetObject(GetThis<GameObject>());
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));
		}
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<Player>(GetThis<Player>()));
		//最初のステートをSeekFarStateに設定
		m_StateMachine->ChangeState(DefaultState::Instance());
	}

	void Player::OnUpdate() {
		m_StateMachine->Update();
	}

	void Player::OnUpdate2() {
		DrawStrings();
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {

	}

	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		//入力の取得
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0;	//動いた時のスピード
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//進行方向の向きを計算
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//進行方向向きからの角度を算出
			float frontAngle = atan2(front.z, front.x);
			//コントローラの向き計算
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			float cntlAngle = atan2(-moveX, moveZ);
			//トータルの角度を算出
			float totalAngle = frontAngle + cntlAngle;
			//角度からベクトルを作成
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//正規化する
			angle.normalize();
			//移動サイズを設定。
			angle *= moveSize;
			//Y軸は変化させない
			angle.y = 0;
		}
		return angle;
	}

	void Player::PlayerMove() {
		m_InputHandler.PushHandle(GetThis<Player>());
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);
	}

	void Player::PlayerShot() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();

		m_IntervalTime += elapsedTime;
		if (m_IntervalTime >= 0.05f) {
			auto transPtr = GetComponent<Transform>();
			Vec3 createPos = Vec3(transPtr->GetPosition() + transPtr->GetForword() * transPtr->GetScale().getX());
			GetStage()->AddGameObject<Bullet>(Vec3(0.1f, 0.1f, 0.1f), transPtr->GetRotation(), createPos, transPtr->GetForword(), 5.0f);
			m_IntervalTime = 0.0f;
		}
	}

	void Player::PlayerWalk() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
	}

	void Player::OnPushA() {

	}

	void Player::OnPushX() {
		this->GetStateMachine()->ChangeState(ShotState::Instance());
	}

	void Player::OnUpX() {
		this->GetStateMachine()->ChangeState(DefaultState::Instance());
	}

	void Player::OnPushY() {
		this->GetStateMachine()->ChangeState(AttackState::Instance());
	}

	void Player::OnUpY() {
		this->GetStateMachine()->ChangeState(DefaultState::Instance());
	}

	//--------------------------------------------------------------------------------------
	//	class DefaultState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	shared_ptr<DefaultState> DefaultState::Instance() {
		static shared_ptr<DefaultState> instance(new DefaultState);
		return instance;
	}
	void DefaultState::Enter(const shared_ptr<Player>& Obj) {
		auto ptrDraw = Obj->GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->ChangeCurrentAnimation(L"Default");
	}
	void DefaultState::Execute(const shared_ptr<Player>& Obj) {
		Obj->PlayerMove();
		if (Obj->GetMoveVector().length() != 0.0f) {
			Obj->GetStateMachine()->ChangeState(WalkState::Instance());
		}
	}

	void DefaultState::Exit(const shared_ptr<Player>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class WalkState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	shared_ptr<WalkState> WalkState::Instance() {
		static shared_ptr<WalkState> instance(new WalkState);
		return instance;
	}
	void WalkState::Enter(const shared_ptr<Player>& Obj) {
		auto ptrDraw = Obj->GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->ChangeCurrentAnimation(L"Walk");
	}
	void WalkState::Execute(const shared_ptr<Player>& Obj) {
		Obj->PlayerMove();
		Obj->PlayerWalk();
		if (Obj->GetMoveVector().length() == 0.0f) {
			Obj->GetStateMachine()->ChangeState(DefaultState::Instance());
		}
	}

	void WalkState::Exit(const shared_ptr<Player>& Obj) {
	}
	
	//--------------------------------------------------------------------------------------
	//	class ShotState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	shared_ptr<ShotState> ShotState::Instance() {
		static shared_ptr<ShotState> instance(new ShotState);
		return instance;
	}
	void ShotState::Enter(const shared_ptr<Player>& Obj) {
		auto ptrDraw = Obj->GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->ChangeCurrentAnimation(L"Shot");
	}
	void ShotState::Execute(const shared_ptr<Player>& Obj) {
		Obj->PlayerMove();
		Obj->PlayerShot();
	}

	void ShotState::Exit(const shared_ptr<Player>& Obj) {
	}
	
	//--------------------------------------------------------------------------------------
	//	class AttackState : public ObjState<Player>;
	//--------------------------------------------------------------------------------------
	shared_ptr<AttackState> AttackState::Instance() {
		static shared_ptr<AttackState> instance(new AttackState);
		return instance;
	}
	void AttackState::Enter(const shared_ptr<Player>& Obj) {
		auto ptrDraw = Obj->GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->ChangeCurrentAnimation(L"Break");
	}
	void AttackState::Execute(const shared_ptr<Player>& Obj) {
		Obj->PlayerMove();
	}

	void AttackState::Exit(const shared_ptr<Player>& Obj) {
	}
}
//end basecross

