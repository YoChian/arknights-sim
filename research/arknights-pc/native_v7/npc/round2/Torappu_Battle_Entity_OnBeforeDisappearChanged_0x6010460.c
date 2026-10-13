/* WARNING: Removing unreachable block (ram,0x0001833006f9) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Entity_OnBeforeDisappearChanged_0x6010460(undefined8 param_1,char param_2)
{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong *plVar6;
  undefined8 *puVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 uVar10;
  ushort uVar11;
  char acStackX_20 [8];
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined1 auStack_40 [8];
  undefined8 uStack_38;
  undefined1 *puStack_30;
  if (DAT_188c908ef == '\0') {
    puStack_30 = (undefined1 *)0x1806f7ab5;
    FUN_18048bf00(&DAT_188949060);
    puStack_30 = (undefined1 *)0x1806f7ac1;
    FUN_18048bf00(&DAT_188841368);
    puStack_30 = (undefined1 *)0x1806f7acd;
    FUN_18048bf00(&DAT_188819760);
    DAT_188c908ef = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    puStack_30 = (undefined1 *)0x1806f7aec;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x918);
  if (lVar9 == 0) {
    puStack_30 = (undefined1 *)0x1806f7b1e;
    func_0x00018050cf60(param_1,param_2,0);
    puStack_30 = (undefined1 *)0x1806f7b28;
    lVar9 = Torappu_Battle_Entity_get_eventPool_0x6010338(param_1,0);
    puStack_30 = (undefined1 *)0x1806f7b41;
    acStackX_20[0] = param_2;
    uVar10 = func_0x00018048b9c0(_DAT_188949060,acStackX_20);
    if (lVar9 == 0) {
      puStack_30 = (undefined1 *)0x1806f7bd0;
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    puStack_30 = (undefined1 *)0x1806f7b61;
    FUN_1848dca60(lVar9,0x1e,uVar10,_DAT_188819760);
    puStack_30 = (undefined1 *)0x1806f7b6b;
    lVar9 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
    if (param_2 == '\0') {
      if (lVar9 != 0) {
        if (cRam0000000188c9041b == '\0') {
          FUN_18048bf00(0x1888d5250,0);
          FUN_18048bf00(0x18882b720);
          FUN_18048bf00(0x188954c98);
          FUN_18048bf00(0x1888cfcb0);
          FUN_18048bf00(0x188959b58);
          FUN_18048bf00(0x1889316a8);
          cRam0000000188c9041b = '\x01';
        }
        uStack_50 = 0;
        uStack_48 = 0;
        lVar8 = *(longlong *)(*(longlong *)(lRam00000001888d5250 + 0xb8) + 0x410);
        if (lVar8 == 0) {
          cVar3 = FUN_18067e3a0(lVar9,0x2b);
          if (cVar3 != '\0') {
            if (*(longlong *)(lVar9 + 0x18) == 0) {
              FUN_18048c0b0();
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
            plVar6 = (longlong *)FUN_185a17960(*(longlong *)(lVar9 + 0x18),uRam000000018882b720);
            do {
              if (plVar6 == (longlong *)0x0) {
code_r0x00018066cbeb:
                FUN_18048c0b0();
                FUN_180472d50();
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
              cVar3 = FUN_180005310(0,uRam0000000188959b58);
              lVar8 = lRam00000001888cfcb0;
              if (cVar3 == '\0') {
                if (plVar6 != (longlong *)0x0) {
                  FUN_180005310(0,uRam0000000188954c98,plVar6);
                }
                FUN_18067e5b0(lVar9,0);
                return;
              }
              if (plVar6 == (longlong *)0x0) {
                FUN_18048c0b0();
                goto code_r0x00018066cbeb;
              }
              lVar1 = *plVar6;
              if (DAT_188ccc7f0 != '\0') {
                func_0x000180446d00(lVar1);
              }
              uVar11 = 0;
              if (*(ushort *)(lVar1 + 0x12e) != 0) {
                do {
                  if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar11 * 0x10) == lVar8
                     ) {
                    puVar7 = (undefined8 *)
                             (((longlong)
                               *(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar11 * 0x10)
                              + 0x14) * 0x10 + lVar1);
                    goto code_r0x00018066cb06;
                  }
                  uVar11 = uVar11 + 1;
                } while (uVar11 < *(ushort *)(lVar1 + 0x12e));
              }
              puVar7 = (undefined8 *)FUN_180445cc0(plVar6,lVar8,0);
code_r0x00018066cb06:
              puVar7 = (undefined8 *)(*(code *)*puVar7)(auStack_40,plVar6,puVar7[1]);
              uStack_50 = *puVar7;
              uStack_48 = puVar7[1];
              lVar8 = FUN_185159d80(&uStack_50,uRam00000001889316a8);
              if ((lVar8 != 0) && (cVar3 = FUN_18068edb0(lVar8,0), cVar3 == '\0')) {
                FUN_180682d50(lVar8,0);
              }
            } while( true );
          }
        }
        else {
          XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar8,lVar9,0);
        }
        return;
      }
    }
    else if (lVar9 != 0) {
      if (cRam0000000188c9041a == '\0') {
        FUN_18048bf00(0x1888d5250,0);
        FUN_18048bf00(0x18882b720);
        FUN_18048bf00(0x188954c98);
        FUN_18048bf00(0x1888cfcb0);
        FUN_18048bf00(0x188959b58);
        FUN_18048bf00(0x1889316a8);
        cRam0000000188c9041a = '\x01';
      }
      uStack_50 = 0;
      uStack_48 = 0;
      lVar8 = *(longlong *)(*(longlong *)(lRam00000001888d5250 + 0xb8) + 0x408);
      if (lVar8 != 0) {
        XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar8,lVar9,0);
        return;
      }
      if (*(longlong *)(lVar9 + 0x18) == 0) {
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      plVar6 = (longlong *)FUN_185a17960(*(longlong *)(lVar9 + 0x18),uRam000000018882b720);
      do {
        if (plVar6 == (longlong *)0x0) {
code_r0x00018066d69d:
          FUN_18048c0b0();
          FUN_180472d50();
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        cVar3 = FUN_180005310(0,uRam0000000188959b58);
        lVar8 = lRam00000001888cfcb0;
        if (cVar3 == '\0') {
          if (plVar6 != (longlong *)0x0) {
            FUN_180005310(0,uRam0000000188954c98,plVar6);
          }
          FUN_18067e5b0(lVar9,0);
          return;
        }
        if (plVar6 == (longlong *)0x0) {
          FUN_18048c0b0();
          goto code_r0x00018066d69d;
        }
        lVar1 = *plVar6;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(lVar1);
        }
        uVar11 = 0;
        if (*(ushort *)(lVar1 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar11 * 0x10) == lVar8) {
              puVar7 = (undefined8 *)
                       (((longlong)
                         *(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar11 * 0x10) + 0x14
                        ) * 0x10 + lVar1);
              goto code_r0x00018066d5b5;
            }
            uVar11 = uVar11 + 1;
          } while (uVar11 < *(ushort *)(lVar1 + 0x12e));
        }
        puVar7 = (undefined8 *)FUN_180445cc0(plVar6,lVar8,0);
code_r0x00018066d5b5:
        puVar7 = (undefined8 *)(*(code *)*puVar7)(auStack_40,plVar6,puVar7[1]);
        uStack_50 = *puVar7;
        uStack_48 = puVar7[1];
        lVar8 = FUN_185159d80(&uStack_50,uRam00000001889316a8);
        if ((lVar8 != 0) && (cVar3 = FUN_18068edb0(lVar8,0), cVar3 == '\0')) {
          FUN_180683130(lVar8,0);
        }
      } while( true );
    }
    puStack_30 = (undefined1 *)0x1806f7bca;
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  if (*(longlong *)(lVar9 + 0x18) == 0) {
    FUN_18048c0b0(lVar9,param_1,param_2,0);
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  uStack_48 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
  if (*(longlong *)(lVar9 + 0x18) != 0) {
    uVar10 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar10,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      lVar8 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
      if (lVar8 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar8,uVar10,param_1,0);
        FUN_183f22430(uVar10,param_2,0);
        iVar5 = FUN_183f22380(uVar10,2,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001833006e0:
          FUN_183f22fd0(uVar10,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar9 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar4 + -1,0);
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
