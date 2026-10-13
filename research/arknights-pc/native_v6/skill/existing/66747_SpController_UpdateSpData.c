
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SpController_UpdateSpData_0x60104bc(longlong param_1,longlong param_2,char param_3)

{
  undefined4 uVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  
  if (DAT_188c90943 == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_188874308);
    DAT_188c90943 = '\x01';
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_188874308 + 0xb8) + 0x60);
  if (lVar2 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp265_0x6000b69(lVar2,param_1,param_2,param_3,0);
    return;
  }
  if (param_2 != 0) {
    uVar1 = *(undefined4 *)(param_2 + 0x44);
    uVar5 = *(undefined4 *)(param_2 + 0x38);
    uVar6 = *(undefined4 *)(param_2 + 0x3c);
    uVar7 = *(undefined4 *)(param_2 + 0x40);
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_2 + 0x34);
    *(undefined4 *)(param_1 + 0x24) = uVar5;
    *(undefined4 *)(param_1 + 0x28) = uVar6;
    *(undefined4 *)(param_1 + 0x2c) = uVar7;
    *(undefined4 *)(param_1 + 0x30) = uVar1;
    if (param_3 != '\0') {
      return;
    }
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_2 + 0x10);
    uVar11 = Torappu_SpData_get_incrementsForAllSpTypes_0x6008054(param_2,0);
    if (*(longlong *)(param_1 + 0x38) != 0) {
      System_Array_Copy_0x6000ea3
                (uVar11,*(undefined8 *)(param_1 + 0x38),
                 *(undefined4 *)(*(longlong *)(param_1 + 0x38) + 0x18),0);
      if (*(longlong *)(param_1 + 0x18) != 0) {
        cVar8 = Torappu_Battle_Entity_get_canRecoverSp_0x601036a(*(longlong *)(param_1 + 0x18),0);
        if (cVar8 == '\0') {
          if (cRam0000000188c90940 == '\0') {
            FUN_18048bf00(&DAT_188874308,0);
            cRam0000000188c90940 = '\x01';
          }
          lVar2 = *(longlong *)(*(longlong *)(_DAT_188874308 + 0xb8) + 0x48);
          if (lVar2 == 0) {
            lVar2 = *(longlong *)(param_1 + 0x40);
            if (lVar2 != 0) {
              if (cRam0000000188ca0d00 == '\0') {
                FUN_18048bf00(&DAT_18885a700);
                cRam0000000188ca0d00 = '\x01';
              }
              if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              uVar11 = func_0x0001866fdac0(0xffffffff,0);
              *(undefined8 *)(lVar2 + 0x18) = uVar11;
              *(undefined8 *)(lVar2 + 0x10) = uVar11;
              return;
            }
            FUN_18048c0b0();
            pcVar4 = (code *)swi(3);
            (*pcVar4)();
            return;
          }
          if (*(longlong *)(lVar2 + 0x18) == 0) {
            FUN_18048c0b0();
            pcVar4 = (code *)swi(3);
            (*pcVar4)();
            return;
          }
          FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar2 + 0x18) + 0x30),&stack0x00000008,0);
          if (*(longlong *)(lVar2 + 0x18) != 0) {
            uVar11 = *(undefined8 *)(*(longlong *)(lVar2 + 0x18) + 0x10);
            iVar9 = FUN_183f23b70(uVar11,*(undefined4 *)(lVar2 + 0x38),*(undefined4 *)(lVar2 + 0x14)
                                  ,0);
            if (*(longlong *)(lVar2 + 0x18) != 0) {
              lVar3 = *(longlong *)(*(longlong *)(lVar2 + 0x18) + 0x20);
              if (lVar3 == 0) {
                FUN_18048c0b0();
              }
              else {
                FUN_183cf8c20(lVar3,uVar11,param_1,0);
                iVar10 = FUN_183f22380(uVar11,1,0,iVar9,0);
                if (iVar10 == 0) {
code_r0x0001833100e8:
                  FUN_183f22fd0(uVar11,iVar9 + -1,0);
                  return;
                }
                if (*(longlong *)(lVar2 + 0x18) != 0) {
                  FUN_183e0d130(*(longlong *)(lVar2 + 0x18),iVar9 + -1,0);
                  goto code_r0x0001833100e8;
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
        lVar2 = *(longlong *)(param_1 + 0x40);
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140(_DAT_18885a700);
        }
        uVar11 = *(undefined8 *)(*(longlong *)(_DAT_18885a700 + 0xb8) + 0x20);
        if (*(longlong *)(param_1 + 0x18) != 0) {
          uVar12 = Torappu_Battle_Entity_get_spRecoveryPerSec_0x60103ae
                             (*(longlong *)(param_1 + 0x18),0);
          uVar11 = Torappu_FP_op_Division_0x6000305(uVar11,uVar12,0);
          if (lVar2 != 0) {
            if (cRam0000000188ca0cff == '\0') {
              FUN_18048bf00(&DAT_18885a700,uVar11,0);
              FUN_18048bf00(&DAT_1888915d8);
              cRam0000000188ca0cff = '\x01';
            }
            if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            uVar12 = func_0x0001866fdac0(0,0);
            uVar13 = func_0x0001866fba10(*(undefined8 *)(lVar2 + 0x10),*(undefined8 *)(lVar2 + 0x18)
                                         ,0);
            uVar13 = func_0x0001866fba10(uVar11,uVar13,0);
            if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            uVar12 = Torappu_TSMath_Max_0x600033b(uVar12,uVar13,0);
            *(undefined8 *)(lVar2 + 0x10) = uVar11;
            *(undefined8 *)(lVar2 + 0x18) = uVar12;
            return;
          }
        }
      }
    }
  }
  FUN_18048c0b0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

