/* WARNING: Removing unreachable block (ram,0x0001832f4d7e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
longlong Torappu_Battle_Entity_get_maxMinusHp_0x6010391(longlong param_1)
{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  longlong lVar8;
  undefined8 uStackX_20;
  longlong alStack_58 [3];
  undefined8 uStack_40;
  undefined1 *puStack_38;
  undefined8 *puStack_30;
  if (DAT_188c90828 == '\0') {
    puStack_30 = (undefined8 *)0x1807074ce;
    FUN_18048bf00(&DAT_188841368);
    puStack_30 = (undefined8 *)0x1807074da;
    FUN_18048bf00(&DAT_18885a700);
    DAT_188c90828 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    puStack_30 = (undefined8 *)0x1807074f9;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x2d8);
  if (lVar8 == 0) {
    puStack_30 = (undefined8 *)0x180707526;
    uVar6 = Torappu_Battle_Entity_get_maxHp_0x6010397(param_1,0);
    if (DAT_188c90826 == '\0') {
      puStack_30 = (undefined8 *)0x18070753e;
      FUN_18048bf00(&DAT_188841368);
      DAT_188c90826 = '\x01';
    }
    if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
      puStack_30 = (undefined8 *)0x18070755d;
      func_0x00018048c140(_DAT_188841368);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x2c8);
    if (lVar8 == 0) {
      uVar7 = *(ulonglong *)(param_1 + 0x188);
    }
    else {
      puStack_30 = (undefined8 *)0x18070758b;
      uVar7 = XLua_DelegateBridge___Gen_Delegate_Imp2620_0x600149c(lVar8,param_1,0);
    }
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      puStack_30 = (undefined8 *)0x1807075a3;
      func_0x00018048c140();
    }
    return ((((longlong)uVar7 >> 0x20) << 0x20) + (uVar7 & 0xffffffff)) * ((longlong)uVar6 >> 0x20)
           + ((uVar7 & 0xffffffff) * (uVar6 & 0xffffffff) >> 0x20) +
           ((longlong)uVar7 >> 0x20) * (uVar6 & 0xffffffff);
  }
  if (cRam0000000188cafb95 == '\0') {
    FUN_18048bf00(0x18883f608);
    cRam0000000188cafb95 = '\x01';
  }
  alStack_58[0] = 0;
  alStack_58[1] = 0;
  if (*(longlong *)(lVar8 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832f4dd5:
    FUN_18048c0b0();
code_r0x0001832f4ddb:
    FUN_18048c0b0();
  }
  else {
    uStackX_20 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
    uStack_40 = 0;
    puStack_38 = &stack0x00000008;
    puStack_30 = &uStackX_20;
    FUN_185ca7f50(uStackX_20,&stack0x00000008,0);
    if (*(longlong *)(lVar8 + 0x18) == 0) goto code_r0x0001832f4de5;
    uVar1 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
      if (lVar2 == 0) goto code_r0x0001832f4dd5;
      FUN_183cf8c20(lVar2,uVar1,param_1,0);
      iVar5 = FUN_183f22380(uVar1,1,1,iVar4,0);
      if (iVar5 == 0) {
code_r0x0001832f4d3c:
        FUN_184565cb0(lVar2,uVar1,iVar4 + 1,alStack_58,uRam000000018883f608);
        FUN_183f22fd0(uVar1,iVar4 + -1,0);
        return alStack_58[0];
      }
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar4 + -1,0);
        goto code_r0x0001832f4d3c;
      }
      goto code_r0x0001832f4ddb;
    }
  }
  FUN_18048c0b0();
code_r0x0001832f4de5:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  lVar8 = (*pcVar3)();
  return lVar8;
}
