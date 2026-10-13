
/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Abilities_AbstractAnimatedAbility_DoAttach_0x601668c
               (longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined4 uVar9;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c956d1 == '\0') {
    puStack_30 = (undefined *)0x180eff955;
    FUN_18048bf00(&DAT_1887f76b0);
    DAT_188c956d1 = '\x01';
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_1887f76b0 + 0xb8) + 0xc0);
  if (lVar5 != 0) {
    if (*(longlong *)(lVar5 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
    if (*(longlong *)(lVar5 + 0x18) != 0) {
      uVar6 = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x10);
      iVar3 = FUN_183f23b70(uVar6,*(undefined4 *)(lVar5 + 0x38),*(undefined4 *)(lVar5 + 0x14),0);
      if (*(longlong *)(lVar5 + 0x18) != 0) {
        lVar1 = *(longlong *)(*(longlong *)(lVar5 + 0x18) + 0x20);
        if (lVar1 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar1,uVar6,param_1,0);
          FUN_183cf8c20(lVar1,uVar6,param_2,0);
          iVar4 = FUN_183f22380(uVar6,2,0,iVar3,0);
          if (iVar4 == 0) {
code_r0x0001832d231b:
            FUN_183f22fd0(uVar6,iVar3 + -1,0);
            return;
          }
          if (*(longlong *)(lVar5 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar5 + 0x18),iVar3 + -1,0);
            goto code_r0x0001832d231b;
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
  if ((int)param_1[0x28] == 1) {
    lVar5 = param_1[0x29];
    if (param_2 == (longlong *)0x0) goto LAB_180effa71;
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (undefined *)0x180eff9a8;
      func_0x000180446d00(*param_2);
    }
    puStack_30 = (undefined *)0x180eff9c8;
    (**(code **)(*param_2 + 2000))(param_2,lVar5,param_1 + 0x2f,*(undefined8 *)(*param_2 + 0x7d8));
  }
  if ((int)param_1[0x28] == 3) {
    puStack_30 = (undefined *)0x180eff9db;
    lVar5 = Torappu_Battle_Ability_get_blackboard_0x600f62a(param_1,0);
    if (lVar5 == 0) goto LAB_180effa71;
    puStack_30 = (undefined *)0x180eff9f6;
    uVar9 = Torappu_Blackboard_GetFloat_0x6007864(lVar5,param_1[0x30],0);
    *(undefined4 *)(param_1 + 0x2f) = uVar9;
  }
  puStack_30 = (undefined *)0x180effa0c;
  Torappu_Battle_Ability_DoAttach_0x600f656(param_1,param_2,0);
  lVar5 = param_1[0xe];
  if (DAT_188ccc7f0 != '\0') {
    puStack_30 = (undefined *)0x180effa21;
    func_0x000180446d00(*param_1);
  }
  puStack_30 = (undefined *)0x180effa37;
  uVar6 = (**(code **)(*param_1 + 0x250))(param_1,*(undefined8 *)(*param_1 + 600));
  if (lVar5 != 0) {
    if (cRam0000000188ca0cff == '\0') {
      puStack_30 = &UNK_181e0450f;
      FUN_18048bf00(&DAT_18885a700,uVar6,0);
      puStack_30 = &UNK_181e0451b;
      FUN_18048bf00(&DAT_1888915d8);
      cRam0000000188ca0cff = '\x01';
    }
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      puStack_30 = &UNK_181e04537;
      func_0x00018048c140();
    }
    puStack_30 = &UNK_181e04540;
    uVar7 = func_0x0001866fdac0(0,0);
    puStack_30 = &UNK_181e04553;
    uVar8 = func_0x0001866fba10(*(undefined8 *)(lVar5 + 0x10),*(undefined8 *)(lVar5 + 0x18),0);
    puStack_30 = &UNK_181e04561;
    uVar8 = func_0x0001866fba10(uVar6,uVar8,0);
    if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
      puStack_30 = &UNK_181e04579;
      func_0x00018048c140();
    }
    puStack_30 = &UNK_181e04587;
    uVar7 = Torappu_TSMath_Max_0x600033b(uVar7,uVar8,0);
    *(undefined8 *)(lVar5 + 0x10) = uVar6;
    *(undefined8 *)(lVar5 + 0x18) = uVar7;
    return;
  }
LAB_180effa71:
  puStack_30 = (undefined *)0x180effa76;
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

