ui_mockup.pdf: ui_mockup.typ graphics/home.svg graphics/setup.svg graphics/int2.svg graphics/int1.svg graphics/int10.svg graphics/int100.svg graphics/int169.svg graphics/int550.svg graphics/time.09.svg graphics/time9m30.svg graphics/time24m.svg graphics/time9h30m.svg
	typst compile $<

graphics/home.svg: Makefile
	python3 gen_matrix.py \
		111000010 \
		100100110 \
		100100010 \
		111000010 \
		100000010 \
		$@

graphics/setup.svg: Makefile
	python3 gen_matrix.py \
		111101001 \
		100001001 \
		111100110 \
		100001001 \
		111101001 \
		$@

graphics/int1.svg: Makefile
	python3 gen_matrix.py \
		000000010 \
		000000110 \
		000000010 \
		000000010 \
		000000010 \
		$@

graphics/int2.svg: Makefile
	python3 gen_matrix.py \
		000000110 \
		000001001 \
		000000010 \
		000000100 \
		000001111 \
		$@

graphics/int10.svg: Makefile
	python3 gen_matrix.py \
		001001111 \
		011001001 \
		001001001 \
		001001001 \
		001001111 \
		$@

graphics/int100.svg: Makefile
	python3 gen_matrix.py \
		101110111 \
		101010101 \
		101010101 \
		101010101 \
		101110111 \
		$@

graphics/int169.svg: Makefile
	python3 gen_matrix.py \
		101110111 \
		101000101 \
		101110111 \
		101010001 \
		101110111 \
		$@

graphics/int550.svg: Makefile
	python3 gen_matrix.py \
		111011100 \
		100010000 \
		111011101 \
		001000100 \
		111011100 \
		$@
	
graphics/time.09.svg: Makefile
	python3 gen_matrix.py \
		001110111 \
		001010101 \
		001010111 \
		001010001 \
		101110111 \
		$@
	
graphics/time9m30.svg: Makefile
	python3 gen_matrix.py \
		111000111 \
		101010001 \
		111000111 \
		001010001 \
		111000111 \
		$@
	
graphics/time24m.svg: Makefile
	python3 gen_matrix.py \
		111010100 \
		001010101 \
		111011100 \
		100000101 \
		111000100 \
		$@

graphics/time9h30m.svg: Makefile
	python3 gen_matrix.py \
		111010111 \
		101010001 \
		111000111 \
		001010001 \
		111010111 \
		$@

watch:
	zathura ui_mockup.pdf &
	echo ./ui_mockup.typ | entr make &
	echo ./Makefile | entr make
