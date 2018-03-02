extends Control

func _ready():
	pass

func _process(delta):
	if(Input.is_key_pressed(KEY_ESCAPE)):
		get_tree().quit()
	if(Input.is_key_pressed(KEY_SHIFT) && Input.is_key_pressed(KEY_SLASH)):
		print("GUIDE ISN'T IMPLEMENTED YET!")