package service

import (
	"html/template"
	"superman/ex01/internal/model"
	"superman/ex01/internal/repository"

	"github.com/russross/blackfriday/v2"
)

type Service struct {
	repo repository.Repository
}

func New(repo repository.Repository) *Service {
	return &Service{repo: repo}
}

func (s *Service) Login(admin model.Admin) bool {
	return s.repo.Login(admin)
}

func (s *Service) Index(page int) ([]model.DataNote, error) {
	DBs, err := s.repo.GetPosts(page)
	return DBs, err
}

func (s *Service) GetArticle(articleId int) (map[string]any, error) {
	dn, err := s.repo.GetArticle(articleId)
	if err != nil {
		return nil, err
	}
	htmlContent := template.HTML(blackfriday.Run([]byte(dn.Content), blackfriday.WithNoExtensions()))
	return map[string]any{
		"Content": htmlContent,
		"Title":   dn.Title,
	}, nil
}

func (s *Service) NewPost(dn *model.DataNote) error {
	err := s.repo.NewPost(dn)
	return err
}
