#pragma once
#include "Observer.h"
#include <steam_api.h>

// Defining our achievements
#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
struct Achievement_t
{
	int m_eAchievementID;
	const char* m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};
// Defining our achievements
enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3,
};


namespace dae {
	class Achievements : public Observer, public Singleton<Achievements>
	{
	public:
		Achievements();
		virtual void onNotify(const BaseComponent* entity, EventType event);

		STEAM_CALLBACK(Achievements, OnUserStatsReceived, UserStatsReceived_t,
			m_CallbackUserStatsReceived);

		STEAM_CALLBACK(Achievements, OnUserStatsStored, UserStatsStored_t,
			m_CallbackUserStatsStored);

		STEAM_CALLBACK(Achievements, OnAchievementStored,
			UserAchievementStored_t, m_CallbackAchievementStored);

		Achievements(const Achievements & other) = delete;
		Achievements(Achievements && other) = delete;
		Achievements& operator=(const Achievements & other) = delete;
		Achievements& operator=(Achievements && other) = delete;
	private:
		bool RequestStats();
		bool SetAchievement(const char* ID);

	private:
		friend class Singleton<Achievements>;
		int m_iAppID; // Our current AppID
		bool m_IsInitialized = false;

		// Achievement array which will hold data about the achievements and their state
		Achievement_t m_Achievements[4]
		{
			_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
			_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
			_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
			_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
		};


	};

}
