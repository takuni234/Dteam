#pragma oncem 
#include "stdafx.h"
#include "Project.h"
#include<Random>


namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rot)
		:GameObject(stage), m_Position(pos), m_Scale(scale), m_Rotation(rot),
		InFlg(false), Speed(0.5f) {

	}
	void Enemy::OnCreate() {
		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_CUBE");

		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(m_Rotation);

		auto collision = AddComponent<CollisionObb>();

		auto gravity = AddComponent<Gravity>();

		changetime = Time() + 3.0f;
	}

	void Enemy::OnUpdate() {
		E_PLAYERCHACE();
		//Attack();
	}

	Vec3 Enemy::PlayerPos() {
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto plyTrans = player->GetComponent<Transform>();
		auto plyPos = plyTrans->GetPosition();
		return plyPos;
	}
	void Enemy::E_PLAYERCHACE() {

		auto plyPos = PlayerPos();
		auto Trans = GetComponent<Transform>();
		auto pos = Trans->GetPosition();
		m_Position = pos;
		Vec3 distance = pos - plyPos;
		float length = distance.length();
		if (length < 4) {
			plyPos = plyPos - pos;
		}
		else {

			Speed = 1.0f;
			changetime = Time() + 3.0f;
			//plyPos = Vec3(0);
			FREEMOVE();
		}

		m_Position += plyPos * App::GetApp()->GetElapsedTime()*Acceleration();
		Trans->SetPosition(m_Position);

		auto bhr = GetBehavior<UtilBehavior>();
		bhr->RotToHead(1.0f);

	}

	float Enemy::Acceleration() {
		if (Speed < MaxSpeed) {
			if (Time() > changetime) {
				Speed += 0.5f;
				changetime = Time()+3.0f;
			}
		}
		return Speed;
	}
	void Enemy::Attack() {
		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		auto plyPos = PlayerPos();
		Vec3 P_lengthPos = Pos - plyPos;
		float P_length = P_lengthPos.length();
		m_Position = Pos;
		if (P_length < 1) {
			m_Position += (plyPos-Pos) * App::GetApp()->GetElapsedTime() * 5;
			Trans->SetPosition(m_Position);
		}

		if (P_length < 0.4f) {
			m_Position -= (plyPos-Pos)*2 * App::GetApp()->GetElapsedTime() * 5;
			Trans->SetPosition(m_Position);
		}

	}
	void Enemy::FREEMOVE() {
		Vec3 movepos;

		auto stage = GetStage()->GetSharedGameObject<FixedBox>(L"Stage");
		auto stageScale = stage->GetComponent<Transform>()->GetScale();

		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		m_Position = Pos;


		if (posX > position.x || posZ > position.z) {
			RandomPos();
		}
		else if (posX < position.x || posZ < position.z) {
			RandomPos();
		}			
		movepos = Vec3(posX - Pos.x, 0, posZ - Pos.z);
		position = movepos;
		m_Position += movepos * App::GetApp()->GetElapsedTime() * 0.25f;
		Trans->SetPosition(m_Position);

		auto bhr = GetBehavior<UtilBehavior>();
		bhr->RotToHead(1.0f);
	}
	Vec3 Enemy::RandomPos() {
		mt19937 mx(static_cast<unsigned int> (time));
		mt19937 mz(static_cast<unsigned int> (time));
		uniform_int_distribution<int> randX(-5, 5);
		uniform_int_distribution<int> randZ(-5, 5);

		posX = randX(mx);
		posZ = randZ(mz);
		return Vec3(randX(mx), 0, randZ(mz));
	}
}