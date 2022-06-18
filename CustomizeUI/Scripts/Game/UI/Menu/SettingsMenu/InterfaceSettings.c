//------------------------------------------------------------------------------------------------
class SCR_InterfaceSettings : SCR_SettingsSubMenuBase
{
	protected ScrollLayoutWidget m_wScrollElements;
	protected Widget m_ContentOverlay;
	
	private ref array<ref InterfaceMenuBinding> m_MenuBindings = {};
	
	[Attribute("{9149F93339C4F95E}UI/layouts/Menus/SettingsMenu/InterfaceMenuEntry.layout", UIWidgets.ResourceNamePicker, "Layout element used", "layout")]
	ResourceName m_MenuLayout;
	
	SCR_ElementContextMenu m_contextMenu;
	InterfaceMenuBinding m_ActiveMenu;
	
		//We cannot use Focus or OnClick on non buttons right now.....
	//Lets build our own ElementStack trough onHover
	private ref array<EditElementComponent> m_BindingStack = {};

	//------------------------------------------------------------------------------------------------
	protected override void OnMenuOpen(SCR_SuperMenuBase parentMenu)
	{
		m_wScrollElements = ScrollLayoutWidget.Cast(m_wRoot.FindAnyWidget("ScrollElements"));
		m_ContentOverlay = m_wRoot.FindAnyWidget("ElementSlot"); 

		super.OnMenuOpen(parentMenu);
	
		m_contextMenu = SCR_ElementContextMenu.Cast(m_wRoot.FindAnyWidget("ContextMenu").FindHandler(SCR_ElementContextMenu));
		m_contextMenu.Disable();
		
		m_MenuBindings.Clear();
		
		SCR_UICore uiCore = SCR_UICore.Cast(SCR_UICore.GetInstance(SCR_UICore));

		
		foreach(SCR_InterfaceMenuContent resource: uiCore.m_EditableMenus)
		{
			SetupMenuButton(resource);
			
		}
		if(m_MenuBindings.IsEmpty()) return;
		//Hack to trigger it enabled
		m_MenuBindings.Get(0).Open();
		m_ActiveMenu = m_MenuBindings.Get(0);
		
	}
	
	override void OnMenuUpdate(SCR_SuperMenuBase parentMenu, float tDelta)
	{
		super.OnMenuUpdate(parentMenu,tDelta);
		if(m_contextMenu.GetIsActive())
			m_contextMenu.TickFromOwner();
	}

	private void SetupMenuButton(SCR_InterfaceMenuContent content)
	{
		// Create button
		Widget button = GetGame().GetWorkspace().CreateWidgets(m_MenuLayout, m_wScroll.FindWidget("Content"));
		if (!button)
		{
			Print("Failed to create button");
			return;
		}

		SCR_ButtonTextComponent textButton = SCR_ButtonTextComponent.Cast(button.FindHandler(SCR_ButtonTextComponent));
		if (!textButton)
		{
			Print("Failed to get button component");
			return;
		}
		
		InterfaceMenuBinding nMenu = new InterfaceMenuBinding(content,textButton,m_ContentOverlay);
		nMenu.Init();
		m_MenuBindings.Insert(nMenu);
		
		nMenu.m_OnBindingActived.Insert(OnEditMenuOpen);
		nMenu.m_OnComponentCreated.Insert(CreateStackBinding);
		
		textButton.SetText(content.m_DisplayName);
	}	
	
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		Print("ButtonDown: " + m_BindingStack.Count());
		if(m_BindingStack.Count() == 0) return false;
		m_contextMenu.OnItemClick(m_BindingStack.Get(m_BindingStack.Count()-1));
		return false;
	}
	
	
		//SelectableStack
	private void OnEditMenuOpen(InterfaceMenuBinding menu)
	{
		if(m_ActiveMenu)
		{
			m_ActiveMenu.Close();
		}
		
		m_ActiveMenu = menu;
		m_BindingStack.Clear();
	}
	
	private void CreateStackBinding(EditElementComponent editComponent)
	{
		editComponent.m_OnMouseEnter.Insert(AddToStack);
		editComponent.m_OnMouseExit.Insert(RemoveFromStack);
	}
	
	private void RemoveFromStack(EditElementComponent editComponent)
	{
		m_BindingStack.RemoveItem(editComponent);
		m_contextMenu.OnStackRemove(editComponent);
		
	}
	
	private void AddToStack(EditElementComponent editComponent)
	{
		m_BindingStack.Insert(editComponent);
	}
	

};