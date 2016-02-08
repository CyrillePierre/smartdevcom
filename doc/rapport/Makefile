
MAIN     = rapport.tex
COMPILER = pdflatex
VIEWER	 = evince
SRC      = $(wildcard *.tex)
PDF      = $(MAIN:.tex=.pdf)

LATEX_FLAGS = -file-line-error -interaction nonstopmode

all : $(PDF)
	$(VIEWER) $<

$(PDF) : $(SRC)
	$(COMPILER) $(LATEX_FLAGS) $(MAIN)

clean :
	rm *.aux *.pdf
