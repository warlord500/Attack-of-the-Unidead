extends Button

func _ready():
	connect("pressed", self, "onPress")

func onPress():
	print("test")