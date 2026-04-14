package datajson

type Body struct {
	Id      string      `json:"id"`
	Name    string      `json:"name"`
	Address string      `json:"address"`
	Phone   string      `json:"phone"`
	Map     Geolocation `json:"location"`
}

type Geolocation struct {
	Lat string `json:"lat"`
	Lon string `json:"lon"`
}

type Err struct {
	Err string `json:"error"`
}
