class SCR_ElementContextMenu : ScriptedWidgetComponent
{
	Widget m_ContextWidget;
	EditElementComponent m_ActiveEditComponent;
	SCR_ColorPickerComponent m_ColorPicker;
	SCR_ButtonBaseComponent m_ApplyButton
	
	private bool m_IsEnabled;
	
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);
		m_ContextWidget = w;
		m_ColorPicker = SCR_ColorPickerComponent.Cast(w.FindAnyWidget("ColorPicker").FindHandler(SCR_ColorPickerComponent));
		//m_ContextWidget.SetVisible(false);
		m_ApplyButton = SCR_ButtonBaseComponent.Cast(w.FindAnyWidget("ApplyButton").FindHandler(SCR_ButtonBaseComponent));
		m_ApplyButton.m_OnClicked.Insert(OnApplyPressed);
	}
	
	void OnApplyPressed()
	{
		m_ActiveEditComponent.SetColor(m_ColorPicker.GetColor());
		m_ActiveEditComponent.Save();
		Disable();
	}
	
	void Disable()
	{
		m_ContextWidget.SetVisible(false);
		m_IsEnabled = false;
		m_ActiveEditComponent = null;
	}
	void Enable(EditElementComponent Target)
	{
		m_ContextWidget.SetVisible(true);
		m_ActiveEditComponent = Target;
		m_IsEnabled = true;
		
		Color c= Target.GetColor();
		m_ColorPicker.SetColor(c.R(),c.G(),c.B(),true);
	}
	
	
	bool GetIsActive(){ return m_IsEnabled;}
	
	void TickFromOwner()
	{
		m_ColorPicker.TickFromOwner();
	}
	
	void OnItemClick(EditElementComponent Target)
	{
		Enable(Target);
	}
	
	void OnStackRemove(EditElementComponent ItemRemoved)
	{
		if(m_ActiveEditComponent == ItemRemoved)
		{
			//Disable();
		}
	}
}