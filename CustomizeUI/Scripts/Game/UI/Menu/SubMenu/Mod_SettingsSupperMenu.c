//------------------------------------------------------------------------------------------------
modded class SCR_SettingsSuperMenu : SCR_SuperMenuBase
{
	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
		SCR_TabViewComponent TabViewComponent = SCR_TabViewComponent.Cast(GetRootWidget().FindAnyWidget("TabViewRoot0").FindHandler(SCR_TabViewComponent));
		
		//void AddTab(ResourceName layout, string content, bool enabled = true, ResourceName tabImage = string.Empty, ResourceName iconLayout = string.Empty, float width = 32, float height = 32)

		TabViewComponent.AddTab("{7A98E57664F2E836}UI/layouts/Menus/SettingsMenu/InterfaceSettings.layout","Interface",);
		Print("test");
		
		super.OnMenuOpen();
	}
};