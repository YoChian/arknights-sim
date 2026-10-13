
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Entity_RemoveBuffs_0x60103f9
               (undefined8 param_1,undefined8 param_2,char param_3,undefined1 param_4,
               undefined4 param_5,undefined8 param_6)

{
  code *pcVar1;
  longlong lVar2;
  undefined8 in_stack_ffffffffffffffe0;
  undefined4 uVar3;
  
  uVar3 = (undefined4)((ulonglong)in_stack_ffffffffffffffe0 >> 0x20);
  if (DAT_188c9088f == '\0') {
    FUN_18048bf00(&DAT_188841368);
    DAT_188c9088f = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x610);
  if (lVar2 == 0) {
    lVar2 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
    if (param_3 == '\0') {
      if (lVar2 == 0) {
LAB_1806fbfff:
        FUN_18048c0b0();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      BuffContainer_RemoveBuffs_0x600ff23(lVar2,param_2,param_6,0);
    }
    else {
      if (lVar2 == 0) goto LAB_1806fbfff;
      BuffContainer_DecStackCntBuffsOrMarkFinish_0x600ff2b(lVar2,param_2,param_4,param_5,param_6,0);
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp3047_0x6001647
              (lVar2,param_1,param_2,param_3,param_4,CONCAT44(uVar3,param_5),param_6,0);
  }
  return;
}

