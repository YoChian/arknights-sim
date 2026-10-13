/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8 * Torappu_Battle_Buff_OnTakeDamage_0x600fe94(undefined8 param_1,undefined8 *param_2)
{
  ulonglong *puVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 *puVar19;
  longlong lVar20;
  uint uVar21;
  bool bVar22;
  undefined1 auStack_f8 [240];
  if (DAT_188c90319 == '\0') {
    FUN_18048bf00(&DAT_18895c250);
    DAT_188c90319 = '\x01';
  }
  if (*(int *)(_DAT_18895c250 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18895c250);
  }
  lVar20 = *(longlong *)(*(longlong *)(_DAT_18895c250 + 0xb8) + 0x3d8);
  if (lVar20 == 0) {
    puVar19 = (undefined8 *)Torappu_Battle_Buff__IsActionValid_0x600fe58(param_1,10,0);
    if ((char)puVar19 != '\0') {
      lVar20 = Torappu_Battle_Buff__RunActions_0x600fee4(auStack_f8,param_1,10,1,0);
      uVar3 = *(undefined8 *)(lVar20 + 0x28);
      uVar4 = *(undefined8 *)(lVar20 + 0x30);
      uVar5 = *(undefined8 *)(lVar20 + 0x38);
      uVar6 = *(undefined8 *)(lVar20 + 0x40);
      uVar7 = *(undefined8 *)(lVar20 + 0x48);
      uVar8 = *(undefined8 *)(lVar20 + 0x50);
      uVar9 = *(undefined8 *)(lVar20 + 0x58);
      uVar10 = *(undefined8 *)(lVar20 + 0x60);
      uVar11 = *(undefined8 *)(lVar20 + 0x68);
      uVar12 = *(undefined8 *)(lVar20 + 0x70);
      uVar13 = *(undefined8 *)(lVar20 + 0x78);
      puVar19 = (undefined8 *)(lVar20 + 0x80);
      uVar14 = *puVar19;
      uVar15 = *(undefined8 *)(lVar20 + 0x88);
      uVar16 = *(undefined8 *)(lVar20 + 0x90);
      uVar17 = *(undefined8 *)(lVar20 + 0x98);
      uVar18 = *(undefined8 *)(lVar20 + 0xa0);
      *param_2 = *(undefined8 *)(lVar20 + 0x20);
      param_2[1] = uVar3;
      param_2[2] = uVar4;
      param_2[3] = uVar5;
      param_2[4] = uVar6;
      param_2[5] = uVar7;
      param_2[6] = uVar8;
      param_2[7] = uVar9;
      param_2[8] = uVar10;
      param_2[9] = uVar11;
      param_2[10] = uVar12;
      param_2[0xb] = uVar13;
      param_2[0xc] = uVar14;
      param_2[0xd] = uVar15;
      param_2[0xe] = uVar16;
      param_2[0xf] = uVar17;
      param_2[0x10] = uVar18;
      if (iRam0000000188cccdd8 != 0) {
        uVar21 = (uint)((ulonglong)param_2 >> 0xc);
        puVar1 = (ulonglong *)((ulonglong)((uVar21 & 0x1fffff) >> 6) * 8 + 0x188d15560);
        do {
          puVar2 = (undefined8 *)*puVar1;
          LOCK();
          puVar19 = (undefined8 *)*puVar1;
          bVar22 = puVar2 == puVar19;
          if (bVar22) {
            *puVar1 = (ulonglong)puVar2 | 1L << (uVar21 & 0x3f);
            puVar19 = puVar2;
          }
          UNLOCK();
        } while (!bVar22);
      }
      return puVar19;
    }
  }
  else {
    puVar19 = (undefined8 *)
              XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar20,param_1,param_2,0);
  }
  return puVar19;
}
