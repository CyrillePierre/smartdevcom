
MAIN     = rapport.tex
COMPILER = pdflatex
SRC      = $(wildcard *.tex)
PDF      = $(MAIN:.tex=.pdf)

LATEX_FLAGS = -file-line-error -interaction nonstopmode

$(PDF) : $(SRC)
	$(COMPILER) $(LATEX_FLAGS) $(MAIN)

clean :
	rm *.aux *.pdf
