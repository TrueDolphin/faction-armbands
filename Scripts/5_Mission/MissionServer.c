//name:TrueDolphin
//date:8/8/2024
//Faction changes with armbands on respawn/load-in
//testing, contains ingame message function.

modded class MissionServer {

  private const static string ProfilesFolder = "$profile:ExpansionMod\\AI\\Armbands\\"; // path
  private const static string ArmBand_Settings = ProfilesFolder + "ArmbandSettings.json"; // config json
  string ArmbandFaction; // West, East, Shamans etc
  string ArmbandColour; // Armband classname
  string ArmbandPlayer;
  ref ArmbandGroups m_ArmbandGroups;	// Group identity
  void MissionServer() {
    int timer = 10000;
    //! que call
    Print("Factions Based on Armbands Enabled");
    loadArmbandGroups();
    Print("Default faction Set to " + m_ArmbandGroups.Default_Faction);
    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.OnlinePlayerCheck, timer, true);
  }

  void OnlinePlayerCheck() {
    array < Man > players = new array < Man > ;
    GetGame().GetPlayers(players); 
    for (int i = 0; i < players.Count(); i++) //! because we love loops
    {
      PlayerBase player = PlayerBase.Cast(players[i]);
      if (!player)
      return;
      if (!player.GetIdentity())
      return;

      FactionArmbandCheck(player);
    }
  }

