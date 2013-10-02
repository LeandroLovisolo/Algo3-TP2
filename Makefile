.PHONY: all clean

###############################################################################
# Flags                                                                       #
###############################################################################

# Directorio de la la librería googletest
GTEST_DIR = lib/gtest-1.6.0

# Flags del preprocesador C++.
CPPFLAGS += -I$(GTEST_DIR)/include -Isrc

# Flags del compilador C++.
CXXFLAGS += -g -Wall -Wextra -std=c++0x

# Comando para generar código objeto (.o)
OBJ       = $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c

# Comando para generar los binarios de las soluciones
BIN_MAIN  = $(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

# Comando para generar los binarios de los tests
BIN_TEST  = $(BIN_MAIN) -lpthread

# Dependencias extra para los binarios de los tests
TEST_DEPS = gtest-all.o

# Binarios generados
BINS      = problema1 problema1_tests problema1_perf \
            problema2 problema2_tests problema2_perf\
            problema3 problema3_tests problema3_perf

###############################################################################
# Targets generales                                                           #
###############################################################################

all: $(BINS)

clean:
	rm -f *.o $(BINS)
	rm -f informe.pdf tex/*.pdf tex/*.aux tex/*.log tex/*.toc

gtest-all.o:
	$(OBJ) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc

###############################################################################
# Problema 1                                                                  #
###############################################################################

problema1: problema1.o problema1_main.o
	$(BIN_MAIN)

problema1.o: src/problema1/problema1.cpp src/problema1/problema1.h
	$(OBJ) src/problema1/problema1.cpp

problema1_main.o: src/problema1/problema1.h src/problema1/problema1_main.cpp
	$(OBJ) src/problema1/problema1_main.cpp

problema1_tests: $(TEST_DEPS) problema1.o problema1_tests.o
	$(BIN_TEST)

problema1_tests.o: src/problema1/problema1.h src/problema1/problema1_tests.cpp
	$(OBJ) src/problema1/problema1_tests.cpp

problema1_perf: $(TEST_DEPS) problema1.o problema1_perf.o
	$(BIN_TEST)

problema1_perf.o: src/problema1/problema1.h src/problema1/problema1_perf.cpp src/medir.h
	$(OBJ) src/problema1/problema1_perf.cpp

###############################################################################
# Problema 2                                                                  #
###############################################################################

problema2: problema2.o problema2_main.o
	$(BIN_MAIN)

problema2.o: src/problema2/problema2.cpp src/problema2/problema2.h
	$(OBJ) src/problema2/problema2.cpp

problema2_main.o: src/problema2/problema2.h src/problema2/problema2_main.cpp
	$(OBJ) src/problema2/problema2_main.cpp

problema2_tests: $(TEST_DEPS) problema2.o problema2_tests.o
	$(BIN_TEST)

problema2_tests.o: src/problema2/problema2.h src/problema2/problema2_tests.cpp
	$(OBJ) src/problema2/problema2_tests.cpp

problema2_perf: $(TEST_DEPS) problema2.o problema2_perf.o
	$(BIN_TEST)

problema2_perf.o: src/problema2/problema2.h src/problema2/problema2_perf.cpp src/medir.h
	$(OBJ) src/problema2/problema2_perf.cpp

###############################################################################
# Problema 3                                                                  #
###############################################################################

problema3: problema3.o problema3_main.o
	$(BIN_MAIN)

problema3.o: src/problema3/problema3.cpp src/problema3/problema3.h
	$(OBJ) src/problema3/problema3.cpp

problema3_main.o: src/problema3/problema3.h src/problema3/problema3_main.cpp
	$(OBJ) src/problema3/problema3_main.cpp

problema3_tests: $(TEST_DEPS) problema3.o problema3_tests.o
	$(BIN_TEST)

problema3_tests.o: src/problema3/problema3.h src/problema3/problema3_tests.cpp
	$(OBJ) src/problema3/problema3_tests.cpp

problema3_perf: $(TEST_DEPS) problema3.o problema3_perf.o
	$(BIN_TEST)

problema3_perf.o: src/problema3/problema3.h src/problema3/problema3_perf.cpp src/medir.h
	$(OBJ) src/problema3/problema3_perf.cpp

###############################################################################
# Informe                                                                     #
###############################################################################

.PHONY: graficos

informe.pdf: tex/*.tex
	cd tex; pdflatex -interactive=nonstopmode -halt-on-error informe.tex
	cd tex; pdflatex -interactive=nonstopmode -halt-on-error informe.tex
	cp tex/informe.pdf .

graficos: graficos-problema1 graficos-problema2 graficos-problema3

###############################################################################
# Gráficos problema 1                                                         #
###############################################################################

.PHONY: graficos-problema1 \
	    graficos-problema1-caso-general \
	    graficos-problema1-instancias-aleatorias \
	    graficos-problema1-instancias-aleatorias \
	    grafico-problema1-caso-general \
	    grafico-problema1-caso-general-n \
	    grafico-problema1-caso-general-n2 \
	    grafico-problema1-instancias-aleatorias \
	    grafico-problema1-instancias-aleatorias-n \
	    grafico-problema1-instancias-aleatorias-n2

graficos-problema1: graficos-problema1-caso-general \
	                graficos-problema1-instancias-aleatorias

graficos-problema1-caso-general: grafico-problema1-caso-general \
	                             grafico-problema1-caso-general-n \
	                             grafico-problema1-caso-general-n2

graficos-problema1-instancias-aleatorias: grafico-problema1-instancias-aleatorias \
	                                      grafico-problema1-instancias-aleatorias-n \
	                                      grafico-problema1-instancias-aleatorias-n2

grafico-problema1-caso-general:
	octave/graficar problema1-caso-general

grafico-problema1-caso-general-n:
	octave/graficar problema1-caso-general-n

grafico-problema1-caso-general-n2:
	octave/graficar problema1-caso-general-n2

grafico-problema1-instancias-aleatorias:
	octave/graficar problema1-instancias-aleatorias

grafico-problema1-instancias-aleatorias-n:
	octave/graficar problema1-instancias-aleatorias-n

grafico-problema1-instancias-aleatorias-n2:
	octave/graficar problema1-instancias-aleatorias-n2

###############################################################################
# Gráficos problema 2                                                         #
###############################################################################

.PHONY: graficos-problema2 \
	    graficos-problema2-caso-general \
	    graficos-problema2-instancias-aleatorias \
	    graficos-problema2-instancias-aleatorias \
	    grafico-problema2-caso-general \
	    grafico-problema2-caso-general-n \
	    grafico-problema2-instancias-aleatorias \
	    grafico-problema2-instancias-aleatorias-n

graficos-problema2: graficos-problema2-caso-general \
	                graficos-problema2-instancias-aleatorias

graficos-problema2-caso-general: grafico-problema2-caso-general \
	                             grafico-problema2-caso-general-n

graficos-problema2-instancias-aleatorias: grafico-problema2-instancias-aleatorias \
	                                      grafico-problema2-instancias-aleatorias-n

grafico-problema2-caso-general:
	octave/graficar problema2-caso-general

grafico-problema2-caso-general-n:
	octave/graficar problema2-caso-general-n

grafico-problema2-instancias-aleatorias:
	octave/graficar problema2-instancias-aleatorias

grafico-problema2-instancias-aleatorias-n:
	octave/graficar problema2-instancias-aleatorias-n

###############################################################################
# Gráficos problema 3                                                         #
###############################################################################

.PHONY: graficos-problema3 \
	    grafico-problema3-peor-caso \
	    grafico-problema3-mejor-caso \
	    grafico-problema3-instancias-aleatorias \

graficos-problema3: grafico-problema3-peor-caso \
	                grafico-problema3-mejor-caso \
	                grafico-problema3-instancias-aleatorias

grafico-problema3-peor-caso:
	octave/graficar problema3-peor-caso

grafico-problema3-mejor-caso:
	octave/graficar problema3-mejor-caso

grafico-problema3-instancias-aleatorias:
	octave/graficar problema3-instancias-aleatorias