
void Torappu_StateMachine_Tick_0x60081fb(longlong *param_1,undefined8 param_2)

{
  if (param_1[10] != 0) {
    FUN_185c34d70(param_1[10],param_2,0);
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
                    /* WARNING: Could not recover jumptable at 0x000182648435. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x1c0))(param_1,param_2,*(undefined8 *)(*param_1 + 0x1c8));
  return;
}

