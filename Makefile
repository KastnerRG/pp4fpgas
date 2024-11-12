base=main
all: main.pdf

# pdflatex is part of the Texlive distribution.  
#
# See https://tug.org/texlive/ for TexLive installation instructions.
# Docker image available at https://hub.docker.com/r/texlive/texlive/

# NOTE: You *must* put the path to your texlive installation here.
TEXLIVE_BINDIR=/wrk/xsjhdnobkup2/mpettigr/projects_nobkup/texlive/texlive/install-tl-20240625/./texlive/2024/bin/x86_64-linux
PDFLATEX=PATH=$(TEXLIVE_BINDIR):$$PATH $(TEXLIVE_BINDIR)/pdflatex
BIBTEX=PATH=$(TEXLIVE_BINDIR):$$PATH $(TEXLIVE_BINDIR)/bibtex

main.aux: all.bib
	$(PDFLATEX) \\nonstopmode\\input main.tex
	$(BIBTEX) main

main.pdf: main.aux *.tex
	$(PDFLATEX) \\nonstopmode\\input main.tex
	$(PDFLATEX) \\nonstopmode\\input main.tex

clean:
	rm -rf main.pdf *.log *~ *.aux *.bbl *.blg *.out

