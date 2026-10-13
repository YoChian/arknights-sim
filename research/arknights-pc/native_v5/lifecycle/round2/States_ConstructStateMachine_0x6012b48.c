/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
longlong States_ConstructStateMachine_0x6012b48(undefined8 param_1)
{
  longlong lVar1;
  code *pcVar2;
  longlong lVar3;
  longlong lVar4;
  undefined8 uVar5;
  bool bVar6;
  if (DAT_188c928fd == '\0') {
    FUN_18048bf00(&DAT_188883d50);
    FUN_18048bf00(&DAT_1888841c8);
    FUN_18048bf00(&DAT_188884400);
    FUN_18048bf00(&DAT_188884640);
    FUN_18048bf00(&DAT_188884878);
    FUN_18048bf00(&DAT_188884ab8);
    FUN_18048bf00(&DAT_188884cf0);
    FUN_18048bf00(&DAT_188884f30);
    FUN_18048bf00(&DAT_188885168);
    FUN_18048bf00(&DAT_1888853a8);
    FUN_18048bf00(&DAT_1888855e0);
    FUN_18048bf00(&DAT_18889ba68);
    FUN_18048bf00(&DAT_188885820);
    FUN_18048bf00(&DAT_188885a58);
    FUN_18048bf00(&DAT_188885c98);
    FUN_18048bf00(&DAT_188885ed0);
    FUN_18048bf00(&DAT_188886110);
    FUN_18048bf00(&DAT_188886348);
    FUN_18048bf00(&DAT_188886588);
    DAT_188c928fd = '\x01';
  }
  lVar3 = func_0x00018045cfe0(_DAT_1888841c8);
  if (lVar3 != 0) {
    func_0x00018050cf60(lVar3,0);
    *(undefined8 *)(lVar3 + 0x40) = param_1;
    func_0x00018048b9e0(lVar3 + 0x40,param_1);
    lVar4 = func_0x00018045cfe0(_DAT_188885168);
    if (lVar4 != 0) {
      if (DAT_188c92901 == '\0') {
        FUN_18048bf00(&DAT_188885168);
        FUN_18048bf00(&DAT_18889b830);
        DAT_188c92901 = '\x01';
      }
      FUN_18499ca10(lVar4,param_1,lVar3,_DAT_18889b830);
      if (**(longlong **)(_DAT_188885168 + 0xb8) != 0) {
        XLua_DelegateBridge___Gen_Delegate_Imp36_0x6000a84
                  (**(longlong **)(_DAT_188885168 + 0xb8),lVar4,param_1,lVar3,0);
      }
      lVar3 = func_0x00018045cfe0(_DAT_188884640);
      if (lVar3 != 0) {
        if (DAT_188c92909 == '\0') {
          FUN_18048bf00(&DAT_188884640);
          FUN_18048bf00(&DAT_18885a700);
          DAT_188c92909 = '\x01';
        }
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar5 = func_0x0001866fdac0(0,0);
        bVar6 = DAT_188c92903 == '\0';
        *(undefined8 *)(lVar3 + 0x18) = uVar5;
        if (bVar6) {
          FUN_18048bf00(&DAT_188883f88);
          FUN_18048bf00(&DAT_188956de0);
          DAT_188c92903 = '\x01';
        }
        func_0x00018050fcc0(lVar3,_DAT_188956de0);
        if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
          XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                    (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
        }
        lVar1 = *(longlong *)(*(longlong *)(_DAT_188884640 + 0xb8) + 0x28);
        if (lVar1 != 0) {
          XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
        }
        FUN_18499c930(lVar4,6,lVar3,0,_DAT_18889ba68);
        lVar3 = func_0x00018045cfe0(_DAT_188885a58);
        if (lVar3 != 0) {
          if (DAT_188c92913 == '\0') {
            FUN_18048bf00(&DAT_188885a58);
            DAT_188c92913 = '\x01';
          }
          if (DAT_188c92903 == '\0') {
            FUN_18048bf00(&DAT_188883f88);
            FUN_18048bf00(&DAT_188956de0);
            DAT_188c92903 = '\x01';
          }
          func_0x00018050fcc0(lVar3,_DAT_188956de0);
          if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
            XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                      (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
          }
          lVar1 = *(longlong *)(*(longlong *)(_DAT_188885a58 + 0xb8) + 0x30);
          if (lVar1 != 0) {
            XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
          }
          FUN_18499c930(lVar4,1,lVar3,1,_DAT_18889ba68);
          lVar3 = func_0x00018045cfe0(_DAT_188883d50);
          if (lVar3 != 0) {
            if (DAT_188c92918 == '\0') {
              FUN_18048bf00(&DAT_188883d50);
              DAT_188c92918 = '\x01';
            }
            if (DAT_188c92903 == '\0') {
              FUN_18048bf00(&DAT_188883f88);
              FUN_18048bf00(&DAT_188956de0);
              DAT_188c92903 = '\x01';
            }
            func_0x00018050fcc0(lVar3,_DAT_188956de0);
            if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
              XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                        (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
            }
            lVar1 = *(longlong *)(*(longlong *)(_DAT_188883d50 + 0xb8) + 0x20);
            if (lVar1 != 0) {
              XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
            }
            FUN_18499c930(lVar4,2,lVar3,0,_DAT_18889ba68);
            lVar3 = func_0x00018045cfe0(_DAT_188886348);
            if (lVar3 != 0) {
              if (DAT_188c92932 == '\0') {
                FUN_18048bf00(&DAT_188886348);
                DAT_188c92932 = '\x01';
              }
              if (DAT_188c92903 == '\0') {
                FUN_18048bf00(&DAT_188883f88);
                FUN_18048bf00(&DAT_188956de0);
                DAT_188c92903 = '\x01';
              }
              func_0x00018050fcc0(lVar3,_DAT_188956de0);
              if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                          (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
              }
              lVar1 = *(longlong *)(*(longlong *)(_DAT_188886348 + 0xb8) + 0x18);
              if (lVar1 != 0) {
                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
              }
              FUN_18499c930(lVar4,4,lVar3,0,_DAT_18889ba68);
              lVar3 = func_0x00018045cfe0(_DAT_188884878);
              if (lVar3 != 0) {
                if (DAT_188c9292e == '\0') {
                  FUN_18048bf00(&DAT_188884878);
                  DAT_188c9292e = '\x01';
                }
                if (DAT_188c92903 == '\0') {
                  FUN_18048bf00(&DAT_188883f88);
                  FUN_18048bf00(&DAT_188956de0);
                  DAT_188c92903 = '\x01';
                }
                func_0x00018050fcc0(lVar3,_DAT_188956de0);
                if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                  XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                            (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                }
                lVar1 = *(longlong *)(*(longlong *)(_DAT_188884878 + 0xb8) + 0x18);
                if (lVar1 != 0) {
                  XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
                }
                FUN_18499c930(lVar4,3,lVar3,0,_DAT_18889ba68);
                lVar3 = func_0x00018045cfe0(_DAT_188884ab8);
                if (lVar3 != 0) {
                  if (DAT_188c9291d == '\0') {
                    FUN_18048bf00(&DAT_188884ab8);
                    DAT_188c9291d = '\x01';
                  }
                  if (DAT_188c92903 == '\0') {
                    FUN_18048bf00(&DAT_188883f88);
                    FUN_18048bf00(&DAT_188956de0);
                    DAT_188c92903 = '\x01';
                  }
                  func_0x00018050fcc0(lVar3,_DAT_188956de0);
                  if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                              (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                  }
                  lVar1 = *(longlong *)(*(longlong *)(_DAT_188884ab8 + 0xb8) + 0x20);
                  if (lVar1 != 0) {
                    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
                  }
                  FUN_18499c930(lVar4,5,lVar3,0,_DAT_18889ba68);
                  lVar3 = func_0x00018045cfe0(_DAT_188886110);
                  if (lVar3 != 0) {
                    if (DAT_188c9299c == '\0') {
                      FUN_18048bf00(&DAT_188886110);
                      DAT_188c9299c = '\x01';
                    }
                    if (DAT_188c92903 == '\0') {
                      FUN_18048bf00(&DAT_188883f88);
                      FUN_18048bf00(&DAT_188956de0);
                      DAT_188c92903 = '\x01';
                    }
                    func_0x00018050fcc0(lVar3,_DAT_188956de0);
                    if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                      XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                    }
                    lVar1 = *(longlong *)(*(longlong *)(_DAT_188886110 + 0xb8) + 0x68);
                    if (lVar1 != 0) {
                      XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
                    }
                    FUN_18499c930(lVar4,8,lVar3,0,_DAT_18889ba68);
                    lVar3 = func_0x00018045cfe0(_DAT_188885ed0);
                    if (lVar3 != 0) {
                      if (DAT_188c92925 == '\0') {
                        FUN_18048bf00(&DAT_188885ed0);
                        DAT_188c92925 = '\x01';
                      }
                      if (DAT_188c92903 == '\0') {
                        FUN_18048bf00(&DAT_188883f88);
                        FUN_18048bf00(&DAT_188956de0);
                        DAT_188c92903 = '\x01';
                      }
                      func_0x00018050fcc0(lVar3,_DAT_188956de0);
                      if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                        XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                  (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                      }
                      lVar1 = *(longlong *)(*(longlong *)(_DAT_188885ed0 + 0xb8) + 0x20);
                      if (lVar1 != 0) {
                        XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
                      }
                      FUN_18499c930(lVar4,7,lVar3,0,_DAT_18889ba68);
                      lVar3 = func_0x00018045cfe0(_DAT_188886588);
                      if (lVar3 != 0) {
                        if (DAT_188c92964 == '\0') {
                          FUN_18048bf00(&DAT_188886588);
                          DAT_188c92964 = '\x01';
                        }
                        if (DAT_188c92903 == '\0') {
                          FUN_18048bf00(&DAT_188883f88);
                          FUN_18048bf00(&DAT_188956de0);
                          DAT_188c92903 = '\x01';
                        }
                        func_0x00018050fcc0(lVar3,_DAT_188956de0);
                        if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                          XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                    (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                        }
                        lVar1 = *(longlong *)(*(longlong *)(_DAT_188886588 + 0xb8) + 0x80);
                        if (lVar1 != 0) {
                          XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
                        }
                        FUN_18499c930(lVar4,9,lVar3,0,_DAT_18889ba68);
                        lVar3 = func_0x00018045cfe0(_DAT_1888853a8);
                        if (lVar3 != 0) {
                          if (DAT_188c92969 == '\0') {
                            FUN_18048bf00(&DAT_1888853a8);
                            DAT_188c92969 = '\x01';
                          }
                          bVar6 = DAT_188c92903 == '\0';
                          *(undefined4 *)(lVar3 + 0x18) = 0x3f400000;
                          *(undefined4 *)(lVar3 + 0x1c) = 0x3f800000;
                          *(undefined4 *)(lVar3 + 0x20) = 0x3e4ccccd;
                          if (bVar6) {
                            FUN_18048bf00(&DAT_188883f88);
                            FUN_18048bf00(&DAT_188956de0);
                            DAT_188c92903 = '\x01';
                          }
                          func_0x00018050fcc0(lVar3,_DAT_188956de0);
                          if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                            XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                      (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                          }
                          lVar1 = *(longlong *)(*(longlong *)(_DAT_1888853a8 + 0xb8) + 0x20);
                          if (lVar1 != 0) {
                            XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
                          }
                          FUN_18499c930(lVar4,10,lVar3,0,_DAT_18889ba68);
                          lVar3 = func_0x00018045cfe0(_DAT_188884f30);
                          if (lVar3 != 0) {
                            if (DAT_188c9297b == '\0') {
                              FUN_18048bf00(&DAT_188884f30);
                              DAT_188c9297b = '\x01';
                            }
                            bVar6 = DAT_188c92903 == '\0';
                            *(undefined1 *)(lVar3 + 0x28) = 1;
                            if (bVar6) {
                              FUN_18048bf00(&DAT_188883f88);
                              FUN_18048bf00(&DAT_188956de0);
                              DAT_188c92903 = '\x01';
                            }
                            func_0x00018050fcc0(lVar3,_DAT_188956de0);
                            if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                              XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                        (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                            }
                            lVar1 = *(longlong *)(*(longlong *)(_DAT_188884f30 + 0xb8) + 0x68);
                            if (lVar1 != 0) {
                              XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
                            }
                            FUN_18499c930(lVar4,0xb,lVar3,0,_DAT_18889ba68);
                            lVar3 = func_0x00018045cfe0(_DAT_188884400);
                            if (lVar3 != 0) {
                              if (DAT_188c9298d == '\0') {
                                FUN_18048bf00(&DAT_188884400);
                                DAT_188c9298d = '\x01';
                              }
                              if (DAT_188c92903 == '\0') {
                                FUN_18048bf00(&DAT_188883f88);
                                FUN_18048bf00(&DAT_188956de0);
                                DAT_188c92903 = '\x01';
                              }
                              func_0x00018050fcc0(lVar3,_DAT_188956de0);
                              if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                          (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                              }
                              lVar1 = *(longlong *)(*(longlong *)(_DAT_188884400 + 0xb8) + 0x58);
                              if (lVar1 != 0) {
                                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
                              }
                              FUN_18499c930(lVar4,0xc,lVar3,0,_DAT_18889ba68);
                              lVar3 = func_0x00018045cfe0(_DAT_1888855e0);
                              if (lVar3 != 0) {
                                if (DAT_188c92945 == '\0') {
                                  FUN_18048bf00(&DAT_1888855e0);
                                  DAT_188c92945 = '\x01';
                                }
                                if (DAT_188c92903 == '\0') {
                                  FUN_18048bf00(&DAT_188883f88);
                                  FUN_18048bf00(&DAT_188956de0);
                                  DAT_188c92903 = '\x01';
                                }
                                func_0x00018050fcc0(lVar3,_DAT_188956de0);
                                if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                                  XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                            (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                                }
                                lVar1 = *(longlong *)(*(longlong *)(_DAT_1888855e0 + 0xb8) + 0x58);
                                if (lVar1 != 0) {
                                  XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,lVar3,0);
                                }
                                FUN_18499c930(lVar4,0xd,lVar3,0,_DAT_18889ba68);
                                lVar3 = func_0x00018045cfe0(_DAT_188885820);
                                if (lVar3 != 0) {
                                  if (DAT_188c92952 == '\0') {
                                    FUN_18048bf00(&DAT_188885820);
                                    DAT_188c92952 = '\x01';
                                  }
                                  if (DAT_188c92903 == '\0') {
                                    FUN_18048bf00(&DAT_188883f88);
                                    FUN_18048bf00(&DAT_188956de0);
                                    DAT_188c92903 = '\x01';
                                  }
                                  func_0x00018050fcc0(lVar3,_DAT_188956de0);
                                  if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                                    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                              (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                                  }
                                  if (*(int *)(_DAT_188885820 + 0xe0) == 0) {
                                    func_0x00018048c140(_DAT_188885820);
                                  }
                                  lVar1 = *(longlong *)(*(longlong *)(_DAT_188885820 + 0xb8) + 0x78)
                                  ;
                                  if (lVar1 != 0) {
                                    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                              (lVar1,lVar3,0);
                                  }
                                  FUN_18499c930(lVar4,0xe,lVar3,0,_DAT_18889ba68);
                                  lVar3 = func_0x00018045cfe0(_DAT_188884cf0);
                                  if (lVar3 != 0) {
                                    if (DAT_188c929ae == '\0') {
                                      FUN_18048bf00(&DAT_188884cf0);
                                      FUN_18048bf00(&DAT_18885a700);
                                      DAT_188c929ae = '\x01';
                                    }
                                    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                                      func_0x00018048c140();
                                    }
                                    uVar5 = func_0x0001866fdac0(0xffffffff,0);
                                    bVar6 = DAT_188c92903 == '\0';
                                    *(undefined8 *)(lVar3 + 0x18) = uVar5;
                                    if (bVar6) {
                                      FUN_18048bf00(&DAT_188883f88);
                                      FUN_18048bf00(&DAT_188956de0);
                                      DAT_188c92903 = '\x01';
                                    }
                                    func_0x00018050fcc0(lVar3,_DAT_188956de0);
                                    if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                                      XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                                (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                                    }
                                    lVar1 = *(longlong *)
                                             (*(longlong *)(_DAT_188884cf0 + 0xb8) + 0x70);
                                    if (lVar1 != 0) {
                                      XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                                (lVar1,lVar3,0);
                                    }
                                    FUN_18499c930(lVar4,0xf,lVar3,0,_DAT_18889ba68);
                                    lVar3 = func_0x00018045cfe0(_DAT_188885c98);
                                    if (lVar3 != 0) {
                                      if (DAT_188c92938 == '\0') {
                                        FUN_18048bf00(&DAT_188885c98);
                                        DAT_188c92938 = '\x01';
                                      }
                                      if (DAT_188c92903 == '\0') {
                                        FUN_18048bf00(&DAT_188883f88);
                                        FUN_18048bf00(&DAT_188956de0);
                                        DAT_188c92903 = '\x01';
                                      }
                                      func_0x00018050fcc0(lVar3,_DAT_188956de0);
                                      if (**(longlong **)(_DAT_188883f88 + 0xb8) != 0) {
                                        XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                                  (**(longlong **)(_DAT_188883f88 + 0xb8),lVar3,0);
                                      }
                                      if (*(int *)(_DAT_188885c98 + 0xe0) == 0) {
                                        func_0x00018048c140(_DAT_188885c98);
                                      }
                                      lVar1 = *(longlong *)
                                               (*(longlong *)(_DAT_188885c98 + 0xb8) + 0x38);
                                      if (lVar1 != 0) {
                                        XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b
                                                  (lVar1,lVar3,0);
                                      }
                                      FUN_18499c930(lVar4,0x10,lVar3,0,_DAT_18889ba68);
                                      return lVar4;
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
      }
    }
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  lVar3 = (*pcVar2)();
  return lVar3;
}
