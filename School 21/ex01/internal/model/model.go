package model

type Admin struct {
	Login    string `json:"login"`
	Password string `json:"password"`
}

type DataNote struct {
	Id      int    `json:"id"`
	Title   string `json:"title"`
	Preview string `json:"preview"`
	Content string `json:"content"`
}
