
void Torappu_Battle_BObject_Init_0x600fe06
               (longlong *param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,
               undefined4 param_5)

{
  *(undefined4 *)((longlong)param_1 + 0x1c) = param_2;
  *(undefined4 *)(param_1 + 4) = param_3;
  Torappu_Battle_VisualObject_SetPositionWithHeight_0x601303b(param_4,param_4,param_5,0);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  (**(code **)(*param_1 + 800))(param_1,param_5,*(undefined8 *)(*param_1 + 0x328));
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  (**(code **)(*param_1 + 0x330))(param_1,*(undefined8 *)(*param_1 + 0x338));
  *(undefined1 *)((longlong)param_1 + 0x24) = 1;
  return;
}

