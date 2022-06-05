class UISettings: ModuleGameSettings
{
	[Attribute()]
	ref array<ref UIElementSettings> arrayelm;
	
	static void SaveArray(notnull TUIElementMap maped)
	{
		UISettings settings = new UISettings;
		BaseContainerTools.WriteToInstance(settings, GetGame().GetGameUserSettings().GetModule("UISettings"));
	
		ref array<ref UIElementSettings> t ={};
		
		foreach ( auto itt : maped)
		{
			t.Insert(itt);
		}
		settings.arrayelm = t;	
	
	
		BaseContainerTools.ReadFromInstance(settings, GetGame().GetGameUserSettings().GetModule("UISettings"));
		
		// notify system about change
		GetGame().UserSettingsChanged(); // -> here is also OnSpeedChanged() called
		GetGame().SaveUserSettings();
	}
	
	static void LoadArray(out TUIElementMap mapped)
	{
		mapped = new TUIElementMap();
		
		UISettings settings = new UISettings;
		BaseContainerTools.WriteToInstance(settings, GetGame().GetGameUserSettings().GetModule("UISettings"));
	
		foreach ( UIElementSettings setting : settings.arrayelm)
		{
			mapped.Insert(setting.Key,setting);
		}
	}
	
}

class EditElementComponent : UICustomizeComponent
{
	// Arguments passed: EditElementComponent
	ref ScriptInvoker m_OnMouseEnter = new ref ScriptInvoker();
	// Arguments passed: EditElementComponent
	ref ScriptInvoker m_OnMouseExit = new ref ScriptInvoker();
	
		
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);
		m_wRoot.ClearFlags(WidgetFlags.IGNORE_CURSOR);
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		m_OnMouseEnter.Invoke(this);
		return false;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		m_OnMouseExit.Invoke(this);
		return false;
	}
	
	void Save()
	{
		UIElementSettings us = new UIElementSettings();
		us.Key = m_binding.m_Element;
		us.elementColor = GetColor();
		
		GetGame().tm.Insert(m_binding.m_Element,us);
		UISettings.SaveArray(GetGame().tm);
	}	
}