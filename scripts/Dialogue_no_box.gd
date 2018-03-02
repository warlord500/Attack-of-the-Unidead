extends RichTextLabel

var displaying = false
var waiting = false
var timer = 0
var textToDisplay = ""

var currentChar = 0

const SPEED = .06

func _ready():
	# _display_dialogue("Hey!\n\nWake up!")
	pass

func _process(delta):
	if(displaying):
		timer += delta;
		if(timer > SPEED && currentChar < textToDisplay.length()):
			set_bbcode(get_bbcode() + textToDisplay[currentChar])
			currentChar += 1
			timer = 0
		
		if(currentChar >= textToDisplay.length()):
			if(Input.is_key_pressed(KEY_ENTER)):
				currentChar = 0
				textToDisplay = ""
				displaying = false
				timer = 0
			if(waiting == false):
				set_bbcode(get_bbcode() + 
				"\n[color=#8a8a8a]Press [color=#70db70]Enter[/color] or" + 
				" click to continue.[/color]")
				waiting = true

func _display_dialogue(text):
	displaying = true
	waiting = false
	textToDisplay = text
	set_bbcode("[center]")