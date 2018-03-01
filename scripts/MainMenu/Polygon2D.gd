extends Polygon2D

func _ready():
	pass

func _process(delta):
	set_position(Vector2(0, 0))
	set_size(get_viewport_rect().size.x, get_viewport_rect().size.y)
