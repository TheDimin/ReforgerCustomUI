class SCR_ColorPickerComponent : ScriptedWidgetComponent
{
	[Attribute("Slider")]
	string SliderName;
	[Attribute("EditBox")]
	string EditBoxName;
	
	SliderWidget m_SliderWidget[3];
	EditBoxWidget m_EditBox[3];
	
	ref Color m_OldValue = Color.White;
	ref Color m_StartColor;
	
	
	override void HandlerAttached(Widget w)
	{
		Widget sl = w.FindAnyWidget("Sliders");
		
		m_SliderWidget[0] = SliderWidget.Cast(sl.FindWidget("Red")); 
		m_SliderWidget[1] = SliderWidget.Cast(sl.FindWidget("Green")); 
		m_SliderWidget[2] = SliderWidget.Cast(sl.FindWidget("Blue")); 

	}
	
	bool TickFromOwner()
	{
		if( m_SliderWidget[0].GetCurrent() == m_OldValue.R() &&
			m_SliderWidget[1].GetCurrent() == m_OldValue.G() &&
			m_SliderWidget[2].GetCurrent() == m_OldValue.B())
		return true;
		
		SetColor(m_SliderWidget[0].GetCurrent(),
				m_SliderWidget[1].GetCurrent(),
				m_SliderWidget[2].GetCurrent());
		
		return true;
	}
	
	
	void SetColor(float r,float g,float b,bool force = false)
	{
		m_OldValue.SetR(r);
		m_OldValue.SetG(g);
		m_OldValue.SetB(b);
		
		
		for(int i =0; i<3;i++)
		{
			m_SliderWidget[i].SetColor(m_OldValue);
		}
		
		if(force)
		{
			m_SliderWidget[0].SetCurrent(m_OldValue.R());
			m_SliderWidget[1].SetCurrent(m_OldValue.G());
			m_SliderWidget[2].SetCurrent(m_OldValue.B());
		}
	}
	
	Color GetColor(){return m_OldValue;}
}