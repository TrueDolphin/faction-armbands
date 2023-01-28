#define _ARMA_

class CfgPatches
{
	class DayZ_Expansion_AI_Armbands_scripts
	{
		requiredAddons[] = {"DayZExpansion_AI_Scripts"};
	};
};
class CfgMods
{
	class DayZ_Expansion_AI_Armbands
	{
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "AI Additional Scripts";
		credits = "DayZ Expansion and dolphin";
		author = "Dolphin";
		authorID = "";
		version = "0.1";
		extra = 0;
		type = "servermod";
		dependencies[] = {"Game","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"dolphin/DayZ-Expansion-AI-Armbands/Scripts/3_Game"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"dolphin/DayZ-Expansion-AI-Armbands/Scripts/5_Mission"};
			};
		};
	};
};
