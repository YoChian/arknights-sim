
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Blackboard_AssignValueStrByPrefix_0x600787d
               (undefined8 param_1,longlong *param_2,longlong param_3)

{
  longlong lVar1;
  code *pcVar2;
  undefined8 uVar3;
  char cVar4;
  ushort uVar5;
  int iVar6;
  undefined8 *puVar7;
  undefined4 *puVar8;
  longlong lVar9;
  ushort uVar10;
  int iVar11;
  undefined8 *in_stack_ffffffffffffff58;
  undefined4 uVar12;
  undefined8 uStack_98;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined8 uStack_80;
  undefined8 uStack_68;
  undefined1 auStack_60 [16];
  undefined8 uStack_50;
  undefined1 auStack_48 [32];
  
  if (DAT_188ca4fad == '\0') {
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_1888a3510);
    FUN_18048bf00(&DAT_188900b50);
    DAT_188ca4fad = '\x01';
  }
  iVar11 = 0;
  uStack_98 = 0;
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x148);
  if (lVar9 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp36_0x6000a84(lVar9,param_1,param_2,param_3,0);
    return;
  }
  if (param_2 == (longlong *)0x0) {
    return;
  }
LAB_18231ddc1:
  do {
    lVar1 = _DAT_1888a3510;
    lVar9 = *param_2;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar9);
    }
    uVar5 = 0;
    if (*(ushort *)(lVar9 + 0x12e) != 0) {
      uVar10 = uVar5;
      do {
        if (*(longlong *)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar10 * 0x10) == lVar1) {
          puVar7 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar10 * 0x10)
                    + 0x14) * 0x10 + lVar9);
          goto LAB_18231de26;
        }
        uVar10 = uVar10 + 1;
      } while (uVar10 < *(ushort *)(lVar9 + 0x12e));
    }
    puVar7 = (undefined8 *)FUN_180445cc0(param_2,lVar1,0);
LAB_18231de26:
    iVar6 = (*(code *)*puVar7)(param_2,puVar7[1]);
    lVar9 = _DAT_188900b50;
    if (iVar6 <= iVar11) {
      return;
    }
    lVar1 = *param_2;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar1);
    }
    if (*(ushort *)(lVar1 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar5 * 0x10) == lVar9) {
          puVar7 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar5 * 0x10) +
                    0x14) * 0x10 + lVar1);
          goto LAB_18231de96;
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < *(ushort *)(lVar1 + 0x12e));
    }
    puVar7 = (undefined8 *)FUN_180445cc0(param_2,lVar9,0);
LAB_18231de96:
    puVar8 = (undefined4 *)(*(code *)*puVar7)(auStack_48,param_2,iVar11,puVar7[1]);
    uStack_90 = *puVar8;
    uStack_8c = puVar8[1];
    uStack_88 = puVar8[2];
    uStack_84 = puVar8[3];
    uStack_50 = *(undefined8 *)(puVar8 + 4);
    if (DAT_188ca4fb1 == '\0') {
      FUN_18048bf00(&DAT_188941920);
      DAT_188ca4fb1 = '\x01';
    }
    lVar9 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x168);
    if (lVar9 == 0) {
      lVar9 = CONCAT44(uStack_8c,uStack_90);
      if (lVar9 == 0) goto LAB_18231e0a3;
      cVar4 = System_String_StartsWith_0x60002c3(lVar9,param_3,5,0);
      uVar12 = (undefined4)((ulonglong)in_stack_ffffffffffffff58 >> 0x20);
      if (cVar4 == '\0') {
        uStack_98 = 0;
        func_0x00018048b9e0(&uStack_98,0);
        iVar11 = iVar11 + 1;
        goto LAB_18231ddc1;
      }
      if (param_3 == 0) {
LAB_18231e0a3:
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      uStack_98 = func_0x000185dbf0a0(lVar9,*(undefined4 *)(param_3 + 0x10),0);
      func_0x00018048b9e0(&uStack_98,uStack_98);
LAB_18231dfcb:
      in_stack_ffffffffffffff58 = (undefined8 *)CONCAT44(uVar12,iVar11);
      lVar9 = FUN_18006ac50(auStack_60,0,_DAT_188900b50,param_2,in_stack_ffffffffffffff58);
      uStack_68 = *(undefined8 *)(lVar9 + 0x10);
      cVar4 = func_0x000185db9d60(uStack_68,0);
      uVar3 = uStack_98;
      if (cVar4 == '\0') {
        in_stack_ffffffffffffff58 =
             (undefined8 *)CONCAT44((int)((ulonglong)in_stack_ffffffffffffff58 >> 0x20),iVar11);
        puVar8 = (undefined4 *)
                 FUN_18006ac50(auStack_60,0,_DAT_188900b50,param_2,in_stack_ffffffffffffff58);
        uStack_90 = *puVar8;
        uStack_8c = puVar8[1];
        uStack_88 = puVar8[2];
        uStack_84 = puVar8[3];
        uStack_80 = *(undefined8 *)(puVar8 + 4);
        Torappu_Blackboard_Assign_0x600785d(param_1,uVar3,uStack_80,0);
      }
    }
    else {
      in_stack_ffffffffffffff58 = &uStack_98;
      cVar4 = XLua_DelegateBridge___Gen_Delegate_Imp79_0x6000aaf
                        (lVar9,param_1,CONCAT44(uStack_8c,uStack_90),param_3,
                         in_stack_ffffffffffffff58,0);
      uVar12 = (undefined4)((ulonglong)in_stack_ffffffffffffff58 >> 0x20);
      if (cVar4 != '\0') goto LAB_18231dfcb;
    }
    iVar11 = iVar11 + 1;
  } while( true );
}

