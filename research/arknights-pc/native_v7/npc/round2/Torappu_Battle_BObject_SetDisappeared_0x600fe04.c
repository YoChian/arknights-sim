undefined8 Torappu_Battle_BObject_SetDisappeared_0x600fe04(longlong *param_1,char param_2)
{
  if (((int)param_1[3] != 0) && (param_2 != *(char *)((longlong)param_1 + 0x26))) {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    (**(code **)(*param_1 + 0x350))(param_1,param_2,*(undefined8 *)(*param_1 + 0x358));
    *(char *)((longlong)param_1 + 0x26) = param_2;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    (**(code **)(*param_1 + 0x360))(param_1,param_2,*(undefined8 *)(*param_1 + 0x368));
    return 1;
  }
  return 0;
}
