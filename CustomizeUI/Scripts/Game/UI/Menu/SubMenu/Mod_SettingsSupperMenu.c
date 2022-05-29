//------------------------------------------------------------------------------------------------
modded class SCR_SettingsSuperMenu : SCR_SuperMenuBase
{
	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
		//Inject our UI tab
		SCR_TabViewComponent TabViewComponent = SCR_TabViewComponent.Cast(GetRootWidget().FindAnyWidget("TabViewRoot0").FindHandler(SCR_TabViewComponent));
		TabViewComponent.AddTab("{7A98E57664F2E836}UI/layouts/Menus/SettingsMenu/InterfaceSettings.layout","Interface",);
		super.OnMenuOpen();
	}
};