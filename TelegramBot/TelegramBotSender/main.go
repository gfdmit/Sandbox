package main

import (
	"database/sql"
	"log"
	"time"

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

	for {
		if time.Now().Weekday() == time.Monday && time.Now().Hour() == 10 && time.Now().Minute() == 5 {
			sendMessageToUsers(bot, "Через 5 минут начнётся консультация по предмету \"Разработка Интернет приложений\" \nПреподаватель: Прокопьев Н.А. \nСсылка для подключения: https://discord.gg/3R8tBn5uAw")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Monday && time.Now().Hour() == 12 && time.Now().Minute() == 5 {
			sendMessageToUsers(bot, "Через 5 минут начнётся консультация по предмету \"Язык Python и его приложения\" \nПреподаватель: Прокопьев Н.А. \nСсылка для подключения: https://discord.gg/3R8tBn5uAw")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Monday && time.Now().Hour() == 13 && time.Now().Minute() == 45 {
			sendMessageToUsers(bot, "Через 5 минут начнётся консультация по предмету \"Параллельные вычисления\" \nПреподаватель: Гилемзянов А.Ф. \nСсылка для подключения: https://telemost.yandex.ru/j/89907295019057")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Tuesday && time.Now().Hour() == 10 && time.Now().Minute() == 5 {
			sendMessageToUsers(bot, "Через 5 минут начнётся консультация по предмету \"Программирование на Java\" \nПреподаватель: Маклецов С.В. \nСсылка для подключения: https://yandex.ru/chat#/join/d52b9c5e-5078-44d3-a39b-5e76a61745e4")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Tuesday && time.Now().Hour() == 12 && time.Now().Minute() == 5 {
			sendMessageToUsers(bot, "Через 5 минут начнутся консультации по предметам \"Программирование для Web\" и \"Интернет-технологии\" \nПреподаватели: Гилемзянов А.Ф. и Прокопьев Н.А. \nСсылки для подключения: https://telemost.yandex.ru/j/52748185377057 и https://discord.gg/3R8tBn5uAw")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Wednesday && time.Now().Hour() == 12 && time.Now().Minute() == 5 {
			sendMessageToUsers(bot, "Через 5 минут начнётся консультация по предмету \"Философия\" \nПреподаватель: Ибрагимова З.З. \nСсылка для подключения: https://telemost.yandex.ru/j/00441414569973")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Wednesday && time.Now().Hour() == 12 && time.Now().Minute() == 5 {
			sendMessageToUsers(bot, "Через 5 минут начнётся консультация по предмету \"Численные методы\" \nПреподаватель: Глазырина Л.Л. \nСсылка для подключения: https://telemost.yandex.ru/j/33892232118281")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Wednesday && time.Now().Hour() == 12 && time.Now().Minute() == 5 {
			sendMessageToUsers(bot, "Через 5 минут начнётся консультация по предмету \"Технологическая практика\" \nПреподаватель: Минуллин Д.А. \nСсылка для подключения: https://telemost.yandex.ru/j/46471505308830")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Thursday && time.Now().Hour() == 15 && time.Now().Minute() == 45 {
			sendMessageToUsers(bot, "Через 5 минут начнётся консультация по предмету \"Уравнения мат. физики\" \nПреподаватель: Гнеденкова В.Л. \nСсылка для подключения: https://telemost.yandex.ru/j/28680295517825")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Thursday && time.Now().Hour() == 17 && time.Now().Minute() == 25 {
			sendMessageToUsers(bot, "Через 5 минут начнутся консультации по предметам \"CUDA\" и \"1C\" \nПреподаватели: Тумаков Д.Н. и Медведева О.А. \nСсылки для подключения: https://telemost.yandex.ru/j/46076292113794 и https://telemost.yandex.ru/j/66027792740285")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Friday && time.Now().Hour() == 10 && time.Now().Minute() == 5 {
			sendMessageToUsers(bot, "Через 5 минут начнётся консультация по предмету \"Компьютерная лингвистика\" \nПреподаватель: Гатиатуллин А.Р. \nСсылка для подключения: https://telemost.yandex.ru/j/70512149710448")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Friday && time.Now().Hour() == 12 && time.Now().Minute() == 5 {
			sendMessageToUsers(bot, "Через 5 минут начнётся консультация по предмету \"Нейронные сети и их приложения\" \nПреподаватель: Гафаров Ф.М. \nСсылка для подключения: https://telemost.yandex.ru/j/79304545826232")
			time.Sleep(60 * time.Second)
		}
		if time.Now().Weekday() == time.Friday && time.Now().Hour() == 13 && time.Now().Minute() == 45 {
			sendMessageToUsers(bot, "Через 5 минут начнётся консультация по предмету \"Мод. вычисления и криптография\" \nПреподаватель: Гилемзянов А.Ф. \nСсылка для подключения: https://telemost.yandex.ru/j/00397365955832")
			time.Sleep(60 * time.Second)
		}
		time.Sleep(55 * time.Second)
	}
}

func sendMessageToUsers(bot *telego.Bot, message string) {
	db, err := sql.Open("sqlite3", "../users.db")
	if err != nil {
		log.Fatalln(err)
	}

	rows, err := db.Query("SELECT user_id FROM users")
	if err != nil {
		log.Fatalln(err)
	}

	defer rows.Close()
	defer db.Close()

	for rows.Next() {
		var chatID int64
		if err := rows.Scan(&chatID); err != nil {
			log.Printf("Ошибка при сканировании user_id: %v", err)
			continue
		}

		bot.SendMessage(tu.Message(tu.ID(chatID), message))
	}
}
