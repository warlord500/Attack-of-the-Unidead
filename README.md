# Attack of the Unidead

On one particularly ordinary day, something fascinating happened. There was a flash of light, followed by an intense storm.
Upon the storm subsiding, the dead began to rise from their graves. Only the chosen one, the *unicycler*, can save us now.

This is a group project by the students of the Computer Science department at CCC. A roguelike dungeon-crawler with a nonsense
and absurd take on its theme. The project uses the Godot engine.

## TODO

- [ ] Load configuration from init.txt file
- [ ] Load monster data from file
- [ ] Figure out someone to do music because no one can agree
- [ ] Design rooms to be inserted into dungeon generator
- [ ] Create dungeon generator
- [x] Draw sprite art for Unicycle dude
- [ ] Design enemies
- [ ] Draw art for enemies
- [ ] Create enemies (in code)
- [ ] Implement enemy AI
- [ ] Create UI skins for menus
- [ ] Create interface for misc. things like health

## Godot

Download this
https://godotengine.org/download/windows

## Documentation

To make a dialogue, you create a Control node, then add a RichTextLabel child node to it. Attach the "Dialogue_no_box.gd" script to the RichTextLabel. Then, create a script for the Control node.

Here's an example:
```GDscript
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

```

## Contributors

### Project Manager
Corbin Stark
### Lead Programmer
Don't know yet
### Programmers
Corbin Stark
### Code Quality Assurance
Jadon Belezos
### Lead Artist
Cody Potter
### Software Testers
Bela, Jared, John

## Contact

Email: starkcorbin@gmail.com
