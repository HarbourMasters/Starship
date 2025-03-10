function OnPlayUpdate(ev)
    print("OnPlayUpdate 1")
    -- HUD_LivesCount2_Draw(50.0, 50.0, 2);
    RCP_AutoSetupDL(SetupDL.SETUPDL_76_POINT)
    Graphics_DisplaySmallText(50, 50, 1.0, 1.0, "RUNNING FROM LUA");
end

RegisterListener(DrawLivesCounterHUDEventID, OnPlayUpdate, EventPriority.NORMAL)