
/* WARNING: Removing unreachable block (ram,0x00018324ea09) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong * Torappu_Battle_Character_ConstructStateMachine_0x6012903(undefined8 param_1)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  longlong *unaff_RSI;
  bool bVar10;
  
  if (DAT_188c9263c == '\0') {
    FUN_18048bf00(&DAT_18886c268);
    DAT_188c9263c = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18886c268);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x6d0);
  if (lVar6 == 0) {
    if (cRam0000000188c92770 == '\0') {
      FUN_18048bf00(0x188876b48,0);
      FUN_18048bf00(0x188876fc0);
      FUN_18048bf00(0x1888771f8);
      FUN_18048bf00(0x188877438);
      FUN_18048bf00(0x188877670);
      FUN_18048bf00(0x1888778b0);
      FUN_18048bf00(0x188877ae8);
      FUN_18048bf00(0x188877d28);
      FUN_18048bf00(0x188877f60);
      FUN_18048bf00(0x1888781a0);
      FUN_18048bf00(0x18889b3b8);
      FUN_18048bf00(0x18889b178);
      FUN_18048bf00(0x188895148);
      FUN_18048bf00(0x1888783d8);
      FUN_18048bf00(0x188878618);
      FUN_18048bf00(0x188878850);
      FUN_18048bf00(0x188878cc8);
      cRam0000000188c92770 = '\x01';
    }
    lVar6 = func_0x00018045cfe0(uRam0000000188876fc0);
    if (lVar6 != 0) {
      func_0x00018050cf60(lVar6,0);
      *(undefined8 *)(lVar6 + 0x10) = param_1;
      func_0x00018048b9e0(lVar6 + 0x10,param_1);
      plVar7 = (longlong *)func_0x00018045cfe0(uRam0000000188895148);
      if (plVar7 != (longlong *)0x0) {
        FUN_18499ca10(plVar7,param_1,lVar6,uRam000000018889b178);
        lVar6 = func_0x00018045cfe0(lRam00000001888771f8);
        if (lVar6 != 0) {
          if (cRam0000000188c92777 == '\0') {
            FUN_18048bf00(0x1888771f8);
            FUN_18048bf00(&DAT_18885a700);
            cRam0000000188c92777 = '\x01';
          }
          if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          uVar8 = func_0x0001866fdac0(0,0);
          bVar10 = cRam0000000188c92772 == '\0';
          *(undefined8 *)(lVar6 + 0x18) = uVar8;
          if (bVar10) {
            FUN_18048bf00(0x188876d80);
            FUN_18048bf00(0x1889562a0);
            cRam0000000188c92772 = '\x01';
          }
          func_0x00018050fcc0(lVar6,uRam00000001889562a0);
          lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
          if (lVar1 != 0) {
            XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
          }
          lVar1 = *(longlong *)(*(longlong *)(lRam00000001888771f8 + 0xb8) + 0x20);
          if (lVar1 != 0) {
            XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
          }
          FUN_18499c930(plVar7,7,lVar6,0,uRam000000018889b3b8);
          lVar6 = func_0x00018045cfe0(lRam0000000188877d28);
          if (lVar6 != 0) {
            if (cRam0000000188c927b1 == '\0') {
              FUN_18048bf00(0x188877d28);
              cRam0000000188c927b1 = '\x01';
            }
            if (cRam0000000188c92772 == '\0') {
              FUN_18048bf00(0x188876d80);
              FUN_18048bf00(0x1889562a0);
              cRam0000000188c92772 = '\x01';
            }
            func_0x00018050fcc0(lVar6,uRam00000001889562a0);
            lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
            if (lVar1 != 0) {
              XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
            }
            lVar1 = *(longlong *)(*(longlong *)(lRam0000000188877d28 + 0xb8) + 0x58);
            if (lVar1 != 0) {
              XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
            }
            FUN_18499c930(plVar7,0xd,lVar6,0,uRam000000018889b3b8);
            lVar6 = func_0x00018045cfe0(lRam00000001888783d8);
            if (lVar6 != 0) {
              if (cRam0000000188c9277a == '\0') {
                FUN_18048bf00(0x1888783d8);
                cRam0000000188c9277a = '\x01';
              }
              if (cRam0000000188c92772 == '\0') {
                FUN_18048bf00(0x188876d80);
                FUN_18048bf00(0x1889562a0);
                cRam0000000188c92772 = '\x01';
              }
              func_0x00018050fcc0(lVar6,uRam00000001889562a0);
              lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
              if (lVar1 != 0) {
                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
              }
              lVar1 = *(longlong *)(*(longlong *)(lRam00000001888783d8 + 0xb8) + 0x10);
              if (lVar1 != 0) {
                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
              }
              FUN_18499c930(plVar7,1,lVar6,1,uRam000000018889b3b8);
              lVar6 = func_0x00018045cfe0(lRam0000000188877438);
              if (lVar6 != 0) {
                if (cRam0000000188c92781 == '\0') {
                  FUN_18048bf00(0x188877438);
                  FUN_18048bf00(&DAT_18885a700);
                  cRam0000000188c92781 = '\x01';
                }
                if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                  func_0x00018048c140();
                }
                uVar8 = func_0x0001866fdac0(0,0);
                bVar10 = cRam0000000188c92772 == '\0';
                *(undefined8 *)(lVar6 + 0x18) = uVar8;
                if (bVar10) {
                  FUN_18048bf00(0x188876d80);
                  FUN_18048bf00(0x1889562a0);
                  cRam0000000188c92772 = '\x01';
                }
                func_0x00018050fcc0(lVar6,uRam00000001889562a0);
                lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
                if (lVar1 != 0) {
                  XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                }
                lVar1 = *(longlong *)(*(longlong *)(lRam0000000188877438 + 0xb8) + 0x30);
                if (lVar1 != 0) {
                  XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                }
                FUN_18499c930(plVar7,3,lVar6,0,uRam000000018889b3b8);
                lVar6 = func_0x00018045cfe0(lRam0000000188876b48);
                if (lVar6 != 0) {
                  if (cRam0000000188c92796 == '\0') {
                    FUN_18048bf00(0x188876b48);
                    FUN_18048bf00(&DAT_18885a700);
                    cRam0000000188c92796 = '\x01';
                  }
                  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                    func_0x00018048c140();
                  }
                  uVar8 = func_0x0001866fdac0(0,0);
                  bVar10 = cRam0000000188c92772 == '\0';
                  *(undefined8 *)(lVar6 + 0x18) = uVar8;
                  if (bVar10) {
                    FUN_18048bf00(0x188876d80);
                    FUN_18048bf00(0x1889562a0);
                    cRam0000000188c92772 = '\x01';
                  }
                  func_0x00018050fcc0(lVar6,uRam00000001889562a0);
                  lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
                  if (lVar1 != 0) {
                    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                  }
                  lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876b48 + 0xb8) + 0x38);
                  if (lVar1 != 0) {
                    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                  }
                  FUN_18499c930(plVar7,2,lVar6,0,uRam000000018889b3b8);
                  lVar6 = func_0x00018045cfe0(lRam0000000188878cc8);
                  if (lVar6 != 0) {
                    if (cRam0000000188c927a3 == '\0') {
                      FUN_18048bf00(0x188878cc8);
                      cRam0000000188c927a3 = '\x01';
                    }
                    if (cRam0000000188c92772 == '\0') {
                      FUN_18048bf00(0x188876d80);
                      FUN_18048bf00(0x1889562a0);
                      cRam0000000188c92772 = '\x01';
                    }
                    func_0x00018050fcc0(lVar6,uRam00000001889562a0);
                    lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
                    if (lVar1 != 0) {
                      XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                    }
                    lVar1 = *(longlong *)(*(longlong *)(lRam0000000188878cc8 + 0xb8) + 0x20);
                    if (lVar1 != 0) {
                      XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                    }
                    FUN_18499c930(plVar7,5,lVar6,0,uRam000000018889b3b8);
                    lVar6 = func_0x00018045cfe0(lRam0000000188878850);
                    if (lVar6 != 0) {
                      if (cRam0000000188c9279d == '\0') {
                        FUN_18048bf00(&DAT_18885a700);
                        FUN_18048bf00(0x188878850);
                        cRam0000000188c9279d = '\x01';
                      }
                      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                        func_0x00018048c140();
                      }
                      uVar8 = func_0x0001866fdac0(0xffffffff,0);
                      bVar10 = cRam0000000188c92772 == '\0';
                      *(undefined8 *)(lVar6 + 0x18) = uVar8;
                      if (bVar10) {
                        FUN_18048bf00(0x188876d80);
                        FUN_18048bf00(0x1889562a0);
                        cRam0000000188c92772 = '\x01';
                      }
                      func_0x00018050fcc0(lVar6,uRam00000001889562a0);
                      lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
                      if (lVar1 != 0) {
                        XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                      }
                      lVar1 = *(longlong *)(*(longlong *)(lRam0000000188878850 + 0xb8) + 0x28);
                      if (lVar1 != 0) {
                        XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                      }
                      FUN_18499c930(plVar7,4,lVar6,0,uRam000000018889b3b8);
                      lVar6 = func_0x00018045cfe0(lRam0000000188877670);
                      if (lVar6 != 0) {
                        if (cRam0000000188c92787 == '\0') {
                          FUN_18048bf00(0x188877670);
                          cRam0000000188c92787 = '\x01';
                        }
                        if (cRam0000000188c92772 == '\0') {
                          FUN_18048bf00(0x188876d80);
                          FUN_18048bf00(0x1889562a0);
                          cRam0000000188c92772 = '\x01';
                        }
                        func_0x00018050fcc0(lVar6,uRam00000001889562a0);
                        lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
                        if (lVar1 != 0) {
                          XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                        }
                        lVar1 = *(longlong *)(*(longlong *)(lRam0000000188877670 + 0xb8) + 0x20);
                        if (lVar1 != 0) {
                          XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                        }
                        FUN_18499c930(plVar7,6,lVar6,0,uRam000000018889b3b8);
                        lVar6 = func_0x00018045cfe0(lRam0000000188877f60);
                        if (lVar6 != 0) {
                          if (cRam0000000188c9278d == '\0') {
                            FUN_18048bf00(0x188877f60);
                            cRam0000000188c9278d = '\x01';
                          }
                          if (cRam0000000188c92772 == '\0') {
                            FUN_18048bf00(0x188876d80);
                            FUN_18048bf00(0x1889562a0);
                            cRam0000000188c92772 = '\x01';
                          }
                          func_0x00018050fcc0(lVar6,uRam00000001889562a0);
                          lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
                          if (lVar1 != 0) {
                            XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                          }
                          lVar1 = *(longlong *)(*(longlong *)(lRam0000000188877f60 + 0xb8) + 0x10);
                          if (lVar1 != 0) {
                            XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                          }
                          FUN_18499c930(plVar7,0xb,lVar6,0,uRam000000018889b3b8);
                          lVar6 = func_0x00018045cfe0(lRam0000000188877ae8);
                          if (lVar6 != 0) {
                            if (cRam0000000188c927a5 == '\0') {
                              FUN_18048bf00(0x188877ae8);
                              cRam0000000188c927a5 = '\x01';
                            }
                            if (cRam0000000188c92772 == '\0') {
                              FUN_18048bf00(0x188876d80);
                              FUN_18048bf00(0x1889562a0);
                              cRam0000000188c92772 = '\x01';
                            }
                            func_0x00018050fcc0(lVar6,uRam00000001889562a0);
                            lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
                            if (lVar1 != 0) {
                              XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                            }
                            lVar1 = *(longlong *)(*(longlong *)(lRam0000000188877ae8 + 0xb8) + 8);
                            if (lVar1 != 0) {
                              XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                            }
                            FUN_18499c930(plVar7,8,lVar6,0,uRam000000018889b3b8);
                            lVar6 = func_0x00018045cfe0(lRam00000001888781a0);
                            if (lVar6 != 0) {
                              if (cRam0000000188c927bd == '\0') {
                                FUN_18048bf00(0x1888781a0);
                                cRam0000000188c927bd = '\x01';
                              }
                              if (cRam0000000188c92772 == '\0') {
                                FUN_18048bf00(0x188876d80);
                                FUN_18048bf00(0x1889562a0);
                                cRam0000000188c92772 = '\x01';
                              }
                              func_0x00018050fcc0(lVar6,uRam00000001889562a0);
                              lVar1 = *(longlong *)(*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
                              if (lVar1 != 0) {
                                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                              }
                              lVar1 = *(longlong *)
                                       (*(longlong *)(lRam00000001888781a0 + 0xb8) + 0x58);
                              if (lVar1 != 0) {
                                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                              }
                              FUN_18499c930(plVar7,9,lVar6,0,uRam000000018889b3b8);
                              lVar6 = func_0x00018045cfe0(lRam0000000188878618);
                              if (lVar6 != 0) {
                                if (cRam0000000188c927ca == '\0') {
                                  FUN_18048bf00(0x188878618);
                                  cRam0000000188c927ca = '\x01';
                                }
                                if (cRam0000000188c92772 == '\0') {
                                  FUN_18048bf00(0x188876d80);
                                  FUN_18048bf00(0x1889562a0);
                                  cRam0000000188c92772 = '\x01';
                                }
                                func_0x00018050fcc0(lVar6,uRam00000001889562a0);
                                lVar1 = *(longlong *)
                                         (*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
                                if (lVar1 != 0) {
                                  XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                                }
                                lVar1 = *(longlong *)
                                         (*(longlong *)(lRam0000000188878618 + 0xb8) + 0x60);
                                if (lVar1 != 0) {
                                  XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar6,0);
                                }
                                FUN_18499c930(plVar7,10,lVar6,0,uRam000000018889b3b8);
                                lVar6 = func_0x00018045cfe0(lRam00000001888778b0);
                                if (lVar6 != 0) {
                                  if (cRam0000000188c927d9 == '\0') {
                                    FUN_18048bf00(0x1888778b0);
                                    FUN_18048bf00(&DAT_18885a700);
                                    cRam0000000188c927d9 = '\x01';
                                  }
                                  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                                    func_0x00018048c140();
                                  }
                                  uVar8 = func_0x0001866fdac0(0xffffffff,0);
                                  bVar10 = cRam0000000188c92772 == '\0';
                                  *(undefined8 *)(lVar6 + 0x18) = uVar8;
                                  if (bVar10) {
                                    FUN_18048bf00(0x188876d80);
                                    FUN_18048bf00(0x1889562a0);
                                    cRam0000000188c92772 = '\x01';
                                  }
                                  func_0x00018050fcc0(lVar6,uRam00000001889562a0);
                                  lVar1 = *(longlong *)
                                           (*(longlong *)(lRam0000000188876d80 + 0xb8) + 8);
                                  if (lVar1 != 0) {
                                    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                              (lVar1,lVar6,0);
                                  }
                                  lVar1 = *(longlong *)
                                           (*(longlong *)(lRam00000001888778b0 + 0xb8) + 0x58);
                                  if (lVar1 != 0) {
                                    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                              (lVar1,lVar6,0);
                                  }
                                  FUN_18499c930(plVar7,0xc,lVar6,0,uRam000000018889b3b8);
                                  return plVar7;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    plVar7 = (longlong *)(*pcVar2)();
    return plVar7;
  }
  if (cRam0000000188caf7e6 == '\0') {
    FUN_18048bf00(0x1888ed758);
    FUN_18048bf00(0x188862be8);
    FUN_18048bf00(0x188906850);
    cRam0000000188caf7e6 = '\x01';
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x00018324ea60:
    FUN_18048c0b0();
code_r0x00018324ea66:
    FUN_18048ba10(unaff_RSI,lVar6);
code_r0x00018324ea71:
    FUN_18048c0b0();
  }
  else {
    FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30),&stack0x00000008,0);
    if (*(longlong *)(lVar6 + 0x18) == 0) goto code_r0x00018324ea7b;
    uVar8 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      unaff_RSI = *(longlong **)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (unaff_RSI != (longlong *)0x0) {
        FUN_183cf8c20(unaff_RSI,uVar8,param_1,0);
        bVar10 = true;
        iVar5 = FUN_183f22380(uVar8,1,1,iVar4,0);
        if (iVar5 != 0) {
          if (*(longlong *)(lVar6 + 0x18) == 0) goto code_r0x00018324ea60;
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
        }
        uVar9 = uRam00000001888ed758;
        if (*(int *)(lRam0000000188906850 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar9 = FUN_185eded20(uVar9,0);
        unaff_RSI = (longlong *)FUN_183cf3ce0(unaff_RSI,uVar8,iVar4 + 1,uVar9,0);
        FUN_183f22fd0(uVar8,iVar4 + -1,0);
        lVar6 = lRam0000000188862be8;
        if (unaff_RSI == (longlong *)0x0) {
          return (longlong *)0x0;
        }
        lVar1 = *unaff_RSI;
        if (DAT_188ccc7f0 == '\0') {
          if ((*(byte *)(lVar1 + 0x130) < *(byte *)(lRam0000000188862be8 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(lVar1 + 200) + -8 +
               (ulonglong)*(byte *)(lRam0000000188862be8 + 0x130) * 8) != lRam0000000188862be8)) {
            bVar10 = false;
          }
          bVar10 = !bVar10;
        }
        else {
          cVar3 = func_0x0001804463e0(lVar1,lRam0000000188862be8);
          bVar10 = cVar3 == '\0';
        }
        plVar7 = (longlong *)0x0;
        if (!bVar10) {
          plVar7 = unaff_RSI;
        }
        if (plVar7 != (longlong *)0x0) {
          return plVar7;
        }
        goto code_r0x00018324ea66;
      }
      goto code_r0x00018324ea71;
    }
  }
  FUN_18048c0b0();
code_r0x00018324ea7b:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  plVar7 = (longlong *)(*pcVar2)();
  return plVar7;
}

