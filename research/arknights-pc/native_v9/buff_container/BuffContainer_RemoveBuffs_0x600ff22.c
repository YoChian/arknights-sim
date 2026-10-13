
/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BuffContainer_RemoveBuffs_0x600ff22(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  longlong lVar2;
  undefined8 uVar3;
  code *pcVar4;
  char cVar5;
  ushort uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined8 *puVar9;
  ushort uVar10;
  int iVar11;
  longlong lStackX_20;
  
  if (DAT_188c903a4 == '\0') {
    FUN_18048bf00(&DAT_1888d5250);
    FUN_18048bf00(&DAT_1888a29e0);
    FUN_18048bf00(&DAT_1888ff290);
    DAT_188c903a4 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x58);
  if (lVar1 == 0) {
    iVar11 = 0;
    if (param_2 == (longlong *)0x0) {
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
LAB_18067b490:
    do {
      lVar2 = _DAT_1888a29e0;
      lVar1 = *param_2;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(lVar1);
      }
      uVar6 = 0;
      if (*(ushort *)(lVar1 + 0x12e) != 0) {
        uVar10 = uVar6;
        do {
          if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar10 * 0x10) == lVar2) {
            puVar9 = (undefined8 *)
                     (((longlong)
                       *(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar10 * 0x10) + 0x14)
                      * 0x10 + lVar1);
            goto LAB_18067b4f6;
          }
          uVar10 = uVar10 + 1;
        } while (uVar10 < *(ushort *)(lVar1 + 0x12e));
      }
      puVar9 = (undefined8 *)FUN_180445cc0(param_2,lVar2,0);
LAB_18067b4f6:
      iVar7 = (*(code *)*puVar9)(param_2,puVar9[1]);
      lVar1 = _DAT_1888ff290;
      if (iVar7 <= iVar11) {
        return;
      }
      lVar2 = *param_2;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(lVar2);
      }
      if (*(ushort *)(lVar2 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar2 + 0xb0) + (ulonglong)uVar6 * 0x10) == lVar1) {
            puVar9 = (undefined8 *)
                     (((longlong)*(int *)(*(longlong *)(lVar2 + 0xb0) + 8 + (ulonglong)uVar6 * 0x10)
                      + 0x14) * 0x10 + lVar2);
            goto LAB_18067b566;
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < *(ushort *)(lVar2 + 0x12e));
      }
      puVar9 = (undefined8 *)FUN_180445cc0(param_2,lVar1,0);
LAB_18067b566:
      uVar8 = (*(code *)*puVar9)(param_2,iVar11,puVar9[1]);
      if (DAT_188c903a3 == '\0') {
        FUN_18048bf00(&DAT_1888d5250);
        FUN_18048bf00(&DAT_188944048);
        DAT_188c903a3 = '\x01';
      }
      lStackX_20 = 0;
      lVar1 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x50);
      if (lVar1 == 0) {
        if (*(longlong *)(param_1 + 0x28) == 0) {
LAB_18067b688:
          FUN_18048c0b0();
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
        cVar5 = FUN_1859851e0(*(longlong *)(param_1 + 0x28),uVar8,&lStackX_20,_DAT_188944048);
        if (cVar5 != '\0') {
          if (lStackX_20 == 0) goto LAB_18067b688;
          Torappu_Battle_Buff_MarkFinish_0x600fe62(lStackX_20,1);
          iVar11 = iVar11 + 1;
          goto LAB_18067b490;
        }
      }
      else {
        XLua_DelegateBridge___Gen_Delegate_Imp299_0x6000b8b(lVar1,param_1,uVar8,0);
      }
      iVar11 = iVar11 + 1;
    } while( true );
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar3 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar11 = FUN_183f23b70(uVar3,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar3,param_1,0);
        FUN_183cf8c20(lVar2,uVar3,param_2,0);
        iVar7 = FUN_183f22380(uVar3,2,0,iVar11,0);
        if (iVar7 == 0) {
code_r0x0001832d231b:
          FUN_183f22fd0(uVar3,iVar11 + -1,0);
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar11 + -1,0);
          goto code_r0x0001832d231b;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

