
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Blackboard__ctor_0x6007856
               (undefined8 param_1,longlong *param_2,float param_3,longlong param_4,char param_5)

{
  undefined8 uVar1;
  undefined1 auVar2 [16];
  longlong lVar3;
  longlong lVar4;
  code *pcVar5;
  char cVar6;
  int iVar7;
  undefined8 *puVar8;
  undefined1 (*pauVar9) [16];
  ushort uVar10;
  int iVar12;
  float fVar13;
  undefined1 auStack_88 [16];
  undefined8 uStack_78;
  ulonglong uVar11;
  
  if (DAT_188ca4f88 == '\0') {
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_1888a3510);
    FUN_18048bf00(&DAT_1888a0cd8);
    FUN_18048bf00(&DAT_188900b50);
    FUN_18048bf00(&DAT_188860eb8);
    FUN_18048bf00(&DAT_188860c88);
    FUN_18048bf00(&DAT_188932198);
    DAT_188ca4f88 = '\x01';
  }
  if (*(int *)(_DAT_188932198 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  FUN_1848f2320(param_1,_DAT_188860c88);
  iVar12 = 0;
  if (param_2 == (longlong *)0x0) {
LAB_182321222:
    FUN_18048c0b0();
    pcVar5 = (code *)swi(3);
    (*pcVar5)();
    return;
  }
  do {
    lVar4 = _DAT_1888a3510;
    lVar3 = *param_2;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar3);
    }
    uVar11 = 0;
    if (*(ushort *)(lVar3 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar3 + 0xb0) + uVar11 * 0x10) == lVar4) {
          puVar8 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar3 + 0xb0) + 8 + uVar11 * 0x10) + 0x14) *
                    0x10 + lVar3);
          goto LAB_182321026;
        }
        uVar10 = (short)uVar11 + 1;
        uVar11 = (ulonglong)uVar10;
      } while (uVar10 < *(ushort *)(lVar3 + 0x12e));
    }
    puVar8 = (undefined8 *)FUN_180445cc0(param_2,lVar4,0);
LAB_182321026:
    iVar7 = (*(code *)*puVar8)(param_2,puVar8[1]);
    lVar3 = _DAT_188900b50;
    if (iVar7 <= iVar12) {
      lVar3 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x10);
      if (lVar3 != 0) {
        XLua_DelegateBridge___Gen_Delegate_Imp944_0x6000e10
                  (lVar3,param_1,param_2,param_3,param_4,param_5,0);
      }
      return;
    }
    lVar4 = *param_2;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar4);
    }
    uVar10 = 0;
    if (*(ushort *)(lVar4 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar4 + 0xb0) + (ulonglong)uVar10 * 0x10) == lVar3) {
          puVar8 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar4 + 0xb0) + 8 + (ulonglong)uVar10 * 0x10)
                    + 0x14) * 0x10 + lVar4);
          goto LAB_182321096;
        }
        uVar10 = uVar10 + 1;
      } while (uVar10 < *(ushort *)(lVar4 + 0x12e));
    }
    puVar8 = (undefined8 *)FUN_180445cc0(param_2,lVar3,0);
LAB_182321096:
    pauVar9 = (undefined1 (*) [16])(*(code *)*puVar8)(auStack_88,param_2,iVar12,puVar8[1]);
    auVar2 = *pauVar9;
    fVar13 = auVar2._8_4_;
    uVar1 = *(undefined8 *)pauVar9[1];
    cVar6 = func_0x000185db9d60(uVar1,0);
    if (cVar6 != '\0') {
      if (param_4 == 0) goto LAB_182321222;
      cVar6 = FUN_180005010(4,_DAT_1888a0cd8,param_4,auVar2._0_8_);
      if (cVar6 == '\0') {
        if (param_5 == '\0') {
          fVar13 = fVar13 * param_3;
        }
        else {
          fVar13 = (fVar13 - 1.0) * param_3 + 1.0;
        }
      }
    }
    if (*(int *)(_DAT_188932198 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    auStack_88._8_4_ = fVar13;
    auStack_88._0_8_ = auVar2._0_8_;
    auStack_88._12_4_ = auVar2._12_4_;
    uStack_78 = uVar1;
    FUN_180012b80(param_1,auStack_88);
    iVar12 = iVar12 + 1;
  } while( true );
}

