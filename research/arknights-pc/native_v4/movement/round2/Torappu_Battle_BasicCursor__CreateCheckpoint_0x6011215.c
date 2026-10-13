
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong Torappu_Battle_BasicCursor__CreateCheckpoint_0x6011215
                   (undefined8 param_1,longlong param_2,undefined8 param_3)

{
  code *pcVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  longlong lVar4;
  
  if (DAT_188c914bd == '\0') {
    FUN_18048bf00(0x1888b8448);
    FUN_18048bf00(0x1888b8680);
    FUN_18048bf00(&DAT_188923568);
    FUN_18048bf00(&DAT_1888a10f8);
    FUN_18048bf00(&DAT_18890aa98);
    FUN_18048bf00(&DAT_188888eb0);
    FUN_18048bf00(&DAT_188943538);
    FUN_18048bf00(0x1888b88b8);
    FUN_18048bf00(0x1888b8af8);
    FUN_18048bf00(0x1888b8d38);
    FUN_18048bf00(0x1888b8f70);
    FUN_18048bf00(0x1888b93e8);
    FUN_18048bf00(0x1888b9628);
    FUN_18048bf00(0x1888b9860);
    FUN_18048bf00(0x1888b9aa0);
    FUN_18048bf00(0x1888b9cd8);
    DAT_188c914bd = '\x01';
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_188923568 + 0xb8) + 0xa0);
  if (lVar4 == 0) {
    if (param_2 != 0) {
      switch(*(undefined4 *)(param_2 + 0x10)) {
      case 0:
        lVar4 = func_0x00018045cfe0(uRam00000001888b8d38);
        if (lVar4 != 0) {
          MoveCheckpoint__ctor_0x601122e(lVar4,param_2,param_3,param_1,0);
          return lVar4;
        }
        break;
      case 1:
        lVar4 = func_0x00018045cfe0(uRam00000001888b9cd8);
        if (lVar4 != 0) {
          Torappu_AVG_AVGTweenFactory__ctor_0x600de1c(lVar4,param_2,param_1,0);
          return lVar4;
        }
        break;
      case 2:
        lVar4 = func_0x00018045cfe0(uRam00000001888b9aa0);
        if (lVar4 != 0) {
          Torappu_AVG_AVGTweenFactory__ctor_0x600de1c(lVar4,param_2,param_1,0);
          return lVar4;
        }
        break;
      case 3:
        lVar4 = func_0x00018045cfe0(uRam00000001888b9628);
        if (lVar4 != 0) {
          Torappu_AVG_AVGTweenFactory__ctor_0x600de1c(lVar4,param_2,param_1,0);
          return lVar4;
        }
        break;
      case 4:
        lVar4 = func_0x00018045cfe0(uRam00000001888b9860);
        if (lVar4 != 0) {
          Torappu_AVG_AVGTweenFactory__ctor_0x600de1c(lVar4,param_2,param_1,0);
          return lVar4;
        }
        break;
      case 5:
        lVar4 = func_0x00018045cfe0(uRam00000001888b88b8);
        if (lVar4 != 0) {
          Torappu_AVG_AVGTweenFactory__ctor_0x600de1c(lVar4,param_2,param_1,0);
          return lVar4;
        }
        break;
      case 6:
        lVar4 = func_0x00018045cfe0(uRam00000001888b8680);
        if (lVar4 != 0) {
          Torappu_AVG_AVGTweenFactory__ctor_0x600de1c(lVar4,param_2,param_1,0);
          return lVar4;
        }
        break;
      case 7:
        lVar4 = func_0x00018045cfe0(uRam00000001888b8448);
        if (lVar4 != 0) {
          Torappu_AVG_AVGTweenFactory__ctor_0x600de1c(lVar4,param_2,param_1,0);
          return lVar4;
        }
        break;
      case 8:
        lVar4 = func_0x00018045cfe0(uRam00000001888b8f70);
        if (lVar4 != 0) {
          PatrolMoveCheckpoint__ctor_0x6011237(lVar4,param_2,param_3,param_1,0);
          return lVar4;
        }
        break;
      case 9:
        lVar4 = func_0x00018045cfe0(uRam00000001888b93e8);
        if (lVar4 != 0) {
          WaitBossrushWaveCheckPoint__ctor_0x601126c(lVar4,param_2,param_1,0);
          return lVar4;
        }
        break;
      case 10:
        lVar4 = func_0x00018045cfe0(uRam00000001888b8af8);
        if (lVar4 != 0) {
          PatrolMoveCheckpoint__ctor_0x6011237(lVar4,param_2,param_3,param_1,0);
          return lVar4;
        }
        break;
      default:
        uVar2 = func_0x00018048bf20(0x18892d528);
        uVar2 = func_0x00018045cfe0(uVar2);
        FUN_180005cb0(uVar2);
        System_NotImplementedException__ctor_0x60009a4(uVar2,0);
        uVar3 = func_0x00018048bf20(0x18895b9a0);
        FUN_18048c070(uVar2,uVar3);
        pcVar1 = (code *)swi(3);
        lVar4 = (*pcVar1)();
        return lVar4;
      }
    }
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    lVar4 = (*pcVar1)();
    return lVar4;
  }
  XLua_DelegateBridge_InvokeSessionStart_0x6003c9d(lVar4,0);
  FUN_1844c6730(lVar4,param_1,_DAT_1888a10f8);
  FUN_1844c6730(lVar4,param_2,_DAT_18890aa98);
  FUN_1844c6730(lVar4,param_3,_DAT_188888eb0);
  XLua_DelegateBridge_Invoke_0x6003c9e(lVar4,1,0);
  lVar4 = FUN_1844c9fe0(lVar4,_DAT_188943538);
  return lVar4;
}

