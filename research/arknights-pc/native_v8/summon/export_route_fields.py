from pathlib import Path
source=Path(__file__).resolve().parents[2]/'native_v4/resources/export_native_fields.py'
text=source.read_text()
a=text.index('roots={');z=text.index('selected=set(roots)',a)
text=text[:a]+'roots={4648,4649}\n'+text[z:]
exec(compile(text,str(source),'exec'),{'__file__':__file__})
