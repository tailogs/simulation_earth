# Simulation of Countries in Console

![image](https://github.com/user-attachments/assets/5235498e-021e-45da-9068-0d15e3d0c9a1)
Figure 1. Running simulation

This project is a console-based simulation of countries interacting with each other in a world map. Each country is represented by a symbol, and over time, they engage in various actions such as trade, war, population growth, and resource redistribution. The project is built in C and makes use of `WinAPI` for managing console output.

## Features

- **Dynamic Simulation**: The program simulates different countries, each with attributes like economy, military, population, and currency.
- **Map Visualization**: A 20x60 grid represents the world map, where countries expand or contract based on their status.
- **Country Interaction**: Countries can trade or engage in war depending on proximity and random events.
- **Economy and Population**: Each country's economy, military, and population change dynamically each round, with potential redistribution of resources.
- **Logging**: The program logs important events such as trade agreements, wars, and country removals to a file.
- **Neural Network Simulation**: A simple neural network is applied to each country to simulate decision-making processes.
- **Real-time Updates**: The map and country statistics update in real-time with color-coded information displayed in the console.

## Getting Started

### Prerequisites

- Windows operating system
- `MinGW` or any other C compiler compatible with Windows.
- `Git` (optional, if you want to clone the repository).

### Compilation using Makefile

This project includes a `Makefile` to simplify compilation. Here's how to compile and run the program using `make`:

1. Ensure that `gcc` and `make` are installed.
2. Open a terminal or `CMD` and navigate to the project directory.
3. To compile the project, run the following command:

   ```bash
   make
   ```

   This will compile all source files and generate the executable.

4. To run the program, use:

   ```bash
   make run
   ```

5. To clean up the generated object files and executable, run:

   ```bash
   make clean
   ```

6. If you need to rebuild the project from scratch, use:

   ```bash
   make rebuild
   ```

### Compilation without Makefile

If you prefer not to use `make`, you can compile the program manually by following these steps:

1. Open the terminal or `CMD`.
2. Navigate to the directory containing the source code.
3. Compile the program using `gcc`:

   ```bash
   gcc -o simulation_earth.exe main.c color.c -std=c18 -Wall
   ```

4. Run the compiled program:

   ```bash
   simulation.exe
   ```

### Running the Program

Once compiled, you can run the program directly by executing the generated file:

```bash
simulation_earth.exe
```

The console window will display the world map, symbol information, and the history of currency rates for each country.

## Key Concepts

- **Countries**: Each country has attributes like `economy`, `military`, `population`, and `currencyRate`. They are identified by unique symbols on the map.
- **Actions**: Countries may engage in actions such as:
  - **Trade**: Exchange resources with neighboring countries.
  - **War**: Military conflict resulting in decreased economy and military power.
  - **Resource Redistribution**: Random events redistribute resources among countries.
  - **Population Growth**: Countries may attract or lose population based on their status.
- **Map**: The map is a 20x60 grid. Each country tries to expand by creating new cells if they have sufficient resources.

## Files

- **simulation.c**: The main source code file containing the logic for the simulation.
- **log.txt**: A file that logs important simulation events (e.g., wars, trade deals, country removals).

## Code Structure

- **`drawMap`**: Renders the 20x60 grid showing the current state of the world.
- **`drawSymbolInfo`**: Displays real-time information about the countries' attributes like economy, military, population, and currency rate.
- **`war`**: Simulates a war between two neighboring countries.
- **`redistributeResources`**: Randomly redistributes resources among countries.
- **`updateMapAndData`**: Updates the map and country data each round, handling changes in economy, population, and military.
- **`applyNN`**: Applies a simple neural network to each country to simulate decision-making processes.

## Dependencies

This project uses standard libraries and `WinAPI` to manage console output. Ensure that you're compiling on Windows or a Windows-like environment such as `Cygwin`.

## Logging

Events such as wars, trades, and country removals are logged into `log.txt` for later analysis. Each log entry is timestamped with the round number.

## Future Work

- More complex interaction models between countries (e.g., alliances).
- AI enhancements to make country behavior more unpredictable.
- Saving and loading simulation states.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
