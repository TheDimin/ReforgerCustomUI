

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
		SCR_UICore uiCore = SCR_UICore.Cast(SCR_UICore.GetInstance(SCR_UICore));
		if(!m_binding.m_Save)
		{
			m_binding.m_Save = new UIElementSave();
			m_binding.m_Save.m_Path = m_binding.m_Element;
		}
		
		m_binding.m_Save.m_Color = GetColor();
		
		uiCore.SaveUIEdits();
		
		//UIElementSettings us = new UIElementSettings();
	//	us.Key = m_binding.m_Element;
	//	us.elementColor = GetColor();
		
	//	GetGame().tm.Insert(m_binding.m_Element,us);
	//	UISettings.SaveArray(GetGame().tm);
	}	
}