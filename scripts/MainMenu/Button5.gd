extends Button

func _ready():
	connect("pressed", self, "onPress")
	add_color_override("font_color_hover", Color(1, 1, 1, 1))
	add_color_override("font_color", Color(.5, .5, .5, 1))

func onPress():
	pass