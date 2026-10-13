"""Exact NPC restore state/cursor field/type layout, no target execution."""
from pathlib import Path
import json
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v4/resources/export_native_fields.py';code=source.read_text()
ns={'__file__':str(source)};exec(code.split('roots={')[0],ns)
roots={11377,11393,10657,10658,10670,11352}
roots.update(i for i,parent in ns['parents'].items() if parent==11377)
start=code.index('roots={');finish=code.index('selected=set(roots)',start)
ns={'__file__':str(OUT/'export_fields.py')}
exec(code[:start]+'roots='+repr(roots)+'\n'+code[finish:],ns)
