#include "MiniginPCH.h"
#include "Achievment.h"
dae::Achievements::Achievements(): 
	m_CallbackUserStatsReceived(this, &Achievements::OnUserStatsReceived),
	m_CallbackUserStatsStored(this, &Achievements::OnUserStatsStored),
	m_CallbackAchievementStored(this, &Achievements::OnAchievementStored)
{
	m_iAppID = SteamUtils()->GetAppID();
	m_IsInitialized = RequestStats();
}

void dae::Achievements::onNotify(const BaseComponent*, EventType event)
{
	switch (event)
	{
	case dae::EventType::WIN_GAME:
		SetAchievement("ACH_WIN_ONE_GAME");
		break;
	case dae::EventType::SCORE_INCREASE:
		break;
	default:
		break;
	}
}
void dae::Achievements::OnUserStatsReceived(UserStatsReceived_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == pCallback->m_nGameID)
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			OutputDebugString("Received stats and achievements from Steam\n");
			m_IsInitialized = true;

			// load achievements
			for (int iAch = 0; iAch < 4; ++iAch)
			{
				Achievement_t& ach = m_Achievements[iAch];

				SteamUserStats()->GetAchievement(ach.m_pchAchievementID, &ach.m_bAchieved);
				_snprintf(ach.m_rgchName, sizeof(ach.m_rgchName), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
						"name"));
				_snprintf(ach.m_rgchDescription, sizeof(ach.m_rgchDescription), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
						"desc"));
			}
		}
		else
		{
			char buffer[128];
			_snprintf(buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult);
			OutputDebugString(buffer);
		}
	}
}
void dae::Achievements::OnUserStatsStored(UserStatsStored_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == pCallback->m_nGameID)
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			OutputDebugString("Stored stats for Steam\n");
		}
		else
		{
			char buffer[128];
			_snprintf(buffer, 128, "StatsStored - failed, %d\n", pCallback->m_eResult);
			OutputDebugString(buffer);
		}
	}
}
void dae::Achievements::OnAchievementStored(UserAchievementStored_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == pCallback->m_nGameID)
	{
		OutputDebugString("Stored Achievement for Steam\n");
	}
}
bool dae::Achievements::RequestStats()
{
	// Is Steam loaded? If not we can't get stats.
	if (NULL == SteamUserStats() || NULL == SteamUser())
	{
		return false;
	}
	// Is the user logged on?  If not we can't get stats.
	if (!SteamUser()->BLoggedOn())
	{
		return false;
	}
	// Request user stats.
	return SteamUserStats()->RequestCurrentStats();
}

bool dae::Achievements::SetAchievement(const char* ID)
{
	// Have we received a call back from Steam yet?
	if (m_IsInitialized)
	{
		SteamUserStats()->SetAchievement(ID);
		return SteamUserStats()->StoreStats();
	}
	// If not then we can't set achievements yet
	return false;
}
