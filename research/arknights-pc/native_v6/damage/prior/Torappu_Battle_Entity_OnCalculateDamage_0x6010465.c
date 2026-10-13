/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Entity_OnCalculateDamage_0x6010465
               (undefined8 param_1,undefined8 param_2,undefined8 *param_3)
{
  longlong lVar1;
  code *pcVar2;
  longlong *plVar3;
  char cVar4;
  longlong lVar5;
  undefined8 *puVar6;
  longlong lVar7;
  ushort uVar8;
  longlong *plStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  longlong **pplStack_a0;
  undefined8 uStack_98;
  undefined8 *puStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined1 auStack_38 [16];
  if (DAT_188c908f4 == '\0') {
    uStack_40 = 0x1806f864d;
    FUN_18048bf00(&DAT_188841368);
    DAT_188c908f4 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    uStack_40 = 0x1806f866c;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x940);
  if (lVar7 != 0) {
    uStack_40 = 0x1806f86cc;
    XLua_DelegateBridge___Gen_Delegate_Imp3064_0x6001658(lVar7,param_1,param_2,param_3);
    return;
  }
  uStack_40 = 0x1806f8690;
  lVar7 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
  if (lVar7 == 0) {
    uStack_40 = 0x1806f86e1;
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  if (cRam0000000188c903fa == '\0') {
    FUN_18048bf00(0x1888d5250,param_2,param_3,0);
    FUN_18048bf00(0x18882b720);
    FUN_18048bf00(&DAT_188954c98);
    FUN_18048bf00(0x1888cfcb0);
    FUN_18048bf00(0x188959b58);
    FUN_18048bf00(0x1889316a8);
    cRam0000000188c903fa = '\x01';
  }
  plStack_b8 = (longlong *)0x0;
  uStack_88 = 0;
  uStack_80 = 0;
  lVar5 = *(longlong *)(*(longlong *)(lRam00000001888d5250 + 0xb8) + 0x308);
  if (lVar5 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp3064_0x6001658(lVar5,lVar7,param_2,param_3,0);
    return;
  }
  lVar5 = FUN_18067ffe0(lVar7,0);
  if (lVar5 != 0) {
    uStack_b0 = FUN_1806c5c20(lVar5,0);
    uStack_98 = 0;
    puStack_90 = &uStack_b0;
    FUN_1806c37b0(&uStack_b0,param_2,0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      plStack_b8 = (longlong *)FUN_185a17960(*(longlong *)(lVar7 + 0x18),uRam000000018882b720);
      uStack_a8 = 0;
      pplStack_a0 = &plStack_b8;
      while (plStack_b8 != (longlong *)0x0) {
        cVar4 = FUN_180005310(0,uRam0000000188959b58);
        plVar3 = plStack_b8;
        lVar5 = lRam00000001888cfcb0;
        if (cVar4 == '\0') {
          if (plStack_b8 != (longlong *)0x0) {
            FUN_180005310(0,_DAT_188954c98,plStack_b8);
          }
          FUN_1806c2ce0(&uStack_b0,0);
          FUN_18067e5b0(lVar7,0);
          return;
        }
        if (plStack_b8 == (longlong *)0x0) {
          FUN_18048c0b0();
          break;
        }
        lVar1 = *plStack_b8;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(lVar1);
        }
        uVar8 = 0;
        if (*(ushort *)(lVar1 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar8 * 0x10) == lVar5) {
              puVar6 = (undefined8 *)
                       (((longlong)
                         *(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar8 * 0x10) + 0x14)
                        * 0x10 + lVar1);
              goto code_r0x00018066ffd9;
            }
            uVar8 = uVar8 + 1;
          } while (uVar8 < *(ushort *)(lVar1 + 0x12e));
        }
        puVar6 = (undefined8 *)FUN_180445cc0(plVar3,lVar5,0);
code_r0x00018066ffd9:
        puVar6 = (undefined8 *)(*(code *)*puVar6)(auStack_38,plVar3,puVar6[1]);
        uStack_88 = *puVar6;
        uStack_80 = puVar6[1];
        lVar5 = FUN_185159d80(&uStack_88,uRam00000001889316a8);
        if ((lVar5 != 0) && (cVar4 = FUN_18068edb0(lVar5,0), cVar4 == '\0')) {
          uStack_68 = *param_3;
          uStack_60 = param_3[1];
          uStack_58 = *(undefined4 *)(param_3 + 2);
          uStack_54 = *(undefined4 *)((longlong)param_3 + 0x14);
          uStack_50 = *(undefined4 *)(param_3 + 3);
          uStack_4c = *(undefined4 *)((longlong)param_3 + 0x1c);
          uStack_48 = param_3[4];
          FUN_1806c3320(&uStack_b0,&uStack_68,0);
          FUN_180684080(lVar5,param_3,0);
        }
      }
      FUN_18048c0b0();
      FUN_180472d50();
      FUN_180472d50();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}
