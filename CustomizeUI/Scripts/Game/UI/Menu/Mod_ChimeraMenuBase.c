modded class ChimeraMenuBase : MenuBase
{
	override void OnMenuInit()
	{
	}
	
	void GetBindables(){
	
	}
	
	
	void EditWidget(Widget widget)
	{
		//EditUIMode =true;
		EditUITraversal(widget);
	}
	
	private void EditUITraversal(Widget widget)
	{
		array<Widget> childs ={};
		//GetAllChildren(widget,childs);

		//foreach(Widget w :childs){
		//	Print("WidgetName:" + w.GetNumHandlers());
		//	EditUITraversal(w);
		//}
	}
	
	private void GetAllChildren(Widget parent, notnull inout array<Widget> allChildren)
    {
        if (!parent)
            return;
        
        Widget child = parent.GetChildren();
        
        while (child)
        {
            allChildren.Insert(child);
            child = child.GetSibling();
        }
    }
};
