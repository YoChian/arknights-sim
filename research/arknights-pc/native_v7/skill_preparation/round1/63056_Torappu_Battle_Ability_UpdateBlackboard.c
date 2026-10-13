
/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Ability_UpdateBlackboard_0x600f651(longlong param_1,longlong *param_2)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong *plVar6;
  undefined8 *puVar7;
  undefined4 *puVar8;
  longlong lVar9;
  longlong lVar10;
  longlong lVar11;
  ushort uVar12;
  int iVar14;
  uint uVar15;
  longlong *plStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_90;
  longlong **pplStack_88;
  undefined *puStack_80;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined8 uStack_68;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined8 auStack_58 [2];
  undefined8 auStack_48 [2];
  ulonglong uVar13;
  
  if (DAT_188c8fce5 == '\0') {
    FUN_18048bf00(&DAT_1889733f0);
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_188827d00);
    DAT_188c8fce5 = '\x01';
  }
  lVar11 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x150);
  plVar6 = param_2;
  if (lVar11 == 0) {
    cVar3 = FUN_1844acab0(param_2,_DAT_188827d00);
    if (cVar3 != '\0') {
      return;
    }
    cVar3 = func_0x000185db9d60(*(undefined8 *)(param_1 + 0x38),0);
    if (cVar3 == '\0') {
      if (param_2 == (longlong *)0x0) goto LAB_1805d70fb;
      plVar6 = (longlong *)
               Torappu_Blackboard_GenerateBlackboardWithPrefix_0x600787b
                         (param_2,*(undefined8 *)(param_1 + 0x38),0);
    }
    else {
      plVar6 = (longlong *)func_0x00018045cfe0(_DAT_188941920);
      if (plVar6 == (longlong *)0x0) goto LAB_1805d70fb;
      Torappu_Blackboard__ctor_0x6007855(plVar6,param_2,0);
    }
    if (DAT_188c8fcc1 == '\0') {
      FUN_18048bf00(&DAT_1889733f0);
      DAT_188c8fcc1 = '\x01';
    }
    lVar11 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x30);
    if (lVar11 == 0) {
      lVar11 = *(longlong *)(param_1 + 0x88);
    }
    else {
      lVar11 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar11,param_1,0);
    }
    if (lVar11 == 0) {
      Torappu_Battle_Ability_set_blackboard_0x600f62b(param_1,plVar6,0);
      return;
    }
    param_1 = Torappu_Battle_Ability_get_blackboard_0x600f62a(param_1,0);
    if (param_1 == 0) {
LAB_1805d70fb:
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    if (cRam0000000188ca4f8b == '\0') {
      FUN_18048bf00(&DAT_188941920);
      FUN_18048bf00(0x1888a3510);
      FUN_18048bf00(0x188900b50);
      FUN_18048bf00(0x1888610f0);
      FUN_18048bf00(0x188861e28);
      cRam0000000188ca4f8b = '\x01';
    }
    lVar9 = lRam00000001888610f0;
    lVar11 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x28);
    if (lVar11 == 0) {
      if (plVar6 != (longlong *)0x0) {
        if (*(int *)(param_1 + 0x18) == 0) {
          uVar15 = *(uint *)(param_1 + 0x18);
          if (*(longlong *)
               (*(longlong *)
                 (*(longlong *)(*(longlong *)(lRam00000001888610f0 + 0x20) + 0xc0) + 0x78) + 0x20)
              == 0) {
            (*(code *)**(undefined8 **)
                        (*(longlong *)(*(longlong *)(lRam00000001888610f0 + 0x20) + 0xc0) + 0x78))()
            ;
          }
          lVar11 = *(longlong *)(*(longlong *)(*(longlong *)(lVar9 + 0x20) + 0xc0) + 0x78);
          if (cRam0000000188cbaec8 == '\0') {
            FUN_18048bf00(0x188954c98);
            FUN_18048bf00(0x188959b58);
            cRam0000000188cbaec8 = '\x01';
          }
          plStack_a8 = (longlong *)0x0;
          if (plVar6 == (longlong *)0x0) {
            FUN_185ed6160(6,0);
          }
          if (*(uint *)(param_1 + 0x18) < uVar15) {
            FUN_185ed63b0(0);
          }
          lVar9 = *(longlong *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x10);
          if ((*(byte *)(lVar9 + 0x136) & 1) == 0) {
            lVar9 = FUN_1804463f0(lVar9);
          }
          lVar9 = func_0x00018048b9f0(plVar6,lVar9);
          if (lVar9 == 0) {
            if ((int)uVar15 < *(int *)(param_1 + 0x18)) {
              if (plVar6 == (longlong *)0x0) {
                FUN_18048c0b0();
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
              lVar9 = *(longlong *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x138);
              if ((*(byte *)(lVar9 + 0x136) & 1) == 0) {
                lVar9 = FUN_1804463f0(lVar9);
              }
              plStack_a8 = (longlong *)FUN_180005310(0,lVar9,plVar6);
              uStack_90 = 0;
              pplStack_88 = &plStack_a8;
              do {
                if (plStack_a8 == (longlong *)0x0) {
code_r0x000184e3ac13:
                  FUN_18048c0b0();
                  FUN_180472d50();
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
                cVar3 = FUN_180005310(0,uRam0000000188959b58);
                plVar6 = plStack_a8;
                if (cVar3 == '\0') {
                  if (plStack_a8 != (longlong *)0x0) {
                    FUN_180005310(0,uRam0000000188954c98,plStack_a8);
                  }
                  goto code_r0x000184e3abf6;
                }
                if (plStack_a8 == (longlong *)0x0) {
                  FUN_18048c0b0();
                  goto code_r0x000184e3ac13;
                }
                lVar9 = *(longlong *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x148);
                if ((*(byte *)(lVar9 + 0x136) & 1) == 0) {
                  lVar9 = FUN_1804463f0(lVar9);
                }
                lVar10 = *plVar6;
                if (DAT_188ccc7f0 != '\0') {
                  func_0x000180446d00(lVar10);
                }
                uVar12 = 0;
                if (*(ushort *)(lVar10 + 0x12e) != 0) {
                  do {
                    if (*(longlong *)(*(longlong *)(lVar10 + 0xb0) + (ulonglong)uVar12 * 0x10) ==
                        lVar9) {
                      puVar7 = (undefined8 *)
                               (((longlong)
                                 *(int *)(*(longlong *)(lVar10 + 0xb0) + 8 +
                                         (ulonglong)uVar12 * 0x10) + 0x14) * 0x10 + lVar10);
                      goto code_r0x000184e3a979;
                    }
                    uVar12 = uVar12 + 1;
                  } while (uVar12 < *(ushort *)(lVar10 + 0x12e));
                }
                puVar7 = (undefined8 *)FUN_180445cc0(plVar6,lVar9,0);
code_r0x000184e3a979:
                puVar8 = (undefined4 *)(*(code *)*puVar7)(auStack_58,plVar6,puVar7[1]);
                uStack_78 = *puVar8;
                uStack_74 = puVar8[1];
                uStack_70 = puVar8[2];
                uStack_6c = puVar8[3];
                uStack_a0 = *(undefined8 *)(puVar8 + 4);
                if (*(longlong *)
                     (*(longlong *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x130) +
                     0x20) == 0) {
                  (*(code *)**(undefined8 **)
                              (*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x130))();
                }
                uStack_68 = uStack_a0;
                FUN_180121e30(param_1,uVar15,&uStack_78,
                              *(undefined8 *)
                               (*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x130));
                uVar15 = uVar15 + 1;
              } while( true );
            }
            if (*(longlong *)
                 (*(longlong *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x28) + 0x20)
                == 0) {
              (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x28)
              )();
            }
            FUN_184e363a0(param_1,plVar6,
                          *(undefined8 *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x28)
                         );
          }
          else {
            lVar10 = *(longlong *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x10);
            if ((*(byte *)(lVar10 + 0x136) & 1) == 0) {
              lVar10 = FUN_1804463f0(lVar10);
            }
            iVar14 = FUN_180005310(0,lVar10,lVar9);
            if (0 < iVar14) {
              iVar4 = *(int *)(param_1 + 0x18);
              if (*(longlong *)
                   (*(longlong *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x60) + 0x20)
                  == 0) {
                (*(code *)**(undefined8 **)
                            (*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x60))();
              }
              FUN_180121740(param_1,iVar4 + iVar14,
                            *(undefined8 *)
                             (*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x60));
              if ((int)uVar15 < *(int *)(param_1 + 0x18)) {
                FUN_185eea240(*(undefined8 *)(param_1 + 0x10),uVar15,*(undefined8 *)(param_1 + 0x10)
                              ,iVar14 + uVar15,*(int *)(param_1 + 0x18) - uVar15,0);
              }
              uVar1 = *(undefined8 *)(param_1 + 0x10);
              if (param_1 == lVar9) {
                FUN_185eea240(uVar1,0,uVar1,uVar15,uVar15,0);
                FUN_185eea240(*(undefined8 *)(param_1 + 0x10),iVar14 + uVar15,
                              *(undefined8 *)(param_1 + 0x10),uVar15 * 2,
                              *(int *)(param_1 + 0x18) - uVar15,0);
              }
              else {
                lVar11 = *(longlong *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x10);
                if ((*(byte *)(lVar11 + 0x136) & 1) == 0) {
                  lVar11 = FUN_1804463f0(lVar11);
                }
                FUN_18000f460(5,lVar11,lVar9,uVar1,uVar15);
              }
              *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + iVar14;
            }
          }
code_r0x000184e3abf6:
          *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
          return;
        }
        iVar14 = 0;
code_r0x00018231e230:
        lVar9 = lRam00000001888a3510;
        lVar11 = *plVar6;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(lVar11);
        }
        uVar13 = 0;
        if (*(ushort *)(lVar11 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar11 + 0xb0) + uVar13 * 0x10) == lVar9) {
              puVar7 = (undefined8 *)
                       (((longlong)*(int *)(*(longlong *)(lVar11 + 0xb0) + 8 + uVar13 * 0x10) + 0x14
                        ) * 0x10 + lVar11);
              goto code_r0x00018231e296;
            }
            uVar12 = (short)uVar13 + 1;
            uVar13 = (ulonglong)uVar12;
          } while (uVar12 < *(ushort *)(lVar11 + 0x12e));
        }
        puVar7 = (undefined8 *)FUN_180445cc0(plVar6,lVar9,0);
