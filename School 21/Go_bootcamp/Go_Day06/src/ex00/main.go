package main

import (
	"image/color"
	"log"

	"github.com/fogleman/gg"
)

const (
	width, height = 300, 300
	outPath       = "amazing_logo.png"
)

func generateLogo(outPath string) error {
	logo := gg.NewContext(width, height)
	logo.SetColor(color.White)
	logo.Clear()

	logo.SetColor(color.Black)
	logo.DrawEllipse(150, 150, 130, 65)
	logo.Fill()

	logo.SetColor(color.RGBA{255, 204, 0, 255})
	logo.DrawEllipse(150, 150, 120, 60)
	logo.Fill()

	logo.SetColor(color.White)
	logo.SetLineWidth(5)
	logo.DrawLine(70, 115, 115, 115)
	logo.DrawLine(115, 115, 70, 185)
	logo.DrawLine(70, 185, 115, 185)
	logo.Stroke()

	logo.SetColor(color.RGBA{0, 0, 255, 255})
	logo.DrawEllipse(150, 150, 30, 37)
	logo.Stroke()

	logo.SetColor(color.RGBA{255, 0, 0, 255})
	logo.SetLineWidth(5)
	logo.DrawLine(185, 115, 207, 185)
	logo.DrawLine(207, 185, 229, 115)
	logo.Stroke()

	err := logo.SavePNG(outPath)
	return err
}

func main() {
	if err := generateLogo(outPath); err != nil {
		log.Fatalln(err)
	}
}
