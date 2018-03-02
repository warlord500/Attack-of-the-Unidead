extends RichTextLabel

func _ready():
	pass

func _process(delta):
	set_position(Vector2(
	(get_viewport_rect().size.x / 2) - (self.get_rect().size.x / 2),
	 get_viewport_rect().size.y - self.get_rect().size.y - 45
	))
