extends Button

func _ready():
	connect("pressed", self, "onPress")

func onPress():
	get_tree().change_scene("res://scenes/start_newgame_cutscene.tscn")