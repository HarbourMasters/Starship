require("test.lua")

function OnPlayUpdate(ev)
    PrintTest()
    if((Game.gInputPress().button & N64Buttons.BTN_L) ~= 0) then
        local reticlePos = Game.D_display_801613E0(0)
        local actorId = math.random(176, 291)
        local actor = Game_SpawnActor(actorId);

        if (actor ~= nil) then
            actor.obj.pos.x = reticlePos.x * 1.7
            actor.obj.pos.y = 200.0
            actor.obj.pos.z = Game.gPlayer().pos.z - 1500.0 - (reticlePos.y * 1.7)
            actor.state = 0
        end
    end
end

RegisterListener(Events.PlayerPreUpdateEvent, OnPlayUpdate, EventPriority.NORMAL)