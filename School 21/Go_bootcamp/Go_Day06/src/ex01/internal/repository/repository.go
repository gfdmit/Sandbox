package repository

import (
	"superman/ex01/internal/model"
)

type Repository interface {
	GetArticle(articleId int) (*model.DataNote, error)
	Login(admin model.Admin) bool
	NewPost(dn *model.DataNote) error
	GetPosts(page int) ([]model.DataNote, error)
}
