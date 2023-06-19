LATEX 		= latex
BIBTEX		= bibtex
PDFLATEX	= pdflatex

DOC		= thesis
LITERATUR	= literatur
WEBLINK		= weblink

all: pdf


run-bibtex:
	$(BIBTEX) $(LITERATUR)
	$(BIBTEX) $(WEBLINK)

pdf:
	$(PDFLATEX) -shell-escape $(DOC)
	$(MAKE) run-bibtex
	$(PDFLATEX) -shell-escape $(DOC)
	$(PDFLATEX) -shell-escape $(DOC)

clean_all:
	$(MAKE) clean
	-rm -f *.pdf

clean:
	-rm -f *.aux *.dvi *.out *.idx *.lof *.lot *.toc literatur.* weblink.*
	-rm -f chapter/*.aux
	-rm -f title/*.aux