protected void FactionArmbandCheck(PlayerBase player) {
    eAIGroup playerGroup = player.GetGroup();
    if (!playerGroup)
      playerGroup = eAIGroup.GetGroupByLeader(player);
    eAIFaction faction = playerGroup.GetFaction();
    Armband_ColorBase currentArmband = Armband_ColorBase.Cast(player.FindAttachmentBySlotName("Armband"));
    if (!currentArmband) { 
      if (faction.GetName() == m_ArmbandGroups.Default_Faction)
        return;
      playerGroup.SetFaction(eAIFaction.Create(m_ArmbandGroups.Default_Faction));
      if (m_ArmbandGroups.Faction_Change == 1) sendPlayerArmbandMessage(player, "Faction Set to " + m_ArmbandGroups.Default_Faction);
      #ifdef EXPANSIONTRACE
      Print("Armband Removed"); //! script log message to host
      Print(player.GetIdentity().GetName() + " has been assigned to faction: " + m_ArmbandGroups.Default_Faction);
      #endif
      return;
    }
    string armband = currentArmband.GetType();
    if (armband) //!check what one is equipped
    {
      InitArmbandCheck(armband, player, faction, playerGroup);
    }
  }

  //Ingame message to player arg
  protected void sendPlayerArmbandMessage(PlayerBase player, string message) {
    if ((player) && (message != "")) {
      Param1 < string > Msgparam;
      Msgparam = new Param1 < string > (message);
      GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, player.GetIdentity());
    }
  }

  void LoggerPrint(string msg) {
    if (GetExpansionSettings().GetLog().AIGeneral)
      GetExpansionSettings().GetLog().PrintLog("[Armbands] " + msg);
  }

  void loadArmbandGroups() {
    if (!FileExist(ArmBand_Settings)) {
      if (!FileExist(ProfilesFolder))
        MakeDirectory(ProfilesFolder);

      LoggerPrint("WARNING: Couldn't find config file !");
      LoggerPrint("Config will be located in: " + ProfilesFolder);
      DefaultArmbandSettings(m_ArmbandGroups);
      JsonFileLoader < ArmbandGroups > .JsonSaveFile(ArmBand_Settings, m_ArmbandGroups);
    } else {
      m_ArmbandGroups = new ArmbandGroups();
      JsonFileLoader < ArmbandGroups > .JsonLoadFile(ArmBand_Settings, m_ArmbandGroups);
      LoggerPrint("Loading config (" + ArmBand_Settings + ")");
    }

   if (m_ArmbandGroups.Version != 3) {
      m_ArmbandGroups.Default_Faction = "Player";
      m_ArmbandGroups.Version = 3;
      JsonFileLoader < ArmbandGroups > .JsonSaveFile(ArmBand_Settings, m_ArmbandGroups);
   }
    if (m_ArmbandGroups.Faction_Change != 1 && m_ArmbandGroups.Faction_Change != 0){
      LoggerPrint("Faction_change value incorrect. setting default off.");
      m_ArmbandGroups.Faction_Change = 0;
    }



  foreach(ArmbandGroup group: m_ArmbandGroups.Group)
    {
      if (group.ArmbandFaction) {
            eAIFaction c = eAIFaction.Create(group.ArmbandFaction);
            if (!c) {
              LoggerPrint("Invalid Data -" + group.ArmbandFaction);
              continue;
            }
        if (group.ArmbandColour) {

          LoggerPrint("Linking :" + group.ArmbandFaction + " TO: " + group.ArmbandColour);
          /*
            if (group.ArmbandFaction == "Player")
               ArmbandPlayer = group.ArmbandColour;
          */
        }
         else {
          LoggerPrint("Invalid Data -" + group.ArmbandColour);
          continue;
        }
      }
       else {
              LoggerPrint("Invalid Data -" + group.ArmbandFaction);
              continue;
            }
    /*
    if (!ArmbandPlayer) {
    LoggerPrint("Faction Player Must be set.");
    LoggerPrint("Stopping Player Checks.");
    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(OnlinePlayerCheck);
    */
    }
      LoggerPrint("Loaded config (" + ArmBand_Settings + ")");
  }
  

  void InitArmbandCheck(string armband, PlayerBase player, eAIFaction faction, eAIGroup playerGroup)
  {
    foreach(ArmbandGroup group: m_ArmbandGroups.Group) {
      if (group.ArmbandFaction) {
        if (group.ArmbandColour) {
          if (armband == group.ArmbandColour) {
            faction = playerGroup.GetFaction();
            string a = faction.GetName();
            string b = group.ArmbandFaction;

            if (a == b) return;
            eAIFaction c = eAIFaction.Create(b);
            if (!c) {
              LoggerPrint("Faction name wrong = " + b);
              continue;
            }
            playerGroup.SetFaction(c);
            faction = playerGroup.GetFaction();
            if (m_ArmbandGroups.Faction_Change == 1) sendPlayerArmbandMessage(player, "Faction Set to " + faction.GetName()); //! Ingame message to player
            #ifdef EXPANSIONTRACE
            Print("Armband Detected"); //! script log message to host
            Print(player.GetIdentity().GetName() + " has been assigned to faction: " + faction.GetName());
            #endif
            break;
          }
        }
         else {
          #ifdef EXPANSIONTRACE
          LoggerPrint("No armband set, skipping section");
          #endif
          continue;
        }
      }
       else {
        #ifdef EXPANSIONTRACE
        LoggerPrint("No faction set, skipping section");
        continue;
        #endif
      }
    }
  }


  void DefaultArmbandSettings(out ArmbandGroups Data) {
    Data = new ArmbandGroups();
    Data.Group.Insert(new ArmbandGroup("Shamans", "Armband_Black"));
    Data.Group.Insert(new ArmbandGroup("West", "Armband_Blue"));
    Data.Group.Insert(new ArmbandGroup("East", "Armband_Green"));
    Data.Group.Insert(new ArmbandGroup("Raiders", "Armband_Orange"));
    Data.Group.Insert(new ArmbandGroup("Civilian", "Armband_Pink"));
    Data.Group.Insert(new ArmbandGroup("Mercenaries", "Armband_Red"));
    Data.Group.Insert(new ArmbandGroup("Passive", "Armband_White"));
    Data.Group.Insert(new ArmbandGroup("Guards", "Armband_Yellow"));
  }
}

class ArmbandGroup{
  string ArmbandFaction; // faction.GetName()
  string ArmbandColour; // Armband.GetType()
  
  void ArmbandGroup(string fac, string col) {
    ArmbandFaction = fac;
    ArmbandColour = col;
}
}

class ArmbandGroups {
  int Version = 3; // default version
  int Faction_Change = 0;
  string Default_Faction = "Player";
  ref array < ref ArmbandGroup > Group;
  void ArmbandGroups() {
    Group = new array < ref ArmbandGroup > ;
  }

};