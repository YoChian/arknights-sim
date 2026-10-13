from pathlib import Path
import json
from ark_bundle import decode_code4,DecodeError
good=b'\x21a\x00\x01\x05hello'
assert decode_code4(good,12)==b'aaaaaaahello'
cases={'zero_offset':(b'\x01a\x00\x00',5),'out_of_history':(b'\x01a\x00\x02',5),'truncated_offset':(b'\x01a\x00',5),'truncated_extension':(b'\x0f\xff',1000),'truncated_literals':(b'\x05x',5),'literal_output_overflow':(b'\x05hello',4),'match_output_overflow':(good,8),'declared_length_mismatch':(good,13)}
rows=[]
for name,(data,size) in cases.items():
 try:decode_code4(data,size)
 except DecodeError as ex:rows.append({'case':name,'rejected':True,'reason':str(ex)})
 else:raise AssertionError('malformed source accepted '+name)
(Path(__file__).parent/'codec_bounds.json').write_text(json.dumps({'valid_overlap_case_passed':True,'malformed_cases':rows},indent=2),'utf-8')
print('valid overlap verified; 8 malformed cases rejected')
