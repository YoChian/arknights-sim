
/* WARNING: Possible PIC construction at 0x000180959045: Changing call to branch */
/* WARNING: Possible PIC construction at 0x00018095906a: Changing call to branch */
/* WARNING: Possible PIC construction at 0x000180959137: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x00018095906f) */
/* WARNING: Removing unreachable block (ram,0x00018095908c) */
/* WARNING: Removing unreachable block (ram,0x00018095904a) */
/* WARNING: Removing unreachable block (ram,0x00018095913c) */
/* WARNING: Removing unreachable block (ram,0x00018095914f) */
/* WARNING: Removing unreachable block (ram,0x0001809590a0) */
/* WARNING: Removing unreachable block (ram,0x0001809590b0) */
/* WARNING: Removing unreachable block (ram,0x0001809591b4) */
/* WARNING: Removing unreachable block (ram,0x0001809590b9) */
/* WARNING: Removing unreachable block (ram,0x0001809591ba) */
/* WARNING: Removing unreachable block (ram,0x0001809590c6) */
/* WARNING: Removing unreachable block (ram,0x0001809590cf) */
/* WARNING: Removing unreachable block (ram,0x0001809590e2) */
/* WARNING: Removing unreachable block (ram,0x00018095913e) */
/* WARNING: Removing unreachable block (ram,0x0001809590f9) */
/* WARNING: Removing unreachable block (ram,0x000180959102) */
/* WARNING: Removing unreachable block (ram,0x00018095911c) */
/* WARNING: Removing unreachable block (ram,0x000180959141) */
/* WARNING: Removing unreachable block (ram,0x00018095912c) */
/* WARNING: Removing unreachable block (ram,0x000180959161) */
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_BasicSkill_Awake_0x6011c02(longlong param_1)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  longlong lVar3;
  undefined8 uVar4;
  longlong lVar5;
  code *pcVar6;
  int iVar7;
  int iVar8;
  ulonglong uVar9;
  uint uVar10;
  bool bVar11;
  
  if (DAT_188c91c73 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(&DAT_18896a750);
    FUN_18048bf00(&DAT_1888d9d98);
    FUN_18048bf00(&DAT_1888e02d8);
    FUN_18048bf00(&DAT_1889032b8);
    DAT_188c91c73 = '\x01';
  }
  lVar3 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x400);
  if (lVar3 == 0) {
    *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_1 + 0x38);
    uVar9 = FUN_1844b9cd0(param_1,_DAT_1888d9d98);
    *(ulonglong *)(param_1 + 0xc0) = uVar9;
    if (iRam0000000188cccdd8 != 0) {
      uVar10 = (uint)(param_1 + 0xc0U >> 0xc);
      puVar1 = (ulonglong *)((ulonglong)((uVar10 & 0x1fffff) >> 6) * 8 + 0x188d15560);
      do {
        uVar2 = *puVar1;
        LOCK();
        uVar9 = *puVar1;
        bVar11 = uVar2 == uVar9;
        if (bVar11) {
          *puVar1 = uVar2 | 1L << (uVar10 & 0x3f);
          uVar9 = uVar2;
        }
        UNLOCK();
      } while (!bVar11);
    }
    return uVar9;
  }
  if (*(longlong *)(lVar3 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar6 = (code *)swi(3);
    uVar9 = (*pcVar6)();
    return uVar9;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar3 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar3 + 0x18) != 0) {
    uVar4 = *(undefined8 *)(*(longlong *)(lVar3 + 0x18) + 0x10);
    iVar7 = FUN_183f23b70(uVar4,*(undefined4 *)(lVar3 + 0x38),*(undefined4 *)(lVar3 + 0x14),0);
    if (*(longlong *)(lVar3 + 0x18) != 0) {
      lVar5 = *(longlong *)(*(longlong *)(lVar3 + 0x18) + 0x20);
      if (lVar5 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar5,uVar4,param_1,0);
        iVar8 = FUN_183f22380(uVar4,1,0,iVar7,0);
        if (iVar8 == 0) {
code_r0x0001833100e8:
          uVar9 = FUN_183f22fd0(uVar4,iVar7 + -1,0);
          return uVar9;
        }
        if (*(longlong *)(lVar3 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar3 + 0x18),iVar7 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar6 = (code *)swi(3);
  uVar9 = (*pcVar6)();
  return uVar9;
}

