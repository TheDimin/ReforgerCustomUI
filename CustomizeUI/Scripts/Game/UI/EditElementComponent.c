class EditElementComponent : SCR_ScriptedWidgetComponent
{
	// Arguments passed: EditElementComponent
	ref ScriptInvoker m_OnMouseEnter = new ref ScriptInvoker();
	// Arguments passed: EditElementComponent
	ref ScriptInvoker m_OnMouseExit = new ref ScriptInvoker();
	
	EBindtype m_BindMask;
	
	void EditElementComponent()
	{
	 Print("EditElementComponent created");
	}
	
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);
		Print("HandlerAttached");
		m_wRoot.ClearFlags(WidgetFlags.IGNORE_CURSOR)
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		m_OnMouseEnter.Invoke(this);
		Print("MouseEnter");
		return false;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		m_OnMouseExit.Invoke(this);
		Print("MouseExit");
		return false;
	}
	
	void SetColor(Color c)
	{
		m_wRoot.SetColor(c);
		//TODO write to disk
	}
	
	Color GetColor()
	{
		return m_wRoot.GetColor();
	}
	
}