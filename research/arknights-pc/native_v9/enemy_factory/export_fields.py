"""Original factory/Enemy/Talent/BORN offsets and metadata identities."""
from pathlib import Path
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v4/resources/export_native_fields.py';code=source.read_text(encoding='utf-8')
ns={'__file__':str(source)};exec(code.split('roots={')[0],ns)
names={'Torappu.Battle.Enemy','Torappu.Battle.Entity','Torappu.Battle.Unit','Torappu.Battle.BObject',
       'Torappu.Battle.BasicTalent','Torappu.Battle.Talent','Torappu.Battle.Enemy.Options',
       'Torappu.Battle.Enemy.States.BornState','Torappu.Battle.BattleFactory'}
roots={i for i in range(len(ns['types'])) if ns['fullname'](i) in names}
start=code.index('roots={');finish=code.index('selected=set(roots)',start)
exec(code[:start]+'roots='+repr(roots)+'\n'+code[finish:],{'__file__':str(OUT/'export_fields.py')})
