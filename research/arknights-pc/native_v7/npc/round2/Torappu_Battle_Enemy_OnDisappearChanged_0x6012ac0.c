/* WARNING: Removing unreachable block (ram,0x0001833006f9) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Enemy_OnDisappearChanged_0x6012ac0(longlong *param_1,char param_2)
{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  longlong *plVar5;
  undefined8 uVar6;
  longlong lVar7;
  char acStackX_20 [8];
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  if (DAT_188c928a8 == '\0') {
    uStack_40 = 0x180a70675;
    FUN_18048bf00(&DAT_188949060);
    uStack_40 = 0x180a70681;
    FUN_18048bf00(&DAT_18881b6b0);
    uStack_40 = 0x180a7068d;
    FUN_18048bf00(&DAT_188819760);
    uStack_40 = 0x180a70699;
    FUN_18048bf00(&DAT_18889bca8);
    DAT_188c928a8 = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    uStack_40 = 0x180a706b8;
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x680);
  if (lVar7 == 0) {
    if (param_2 == '\0') {
      if (DAT_188ccc7f0 != '\0') {
        uStack_40 = 0x180a706f5;
        func_0x000180446d00(*param_1);
      }
      uStack_40 = 0x180a7070b;
      plVar5 = (longlong *)
               (**(code **)(*param_1 + 0xf50))(param_1,*(undefined8 *)(*param_1 + 0xf58));
      if (plVar5 == (longlong *)0x0) {
LAB_180a707fe:
        uStack_40 = 0x180a70803;
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      if (DAT_188ccc7f0 != '\0') {
        uStack_40 = 0x180a70728;
        func_0x000180446d00(*plVar5);
      }
      uStack_40 = 0x180a7073f;
      uVar6 = (**(code **)(*plVar5 + 0x200))(plVar5,*(undefined8 *)(*plVar5 + 0x208));
      uStack_40 = 0x180a7074d;
      uVar6 = Torappu_Battle_Enemy__CalculateFaceDirection_0x6012ae8(param_1,uVar6,0);
      uStack_40 = 0x180a70767;
      Torappu_Battle_Entity_FaceTo_0x60103e8(param_1,uVar6,1,0);
    }
    else {
      uStack_40 = 0x180a70773;
      lVar7 = Torappu_Battle_Enemy_get_stateMachine_0x6012a56(param_1,0);
      if (lVar7 == 0) goto LAB_180a707fe;
      uStack_40 = 0x180a70790;
      FUN_18499c9d0(lVar7,0xb,_DAT_18889bca8);
    }
    uStack_40 = 0x180a7079a;
    lVar7 = Torappu_Battle_Entity_get_eventPool_0x6010338(param_1,0);
    uStack_40 = 0x180a707b3;
    acStackX_20[0] = param_2;
    uVar6 = func_0x00018048b9c0(_DAT_188949060,acStackX_20);
    if (lVar7 == 0) {
      uStack_40 = 0x180a707fd;
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uStack_40 = 0x180a707cf;
    FUN_1848dca60(lVar7,0x17,uVar6,_DAT_188819760);
    return;
  }
  if (*(longlong *)(lVar7 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  uStack_48 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = &uStack_48;
  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
  if (*(longlong *)(lVar7 + 0x18) != 0) {
    uVar6 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
    iVar3 = FUN_183f23b70(uVar6,*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x14),0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
      if (lVar1 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar1,uVar6,param_1,0);
        FUN_183f22430(uVar6,param_2,0);
        iVar4 = FUN_183f22380(uVar6,2,0,iVar3,0);
        if (iVar4 == 0) {
code_r0x0001833006e0:
          FUN_183f22fd0(uVar6,iVar3 + -1,0);
          return;
        }
        if (*(longlong *)(lVar7 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar3 + -1,0);
          goto code_r0x0001833006e0;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}
