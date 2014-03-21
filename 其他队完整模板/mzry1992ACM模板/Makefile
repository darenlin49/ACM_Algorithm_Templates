all: template.pdf

%.pdf: %.dvi
	dvipdfmx $<

%.dvi: %.tex
	latex $<
	latex $<

clean:
	rm -f *.dvi
	rm -f *.pdf
