from pathlib import Path
import json,struct
out=Path(r'D:\Repo\.rea-tools\arknights-pc/native_v9/buff_container');helper=out.parents[1]/'native_v7/targeting/inspect_generic_dispatch.py';ns={'__file__':str(helper)};exec(helper.read_text('utf8').split('outputs=[]')[0],ns)
ident=out.parents[1]/'native_v6/targeting/inspect_generic_identities.py';g={'__file__':str(ident)};exec(ident.read_text('utf8').split('records = []')[0],g)
records=[]
for idx,spec in enumerate(ns['specs']):
 if not 25811<=spec[0]<=25826:continue
 ci=g['generic_inst'](spec[1])
 if spec[1]!=14170:continue
 matched=[(i,x) for i,x in enumerate(ns['funcs']) if x[0]==idx]
 if len(matched)!=1:continue
 i,rec=matched[0];m=g['ns']['methods'][spec[0]];pointer=ns['pointers'][rec[1]]
 records.append(dict(metadata_method_index=spec[0],type=g['ns']['fullname'](m[1]),method=g['ns']['text'](m[0]),token=hex(m[5]),address=hex(pointer),method_spec_index=idx,class_generic_inst=ci,generic_pointer_index=rec[1],pointer_file_offset=ns['table_off']+rec[1]*8,method_table_record_file_offset=ns['function_off']+i*16,method_table_raw16=ns['b'][ns['function_off']+i*16:ns['function_off']+i*16+16].hex()))
(out/'generic_iterator_identities.json').write_text(json.dumps(records,indent=2),'utf8')
print(json.dumps([{k:r[k] for k in ('metadata_method_index','type','method','address')} for r in records],indent=2))
selection=[{k:r[k] for k in ('type','method','metadata_method_index','token','address')}|{'raw_call_target':True,'reason':'Original generic function table binding closed Buff pointer iterator method; reusable iterator/reentry/dispose closure'} for r in records]
(out/'selection_extra.json').write_text(json.dumps(selection,indent=2),'utf8')

