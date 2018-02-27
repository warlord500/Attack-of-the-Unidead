# Attack of the Unidead

On one particularly ordinary day, something fascinating happened. There was a flash of light, followed by an intense storm.
Upon the storm subsiding, the dead began to rise from their graves. Only the chosen one, the *unicycler* can save us now.

This is a group project by the students of Computer Science department at CCC. A roguelike dungeon-crawler with a nonsense
and absurd take on its theme.

## Documentation

The engine utilized aims to simplify the games programming experience. As such there is only one window,
so all functions related to input and drawing are global and can be called from anywhere.

To initialize the window

```cpp
initWindow(width, height, title, fullscreen, vsync, primary_monitor);

initWindow(800, 600, "Attack of the Unidead", true, true, 0);
```

After initialization, the features of the engine become available. The available functions are listed here.

### General

```cpp
void setWindowPos(int x, int y);
void setWindowSize(int width, int height);
void beginDrawing();
void endDrawing();
bool isWindowClosed();

void setClearColor(float r, float g, float b, float a);
void setClearColor(vec4f& color);
void setWindowResizeCallback(void(*resizecallback)(int width, int height));

void getMousePos(double* mousex, double* mousey);
vec2f getMousePos();
void disposeWindow();

void setFPSCap(double FPS);

void setMouseLocked(bool locked);
void setMouseHidden(bool hidden);
void setVSync(bool vsync);

int getWindowWidth();
int getWindowHeight();
double getElapsedTime();
```

### Input

```cpp
bool isKeyPressed(unsigned int keycode);
bool isKeyReleased(unsigned int keycode);
bool isButtonPressed(unsigned int button);
bool isButtonReleased(unsigned int button);
bool isKeyDown(unsigned int keycode);
bool isButtonDown(unsigned int button);
bool isKeyUp(unsigned int keycode);
bool isButtonUp(unsigned int button);
```

### Textures

```cpp
Texture createBlankTexture(int width = 0, int height = 0);
Texture loadTexture(unsigned char* pixels, int width, int height, int param);
Texture loadTexture(std::string filepath, int param);
void disposeTexture(Texture& texture);

void blitTexture(Texture& src, Texture& dest, Rectangle drawFrom, Rectangle drawTo);

void setTexturePixels(Texture& texture, unsigned char* pixels, int width, int height);
void setTexturePixelsFromFile(Texture& texture, std::string filepath);

void bindTexture(Texture& texture, unsigned int slot);
void unbindTexture(unsigned int slot);
```

### Drawing

### Sample program

```cpp
void main() {
    initWindow(800, 600, "Attack of the Unidead", false, true, 0);

    int pos_x = 0;
    int pos_y = 0;

    setMouseHidden(true);
    Texture cursor = loadTexture("data/art/cursor.png", TEXTURE_PARAM);

    while (!isWindowClosed()) {
        beginDrawing();

        if (isKeyDown(KEY_RIGHT))    pos_x -= SCROLL_SPEED;
        if (isKeyDown(KEY_LEFT))    pos_x += SCROLL_SPEED;
        if (isKeyDown(KEY_DOWN))    pos_y -= SCROLL_SPEED;
        if (isKeyDown(KEY_UP))        pos_y += SCROLL_SPEED;

        begin2D();
            drawTexture(cursor, getMousePos().x, getMousePos().y);
        end2D();

        endDrawing();
    }
    disposeTexture(cursor);
    disposeWindow();
}
```

## Contact
