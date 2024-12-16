package main

import (
	"database/sql"
	"log"

	_ "github.com/mattn/go-sqlite3"
	"github.com/mymmrac/telego"
	tu "github.com/mymmrac/telego/telegoutil"
)

func main() {
	botToken := "7393746584:AAGwVkW0930D2km0Vott6oXssW7gMdwe54A"
	bot, err := telego.NewBot(botToken, telego.WithDefaultDebugLogger())
	if err != nil {
		log.Fatalln(err)
	}

	updates, err := bot.UpdatesViaLongPolling(nil)
	if err != nil {
		log.Fatalln(err)
	}

	defer bot.StopLongPolling()

	for update := range updates {
		if update.Message != nil {
			chatID := update.Message.Chat.ID
			db, err := sql.Open("sqlite3", "../users.db")
			if err != nil {
				log.Fatalln(err)
			}
			res, err := db.Exec("INSERT OR IGNORE INTO users (user_id) VALUES (?)", chatID)
			if err != nil {
				log.Fatalln(err)
			}
			rows, err := res.RowsAffected()
			if err != nil {
				log.Fatalln(err)
			} else if rows == 1 {
				bot.SendMessage(tu.Message(tu.ID(chatID), "Вы подписались на рассылку"))
			} else if update.Message.Chat.Type == "private" {
				bot.SendMessage(tu.Message(tu.ID(chatID), "Вы уже подписаны на рассылку"))
			}
			db.Close()
		}
	}
}
