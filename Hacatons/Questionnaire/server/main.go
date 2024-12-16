package main

import (
	"encoding/json"
	"net/http"
	formstore "server/internal/formstore"

	"github.com/gin-gonic/gin"
)

type formServer struct {
	form *formstore.Form
}

func NewFormServer() *formServer {
	form := formstore.New()
	return &formServer{form: form}
}

func (fs *formServer) getAllFormsHandler(c *gin.Context) {
	forms, err := fs.form.GetAllForms()
	if err != nil {
		c.String(http.StatusInternalServerError, err.Error())
		return
	}
	c.JSON(http.StatusOK, forms)
}

func (fs *formServer) createFormHandler(c *gin.Context) {
	form := formstore.Form{}
	if err := c.ShouldBindJSON(&form); err != nil {
		c.String(http.StatusBadRequest, err.Error())
		return
	}
	//fmt.Println(form.Author, form.Description, form.Entities, form.Id, form.Title)

	if err := fs.form.CreateForm(form); err != nil {
		c.String(http.StatusInternalServerError, err.Error())
		return
	}
	c.JSON(http.StatusOK, nil)
}

func (fs *formServer) getFormHandler(c *gin.Context) {
	id := c.Params.ByName("id")
	form, err := fs.form.GetForm(id)
	if err != nil {
		c.String(http.StatusInternalServerError, err.Error())
		return
	}
	retVal, err := json.Marshal(form)
	if err != nil {
		c.String(http.StatusInternalServerError, err.Error())
		return
	}
	c.JSON(http.StatusOK, retVal)
}

func (fs *formServer) updateFormHandler(c *gin.Context) {
	form := formstore.Form{}
	if err := c.ShouldBindJSON(form); err != nil {
		c.String(http.StatusBadRequest, err.Error())
		return
	}
	id := c.Params.ByName("id")
	if err := fs.form.UpdateForm(id, form); err != nil {
		c.String(http.StatusInternalServerError, err.Error())
		return
	}
	c.JSON(http.StatusOK, nil)
}

func (fs *formServer) deleteFormHandler(c *gin.Context) {
	id := c.Params.ByName("id")
	if err := fs.form.DeleteForm(id); err != nil {
		c.String(http.StatusInternalServerError, err.Error())
		return
	}
	c.JSON(http.StatusOK, nil)
}

func main() {
	router := gin.New()
	router.Use(gin.Logger())
	router.Use(gin.Recovery())

	server := NewFormServer()

	router.GET("/form/", server.getAllFormsHandler)
	router.POST("/form/", server.createFormHandler)

	router.GET("/form/:id", server.getFormHandler)
	router.PUT("/form/:id", server.updateFormHandler)
	router.DELETE("/form/:id", server.deleteFormHandler)

	router.Run("localhost:8070")
}
