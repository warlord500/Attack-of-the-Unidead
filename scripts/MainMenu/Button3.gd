extends Button

func _ready():
	connect("pressed", self, "onPress")

func onPress():
	get_tree().quit()