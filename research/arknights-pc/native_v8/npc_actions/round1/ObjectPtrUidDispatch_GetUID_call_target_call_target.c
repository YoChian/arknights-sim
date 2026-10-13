
/* WARNING: Removing unreachable block (ram,0x000183349826) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong ObjectPtrUidDispatch_GetUID_call_target_call_target(longlong *param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined8 *puVar7;
  ulonglong uVar8;
  ushort uVar9;
  longlong lVar10;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined *puStack_30;
  undefined8 *puStack_28;
  
  lVar10 = _DAT_188803fb0;
  switch(*(undefined4 *)(*param_1 + 0x11c)) {
  case 0x4f:
  case 0x50:
  case 0x51:
  case 0x52:
  case 0x58:
  case 0x59:
  case 0x5a:
  case 0x5b:
  case 0x5c:
    if (cRam0000000188c915dc == '\0') {
      puStack_30 = &UNK_1808c5c4e;
      FUN_18048bf00(0x1888c8ad0,0);
      cRam0000000188c915dc = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam00000001888c8ad0 + 0xb8) + 0x38);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 0x25);
    }
    break;
  case 0x53:
  case 0x54:
  case 0x5e:
  case 0x5f:
  case 0x60:
  case 0x61:
  case 0x62:
  case 99:
  case 100:
  case 0x65:
  case 0x66:
  case 0x67:
  case 0x68:
  case 0x69:
  case 0x6a:
  case 0x6b:
  case 0x6c:
  case 0x6d:
  case 0x6e:
  case 0x6f:
  case 0x70:
  case 0x71:
  case 0x72:
  case 0x73:
  case 0x80:
  case 0x81:
  case 0xe7:
    return (ulonglong)*(uint *)(param_1 + 3);
  default:
    lVar1 = *param_1;
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (undefined *)0x180bfed75;
      func_0x000180446d00();
    }
    uVar9 = 0;
    if (*(ushort *)(lVar1 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar9 * 0x10) == lVar10) {
          puVar7 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar9 * 0x10) +
                    0x14) * 0x10 + lVar1);
          goto LAB_180bfedb2;
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < *(ushort *)(lVar1 + 0x12e));
    }
    puStack_30 = (undefined *)0x180bfedb2;
    puVar7 = (undefined8 *)FUN_180445cc0(param_1,lVar10,0);
LAB_180bfedb2:
                    /* WARNING: Could not recover jumptable at 0x000180bfedcb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar8 = (*(code *)*puVar7)(param_1,puVar7[1],(code *)*puVar7);
    return uVar8;
  case 0x74:
    return (ulonglong)*(uint *)(param_1 + 10);
  case 0x75:
  case 0x76:
  case 0x84:
  case 0x85:
  case 0x86:
  case 0x87:
  case 0x88:
  case 0x89:
  case 0x8a:
  case 0x8b:
  case 0x8c:
  case 0x8d:
  case 0x8e:
  case 0x8f:
  case 0x90:
  case 0x91:
  case 0x92:
  case 0x93:
  case 0x94:
  case 0x95:
  case 0x96:
  case 0x97:
  case 0x98:
  case 0x99:
  case 0x9a:
  case 0x9b:
  case 0x9c:
  case 0x9d:
  case 0x9e:
  case 0x9f:
  case 0xa0:
  case 0xa1:
  case 0xa2:
  case 0xa3:
  case 0xa4:
  case 0xa5:
  case 0xa6:
  case 0xa7:
  case 0xa8:
  case 0xa9:
  case 0xaa:
  case 0xab:
  case 0xac:
  case 0xad:
  case 0xae:
  case 0xaf:
  case 0xb0:
  case 0xb1:
  case 0xb2:
  case 0xb3:
  case 0xb4:
  case 0xb5:
  case 0xb6:
  case 0xb7:
  case 0xb8:
  case 0xb9:
  case 0xba:
  case 0xbb:
  case 0xbc:
  case 0xbd:
  case 0xbe:
  case 0xbf:
  case 0xc0:
  case 0xc1:
  case 0xc2:
  case 0xc3:
  case 0xc4:
  case 0xc5:
  case 0xc6:
  case 199:
  case 200:
  case 0xc9:
  case 0xca:
  case 0xcb:
  case 0xcc:
  case 0xcd:
  case 0xce:
    if (cRam0000000188c8fcbc == '\0') {
      puStack_30 = &UNK_1805d7c7e;
      FUN_18048bf00(0x1889733f0,0);
      cRam0000000188c8fcbc = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam00000001889733f0 + 0xb8) + 8);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 0xb);
    }
    break;
  case 0x77:
    if (cRam0000000188c902a7 == '\0') {
      puStack_30 = &UNK_18068ecde;
      FUN_18048bf00(0x18895c250,0);
      cRam0000000188c902a7 = '\x01';
    }
    if (*(int *)(lRam000000018895c250 + 0xe0) == 0) {
      puStack_30 = &UNK_18068ecfd;
      func_0x00018048c140(lRam000000018895c250);
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam000000018895c250 + 0xb8) + 0x48);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 0x43);
    }
    break;
  case 0x78:
    if (cRam0000000188c906a6 == '\0') {
      puStack_30 = &UNK_1806daf2e;
      FUN_18048bf00(0x188882280,0);
      cRam0000000188c906a6 = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam0000000188882280 + 0xb8) + 0x68);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 0xb);
    }
    break;
  case 0x79:
  case 0x7a:
  case 0x7b:
    if (cRam0000000188c90afa == '\0') {
      puStack_30 = &UNK_18072fe8e;
      FUN_18048bf00(0x1888b9a90,0);
      cRam0000000188c90afa = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam00000001888b9a90 + 0xb8) + 0xb8);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 0x29);
    }
    break;
  case 0x7c:
  case 0x7d:
    if (cRam0000000188c90b7f == '\0') {
      puStack_30 = &UNK_18075612e;
      FUN_18048bf00(0x188874bf8,0);
      cRam0000000188c90b7f = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam0000000188874bf8 + 0xb8) + 0x58);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)((longlong)param_1 + 0x34);
    }
    break;
  case 0x7e:
  case 0xd4:
  case 0xe3:
  case 0xe6:
    if (cRam0000000188c913dc == '\0') {
      puStack_30 = &UNK_1808780ee;
      FUN_18048bf00(0x188834478,0);
      cRam0000000188c913dc = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam0000000188834478 + 0xb8) + 8);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 4);
    }
    break;
  case 0x7f:
  case 0xd3:
  case 0xd5:
  case 0xd6:
  case 0xd7:
  case 0xdc:
  case 0xe0:
    if (cRam0000000188c91fb6 == '\0') {
      puStack_30 = &UNK_18099f7be;
      FUN_18048bf00(0x18880fcc8,0);
      cRam0000000188c91fb6 = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam000000018880fcc8 + 0xb8) + 8);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 3);
    }
    break;
  case 0x82:
  case 0x83:
    return (ulonglong)*(uint *)((longlong)param_1 + 0x84);
  case 0xcf:
  case 0xd0:
  case 0xd1:
  case 0xd2:
    if (cRam0000000188c977af == '\0') {
      puStack_30 = &UNK_18119a8de;
      FUN_18048bf00(0x18880f9b0,0);
      cRam0000000188c977af = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam000000018880f9b0 + 0xb8) + 0x28);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 0x19);
    }
    break;
  case 0xd8:
  case 0xda:
  case 0xdf:
  case 0xe1:
  case 0xe2:
  case 0xe4:
  case 0xe5:
  case 0xe8:
    if (cRam0000000188c98240 == '\0') {
      puStack_30 = &UNK_18128636e;
      FUN_18048bf00(0x188934c60,0);
      cRam0000000188c98240 = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam0000000188934c60 + 0xb8) + 8);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 3);
    }
    break;
  case 0xd9:
    if (cRam0000000188c97c1e == '\0') {
      puStack_30 = &UNK_1811f62ae;
      FUN_18048bf00(0x18894ada0,0);
      cRam0000000188c97c1e = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam000000018894ada0 + 0xb8) + 8);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 0x13);
    }
    break;
  case 0xdb:
  case 0xde:
    if (cRam0000000188c98358 == '\0') {
      puStack_30 = &UNK_1812abb5e;
      FUN_18048bf00(0x188956ce8,0);
      cRam0000000188c98358 = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam0000000188956ce8 + 0xb8) + 8);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 5);
    }
    break;
  case 0xdd:
    if (cRam0000000188c98371 == '\0') {
      puStack_30 = &UNK_1812afbbe;
      FUN_18048bf00(0x18896b308,0);
      cRam0000000188c98371 = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(lRam000000018896b308 + 0xb8) + 8);
    if (lVar10 == 0) {
      return (ulonglong)*(uint *)(param_1 + 0x13);
    }
  }
  if (*(longlong *)(lVar10 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x000183349874:
    FUN_18048c0b0();
code_r0x00018334987a:
    FUN_18048c0b0();
  }
  else {
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
    if (*(longlong *)(lVar10 + 0x18) == 0) goto code_r0x000183349884;
    uVar2 = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar10 + 0x38),*(undefined4 *)(lVar10 + 0x14),0);
    if (*(longlong *)(lVar10 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar10 + 0x18) + 0x20);
      if (lVar1 == 0) goto code_r0x000183349874;
      FUN_183cf8c20(lVar1,uVar2,param_1,0);
      iVar5 = FUN_183f22380(uVar2,1,1,iVar4,0);
      if (iVar5 == 0) {
code_r0x0001833497f7:
        uVar6 = FUN_183f256f0(uVar2,iVar4 + 1,0);
        FUN_183f22fd0(uVar2,iVar4 + -1,0);
        return (ulonglong)uVar6;
      }
      if (*(longlong *)(lVar10 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar10 + 0x18),iVar4 + -1,0);
        goto code_r0x0001833497f7;
      }
      goto code_r0x00018334987a;
    }
  }
  FUN_18048c0b0();
code_r0x000183349884:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  uVar8 = (*pcVar3)();
  return uVar8;
}

