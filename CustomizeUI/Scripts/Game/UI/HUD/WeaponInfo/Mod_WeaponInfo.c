//modded class SCR_WeaponInfo : SCR_InfoDisplayExtended
//{	
	//------------------------------------------------------------------------------------------------
	/*override void AnimateWidget_ColorFlash(Widget w, EWeaponFeature requiredFlag = -1, float speed = WidgetAnimator.FADE_RATE_SLOW)
	{
		if (!w)
			return;
		
		if (requiredFlag != -1 && m_eWeaponStateEvent != requiredFlag)
			return;
		
		Color c = w.GetColor();
		w.SetColor(COLOR_ORANGE);
		
		WidgetAnimator.PlayAnimation(w, WidgetAnimationType.Color, c, speed);
	}	*/
	
	//------------------------------------------------------------------------------------------------
	//! Returns player's inventory manager, or vehicle's inv manager if player is in vehicle
	
//};