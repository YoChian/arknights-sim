
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void raw_summon_spawned_mode_dispatch_call_target
               (longlong *param_1,undefined8 param_2,undefined8 param_3)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  longlong lVar4;
  undefined8 uVar5;
  ushort uVar6;
  
  lVar4 = _DAT_188961dd0;
  switch(*(undefined4 *)(*param_1 + 0x11c)) {
  case 0x9b7:
  case 0x9b8:
  case 0x9b9:
  case 0x9ba:
  case 0x9bb:
  case 0x9bc:
  case 0x9be:
  case 0x9bf:
  case 0x9c0:
  case 0x9c1:
  case 0x9c2:
  case 0x9c3:
  case 0x9c4:
  case 0x9c5:
  case 0x9c6:
  case 0x9c7:
  case 0x9c8:
  case 0x9c9:
  case 0x9ca:
  case 0x9cb:
  case 0x9cc:
  case 0x9cd:
  case 0x9ce:
  case 0x9cf:
  case 0x9d0:
  case 0x9d1:
    if (cRam0000000188c939f9 == '\0') {
      FUN_18048bf00(0x1888a8d10,param_2,param_3,0);
      cRam0000000188c939f9 = '\x01';
    }
    lVar4 = *(longlong *)(*(longlong *)(lRam00000001888a8d10 + 0xb8) + 0x298);
    if (lVar4 != 0) {
      XLua_DelegateBridge___Gen_Delegate_Imp36_0x6000a84(lVar4,param_1,param_2,param_3,0);
    }
    return;
  case 0x9bd:
    break;
  default:
    lVar1 = *param_1;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00();
    }
    uVar6 = 0;
    if (*(ushort *)(lVar1 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar6 * 0x10) == lVar4) {
          puVar3 = (undefined8 *)
                   (((longlong)
                     (*(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar6 * 0x10) + 0x50) +
                    0x14) * 0x10 + lVar1);
          goto LAB_1808fe0a5;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < *(ushort *)(lVar1 + 0x12e));
    }
    puVar3 = (undefined8 *)FUN_180445cc0(param_1,lVar4,0x50);
LAB_1808fe0a5:
                    /* WARNING: Could not recover jumptable at 0x0001808fe0cf. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)*puVar3)(param_1,param_2,param_3,puVar3[1]);
    return;
  }
  if (cRam0000000188c9366b == '\0') {
    FUN_18048bf00(0x1888a81f0,param_2,param_3,0);
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(0x1888f8868);
    FUN_18048bf00(0x1888c6538);
    cRam0000000188c9366b = '\x01';
  }
  lVar4 = *(longlong *)(*(longlong *)(lRam00000001888a81f0 + 0xb8) + 0xb8);
  if (lVar4 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp36_0x6000a84(lVar4,param_1,param_2,param_3,0);
    return;
  }
  if (*(int *)(lRam00000001888c6538 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar4 = FUN_185338d50(uRam00000001888f8868);
  if ((lVar4 != 0) && (plVar2 = *(longlong **)(lVar4 + 0x80), plVar2 != (longlong *)0x0)) {
    uVar5 = FUN_1800057a0(param_2,_DAT_18881b6b0);
    lVar1 = lRam00000001889330a0;
    lVar4 = *plVar2;
    if (*(int *)(lVar4 + 0x11c) == 0x9af) {
      FUN_180bc6030(plVar2,uVar5,param_3,0);
    }
    else {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00();
      }
      uVar6 = 0;
      if (*(ushort *)(lVar4 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar4 + 0xb0) + (ulonglong)uVar6 * 0x10) == lVar1) {
            puVar3 = (undefined8 *)
                     (((longlong)
                       (*(int *)(*(longlong *)(lVar4 + 0xb0) + 8 + (ulonglong)uVar6 * 0x10) + 7) +
                      0x14) * 0x10 + lVar4);
            goto code_r0x000180bd90a5;
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < *(ushort *)(lVar4 + 0x12e));
      }
      puVar3 = (undefined8 *)FUN_180445cc0(plVar2,lVar1,7);
code_r0x000180bd90a5:
      (*(code *)*puVar3)(plVar2,uVar5,param_3,puVar3[1]);
    }
  }
  return;
}

