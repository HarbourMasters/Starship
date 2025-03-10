function OnPlayUpdate(ev)
    print(ev.player.pos.x)
    print(ev.player.pos.y)
    print(ev.player.pos.z)
end

RegisterListener(PlayerPostUpdateEventID, OnPlayUpdate, EventPriority.NORMAL)