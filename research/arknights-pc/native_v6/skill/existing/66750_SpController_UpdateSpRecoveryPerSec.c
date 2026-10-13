
/* WARNING: Removing unreachable block (ram,0x000181e04805) */
/* WARNING: Removing unreachable block (ram,0x000181e04815) */
/* WARNING: Removing unreachable block (ram,0x000181e0481a) */
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SpController_UpdateSpRecoveryPerSec_0x60104bf
               (longlong param_1,undefined8 param_2,undefined8 param_3)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 unaff_RDI;
  bool bVar10;
  
  if (DAT_188c90946 == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_188874308);
    DAT_188c90946 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188874308 + 0xb8) + 0x78);
  if (lVar1 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp4704_0x6001cc0(lVar1,param_1,param_2,param_3,0);
    return;
  }
  if (*(longlong *)(param_1 + 0x40) != 0) {
    cVar4 = Torappu_PeriodicTimer_get_isValid_0x600656e(*(longlong *)(param_1 + 0x40),0);
    if (cVar4 == '\0') {
      lVar1 = *(longlong *)(param_1 + 0x40);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar7 = func_0x0001866fdad0(0x3f800000,0);
      uVar7 = Torappu_FP_op_Division_0x6000305(uVar7,param_2,0);
      if (lVar1 != 0) {
        if (cRam0000000188ca0cfe == '\0') {
          FUN_18048bf00(&DAT_18885a700,uVar7,1,0,unaff_RDI);
          FUN_18048bf00(&DAT_1888915d8);
          cRam0000000188ca0cfe = '\x01';
        }
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar8 = func_0x0001866fdac0(0,0);
        if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar7 = Torappu_TSMath_Max_0x600033b(uVar8,uVar7,0);
        bVar10 = cRam0000000188ca0cfd == '\0';
        *(undefined8 *)(lVar1 + 0x10) = uVar7;
        if (bVar10) {
          FUN_18048bf00(&DAT_18885a700);
          cRam0000000188ca0cfd = '\x01';
        }
        *(undefined8 *)(lVar1 + 0x18) = *(undefined8 *)(lVar1 + 0x10);
        return;
      }
    }
    else {
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar7 = func_0x0001866fdac0(0,0);
      SpController_OnTick_0x60104c0(param_1,uVar7,0);
      if (*(longlong *)(param_1 + 0x18) != 0) {
        cVar4 = Torappu_Battle_Entity_get_canRecoverSp_0x601036a(*(longlong *)(param_1 + 0x18),0);
        if (cVar4 == '\0') {
          if (cRam0000000188c90940 == '\0') {
            FUN_18048bf00(&DAT_188874308,0);
            cRam0000000188c90940 = '\x01';
          }
          lVar1 = *(longlong *)(*(longlong *)(_DAT_188874308 + 0xb8) + 0x48);
          if (lVar1 == 0) {
            lVar1 = *(longlong *)(param_1 + 0x40);
            if (lVar1 != 0) {
              if (cRam0000000188ca0d00 == '\0') {
                FUN_18048bf00(&DAT_18885a700);
                cRam0000000188ca0d00 = '\x01';
              }
              if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              uVar7 = func_0x0001866fdac0(0xffffffff,0);
              *(undefined8 *)(lVar1 + 0x18) = uVar7;
              *(undefined8 *)(lVar1 + 0x10) = uVar7;
              return;
            }
            FUN_18048c0b0();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          if (*(longlong *)(lVar1 + 0x18) == 0) {
            FUN_18048c0b0();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30),&stack0x00000008,0);
          if (*(longlong *)(lVar1 + 0x18) != 0) {
            uVar7 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
            iVar5 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),
                                  0);
            if (*(longlong *)(lVar1 + 0x18) != 0) {
              lVar2 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
              if (lVar2 == 0) {
                FUN_18048c0b0();
              }
              else {
                FUN_183cf8c20(lVar2,uVar7,param_1,0);
                iVar6 = FUN_183f22380(uVar7,1,0,iVar5,0);
                if (iVar6 == 0) {
code_r0x0001833100e8:
                  FUN_183f22fd0(uVar7,iVar5 + -1,0);
                  return;
                }
                if (*(longlong *)(lVar1 + 0x18) != 0) {
                  FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar5 + -1,0);
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
        lVar1 = *(longlong *)(param_1 + 0x40);
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar7 = func_0x0001866fdad0(0x3f800000,0);
        uVar7 = Torappu_FP_op_Division_0x6000305(uVar7,param_2,0);
        if (lVar1 != 0) {
          if (cRam0000000188ca0cff == '\0') {
            FUN_18048bf00(&DAT_18885a700,uVar7,0);
            FUN_18048bf00(&DAT_1888915d8);
            cRam0000000188ca0cff = '\x01';
          }
          if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          uVar8 = func_0x0001866fdac0(0,0);
          uVar9 = func_0x0001866fba10(*(undefined8 *)(lVar1 + 0x10),*(undefined8 *)(lVar1 + 0x18),0)
          ;
          uVar9 = func_0x0001866fba10(uVar7,uVar9,0);
          if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          uVar8 = Torappu_TSMath_Max_0x600033b(uVar8,uVar9,0);
          *(undefined8 *)(lVar1 + 0x10) = uVar7;
          *(undefined8 *)(lVar1 + 0x18) = uVar8;
          return;
        }
      }
    }
  }
  FUN_18048c0b0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

