#ifndef SF64_TAGGING
#define SF64_TAGGING

/* For dynamic actors */
#define TAG_ADDRESS(ptr) ((u32) (ptr) & 0x0FFFFFFF)

/*
    X    XXX    XX     XX
    TYPE  ID  INDEX  CUSTOM
*/
#define TAG_OBJ(ptr) (((((ptr)->obj.id) << 16) & 0x0FFF0000) | ((((ptr)->index) << 8) & 0x0000FF00))

/* Actor Types */
#define TAG_ACTOR(actor) ((u32) (0x10000000 | (TAG_OBJ(actor))))
#define TAG_ACTOR_EVENT(actor) ((u32) (0x20000000 | (TAG_OBJ(actor))))
#define TAG_ACTOR_EVENT_COMMON(actor) ((u32) (0x90000000 | (TAG_OBJ(actor))))
#define TAG_BOSS(boss) ((u32) (0x30000000 | (TAG_OBJ(boss))))
#define TAG_SCENERY(scenery) ((u32) (0x40000000 | (TAG_OBJ(scenery))))
#define TAG_SCENERY_360(scenery360) ((u32) (0x50000000 | (TAG_ADDRESS(scenery360))))
#define TAG_EFFECT(effect) ((u32) (0x60000000 | (TAG_OBJ(effect))))
#define TAG_ITEM(item) ((u32) (0x70000000 | (TAG_OBJ(item))))
#define TAG_PLAYER_SHOT(shot) ((u32) (0xC0000000 | (TAG_OBJ(shot))))

/* Skeletons */
#define TAG_LIMB_ADDRESS(ptr, data) ((((u32) (ptr) << 16) & 0xFFFF0000) | ((u32) (data) & 0x0000FFFF))
#define TAG_LIMB(limb, data) ((u32) (0x80000000 | (TAG_LIMB_ADDRESS(limb, data))))

/* Others */
#define TAG_ARWING_SKEL(arwing) (0xB0000000 | (((u32) (arwing) << 16) & 0x0FFF0000))

#endif
