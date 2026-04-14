EXECUTABLE = stats

all: run

build:
	@go build

run: build
	@./$(EXECUTABLE)

test:
	@cd test && go test -v

clean:
	@rm -rf $(EXECUTABLE)