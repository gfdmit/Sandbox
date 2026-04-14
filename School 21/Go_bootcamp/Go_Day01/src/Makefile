EXECUTABLE00 = readDB
EXECUTABLE01 = compareDB
EXECUTABLE02 = compareFS

ex00:
	@cd ex00 && go build -o $(EXECUTABLE00)
	@mv ex00/$(EXECUTABLE00) ./

ex01:
	@cd ex01 && go build -o $(EXECUTABLE01)
	@mv ex01/$(EXECUTABLE01) ./

ex02:
	@cd ex02 && go build -o $(EXECUTABLE02)
	@mv ex02/$(EXECUTABLE02) ./

clean:
	@rm -rf $(EXECUTABLE00)
	@rm -rf $(EXECUTABLE01)
	@rm -rf $(EXECUTABLE02)

.PHONY: ex00 ex01 ex02