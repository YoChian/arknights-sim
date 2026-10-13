from pathlib import Path
OUT=Path(__file__).parent
source=(OUT/'raw_selected.py').read_text('utf8').replace("OUT/'input.json'","OUT/'input_extra.json'").replace("OUT/'raw.json'","OUT/'raw_extra.json'")
exec(compile(source,str(OUT/'raw_selected.py'),'exec'),{'__file__':str(OUT/'raw_selected.py')})
