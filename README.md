# Ancient Wonders System Generator

## Overview

Ancient Wonders System Generator is a procedural star system generator written in C++ that creates detailed star systems using a series of oracles and random dice rolls. The program simulates the formation of stellar objects, planets, asteroid belts, and various planetary characteristics (heat maps, sizes, densities, atmospheres, and more). It features an interactive, console-based menu system with graphical border elements.

This generator is based on Ancient Wonders by Ludic Pen and intended for use with the starforged system. but should be system agnostic if desired for other use.
- https://www.drivethrurpg.com/en/product/505365/ancient-wonders
- https://ludicpen.itch.io/ancient-wonders

## Requirements

- **Operating System:** Windows 10+
- **Compiler:** A C++11 (or later) compliant compiler.
- **Libraries:** Standard C++ libraries and Windows API.

## Building and Running

1. **Compilation**
   - Open the project in Visual Studio (or any compatible Windows C++ IDE).
   - Ensure that the project is set to use Unicode (for proper wide text output).
   - Compile the project with a C++11 (or later) compliant compiler.

2. **Running the Program**
   - Run the compiled executable from the console.
   - The main menu provides the following options:
     - **Generate a full star system (Random Star):** Rolls for a stellar object and generates a complete system with planets and asteroid belts.
     - **Generate a full star system (Specific Star):** Allows selection of a specific stellar object type.
     - **Roll for a specific planet type:** Rolls for a planet based on a selected planet type.
     - **Change global settings:** Modify parameters such as megastructure chance, tech level, region, and sector size.
     - **Exit:** Quit the program.
   - Navigate using the arrow keys and key presses. Follow on-screen instructions to save or copy system details.

## Known Issues

- **Complex Planets** - Karst Worlds, Tidally Locked Worlds - are not currently properly generated, as they tecnically have "sub"-worlds that need to be rolled on.

- **Specific Planet Generation** - The Specific planet generation has not been updated to the current "graphical" interface and does not display it's results properly.

- **Detailed Sector Sheet** - The current code does not generate detailed sectors. Setting to detailed sectors has no effect.

- **Megastructure Complexities** - The current code does not replace or modify the sector generation based on megastructure specifics

- **Saving to file** - Save to file doesn't work, but copying to clipboard does

- **Modifying the system** - When modifying the system by regenerating plants, removing planets, or toggling asteroid belts, will not modify the total numbers shown in the systems summary section.

- **Race Condition Keypresses** - If keys are pressed during the drawing of the screen, the program may crash

- **Things I am to lazy to list, or haven't found yet.**

## Future Enhancements

- Allow for scrolling in the System screen for each planet as complex planets or large simple sector sheets may reduce the vertical space.

## License

https://creativecommons.org/licenses/by-nc-sa/4.0/
