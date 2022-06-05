modded class ArmaReforgerScripted : ChimeraGame
{
	
	//private ref map<typename, Widget> m_test = new ref map<typename, Widget>;
	private bool EditUIMode = false;
	
	ref TUIElementMap tm = new TUIElementMap;
	
	override void OnWorldPostProcess(World world)
	{
		
		UISettings.LoadArray(tm);
	}
	

	//------------------------------------------------------------------------------------------------
	override bool OnGameStart()
	{
		return super.OnGameStart();
		
	}
};