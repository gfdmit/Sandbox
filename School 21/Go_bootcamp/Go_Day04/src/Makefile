CERT = ../../../../EX01/certs/localhost/cert.pem
KEY = ../../../../EX01/certs/localhost/key.pem
RUN = ./candy-server-server --tls-port=3333 --tls-key $(KEY) --tls-certificate $(CERT)

EX00: 
	cd ./EX00/cmd/candy-server-server/ && go build
	./EX00/cmd/candy-server-server/candy-server-server --port=3333

EX01_server:
	cd ./EX01/candy_server/cmd/candy-server-server/ && go build
	cd ./EX01/candy_server/cmd/candy-server-server/ && $(RUN)

EX01_client:
	cd ./EX01/candy_client/ && go build && ./candy-client

EX02_server:
	cd ./EX02/candy_server/cmd/candy-server-server/ && go build
	cd ./EX02/candy_server/cmd/candy-server-server/ && $(RUN)

clean:
	-rm -f ./EX00/cmd/candy-server-server/candy-server-server
	-rm -f ./EX01/candy_server/cmd/candy-server-server/candy-server-server
	-rm -f ./EX02/candy_server/cmd/candy-server-server/candy-server-server
	-rm -f ./EX01/candy_client/candy_client

test_EX00:
	curl -XPOST -H "Content-Type: application/json" -d '{"money": 20, "candyType": "AA", "candyCount": 1}' http://127.0.0.1:3333/buy_candy
	curl -XPOST -H "Content-Type: application/json" -d '{"money": 46, "candyType": "YR", "candyCount": 2}' http://127.0.0.1:3333/buy_candy

test_EX01:
	cd ./EX01/candy_client/ && go build && ./candy*client -k AA -c 2 -m 50

test_EX02:
	curl -X POST "https://localhost:3333/buy_candy" --cacert EX01/certs/minica.pem --cert EX01/certs/client.crt --key EX01/certs/client.key -H "Content-Type: application/json" -H "x-token: abcdefuvwxyz" -d "{\"money\":34,\"candyType\":\"NT\",\"candyCount\":2}"