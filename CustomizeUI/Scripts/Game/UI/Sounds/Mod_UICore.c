enum EBindtype
{
	Move = 1 ,
	Scale = 1 << 1,
	Color = 1 << 2
}

[BaseContainerProps(), BaseContainerCustomTitleField("m_Element")]
class MenuBinding : Managed
{
	[Attribute()]
	string m_Element;
	[Attribute("", UIWidgets.Flags, enums: ParamEnumArray.FromEnum(EBindtype))]
	EBindtype m_BindMask;
}

[BaseContainerProps(), BaseContainerCustomTitleField("m_DisplayName")]
class SCR_InterfaceMenuContent : Managed
{
	[Attribute("None")]
	string m_DisplayName;
	
	[Attribute("", UIWidgets.ResourceNamePicker, "Layout element used", "layout")]
	ResourceName m_Layout;
	
	[Attribute("", UIWidgets.Object, "")]
	ref array<ref MenuBinding> m_bindings;

}

[BaseContainerProps()]
class UIElementSettings
{
	[Attribute()]
	string Key;
	
	[Attribute()]
	ref Color elementColor;
}
typedef map<string,ref UIElementSettings> TUIElementMap;


[BaseContainerProps(configRoot: true)]
modded class SCR_UICore: SCR_GameCoreBase
{
	ref array<ref SCR_InterfaceMenuContent> m_EditableMenus;
};