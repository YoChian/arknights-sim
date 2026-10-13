
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Entity_OnBorn_0x6010458(longlong *param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  code *pcVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  longlong *plVar8;
  undefined8 *puVar9;
  longlong lVar10;
  longlong lVar11;
  ushort uVar12;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined1 auStack_40 [16];
  undefined8 uStack_30;
  
  if (DAT_188c908e7 == '\0') {
    uStack_30 = 0x1806f7e0e;
    FUN_18048bf00(&DAT_188841368);
    DAT_188c908e7 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    uStack_30 = 0x1806f7e2d;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar11 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x8d8);
  if (lVar11 == 0) {
    lVar11 = param_1[7];
    if (DAT_188ccc7f0 != '\0') {
      uStack_30 = 0x1806f7e60;
      func_0x000180446d00(*param_1);
    }
    uStack_30 = 0x1806f7e76;
    uVar5 = (**(code **)(*param_1 + 0x5a0))(param_1,*(undefined8 *)(*param_1 + 0x5a8));
    if (lVar11 != 0) {
      uStack_30 = 0x1806f7e88;
      Torappu_StateMachine_Start_0x60081f9(lVar11,uVar5,0);
      uStack_30 = 0x1806f7e95;
      Torappu_Battle_Entity_EmitEvent_0x601049c(param_1,0,0);
      uStack_30 = 0x1806f7e9f;
      lVar11 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
      if (lVar11 != 0) {
        if (cRam0000000188c903dd == '\0') {
          FUN_18048bf00(0x1888d5250,0);
          FUN_18048bf00(0x18882b720);
          FUN_18048bf00(0x188954c98);
          FUN_18048bf00(0x1888cfcb0);
          FUN_18048bf00(0x188959b58);
          FUN_18048bf00(0x1889316a8);
          cRam0000000188c903dd = '\x01';
        }
        uStack_50 = 0;
        uStack_48 = 0;
        lVar10 = *(longlong *)(*(longlong *)(lRam00000001888d5250 + 0xb8) + 0x220);
        if (lVar10 != 0) {
          XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar10,lVar11,0);
          return;
        }
        if (*(longlong *)(lVar11 + 0x18) == 0) {
          FUN_18048c0b0();
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        plVar8 = (longlong *)FUN_185a17960(*(longlong *)(lVar11 + 0x18),uRam000000018882b720);
        do {
          if (plVar8 == (longlong *)0x0) {
code_r0x000180675b2d:
            FUN_18048c0b0();
            FUN_180472d50();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          cVar4 = FUN_180005310(0,uRam0000000188959b58);
          lVar10 = lRam00000001888cfcb0;
          if (cVar4 == '\0') {
            if (plVar8 != (longlong *)0x0) {
              FUN_180005310(0,uRam0000000188954c98,plVar8);
            }
            FUN_18067e5b0(lVar11,0);
            return;
          }
          if (plVar8 == (longlong *)0x0) {
            FUN_18048c0b0();
            goto code_r0x000180675b2d;
          }
          lVar1 = *plVar8;
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(lVar1);
          }
          uVar12 = 0;
          if (*(ushort *)(lVar1 + 0x12e) != 0) {
            do {
              if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar12 * 0x10) == lVar10) {
                puVar9 = (undefined8 *)
                         (((longlong)
                           *(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar12 * 0x10) +
                          0x14) * 0x10 + lVar1);
                goto code_r0x000180675a45;
              }
              uVar12 = uVar12 + 1;
            } while (uVar12 < *(ushort *)(lVar1 + 0x12e));
          }
          puVar9 = (undefined8 *)FUN_180445cc0(plVar8,lVar10,0);
code_r0x000180675a45:
          puVar9 = (undefined8 *)(*(code *)*puVar9)(auStack_40,plVar8,puVar9[1]);
          uStack_50 = *puVar9;
          uStack_48 = puVar9[1];
          lVar10 = FUN_185159d80(&uStack_50,uRam00000001889316a8);
          if ((lVar10 != 0) && (cVar4 = FUN_18068edb0(lVar10,0), cVar4 == '\0')) {
            FUN_1806860a0(lVar10,0);
          }
        } while( true );
      }
    }
    uStack_30 = 0x1806f7ecd;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  if (*(longlong *)(lVar11 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uStack_30 = 0;
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar11 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar11 + 0x18) != 0) {
    uVar2 = *(undefined8 *)(*(longlong *)(lVar11 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar11 + 0x38),*(undefined4 *)(lVar11 + 0x14),0);
    if (*(longlong *)(lVar11 + 0x18) != 0) {
      lVar10 = *(longlong *)(*(longlong *)(lVar11 + 0x18) + 0x20);
      if (lVar10 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar10,uVar2,param_1,0);
        uStack_48 = 0;
        iVar7 = FUN_183f22380(uVar2,1,0,iVar6);
        if (iVar7 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar2,iVar6 + -1,0);
          return;
        }
        if (*(longlong *)(lVar11 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar11 + 0x18),iVar6 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

