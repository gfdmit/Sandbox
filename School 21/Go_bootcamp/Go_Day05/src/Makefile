EXECUTABLE00 = dfs
EXECUTABLE01 = bfs
EXECUTABLE02 = heap
EXECUTABLE03 = knapsack

all: ex00 ex01 ex02 ex03

ex00:
	@cd ex00 && go build -o $(EXECUTABLE00)
	@mv ex00/$(EXECUTABLE00) ./

ex01:
	@cd ex01 && go build -o $(EXECUTABLE01)
	@mv ex01/$(EXECUTABLE01) ./

ex02:
	@cd ex02 && go build -o $(EXECUTABLE02)
	@mv ex02/$(EXECUTABLE02) ./

ex03:
	@cd ex03 && go build -o $(EXECUTABLE03)
	@mv ex03/$(EXECUTABLE03) ./

clean:
	@rm -rf $(EXECUTABLE00)
	@rm -rf $(EXECUTABLE01)
	@rm -rf $(EXECUTABLE02)
	@rm -rf $(EXECUTABLE03)

.PHONY: ex00 ex01 ex02 ex03