package formstore

import (
	"database/sql"
	"fmt"
	"strconv"
	"strings"

	_ "github.com/jackc/pgx/v4/stdlib"
)

type Form struct {
	Id          string   `json:"id"`
	Title       string   `json:"title"`
	Description string   `json:"description"`
	Author      string   `json:"author"`
	Entities    []Entity `json:"components"`
}

type Entity struct {
	Id       string   `json:"id"`
	Type     string   `json:"type"`
	Index    int      `json:"index"`
	Value    string   `json:"value"`
	Question string   `json:"question"`
	Options  []string `json:"options"`
	Answer   []string `json:"answer"`
}

func New() *Form {
	form := &Form{}
	return form
}

func (form *Form) CreateForm(fm Form) error {
	connStr := "host=localhost port=5432 user=myuser password=mypassword dbname=mydatabase sslmode=disable"

	db, err := sql.Open("pgx", connStr)
	if err != nil {
		return err
	}
	defer db.Close()

	err = db.Ping()
	if err != nil {
		return err
	}

	query := "INSERT INTO forms (id, title, description, author) VALUES ('" + fm.Id + "', '" + fm.Title + "', '" + fm.Description + "', '" + fm.Author + "');"
	fmt.Println(query)
	_, err = db.Exec(query)
	if err != nil {
		return err
	}
	for _, elem := range fm.Entities {
		query = "INSERT INTO form_entities (entity_id, form_id, entity_type, index, value, question, options, answer) VALUES ('" + elem.Id + "', '" + fm.Id + "', '" + elem.Type + "', " + strconv.Itoa(elem.Index) + ", '" + elem.Value + "', '" + elem.Question + "', ARRAY[" + strings.Join(elem.Options, ", ") + "], ARRAY[" + strings.Join(elem.Options, ", ") + "]);"
		_, err = db.Exec(query)
		if err != nil {
			return err
		}
	}

	return nil
}

func (form *Form) GetForm(id string) (Form, error) {
	connStr := "host=localhost port=5432 user=myuser password=mypassword dbname=mydatabase sslmode=disable"

	db, err := sql.Open("pgx", connStr)
	if err != nil {
		return Form{}, err
	}
	defer db.Close()

	err = db.Ping()
	if err != nil {
		return Form{}, err
	}
	query := "SELECT FROM forms * WHERE id =  '" + id + "');"
	fmt.Println(query)
	_, err = db.Exec(query)
	if err != nil {
		return Form{}, err
	}

	return Form{}, nil
}

func (form *Form) GetAllForms() ([]string, error) {
	connStr := "host=localhost port=5432 user=myuser password=mypassword dbname=mydatabase sslmode=disable"

	db, err := sql.Open("pgx", connStr)
	if err != nil {
		return nil, err
	}
	defer db.Close()

	err = db.Ping()
	if err != nil {
		return nil, err
	}
	rows, err := db.Query("SELECT id FROM forms;")
	if err != nil {
		return nil, err
	}
	defer rows.Close()

	var results []string
	for rows.Next() {
		var value string
		if err := rows.Scan(&value); err != nil {
			return nil, err
		}
		results = append(results, value)
	}
	if err := rows.Err(); err != nil {
		return nil, err
	}

	return results, nil
}

func (form *Form) UpdateForm(id string, fm Form) error {
	connStr := "host=localhost port=5432 user=myuser password=mypassword dbname=mydatabase sslmode=disable"

	db, err := sql.Open("pgx", connStr)
	if err != nil {
		return err
	}
	defer db.Close()

	err = db.Ping()
	if err != nil {
		return err
	}
	form.DeleteForm(id)
	form.CreateForm(fm)
	return nil
}

func (form *Form) DeleteForm(id string) error {
	connStr := "host=localhost port=5432 user=myuser password=mypassword dbname=mydatabase sslmode=disable"

	db, err := sql.Open("pgx", connStr)
	if err != nil {
		return err
	}
	defer db.Close()

	err = db.Ping()
	if err != nil {
		return err
	}
	query := "DELETE FROM forms WHERE id = '" + id + "';"
	_, err = db.Exec(query)
	if err != nil {
		return err
	}
	query = "DELETE FROM form_entities WHERE form_id = '" + id + "';"
	_, err = db.Exec(query)
	if err != nil {
		return err
	}
	return nil
}