code_r0x00018231e296:
        iVar4 = (*(code *)*puVar7)(plVar6,puVar7[1]);
        lVar11 = lRam0000000188900b50;
        if (iVar14 < iVar4) {
          lVar9 = *plVar6;
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(lVar9);
          }
          uVar12 = 0;
          if (*(ushort *)(lVar9 + 0x12e) != 0) {
            do {
              if (*(longlong *)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar12 * 0x10) == lVar11) {
                puVar7 = (undefined8 *)
                         (((longlong)
                           *(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar12 * 0x10) +
                          0x14) * 0x10 + lVar9);
                goto code_r0x00018231e306;
              }
              uVar12 = uVar12 + 1;
            } while (uVar12 < *(ushort *)(lVar9 + 0x12e));
          }
          puVar7 = (undefined8 *)FUN_180445cc0(plVar6,lVar11,0);
code_r0x00018231e306:
          puVar8 = (undefined4 *)(*(code *)*puVar7)(auStack_48,plVar6,iVar14,puVar7[1]);
          uStack_78 = *puVar8;
          uStack_74 = puVar8[1];
          uStack_70 = puVar8[2];
          uStack_6c = puVar8[3];
          pplStack_88 = *(longlong ***)(puVar8 + 4);
          if (cRam0000000188ca4f91 == '\0') {
            FUN_18048bf00(&DAT_188941920);
            FUN_18048bf00(0x188860eb8);
            FUN_18048bf00(0x188861e28);
            FUN_18048bf00(0x188862058);
            FUN_18048bf00(0x188862290);
            cRam0000000188ca4f91 = '\x01';
          }
          lVar11 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x58);
          if (lVar11 == 0) {
            iVar4 = 0;
            if (0 < *(int *)(param_1 + 0x18)) {
              uVar1 = CONCAT44(uStack_74,uStack_78);
              do {
                FUN_184ad2e80(&uStack_68,param_1,iVar4,uRam0000000188862058);
                iVar5 = func_0x000185db2fa0(uStack_68,uVar1,1,0);
                if (iVar5 == 0) {
                  uStack_68 = CONCAT44(uStack_74,uStack_78);
                  uStack_60 = uStack_70;
                  uStack_5c = uStack_6c;
                  auStack_58[0] = pplStack_88;
                  FUN_184ad3170(param_1,iVar4,&uStack_68,uRam0000000188862290);
                  iVar14 = iVar14 + 1;
                  goto code_r0x00018231e230;
                }
                iVar4 = iVar4 + 1;
              } while (iVar4 < *(int *)(param_1 + 0x18));
            }
            uStack_68 = CONCAT44(uStack_74,uStack_78);
            uStack_60 = uStack_70;
            uStack_5c = uStack_6c;
            auStack_58[0] = pplStack_88;
            FUN_180012b80(param_1,&uStack_68);
            iVar14 = iVar14 + 1;
          }
          else {
            uStack_68 = CONCAT44(uStack_74,uStack_78);
            uStack_60 = uStack_70;
            uStack_5c = uStack_6c;
            auStack_58[0] = pplStack_88;
            FUN_1836faef0(lVar11,param_1,&uStack_68,0);
            iVar14 = iVar14 + 1;
          }
          goto code_r0x00018231e230;
        }
      }
      return;
    }
  }
  if (*(longlong *)(lVar11 + 0x18) == 0) {
    puStack_80 = &UNK_1832d239f;
    FUN_18048c0b0(lVar11,param_1,plVar6,0);
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar11 + 0x18) + 0x30);
  puStack_80 = &UNK_1832d2284;
  FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
  if (*(longlong *)(lVar11 + 0x18) != 0) {
    uVar1 = *(undefined8 *)(*(longlong *)(lVar11 + 0x18) + 0x10);
    puStack_80 = &UNK_1832d22a7;
    iVar14 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar11 + 0x38),*(undefined4 *)(lVar11 + 0x14),0);
    if (*(longlong *)(lVar11 + 0x18) != 0) {
      lVar9 = *(longlong *)(*(longlong *)(lVar11 + 0x18) + 0x20);
      if (lVar9 == 0) {
        puStack_80 = &UNK_1832d2383;
        FUN_18048c0b0();
      }
      else {
        puStack_80 = &UNK_1832d22d5;
        FUN_183cf8c20(lVar9,uVar1,param_1,0);
        puStack_80 = &UNK_1832d22e6;
        FUN_183cf8c20(lVar9,uVar1,plVar6,0);
        auStack_58[0] = (longlong **)0x0;
        puStack_80 = &UNK_1832d2302;
        iVar4 = FUN_183f22380(uVar1,2,0,iVar14);
        if (iVar4 == 0) {
code_r0x0001832d231b:
          puStack_80 = &UNK_1832d232a;
          FUN_183f22fd0(uVar1,iVar14 + -1,0);
          return;
        }
        if (*(longlong *)(lVar11 + 0x18) != 0) {
          puStack_80 = &UNK_1832d231b;
          FUN_183e0d130(*(longlong *)(lVar11 + 0x18),iVar14 + -1,0);
          goto code_r0x0001832d231b;
        }
      }
      puStack_80 = &UNK_1832d2389;
      FUN_18048c0b0();
    }
    puStack_80 = &UNK_1832d238e;
    FUN_18048c0b0();
  }
  puStack_80 = &UNK_1832d2393;
  FUN_18048c0b0();
  puStack_80 = &UNK_1832d2399;
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

