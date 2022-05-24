//------------------------------------------------------------------------------------------------
class InterfaceGroup
{
	string MenuName = string.Empty;
	string ElementName = string.Empty;
}

class SCR_InterfaceSettings : SCR_SettingsSubMenuBase
{
	[Attribute("", UIWidgets.Object, "")]
	protected ref array<ref SCR_InterfaceMenuContent> m_menuTypes;
	protected ScrollLayoutWidget m_wScrollElements;

	//------------------------------------------------------------------------------------------------
	protected override void OnMenuOpen(SCR_SuperMenuBase parentMenu)
	{
		
		m_wScrollElements = ScrollLayoutWidget.Cast(m_wRoot.FindAnyWidget("ScrollElements"));
		
		//m_wScroll
		
		//TODO Save bindings
		//	m_aSettingsBindings.Insert(new SCR_SettingBindingEngine("AudioSettings", "Volume", "Master"));

		
		foreach(SCR_InterfaceMenuContent resource: m_menuTypes)
		{
			
			Print("Adding element");
			Widget w = GetGame().GetWorkspace().CreateWidgets(resource.m_ElementLayout,m_wScroll);
		}
		
		super.OnMenuOpen(parentMenu);
	}

	//------------------------------------------------------------------------------------------------
	protected override void OnMenuHide(SCR_SuperMenuBase parentMenu)
	{
		super.OnMenuHide(parentMenu);
		GetGame().SaveUserSettings();
	}

	//------------------------------------------------------------------------------------------------
	protected override void OnMenuShow(SCR_SuperMenuBase parentMenu)
	{
		super.OnMenuShow(parentMenu);
		
		//m_wScrollElements.SetSliderPos(0,0);
	}
	
	
};

[BaseContainerProps(), SCR_BaseContainerLocalizedTitleField("m_InterfaceMenuContent")]
class SCR_InterfaceMenuContent
{
	[Attribute("", UIWidgets.ResourceNamePicker, "Layout element used", "layout")]
	ResourceName m_ElementLayout;
}