"""Bounded v29 metadata constants, per Il2CppDumper author's blob readers.

Primary sources (accessed 2026-10-13):
https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Extensions/BinaryReaderExtensions.cs
https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Utils/Il2CppExecutor.cs
Unsupported tags are rejected. No target constructor is executed.
"""
import math,struct

class Cursor:
    def __init__(self,data,start=0,end=None):
        self.data=data;self.start=start;self.pos=start;self.end=len(data) if end is None else end
        if not 0<=start<=self.end<=len(data):raise ValueError('invalid blob bounds')
    def take(self,n):
        if not 0<=n<=self.end-self.pos:raise ValueError('truncated metadata blob')
        result=self.data[self.pos:self.pos+n];self.pos+=n;return result
    def unpack(self,fmt):return struct.unpack('<'+fmt,self.take(struct.calcsize('<'+fmt)))[0]
    def uint(self):
        first=self.unpack('B')
        if first&0x80==0:return first
        if first&0xc0==0x80:return ((first&0x7f)<<8)|self.unpack('B')
        if first&0xe0==0xc0:return ((first&0x3f)<<24)|int.from_bytes(self.take(3),'big')
        if first==0xf0:return self.unpack('I')
        if first==0xfe:return 0xfffffffe
        if first==0xff:return 0xffffffff
        raise ValueError('invalid compressed integer format '+hex(first))
    def sint(self):
        value=self.uint()
        if value==0xffffffff:return -2147483648
        return -(1+(value>>1)) if value&1 else value>>1

def primitive_value(cursor,tag):
    if tag==8:return cursor.sint()
    if tag==9:return cursor.uint()
    fmt={2:'B',3:'H',4:'b',5:'B',6:'h',7:'H',10:'q',11:'Q',12:'f',13:'d'}.get(tag)
    if fmt:
        value=cursor.unpack(fmt)
        if tag==2:
            if value not in [0,1]:raise ValueError('invalid attribute Boolean')
            return bool(value)
        if tag in [12,13] and not math.isfinite(value):raise ValueError('nonfinite attribute scalar')
        return value
    if tag==14:
        length=cursor.sint()
        if length==-1:return None
        if length<0:raise ValueError('negative string length')
        return cursor.take(length).decode('utf-8')
    raise ValueError('unsupported constant tag '+hex(tag))
