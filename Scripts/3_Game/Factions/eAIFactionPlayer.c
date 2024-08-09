[eAIRegisterFaction(eAIFactionPlayer)]
class eAIFactionPlayer : eAIFaction
{
	void eAIFactionPlayer()
	{
		m_Name = "Player";
		m_Loadout = "HumanLoadout";
	}

	override bool IsFriendly(notnull eAIFaction other)
	{
		if (other.IsInherited(eAIFactionPlayer)) return true;
		if (other.IsInherited(eAIFactionCivilian)) return true;
		return false;
	}
};
