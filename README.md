# Attack of the Unidead
This is a group project by the students of the Computer Science department at CCC. A roguelike dungeon-crawler with a nonsense and absurd theme.

## Code Style Guide

Function are formatted like this: 
```
void example_function(int exampleParameter);
```
Types (structs and classes) are formatted like this: 
```
struct TestStruct { };
```
Variables are formatted like this: 
```
TestStruct testVariableName;
```
Globals, macros, and enums are formatted like this: 
```
#define TEST_MACRO(x) #x
global_var TEST_GLOBAL_VAR;

enum TestEnum {
SCREAMING_SNAKE_CASE,
ENUM_OPTION_2,
}
```
Curly Braces are formatted like this:
```
void example_function() {
	//code;
}
```

## Linking the library into Visual Studio

> If you aren't using Visual Studio 2017, this may not work. Upgrading to Visual Studio 2017 is highly recommended. Any 'p1' and 'p2' mismatch is likely due to having a wrong Visual Studio version. I could also recompile the engine on a different VS version if that is preferable.

If you are not using Visual Studio, make sure you are using an up-to-date compiler and link in the .lib

After creating your project, right click it and select properties.
Make sure your configuration is in "All Configurations" before continuing
```
Properties > VC++ Directories > Include Directories
```
Edit the include directories, and add the BahamutInclude directory to it.

```
Properties > Linker > Input > Additional Dependencies
```
Edit the additional dependencies and type the following into it:
```
bahamut.lib
```
Next, go to:
```
Properties > System > SubSystem
```
Change your SubSystem to Console.

Then change your configuration to debug.

```
Properties > VC++ Directories > Library Directories
```
Edit the library directories, and add the DebugBahamutLibrary directory to it.
Once finished with that, change your configuration to release.

```
Properties > VC++ Directories > Library Directories
```
Edit the library directories, and add the BahamutLibrary directory to it.

Finished!
Contact me if this did not work for you.

## Documentation


## Contributors
### Project Manager
Corbin Stark
### Programmers
Josiah Baldwin, Corbin Stark, Jadon Belezos
### Code Quality Assurance
Jadon Belezos
### Sound Design
Steven Schulze

## Contact

Email: starkcorbin@gmail.com
