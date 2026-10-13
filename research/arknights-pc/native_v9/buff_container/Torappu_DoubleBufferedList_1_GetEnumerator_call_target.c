
longlong Torappu_DoubleBufferedList_1_GetEnumerator_call_target(longlong param_1,longlong param_2)

{
  short sVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  int iVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong lVar9;
  
  lVar8 = **(longlong **)(*(longlong *)(param_2 + 0x20) + 0xc0);
  if ((*(byte *)(lVar8 + 0x136) & 1) == 0) {
    lVar8 = FUN_1804463f0(lVar8);
  }
  lVar8 = *(longlong *)(*(longlong *)(lVar8 + 0xb8) + 0x40);
  if (lVar8 != 0) {
    XLua_DelegateBridge_InvokeSessionStart_0x6003c9d(lVar8,0);
    if (*(longlong *)(*(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 8) + 0x20)
        == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 8))();
    }
    FUN_1844c6730(lVar8,param_1,
                  *(undefined8 *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 8));
    XLua_DelegateBridge_Invoke_0x6003c9e(lVar8,1,0);
    if (*(longlong *)
         (*(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x70) + 0x20) == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x70))();
    }
    lVar9 = *(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x70);
    if (*(longlong *)(lVar9 + 0x38) == 0) {
      FUN_180446470(lVar9);
    }
    if (*(longlong *)(lVar8 + 0x18) == 0) {
      FUN_18048c0b0();
    }
    else {
      uVar6 = FUN_183e0e550(*(longlong *)(lVar8 + 0x18),0);
      iVar5 = FUN_183f21da0(uVar6,0);
      if (iVar5 < *(int *)(lVar8 + 0x40) + 2) {
        XLua_DelegateBridge_InvokeSessionEnd_0x6003c9f(lVar8,0);
        uVar6 = func_0x00018048bf20(0x1888506e8);
        uVar6 = func_0x00018045cfe0(uVar6);
        FUN_180005cb0(uVar6);
        uVar7 = func_0x00018048bf20(0x18887bcf0);
        FUN_185eb96e0(uVar6,uVar7,0);
        FUN_18048c070(uVar6,lVar9);
        pcVar4 = (code *)swi(3);
        lVar8 = (*pcVar4)();
        return lVar8;
      }
      lVar2 = *(longlong *)(lVar8 + 0x18);
      if (lVar2 == 0) goto code_r0x0001844ca116;
      lVar3 = *(longlong *)(lVar2 + 0x20);
      uVar6 = FUN_183e0e550(lVar2,0);
      iVar5 = *(int *)(lVar8 + 0x40);
      if (lVar3 != 0) {
        if (((undefined8 *)**(longlong **)(lVar9 + 0x38))[4] == 0) {
          (**(code **)**(longlong **)(lVar9 + 0x38))();
        }
        FUN_18456c000(lVar3,uVar6,iVar5 + 2,&stack0x00000010,**(undefined8 **)(lVar9 + 0x38));
        XLua_DelegateBridge_InvokeSessionEnd_0x6003c9f(lVar8,0);
        return 0;
      }
    }
    FUN_18048c0b0();
code_r0x0001844ca116:
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar4 = (code *)swi(3);
    lVar8 = (*pcVar4)();
    return lVar8;
  }
  sVar1 = *(short *)(param_1 + 0x20);
  *(short *)(param_1 + 0x20) = sVar1 + 1;
  if (sVar1 == 0) {
    lVar8 = *(longlong *)(param_1 + 0x18);
    if (lVar8 == 0) goto LAB_185a17d32;
    if (*(longlong *)
         (*(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x68) + 0x20) == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x68))();
    }
    iVar5 = *(int *)(lVar8 + 0x18);
    *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
    *(undefined4 *)(lVar8 + 0x18) = 0;
    if (0 < iVar5) {
      System_Array_Clear_0x6000ea1(*(undefined8 *)(lVar8 + 0x10),0,iVar5,0);
    }
    lVar8 = *(longlong *)(param_1 + 0x18);
    uVar6 = *(undefined8 *)(param_1 + 0x10);
    if (lVar8 == 0) goto LAB_185a17d32;
    if (*(longlong *)
         (*(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x78) + 0x20) == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x78))();
    }
    FUN_184bac9e0(lVar8,uVar6,
                  *(undefined8 *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x78));
  }
  lVar8 = *(longlong *)(param_1 + 0x28);
  if (lVar8 != 0) {
    if (*(longlong *)
         (*(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x80) + 0x20) == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x80))();
    }
    if (*(int *)(lVar8 + 0x18) < 1) {
      uVar6 = *(undefined8 *)(param_1 + 0x18);
      lVar8 = *(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0xa8);
      if ((*(byte *)(lVar8 + 0x136) & 1) == 0) {
        lVar8 = FUN_1804463f0(lVar8);
      }
      lVar8 = func_0x00018045cfe0(lVar8);
      if (lVar8 != 0) {
        if (*(longlong *)
             (*(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0xb0) + 0x20) == 0
           ) {
          (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0xb0))()
          ;
        }
        lVar9 = *(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0);
        PinchUpdateExtendedDelegate__ctor_0x60054bb
                  (lVar8,param_1,*(undefined8 *)(lVar9 + 0xa0),*(undefined8 *)(lVar9 + 0xb0));
        lVar9 = *(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x90);
        if ((*(byte *)(lVar9 + 0x136) & 1) == 0) {
          lVar9 = FUN_1804463f0(lVar9);
        }
        lVar9 = func_0x00018045cfe0(lVar9);
        if (lVar9 != 0) {
          if (*(longlong *)
               (*(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0xb8) + 0x20) ==
              0) {
            (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0xb8))
                      ();
          }
          FUN_184916ca0(lVar9,uVar6,lVar8,
                        *(undefined8 *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0xb8))
          ;
          return lVar9;
        }
      }
    }
    else {
      lVar8 = *(longlong *)(param_1 + 0x28);
      if (lVar8 != 0) {
        if (*(longlong *)
             (*(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x88) + 0x20) == 0
           ) {
          (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x88))()
          ;
        }
        lVar8 = FUN_185366bb0(lVar8,*(undefined8 *)
                                     (*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x88));
        uVar6 = *(undefined8 *)(param_1 + 0x18);
        if (lVar8 != 0) {
          if (*(longlong *)
               (*(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x98) + 0x20) ==
              0) {
            (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x98))
                      ();
          }
          FUN_184916b60(lVar8,uVar6,
                        *(undefined8 *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x98))
          ;
          return lVar8;
        }
      }
    }
  }
LAB_185a17d32:
  FUN_18048c0b0();
  pcVar4 = (code *)swi(3);
  lVar8 = (*pcVar4)();
  return lVar8;
}

