extends Button

func _ready():
	connect("pressed", self, "onPress")

func onPress():
	# TODO: load the save file, then figure out what scene the player is
	# on, and change to that scene (then probably load things IN the scene 
	# as they were)
	pass
	