#define _ARMA_

class CfgPatches
{
	class DayZ_Expansion_AI_Armbands_scripts
	{
		requiredAddons[] = {"DZ_Scripts","DayZExpansion_AI_Scripts"};
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
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"DayZExpansion/AI/Scripts/Common","DayZExpansion/AI/Scripts/3_Game","dolphin/DayZ-Expansion-AI-Armbands/Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"DayZExpansion/AI/Scripts/Common","DayZExpansion/AI/Scripts/4_World","dolphin/DayZ-Expansion-AI-Armbands/World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"DayZExpansion/AI/Scripts/Common","DayZExpansion/AI/Scripts/5_Mission","dolphin/DayZ-Expansion-AI-Armbands/Mission"};
			};
		};
	};
};
