#include <iostream>
#include <SFML/Graphics.hpp>

const int FRAME_WIDTH(720), FRAME_HEIGHT(720);

const int CELL_SIZE(2);

const int GRID_WIDTH(FRAME_WIDTH / CELL_SIZE), GRID_HEIGHT(FRAME_HEIGHT / CELL_SIZE);

const int GRAINS_DROPPED(200000);

int grid[GRID_WIDTH][GRID_HEIGHT] = {0};

void drawGrid(sf::RenderWindow *);

void addSandGrain();

void fallIfTooMuch(int, int);

int main() {
    sf::RenderWindow window(sf::VideoMode(FRAME_WIDTH, FRAME_HEIGHT), "sfml_snadpiles");

    for (int i(0); i < GRAINS_DROPPED; i++)
        addSandGrain();

    drawGrid(&window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}

void addSandGrain() {
    int x(GRID_WIDTH / 2), y(GRID_HEIGHT / 2);

    grid[x][y]++;

    fallIfTooMuch(x, y);
}

void fallIfTooMuch(int x, int y) {
    if (grid[x][y] > 3) {
        grid[x][y] = 0;
        if (x - 1 >= 0) {
            grid[x - 1][y]++;
            fallIfTooMuch(x - 1, y);
        }
        if (y - 1 >= 0) {
            grid[x][y - 1]++;
            fallIfTooMuch(x, y - 1);
        }
        if (x + 1 <= GRID_WIDTH) {
            grid[x + 1][y]++;
            fallIfTooMuch(x + 1, y);
        }
        if (y + 1 <= GRID_HEIGHT) {
            grid[x][y + 1]++;
            fallIfTooMuch(x, y + 1);
        }
    }
}

void drawGrid(sf::RenderWindow * window) {
    window->clear();

    for (int x(0); x < GRID_WIDTH; x++) {
        for (int y(0); y < GRID_HEIGHT; y++) {
            if (grid[x][y] > 0) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);

                if (grid[x][y] == 1) {
                    cell.setFillColor(sf::Color::White);
                } else if (grid[x][y] == 2) {
                    cell.setFillColor(sf::Color::Green);
                } else {
                    cell.setFillColor(sf::Color::Blue);
                }

                window->draw(cell);
            }
        }
    }

    window->display();
}