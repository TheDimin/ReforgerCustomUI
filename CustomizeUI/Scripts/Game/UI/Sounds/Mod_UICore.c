enum EBindtype
{
	Move = 1 ,
	Scale = 1 << 1,
	Color = 1 << 2
}

// Contains info of the saved customized ui element.
//The element name is full binding path.
[BaseContainerProps()]
class UIElementSave : Managed
{
	[Attribute()]
	string m_Path;
	
	[Attribute()]
	ref Color m_Color;
}

[BaseContainerProps(), BaseContainerCustomTitleField("m_Element")]
class MenuBinding : Managed
{
	[Attribute()]
	string m_Element;
	[Attribute("", UIWidgets.Flags, enums: ParamEnumArray.FromEnum(EBindtype))]
	EBindtype m_BindMask;
	
	ref UIElementSave m_Save;
	
	ref ScriptInvoker m_OnValueChanged = new ScriptInvoker();
}

[BaseContainerProps(), BaseContainerCustomTitleField("m_DisplayName")]
class SCR_InterfaceMenuContent : Managed
{
	[Attribute("None")]
	string m_DisplayName;
	
	[Attribute("", UIWidgets.ResourceNamePicker, "Layout element used", "layout")]
	ResourceName m_Layout;
	
	[Attribute("", UIWidgets.Object, "")]
	ref array<ref MenuBinding> m_Bindings;

}

class UISettings: ModuleGameSettings
{
	[Attribute()]
	ref array<ref UIElementSave> arrayelm;
	
	static void SaveArray(array<ref SCR_InterfaceMenuContent> dataSource)
	{
		UISettings settings = new UISettings();
		BaseContainerTools.WriteToInstance(settings, GetGame().GetGameUserSettings().GetModule("UISettings"));
		
		settings.arrayelm.Clear();
		

		
		foreach(SCR_InterfaceMenuContent menuContent : dataSource)
		{
			bool found =false;
			foreach(MenuBinding menuBinding : menuContent.m_Bindings)
			{
					settings.arrayelm.Insert(menuBinding.m_Save);
			}
		}
	
		//Print("SaveTest:"+ settings.arrayelm.Count());
	
		BaseContainerTools.ReadFromInstance(settings, GetGame().GetGameUserSettings().GetModule("UISettings"));
		
		// notify system about change
		GetGame().UserSettingsChanged(); // -> here is also OnSpeedChanged() called
		GetGame().SaveUserSettings();
	}
	
	static void LoadArray(array<ref SCR_InterfaceMenuContent> DataElements)
	{
				
		UISettings settings = new UISettings();
		BaseContainerTools.WriteToInstance(settings, GetGame().GetGameUserSettings().GetModule("UISettings"));
	
		//Terrible oN operation... Find something better for this..
		
		foreach(SCR_InterfaceMenuContent menuContent : DataElements)
		{
			//Print("SCR_InterfaceMenuContent::" + menuContent.m_Bindings.Count());
			bool found =false;
			foreach(MenuBinding menuBinding : menuContent.m_Bindings)
			{
				//Print("Binding Itt");
				foreach ( UIElementSave setting : settings.arrayelm)
				{
					//Print("Compared:: " +menuBinding.m_Element + " :: "+setting.m_Path);
					if(menuBinding.m_Element == setting.m_Path)
					{
						menuBinding.m_Save = setting;
						found = true;
						break;
					}
				}
			}
		}
		
	}
	
}

[BaseContainerProps(configRoot: true)]
modded class SCR_UICore: SCR_GameCoreBase
{
	
	private bool EditUIMode = false;
	
	[Attribute()]
	ref array<ref SCR_InterfaceMenuContent> m_EditableMenus;

	override void OnAfterInit()
	{
		UISettings.LoadArray(m_EditableMenus);
	}
	
	void SaveUIEdits()
	{
		UISettings.SaveArray(m_EditableMenus);
	}
	
	void RevertUIEdits()
	{
		UISettings.LoadArray(m_EditableMenus);
	}
	
	bool BindPanel(Widget widgetInstance,ResourceName widgetName)
	{
	
		foreach(SCR_InterfaceMenuContent ittPanel: m_EditableMenus)
		{
			if(ittPanel.m_Layout == widgetName)
			{
				BindElements(widgetInstance,ittPanel.m_Bindings);
				return true;
			}
		}
		
		return false;
	}
	
	void BindElements(Widget widgetInstance,array<ref MenuBinding> Bindings,ScriptInvoker OnCreation = null)
	{
		foreach(MenuBinding binding: Bindings)
		{
			Widget w = widgetInstance.FindWidget(binding.m_Element);
			if(!w)
			{
				Print("Invalid binding: " + binding.m_Element ,LogLevel.FATAL);
				return;
			}
			
			
			EditElementComponent editComponent = new EditElementComponent(binding);

			if(OnCreation)
				OnCreation.Invoke(editComponent);
			
			w.AddHandler(editComponent);
		}
	}
	
};