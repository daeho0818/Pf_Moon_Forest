#pragma once
#include "Enemy1_1.h"
#include "Enemy1_2.h"
#include "Enemy1_3.h"
#include "Enemy1_4.h"
#include "Boss1_1.h"
class Scene_Stage1 : public Scene
{
public:
	Scene_Stage1();
	~Scene_Stage1();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	void WavePattern1(float current_coolTime, bool is_end);
	void WavePattern2(float current_coolTime, bool is_end);
	void WavePattern3(float current_coolTime, bool is_end);
	void WavePattern4(float current_coolTime, bool is_end);
	void WavePattern5(float current_coolTime, bool is_end);

	void SetAllWavePatterns();

	// index 0 : player, 1 : boss
	void DestroyAnimation(int index);

	// helpers
	PatternHelper* pattern_helper = nullptr;
	ScrollHelper* scroll_helper = nullptr;

	// objects
	Object* m_playerObject = nullptr;
	Player* m_player = nullptr;

	Object* m_bossObject = nullptr;
	Boss1_1* m_boss = null;

	// field of stage patterns
	Timer* t_enemy1_spawn = nullptr;
	int enemy1_position_x;

	bool pattern2;
	Vector2 enemy2_position[2];

	Timer* t_enemy3_spawn = nullptr;
	Vector2 enemy3_spawn_positions[3];
	int enemy3_spawn_count = 0;

	bool pattern5;

	// boss help
	char boss_appear_str[256] = "";
	int boss_appear_count;
	Timer* boss_appear_timer = nullptr;

	Timer* player_destroy_animation = nullptr;
	int player_destroy_loop_count;

	Timer* boss_destroy_animation = nullptr;
	int boss_destroy_loop_count;

	// 스테이지 텍스트 애니메이션
	string stage_text;
	string complete_stage_text = "스테이지 1";
	int text_index = 0;
	Timer* stage_text_animation = nullptr;

	// Player Hp
	Image* player_hp_bg;
	Image* player_hp_bar;

};
