extends Panel

func _ready():
	set_position(Vector2(
	(get_viewport_rect().size.x / 2) - (self.get_rect().size.x / 2), 
	(get_viewport_rect().size.y / 2) - (self.get_rect().size.y / 2))
	)

func _process(delta):
	set_position(Vector2(
	(get_viewport_rect().size.x / 2) - (self.get_rect().size.x / 2), 
	(get_viewport_rect().size.y / 2) - (self.get_rect().size.y / 2))
	)
