//Class that takes responsiblity of Binding to specific Menu
class InterfaceMenuBinding : Managed
{	
	private SCR_InterfaceMenuContent m_MenuContent;
	//Button that causes us to be toggeled
	private SCR_ButtonBaseComponent m_OwningButton;
	private Widget m_ContentWidget;
	
	private ref Widget m_WidgetInstance;
	
		// Arguments passed: InterfaceMenuBinding
	ref ScriptInvoker m_OnBindingActived = new ref ScriptInvoker();
	// Arguments passed: EditElementComponent
	ref ScriptInvoker m_OnComponentCreated = new ref ScriptInvoker();
	
	
	void InterfaceMenuBinding(notnull SCR_InterfaceMenuContent MenuContent,notnull SCR_ButtonBaseComponent OwningButton,notnull Widget ContentParrent)
	{
		m_MenuContent = MenuContent;
		m_OwningButton = OwningButton;
		m_ContentWidget = ContentParrent;
	}
	
	void Init()
	{
		m_OwningButton.m_OnClicked.Insert(OnItemClick);
	}
	
	void Open()
	{
		m_WidgetInstance = GetGame().GetWorkspace().CreateWidgets(m_MenuContent.m_Layout, m_ContentWidget);
		
		AlignableSlot.SetHorizontalAlign(m_WidgetInstance,LayoutHorizontalAlign.Stretch);
		AlignableSlot.SetVerticalAlign(m_WidgetInstance,LayoutVerticalAlign.Stretch);
		
		if(m_OwningButton)
			m_OwningButton.SetToggled(true);
		
		m_OnBindingActived.Invoke(this);
		
		foreach(MenuBinding binding: m_MenuContent.m_bindings)
		{
			Widget w = m_WidgetInstance.FindWidget(binding.m_Element);
			if(!w)
			{
				Print("Invalid binding: " + binding.m_Element ,LogLevel.FATAL);
				return;
			}
			
			
			EditElementComponent editComponent = new EditElementComponent();
			editComponent.m_BindMask = binding.m_BindMask;
			m_OnComponentCreated.Invoke(editComponent);
			w.AddHandler(editComponent);
		}
	}
	
	void Close()
	{
		if(m_OwningButton)
			m_OwningButton.SetToggled(false);
		
		if(m_WidgetInstance)
		{
			m_WidgetInstance.RemoveFromHierarchy();
			delete m_WidgetInstance;
		}
	}
	
	
	//Do we need to have the parameter ?
	protected void OnItemClick(SCR_ButtonBaseComponent sb)
	{
		if(m_WidgetInstance != null) return;
		Open();
	}

}