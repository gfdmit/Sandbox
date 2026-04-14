package v1

import (
	"html/template"
	"log"
	"net/http"
	"strconv"
	"superman/ex01/internal/model"
	"superman/ex01/internal/service"

	"github.com/gorilla/sessions"
)

func New(key string, svc *service.Service) (*http.ServeMux, error) {
	var (
		mux = http.ServeMux{}
	)
	sessionStore := sessions.NewCookieStore([]byte(key))

	mux.Handle("/img/", http.StripPrefix("/img/", http.FileServer(http.Dir("web/img/"))))

	mux.HandleFunc("/", RateLimitMiddleware(func(w http.ResponseWriter, r *http.Request) {
		page := 1
		pageStr := r.URL.Query().Get("page")
		p, _ := strconv.Atoi(pageStr)
		if p > 0 {
			page = p
		}
		DBs, err := svc.Index(page)
		if err != nil {
			http.Error(w, "Not found", http.StatusNotFound)
			return
		}
		tmpl, err := template.ParseFiles("web/html/root.html")
		if err != nil {
			http.Error(w, "Not found", http.StatusNotFound)
			return
		}
		tmpl.Execute(w, map[string]interface{}{
			"Articles": DBs,
			"Prev":     page - 1,
			"Next":     page + 1,
		})
	}))

	mux.HandleFunc("/login", RateLimitMiddleware(func(w http.ResponseWriter, r *http.Request) {
		sessions, err := sessionStore.Get(r, "sessions")
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
		}
		if auth, ok := sessions.Values["auth"].(bool); ok && auth {
			http.Redirect(w, r, "/admin", http.StatusSeeOther)
			return
		}
		admin := &model.Admin{Login: r.FormValue("Login"), Password: r.FormValue("Password")}
		if svc.Login(*admin) {
			sessions, _ := sessionStore.Get(r, "sessions")
			sessions.Values["auth"] = true
			sessions.Save(r, w)
			http.Redirect(w, r, "/admin", http.StatusSeeOther)
			return
		} else {
			templ, err := template.ParseFiles("web/html/auth.html")
			if err != nil {
				http.Error(w, "Not found", http.StatusNotFound)
				return
			}
			templ.Execute(w, nil)
		}
	}))

	mux.HandleFunc("/logout", RateLimitMiddleware(func(w http.ResponseWriter, r *http.Request) {
		sessions, _ := sessionStore.Get(r, "sessions")
		delete(sessions.Values, "auth")
		sessions.Save(r, w)
		http.Redirect(w, r, "/", http.StatusSeeOther)
	}))

	mux.HandleFunc("/admin", RateLimitMiddleware(func(w http.ResponseWriter, r *http.Request) {
		sessions, err := sessionStore.Get(r, "sessions")
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
		}
		if auth, ok := sessions.Values["auth"].(bool); !ok || !auth {
			http.Redirect(w, r, "/login", http.StatusSeeOther)
			return
		}
		templ, err := template.ParseFiles("web/html/admin.html")
		if err != nil {
			http.Error(w, "Not found", http.StatusNotFound)
			return
		}
		templ.Execute(w, nil)
	}))

	mux.HandleFunc("/article", RateLimitMiddleware(func(w http.ResponseWriter, r *http.Request) {
		articleId, _ := strconv.Atoi(r.URL.Query().Get("id"))
		article, err := svc.GetArticle(articleId)
		if err != nil {
			http.Error(w, "Post not found", http.StatusNotFound)
			return
		}
		templ, err := template.ParseFiles("web/html/article.html")
		if err != nil {
			http.Error(w, "", http.StatusNotFound)
			return
		}
		templ.Execute(w, article)
	}))

	mux.HandleFunc("/post", RateLimitMiddleware(func(w http.ResponseWriter, r *http.Request) {
		if r.Method != http.MethodPost {
			http.Error(w, "Invalid requst metod", http.StatusMethodNotAllowed)
			return
		}

		dn := &model.DataNote{
			Content: r.FormValue("content"),
			Title:   r.FormValue("title"),
		}
		err := svc.NewPost(dn)
		if err != nil {
			log.Println(err)
			return
		}
		http.Redirect(w, r, "/", http.StatusSeeOther)
	}))

	return &mux, nil
}
