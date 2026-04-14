EXECUTABLE00 = logo
EXECUTABLE01 = blog

all: ex00 ex01

ex00:
	@cd ex00 && go build -o $(EXECUTABLE00)
	@mv ex00/$(EXECUTABLE00) ./

ex01:
	@cd ex01/cmd && go build -o $(EXECUTABLE01)
	@mv ex01/cmd/$(EXECUTABLE01) ./

clean:
	@rm -rf $(EXECUTABLE00)
	@rm -rf $(EXECUTABLE01)

.PHONY: ex00 ex01