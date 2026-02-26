package postgres

import (
	"database/sql"
	"errors"
	"fmt"
	"log"
	"superman/ex01/config"
	"superman/ex01/internal/model"
	"unicode/utf8"

	"github.com/golang-migrate/migrate/v4"
	"github.com/golang-migrate/migrate/v4/database/postgres"

	_ "github.com/golang-migrate/migrate/v4/source/file"

	_ "github.com/lib/pq"
)

type postgresRepository struct {
	db *sql.DB
}

func New(conf config.Postgres) (*postgresRepository, error) {
	url := fmt.Sprintf(
		"postgresql://%v:%v@%v:%v/%v?sslmode=disable",
		conf.Username,
		conf.Password,
		conf.Host,
		conf.Port,
		conf.DB,
	)

	db, err := sql.Open("postgres", url)
	if err != nil {
		return nil, fmt.Errorf("sql.Open: %v", err)
	}

	err = db.Ping()
	if err != nil {
		return nil, fmt.Errorf("db.Ping: %v", err)
	}

	driver, err := postgres.WithInstance(db, &postgres.Config{})
	if err != nil {
		return nil, fmt.Errorf("postgers.WithInstance: %v", err)
	}

	migrations := fmt.Sprintf("file://%v", conf.Migrations)
	m, err := migrate.NewWithDatabaseInstance(migrations, conf.DB, driver)
	if err != nil {
		return nil, fmt.Errorf("migrate.NewWithDatabaseInstance: %v", err)
	}

	log.Println("applying migrations...")
	if err := m.Up(); err != nil {
		if errors.Is(err, migrate.ErrNoChange) {
			log.Println("nothing to migrate")
		} else {
			return nil, fmt.Errorf("error when migrating: %v", err)
		}
	} else {
		log.Println("migrated successfully!")
	}

	return &postgresRepository{
		db: db,
	}, nil
}

func (pr postgresRepository) GetArticle(articleId int) (*model.DataNote, error) {
	dn := &model.DataNote{}
	err := pr.db.QueryRow("SELECT id, header, content FROM posts WHERE id = $1", articleId).Scan(&dn.Id, &dn.Title, &dn.Content)
	if err != nil {
		return nil, err
	}
	return dn, nil
}

func (pr postgresRepository) Login(admin model.Admin) bool {
	isAdmin := &model.Admin{}
	err := pr.db.QueryRow("SELECT login, password FROM admins WHERE login = $1 AND password = $2", admin.Login, admin.Password).Scan(&isAdmin.Login, &isAdmin.Password)
	if err != nil {
		return false
	}
	return true
}

func (pr postgresRepository) NewPost(dn *model.DataNote) error {
	stmt, err := pr.db.Prepare("INSERT INTO posts(header, content) VALUES($1, $2)")
	if err != nil {
		return err
	}
	defer stmt.Close()

	_, err = stmt.Exec(dn.Title, dn.Content)
	if err != nil {
		return err
	}
	return nil
}

func (pr postgresRepository) GetPosts(page int) ([]model.DataNote, error) {
	dns := []model.DataNote{}

	rows, err := pr.db.Query("SELECT id, header, content FROM posts")
	if err != nil {
		return nil, err
	}
	defer rows.Close()

	for rows.Next() {
		dn := model.DataNote{}
		err = rows.Scan(&dn.Id, &dn.Title, &dn.Content)
		if err != nil {
			return nil, err
		}
		previewLen := min(utf8.RuneCountInString(dn.Content), 20)
		dn.Preview = string([]rune(dn.Content)[:previewLen]) + "..."
		dns = append(dns, dn)
	}

	if err = rows.Err(); err != nil {
		return nil, err
	}

	if len(dns) <= (page-1)*3 {
		return nil, nil
	} else if len(dns) <= page*3 {
		return dns[(page-1)*3:], nil
	} else {
		return dns[(page-1)*3 : page*3], nil
	}
}
