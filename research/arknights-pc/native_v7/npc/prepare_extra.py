"""Prepare the separate follow-up input without rewriting round-one selection."""
from pathlib import Path
OUT=Path(__file__).parent
source=(OUT/'prepare.py').read_text('utf8').replace("OUT/'selection.json'","OUT/'selection_extra.json'").replace("OUT/'input.json'","OUT/'input_extra.json'")
exec(compile(source,str(OUT/'prepare.py'),'exec'),{'__file__':str(OUT/'prepare.py')})
