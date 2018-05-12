base=main
all: main.pdf

main.aux: all.bib
	pdflatex \\nonstopmode\\input main.tex
	bibtex main

main.pdf: main.aux *.tex
	pdflatex \\nonstopmode\\input main.tex
	pdflatex \\nonstopmode\\input main.tex

clean:
	rm -rf main.pdf *.log *~ *.aux *.bbl *.blg *.out
