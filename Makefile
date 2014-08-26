all:
	pandoc --template=./template.tex --latex-engine=xelatex --toc -s -S -N -o design_pattern.pdf `ls contents/*.md`
