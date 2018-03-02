extends Button

func _ready():
	add_color_override("font_color_hover", Color(1, 1, 1, 1))
	add_color_override("font_color", Color(.5, .5, .5, 1))
	connect("pressed", self, "onPress")

func onPress():
	# TODO: load the save file, then figure out what scene the player is
	# on, and change to that scene (then probably load things IN the scene 
	# as they were)
	pass
