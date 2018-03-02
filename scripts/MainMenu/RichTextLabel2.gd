extends RichTextLabel

func _ready():
	pass

func _process(delta):
	set_position(Vector2(
	0,
	 get_viewport_rect().size.y - self.get_rect().size.y - 5
	))
