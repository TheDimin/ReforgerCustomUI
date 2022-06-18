modded class SCR_HUDManagerComponent : HUDManagerComponent
{
	
	
	//------------------------------------------------------------------------------------------------
	override Widget CreateLayout(ResourceName path, EHudLayers layer, int zOrder = 0)
	{
		Widget createdWidget = super.CreateLayout(path,layer,zOrder);
		
		if(createdWidget)
		{
			SCR_UICore.Cast(SCR_UICore.GetInstance(SCR_UICore)).BindPanel(createdWidget,path);
		}
		
		return createdWidget;
	}
};
