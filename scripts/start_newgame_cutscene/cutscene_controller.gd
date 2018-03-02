extends Control

var current_dialogue = 0
var dialogue = Array()

func _ready():
	dialogue.append("Hey!\nWake up!")
	
	dialogue.append("You have to get out of here! It's not safe!\n" +
	"You won't be able to get away on foot.\nTake this unicycle! "+
	"It's the most mobile thing in this place!")
	
	dialogue.append("Flee, Hero! Go far away to the capital, Stormguard:\n"+
	"there you will find the king; tell him Aeylynn sent you!")
	
	dialogue.append("(At this point it should fade in to the actual game "+
	"or\nsomething like that. We'll figure it out.)")
	
	if(get_child_count() > 0):
		get_child(0)._display_dialogue(dialogue[0])

func _process(delta):
	if(get_child(0).displaying == false):
		if(current_dialogue + 1 < dialogue.size()):
			current_dialogue += 1
			get_child(0)._display_dialogue(dialogue[current_dialogue])
