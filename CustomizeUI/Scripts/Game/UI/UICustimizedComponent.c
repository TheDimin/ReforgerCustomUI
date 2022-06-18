class UICustomizeComponent : SCR_ScriptedWidgetComponent
{
	protected MenuBinding m_binding;
	
    void UICustomizeComponent(notnull MenuBinding MBinding)
	{
		m_binding = MBinding;
	}
	
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);
		Load();
	}
	
	void SetColor(Color c)
	{
		m_wRoot.SetColor(c);
	}
	
	Color GetColor()
	{
		return m_wRoot.GetColor();
	}
	
	void Load()
	{
		
	//	auto e = GetGame().tm.Get(m_binding.m_Element);
		if(m_binding.m_Save)
			SetColor(m_binding.m_Save.m_Color)
	}
}