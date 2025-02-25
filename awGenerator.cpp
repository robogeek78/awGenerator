#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <random>
#include <chrono>
#include <limits>
#include <tuple>
#include <conio.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

// Global random engine seeded with current time.
std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

std::string titleString = "Ancient Wonders System Generator";
std::string versionString = "v0.0.1";

static const int numOfOrbits = 6;
static const int greyText = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
static const int whiteText = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
static const int menuSelectedColor = BACKGROUND_RED | whiteText;
static const int menuUnselectedColor = whiteText;
static const int menuTitleBorder = whiteText | BACKGROUND_INTENSITY;
static const int menuTitleColor = whiteText;
static const int borderColor = greyText;

struct sMenuItem_t {
    char index;
    int color;
    int value;
    void (*action) (void);
    std::string menuText;
    std::vector<std::string> values;

    // Constructor with a default parameter for 'values'.
    sMenuItem_t(char idx, int col, int val, void (*act)(void), const std::string& text,
        const std::vector<std::string>& vals = {})
        : index(idx), color(col), value(val), action(act), menuText(text), values(vals)
    {
    }
};

bool exitProgram = false;

//---------------------------------------------------------------------------------------------------------------------
// Structure to hold Rolled details.
static struct rolledItem {
    int diceRoll;
    int index;
    std::string details;
};


struct BiomeEntry {
    std::string Biome;
    std::string Feature;
};

static struct moonData {
    bool present = false;  // True if an asteroid belt exists at this location.
    std::string details;   // Details about the belt.
};

//---------------------------------------------------------------------------------------------------------------------
// Structure to hold planet details.
static struct Planet {
    bool exists = false;       // True if a planet is present in this orbit.
    int heatLevel;
    int orbit;         // e.g., "Orbit 1", "Orbit 2", etc.
    int position;
    rolledItem planetName;
    rolledItem planetClass;
    rolledItem size;
    rolledItem density;
    std::string gravity;
    int circumference;
    rolledItem orbitalFeature;
    rolledItem orbitalFeatureDetails;
    int numOfMoons;
    std::vector<moonData> moons;
    rolledItem atmosphere;
    rolledItem life;
    rolledItem settlements;
    rolledItem biomeDiversity;
    std::vector<rolledItem> biomeRolls;
    std::vector<BiomeEntry> biomes;
    int surfaceFeaturesCount;
    std::array<rolledItem,2> surfaceFeatures;
};

//---------------------------------------------------------------------------------------------------------------------
// Structure to hold Megastructure Details belt details.
static struct AsteroidBelt {
    bool present = false;  // True if an asteroid belt exists at this location.
    std::string details;   // Details about the belt.
};

//---------------------------------------------------------
// Structure to hold the complete system data.
static struct SystemData {
    int systemRegionIndex;
    std::string systemRegion;                       // e.g., Terminus, Outlands, Expanse.
    rolledItem systemName;
    rolledItem stellarObject;
    bool megaStructurePresent;
    rolledItem megaStructure;
    rolledItem numOfPlanets;
    rolledItem numOfBelts;
    std::array<int, 6> heatMap;             // Heat map for each orbit.
    std::array<Planet, 6> planets;                  // One for each orbit.
    std::array<AsteroidBelt, 5> asteroidBelts;      // One for each inter-orbital location.
};

static SystemData gSystem;

#include "oracles.h"
#include "planetNames.h"

enum eSettingsIndex_t {
    Settings_RegionType = 0,
    Settings_MegaChance,
    Settings_MegaTech,
    Settings_SectorSheet,
    Settings_SectorSize,
    Settings_Exit
};

std::vector<sMenuItem_t> settingsM = {
    { '0' , menuUnselectedColor, 0, nullptr, "Roll for a specific planet type." , regionList },
    { '1' , menuUnselectedColor, 2, nullptr, "Megastructure Chance", megastructureChanceList },
    { '2' , menuUnselectedColor, 2, nullptr, "Megastructure Tech Level" , megastructureTechList },
    { '3' , menuUnselectedColor, 0, nullptr, "SectorSheet Type.", sectorSheetList },
    { '4' , menuUnselectedColor, 0, nullptr, "SectorSheet Size [Simple Only].", sectorSheetSizeList },
    { '5' , menuUnselectedColor, 0, nullptr, "Close Settings.", {""}},
};

static std::vector<sMenuItem_t> oracleToMenu(std::vector< OracleEntry> oracle) {
    std::vector<sMenuItem_t> menu;
    for (const auto& item : oracle) {
        char newIndex = '0';
        if (item.index < 10) {
            newIndex += item.index; //make an ascii number
        }
        else if (item.index < (10 + 26) ) {
            newIndex = 'a' + item.index - 10; // Make a character
        }
        else {
            break; // no menus over 36 items
        }

        sMenuItem_t newItem = { newIndex, menuUnselectedColor, 0, nullptr, item.result };

        menu.emplace_back(newItem);

    } 
    return menu;
}

static std::vector<sMenuItem_t> stringListToMenu(std::vector< std::string> stringList) {
    std::vector<sMenuItem_t> menu;
    int index = 0;

    for (const auto& item : stringList) {
        char newIndex = '0';
        if (index < 10) {
            newIndex += index; //make an ascii number
        }
        else if (index < (10 + 26)) {
            newIndex = 'a' + index - 10; // Make a character
        }
        else {
            break; // no menus over 36 items
        }

        index++;
        sMenuItem_t newItem = { newIndex, menuUnselectedColor, 0, nullptr, item };

        menu.emplace_back(newItem);

    }
    return menu;
}

struct comma_numpunct : std::numpunct<char> {
protected:
    // Specify the thousands separator.
    virtual char do_thousands_sep() const override { return ','; }
    // Specify the grouping pattern; "\03" means groups of 3 digits.
    virtual std::string do_grouping() const override { return "\03"; }
};

static void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

static void setCursor(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

static void cursorBlinkOff(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Retrieve the current cursor information.
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);

    // Turn off the cursor (make it invisible).
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// Helper function to join vector of strings with CRLF ("\r\n") between each element.
std::string joinStringsWithCRLF(const std::vector<std::string>& lines) {
    std::string result;
    for (size_t i = 0; i < lines.size(); ++i) {
        result += lines[i];
        if (i < lines.size() - 1) {
            result += "\r\n";  // Append CRLF between lines.
        }
    }
    return result;
}

// Function to set text on the clipboard (using CF_TEXT for ANSI text).
bool setClipboardText(const std::string& text) {
    if (!OpenClipboard(nullptr))
        return false;
    if (!EmptyClipboard()) {
        CloseClipboard();
        return false;
    }

    // Allocate global memory for the text (including the null terminator).
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    if (hGlobal == nullptr) {
        CloseClipboard();
        return false;
    }

    // Lock the memory and copy the text.
    char* pGlobal = static_cast<char*>(GlobalLock(hGlobal));
    if (pGlobal == nullptr) {
        GlobalFree(hGlobal);
        CloseClipboard();
        return false;
    }
    memcpy(pGlobal, text.c_str(), text.size() + 1);
    GlobalUnlock(hGlobal);

    // Set the clipboard data.
    if (SetClipboardData(CF_TEXT, hGlobal) == nullptr) {
        GlobalFree(hGlobal);
        CloseClipboard();
        return false;
    }

    CloseClipboard();
    return true;
}

static void borderDrawWithTitle(int x, int y, int width, int height, std::string title, int color = borderColor)
{
    

    _setmode(_fileno(stdout), _O_U16TEXT);
    setColor(color);
    setCursor(x, y);
    std::wcout << L"╔" << std::wstring(width - 2, L'═') << L"╗";

    for (int i = 1; i < height - 1; ++i) {
        setCursor(x, y + i);
        // Vertical lines: ║
        std::wcout << L"║";
        
        setColor(menuUnselectedColor);
        std::wcout <<  std::wstring(width - 2, L' ');

        setColor(color);
        std::wcout << L"║";
    }

    setCursor(x, y + height - 1);
    std::wcout << L"╚" << std::wstring(width - 2, L'═') << L"╝";

    _setmode(_fileno(stdout), _O_TEXT);
    setCursor(x + 2, y);
    std::cout << " " << title << " ";
}

static int menuDrawSelect(std::vector<sMenuItem_t> menu, std::string header, boolean displayValue = false) {
    
    int width = 0;
    int height = 0;
    for (const auto& item : menu) {
        std::string tempStr = item.index + ". " + item.menuText;

        if (displayValue) {
            tempStr = tempStr + " ( " + item.values[item.value] + " )";
        }

        if (width < tempStr.size())
        {
            width = tempStr.size();
        }

        height++;
    }



    borderDrawWithTitle(2,2, width + 9 , height +4 , header);


    int selection = 0;
    menu[selection].color = menuSelectedColor;
    bool active = true;

    while (active)
    {
        int i = 4;
        for (const auto& item : menu) {
            setCursor(5, i);
            i++;

            setColor(item.color);
            std::cout << item.index << ". " << item.menuText;
            if (displayValue) {
                std::cout << " ( " << item.values[item.value] << " )";
            }
        }

        char keyPress = _getch();

        if (keyPress == 72) { // up arrow
            if (selection > 0) {
                menu[selection].color = menuUnselectedColor;
                selection--;
                menu[selection].color = menuSelectedColor;
            }
        }
        else if (keyPress == 80) { // down arrow
            if (selection < menu.size() - 1) {
                menu[selection].color = menuUnselectedColor;
                selection++;
                menu[selection].color = menuSelectedColor;
            }
        }
        else if (keyPress == '\r') {
            active == false;
            break;
        }
        else {
            //Check all other keypresses for matching menu item indexes

            int index = 0;
            for (const auto& item : menu) {
                if (item.index == keyPress) {
                    menu[selection].color = menuUnselectedColor;
                    selection = index;
                    menu[selection].color = menuSelectedColor;
                }

                index++;
            }

        }

    }

    return selection;
}

//---------------------------------------------------------------------------------------------------------------------
// Utility functions
//---------------------------------------------------------------------------------------------------------------------

// Roll a dice with a given number of sides (default 100)
static int rollDice(int sides = 100) {
    std::uniform_int_distribution<int> distribution(1, sides);
    return distribution(rng);
}

// Return a random integer in the inclusive range [min, max]
static int randomInRange(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(rng);
}

static bool oracleRoll(int chance)
{
    int challenge = 0;
    int roll = rollDice();
    switch (chance)
    {
        case 0: challenge = 10; break;
        case 1: challenge = 25; break;
        case 2: challenge = 50; break;
        case 3: challenge = 75; break;
        case 4: challenge = 90; break;
    }

    if (roll < challenge)
        return true;

    return false;
}

static rolledItem rollOnTable(std::vector<OracleEntry> table)
{
    rolledItem localRoll;
    localRoll.diceRoll = rollDice();

    for (const auto& entry : table) {
        if (localRoll.diceRoll >= entry.minRoll && localRoll.diceRoll <= entry.maxRoll) {
            localRoll.index = entry.index;
            localRoll.details = entry.result;
            break;
        }
    }
    return localRoll;
}

static rolledItem rollOnTable(std::vector<OracleEntryND> table)
{
    rolledItem localRoll;
    localRoll.diceRoll = rollDice();

    for (const auto& entry : table) {
        if (localRoll.diceRoll >= entry.minRoll && localRoll.diceRoll <= entry.maxRoll) {
            localRoll.index = entry.index;
            break;
        }
    }
    return localRoll;
}






// AW page 22: PLANETS QUANTITY
static rolledItem determineNumberOfPlanets() {
    rolledItem localRoll;
    localRoll.diceRoll = rollDice();
    if (localRoll.diceRoll < 10)
        localRoll.index = 0;
    else if (localRoll.diceRoll <= 25)
        localRoll.index = 1;
    else if (localRoll.diceRoll <= 45)
        localRoll.index = 2;
    else if (localRoll.diceRoll <= 70)
        localRoll.index = 3;
    else if (localRoll.diceRoll <= 85)
        localRoll.index = 4;
    else if (localRoll.diceRoll <= 95)
        localRoll.index = 5;
    else
        localRoll.index = 6;
    return localRoll;
}

// AW page 22: ASTEROID BELTS QUANTITY
static rolledItem determineNumberOfAsteroidBelts() {
    rolledItem localRoll;
    localRoll.diceRoll = rollDice();
    if ( localRoll.diceRoll <= 25)
        localRoll.index = 0;
    else if ( localRoll.diceRoll <= 75)
        localRoll.index = 1;
    else if ( localRoll.diceRoll < 95)
        localRoll.index = 2;
    else
        localRoll.index = 3;
    return localRoll;
}

// AW page 26: STELLAR OBJECT HEAT MAPSTELLAR MAP
static std::array<int, numOfOrbits> generatePlanetaryHeatMap(int argStarType) {
    std::array<int, numOfOrbits> localHeatMap;

    std::copy(heatMap[argStarType], heatMap[argStarType] + numOfOrbits, localHeatMap.begin());

    return localHeatMap;
}

static Planet generatePlanetDetails(int orbit, int forcePlanet = -1) {
    Planet planet;
    planet.exists = true;
    planet.orbit = orbit;

    planet.heatLevel = gSystem.heatMap[orbit];

    // Determine orbit position
    planet.position = rollDice(settingsM[Settings_SectorSize].value * 2 + 13);

    if (orbit == 1)
    {
        int minNum = ((settingsM[Settings_SectorSize].value * 2 + 13) / 2) - 4;
        int maxNum = ((settingsM[Settings_SectorSize].value * 2 + 13) / 2) + 4;

        if (planet.position < minNum)  
            planet.position = minNum;

        if (planet.position > maxNum)  
            planet.position = maxNum;
    }


    if (forcePlanet < 0)
    {
        //roll on approprate planetType Oracle
        std::vector<OracleEntryND> localPlanetOracle = planetTypeOracles[gSystem.heatMap[orbit]];
        planet.planetClass = rollOnTable(localPlanetOracle);
        planet.planetClass.details = planetTypeStrings[planet.planetClass.index];
    }
    else
    {
        planet.planetClass.diceRoll = -1;
        planet.planetClass.index = forcePlanet;
        planet.planetClass.details = planetTypeStrings[planet.planetClass.index];
    }

    //pick a name
    std::vector<std::string> localNameList = planetNameArray[planet.planetClass.index];
    planet.planetName.diceRoll = rollDice(localNameList.size());
    planet.planetName.index = planet.planetName.diceRoll;
    planet.planetName.details = localNameList[planet.planetName.index];


    // Determine planetary size.
    planet.size = rollOnTable(planetSizeTable);

    // Determine density (used as a proxy for gravity).
    planet.density = rollOnTable(planetDensityTable);

    // Determine Gravity from Size and density
    planet.gravity = planetGravityTable[planet.size.index][planet.density.index];

    // Determine Circumference from size
    planet.circumference =  1000 * randomInRange(planetCircumferenceTable[planet.size.index][0], planetCircumferenceTable[planet.size.index][1]);


    // Determine orbital feature.
    planet.orbitalFeature = rollOnTable(orbitalFeatureTable);

    // Generate Rings if applicable.
    if (planet.orbitalFeature.index == 1)
    {
        planet.orbitalFeatureDetails = rollOnTable(ringSystemTable);
    }
        
    if (planet.orbitalFeature.index == 2)
    {
        std::vector<OracleEntry> localMoonNumber = moonNumberTable[planet.size.index];
        planet.orbitalFeatureDetails = rollOnTable(localMoonNumber);
        planet.numOfMoons = randomInRange(moonQuantity[planet.orbitalFeatureDetails.index][0], moonQuantity[planet.orbitalFeatureDetails.index][1]);

        //TODO: generate moon data
    }
    else
    {
        planet.numOfMoons = 0;
    }

    //roll for Atmosphere Oracle
    std::vector<OracleEntry> localAtmosphereOracle = atmosphereTable[planet.planetClass.index];
    planet.atmosphere = rollOnTable(localAtmosphereOracle);

    //roll for life Oracle
    std::vector<OracleEntry> localLifeOracle = LifeTable[planet.planetClass.index];
    planet.life = rollOnTable(localLifeOracle);

    // Generate 1 or 2 surface features.
    planet.surfaceFeaturesCount = rollDice(2);  // returns 1 or 2

    std::vector<OracleEntry> localSurfaceOracle = SurfaceFeatureTable[planet.planetClass.index];
    planet.surfaceFeatures[0] = rollOnTable(localSurfaceOracle);
    if (planet.surfaceFeaturesCount > 1)
    {
        planet.surfaceFeatures[1] = rollOnTable(localSurfaceOracle);
    }

    //Roll For biome Diversity
    std::vector<OracleEntryND> localBDOracle = biomeDiversityTable[planet.planetClass.index][planet.size.index/4];
    planet.biomeDiversity = rollOnTable(localBDOracle);

    // Select biomes.
    if (planet.biomeDiversity.index > 0)
    {
        std::vector<int> biomeIndices = BiomesOrderTable[planet.planetClass.index];
        std::shuffle(biomeIndices.begin(), biomeIndices.end(), rng);
        for (int i = 0; i < planet.biomeDiversity.index; ++i) {
            BiomeEntry biome;
            std::vector<biomeOracle> localBiomeTable = BiomesTable[planet.planetClass.index];
            int planetIndex = localBiomeTable[i].PlanetType;
            int Index = localBiomeTable[i].FeatureIndex;
            biome.Biome = localBiomeTable[i].biome;

            std::vector<OracleEntry> biomeFeatureOracle = BiomeFeatureTable[planetIndex][Index];
            planet.biomeRolls.emplace_back(rollOnTable(biomeFeatureOracle));
            biome.Feature = planet.biomeRolls[i].details;
            planet.biomeRolls[i].details = biome.Biome + ": " + biome.Feature;
            planet.biomes.emplace_back(biome);
        }
    }

    std::vector<OracleEntryND> localSettlementsOracle = SettlementsTable[planet.planetClass.index][gSystem.systemRegionIndex];
    planet.settlements = rollOnTable(localSettlementsOracle);
    planet.settlements.details = settlementsList[planet.settlements.index];
    
    return planet;
}

static const int boxVerticalPadding = 2;
static const int boxHorizontalPadding = 3;

static const int systemMapXCoord = 55;
static const int systemMapYCoord = 2;
static const int systemMapWidth = 63;
static const int systemOrbitPitch = 10;
static const int planetDetailsXCoord = 2;
static const int planetDetailsYCoordOffset = 3;

static std::vector<std::string> displaySystemDetails(bool showRolls)
{
    std::vector<std::string> systemStringsData;
    int numOfMapRows = settingsM[Settings_SectorSize].value * 2 + 13;
    int systemDetailsWidth = 120 - systemMapWidth - planetDetailsXCoord * 2;
    int systemDetailsHeight = numOfMapRows + boxVerticalPadding * 2 + 1;
    int maxTextYcoord = systemDetailsHeight - 4;

    borderDrawWithTitle(planetDetailsXCoord, systemMapYCoord, systemDetailsWidth, systemDetailsHeight, "System Details");

    if (showRolls)
    {
        systemStringsData.push_back("NAME: " + gSystem.systemName.details + " (" + gSystem.systemRegion + ")");
        systemStringsData.push_back(gSystem.stellarObject.details + " (" + std::to_string(gSystem.stellarObject.diceRoll) + ")");
        systemStringsData.push_back("PLANETS: " + std::to_string(gSystem.numOfPlanets.index) + " (" + std::to_string(gSystem.stellarObject.diceRoll) + ") --- " +
            "BELTS: " + std::to_string(gSystem.numOfBelts.index) + " (" + std::to_string(gSystem.numOfBelts.diceRoll) + ")");
        systemStringsData.push_back("HEAT MAP: ");
        for (int orbit = 0; orbit < numOfOrbits; orbit++)
        {
            systemStringsData.push_back("  - " + std::to_string(orbit) + ": " + heatLevelStrings[gSystem.heatMap[orbit]]);
        }
        if (gSystem.megaStructurePresent)
        {
            systemStringsData.push_back("MEGASTRUCTURE: " + gSystem.megaStructure.details + " (" + std::to_string(gSystem.megaStructure.diceRoll) + ")");
        }
        else
        {
            systemStringsData.push_back("MEGASTRUCTURE: None" );
        }
    }


    int yCoord = systemMapYCoord + boxVerticalPadding;
    for (const auto& entry : systemStringsData) {
        std::string print = entry.substr(0, systemDetailsWidth - 6);

        setCursor(planetDetailsXCoord + boxHorizontalPadding, yCoord);
        std::cout << print;
        yCoord++;

        //if (yCoord >= maxTextYcoord) break;

    }

    return systemStringsData;
}

static std::vector<std::string> displayPlanetDetails(int orbit, int xCoord, bool fullSize, bool showRolls)
{
    std::vector<std::string> planetStringsData;
    Planet planet = gSystem.planets[orbit];
    int numOfMapRows = settingsM[Settings_SectorSize].value * 2 + 13;
    int planetDetailsYCoord = numOfMapRows + systemMapYCoord + 2 * boxVerticalPadding + 1;
    int planetDetailsHeight = 50 - planetDetailsYCoord - boxVerticalPadding * 2;
    int maxTextYcoord = planetDetailsYCoord + planetDetailsHeight - boxVerticalPadding;
    int width = fullSize ? 51 : 13;

    borderDrawWithTitle(xCoord, planetDetailsYCoord, width, planetDetailsHeight, "Orbit " + std::to_string(orbit + 1));

    if (planet.exists)
    {
        if (showRolls)
        {
            planetStringsData.push_back("NAME: " + planet.planetName.details);
            planetStringsData.push_back(planet.planetClass.details + " (" + std::to_string(planet.planetClass.diceRoll) + ") - " + heatLevelStrings[planet.heatLevel]);
            planetStringsData.push_back("POS: " + std::to_string(planet.position) + " - " + "SIZE: " + planet.size.details + " (" + std::to_string(planet.size.diceRoll) + ")");
            planetStringsData.push_back("DENSITY: " + planet.density.details + " (" + std::to_string(planet.density.diceRoll) + ")");
            planetStringsData.push_back("GRAVITY: " + planet.gravity);
            planetStringsData.push_back("CIRCUMFERENCE: " + std::to_string(planet.circumference) + " km");
            planetStringsData.push_back("ORBITAL FEAT: " + planet.orbitalFeature.details + " (" + std::to_string(planet.orbitalFeature.diceRoll) + ")");
            if (planet.orbitalFeature.index == 1) // rings
            {
                planetStringsData.push_back("  - RINGS: " + planet.orbitalFeatureDetails.details + " (" + std::to_string(planet.orbitalFeatureDetails.diceRoll) + ")");
            }

            if (planet.orbitalFeature.index == 2) // Moons
            {
                planetStringsData.push_back("  - MOONS: " + planet.orbitalFeatureDetails.details + " (" + std::to_string(planet.orbitalFeatureDetails.diceRoll) + ")");
                planetStringsData.push_back("  - NUMBER: " + std::to_string(planet.numOfMoons));

                //TODO: Moon data
            }

            planetStringsData.push_back("ATMOSPHERE: " + planet.atmosphere.details + " (" + std::to_string(planet.atmosphere.diceRoll) + ")");
            planetStringsData.push_back("LIFE: " + planet.life.details + " (" + std::to_string(planet.life.diceRoll) + ")");
            planetStringsData.push_back("SETTLEMENTS: " + planet.settlements.details + " (" + std::to_string(planet.settlements.diceRoll) + ")");
            planetStringsData.push_back("FEATURES: " + planet.surfaceFeatures[0].details + " (" + std::to_string(planet.surfaceFeatures[0].diceRoll) + ")");
            if (planet.surfaceFeaturesCount > 1)
            {
                planetStringsData.push_back("          " + planet.surfaceFeatures[1].details + " (" + std::to_string(planet.surfaceFeatures[1].diceRoll) + ")");
            }

            planetStringsData.push_back("BIOMES: " + planet.biomeDiversity.details + " (" + std::to_string(planet.biomeDiversity.diceRoll) + ")");
            for (const auto& entry : planet.biomeRolls) {
                planetStringsData.push_back("  - " + entry.details + " (" + std::to_string(entry.diceRoll) + ")");
            }
        }


        int yCoord = planetDetailsYCoord + boxVerticalPadding;
        for (const auto& entry : planetStringsData) {
            std::string print;
            if (fullSize)
            {
                print = entry.substr(0, 46);
            }
            else
            {
                print = entry.substr(0, 7);
            }

            setCursor(xCoord + boxHorizontalPadding, yCoord);
            std::cout << print;
            yCoord++;

            if (yCoord >= maxTextYcoord) break;

        }

    }
    else
    {
        setCursor(xCoord + boxHorizontalPadding, planetDetailsYCoord + boxVerticalPadding);
        std::cout << "No";
        setCursor(xCoord + boxHorizontalPadding, planetDetailsYCoord + boxVerticalPadding+1);
        std::cout << "Planet.";

        planetStringsData.push_back("No Planet.");
    }
    
    return planetStringsData;
}


static void drawInteractiveSystem(void)
{
    int numOfMapRows = settingsM[Settings_SectorSize].value * 2 + 13;
    int centerOfMap = numOfMapRows / 2;
    int startX = systemMapXCoord + boxHorizontalPadding;
    int selectedOrbit = 2;

    for (int orbit = 0; orbit < numOfOrbits; orbit++)
    {
        if (gSystem.planets[orbit].exists)
        {
            selectedOrbit = orbit;
            break;
        }
    }


    

    while (1)
    {
        borderDrawWithTitle(systemMapXCoord, systemMapYCoord, systemMapWidth, numOfMapRows + boxVerticalPadding * 2 + 1, "System Map");

        _setmode(_fileno(stdout), _O_WTEXT);
        std::vector<std::string> systemDataStrings = { "Generated by: " + titleString + " - " + versionString , "-----------------", ""};

        setCursor(startX, systemMapYCoord + boxVerticalPadding + centerOfMap + 1);
        std::wcout << L"✶";

        for (int row = 0; row < numOfMapRows; row++)
        {
            std::wstring orbitChar = L"│";
            int rowOffset = systemOrbitPitch;

            if (row > centerOfMap)
            {
                rowOffset -= (row - centerOfMap);
                orbitChar = L"/";
            }
            else if (row < centerOfMap)
            {
                rowOffset -= (centerOfMap - row);
                orbitChar = L"\\";
            }


            for (int orbit = 0; orbit < numOfOrbits; orbit++)
            {
                if (gSystem.planets[orbit].exists)
                {
                    int newX = startX + rowOffset + systemOrbitPitch * orbit - systemOrbitPitch / 2;

                    if (newX > startX)
                    {
                        if (row == 0)
                        {
                            setCursor(newX, systemMapYCoord + boxVerticalPadding + row);
                            std::wcout << (orbit + 1);
                        }
                        setCursor(newX, systemMapYCoord + boxVerticalPadding + row + 1);
                        if (gSystem.planets[orbit].position == (row + 1))
                        {

                            std::wcout << L"○";
                        }
                        else
                        {
                            std::wcout << orbitChar;
                        }
                    }
                }

                if (orbit < 5)
                {
                    if (gSystem.asteroidBelts[orbit].present)
                    {
                        int newX = startX + rowOffset + systemOrbitPitch * orbit;

                        if (newX > startX)
                        {
                            setCursor(newX, systemMapYCoord + boxVerticalPadding + row + 1);
                            std::wcout << L"◊";

                        }
                    }
                }
            }
        }

        _setmode(_fileno(stdout), _O_TEXT);

        auto systemStrings = displaySystemDetails(true);

        systemDataStrings.insert(systemDataStrings.end(), systemStrings.begin(), systemStrings.end());

        int localXCoord = 2;

        for (int orbit = 0; orbit < numOfOrbits; orbit++)
        {
            bool fullSize = false;
            if (selectedOrbit == orbit)
            {
                fullSize = true;

            }




            auto planetStrings = displayPlanetDetails(orbit, localXCoord, fullSize, true);

            systemDataStrings.push_back("");
            systemDataStrings.push_back("Orbit " + std::to_string(orbit + 1));
            systemDataStrings.push_back("-----------------");
            systemDataStrings.insert(systemDataStrings.end(), planetStrings.begin(), planetStrings.end());

            if (selectedOrbit == orbit)
            {
                localXCoord += 51;
            }
            else
            {
                localXCoord += 13;
            }
        }

        //draw modifcation menu
        setCursor(3, 47);
        std::cout << "PLANETS: (R)EGENERATE --- (D)ELETE           ASTEROID: (T)OGGLE           ROLLS: (O)N/OFF";
        setCursor(3, 48);
        std::cout << "SYSTEM: (S)AVE TO FILE --- (C)OPY TO CLIPBOARD --- (ENTER) BACK TO MENU --- (LEFT/RIGHT ARROWS)NAVIGATION";


        char keyPress = _getch();

        if (keyPress == 75) { // Left arrow
            if (selectedOrbit > 0) {
                selectedOrbit--;
            }
        }
        else if (keyPress == 77) { // Right arrow
            if (selectedOrbit < 5) {
                selectedOrbit++;
            }
        }
        else if (keyPress == '\r') {
            break;
        }
        else if (keyPress == 'R' or keyPress == 'r') {
            gSystem.planets[selectedOrbit] = generatePlanetDetails(selectedOrbit);
        }
        else if (keyPress == 'D' or keyPress == 'd') {
            gSystem.planets[selectedOrbit].exists = false;
        }
        else if (keyPress == 'T' or keyPress == 't') {
            if (selectedOrbit < 5)
            {
                if (gSystem.asteroidBelts[selectedOrbit].present)
                {
                    gSystem.asteroidBelts[selectedOrbit].present = false;
                }
                else
                {
                    gSystem.asteroidBelts[selectedOrbit].present = true;
                }
            }
        }
        else if (keyPress == 'C' or keyPress == 'c') {
            std::string joinedText = joinStringsWithCRLF(systemDataStrings);
            setClipboardText(joinedText);
        }



    }
}



static void generateFullSystem( void )
{
    std::string megastructureType = "None";
    int roll = -1;

    //name the system
    std::vector<std::string> stellarObjectDescriptor = stellarObjectDescriptorArray[gSystem.stellarObject.index];
    gSystem.systemName.diceRoll = rollDice(stellarObjectDescriptor.size());
    gSystem.systemName.index = rollDice(commonStarNames.size());
    gSystem.systemName.details = stellarObjectDescriptor[gSystem.systemName.diceRoll] + " " + commonStarNames[gSystem.systemName.index];

    gSystem.systemRegionIndex = settingsM[Settings_RegionType].value;
    gSystem.systemRegion = regionList[gSystem.systemRegionIndex];

    if (oracleRoll(settingsM[Settings_MegaTech].value))
    {
        gSystem.megaStructurePresent = true;
        std::vector<OracleEntry> localMegastructureOracle = megastructureTable[settingsM[Settings_MegaTech].value];
        gSystem.megaStructure = rollOnTable(localMegastructureOracle);
    }
    else
    {
        gSystem.megaStructurePresent = false;
    }

    // Step 2: Determine number of planets.
    gSystem.numOfPlanets = determineNumberOfPlanets();

    // Step 3: Determine number of asteroid belts.
    gSystem.numOfBelts = determineNumberOfAsteroidBelts();

    // Step 4: Generate planetary heat map.
    gSystem.heatMap = generatePlanetaryHeatMap(gSystem.stellarObject.index);


    // Step 5: Generate planet array.
    for (int i = 0; i < 6; ++i) {
        gSystem.planets[i].exists = false;
        gSystem.planets[i].orbit = i + 1;
    }
    // Create a vector of orbit indices [0, 1, 2, 3, 4, 5].
    std::vector<int> orbitIndices = { 0, 1, 2, 3, 4, 5 };
    std::shuffle(orbitIndices.begin(), orbitIndices.end(), rng);
    // Place a planet in the first numPlanetsToPlace randomly chosen orbits.
    for (int i = 0; i < gSystem.numOfPlanets.index && i < 6; ++i) {
        int idx = orbitIndices[i];
        gSystem.planets[idx] = generatePlanetDetails(idx);
    }

    // Step 6: Generate asteroid belt array.
    for (int i = 0; i < 5; ++i) {
        gSystem.asteroidBelts[i].present = false;
        gSystem.asteroidBelts[i].details = "No asteroid belt";
    }
    // Create a vector of belt indices [0, 1, 2, 3, 4].
    std::vector<int> beltIndices = { 0, 1, 2, 3, 4 };
    std::shuffle(beltIndices.begin(), beltIndices.end(), rng);
    // Mark the first numBeltsToPlace positions as having an asteroid belt.
    for (int i = 0; i < gSystem.numOfBelts.index && i < 5; ++i) {
        int idx = beltIndices[i];
        gSystem.asteroidBelts[idx].present = true;
        gSystem.asteroidBelts[idx].details = "Belt Present";
    }


    drawInteractiveSystem();
}

static void generateRandomFullSystem(void)
{

    setColor(menuTitleColor);

    // Step 1: Roll for stellar object.
    gSystem.stellarObject = rollOnTable(stellarObjectTable);


    generateFullSystem();
}

static void generateSpecificFullSystem(void) {
    setColor(menuTitleColor);

    auto generatedMenu = oracleToMenu(stellarObjectTable);

    int StellarObjectIndex = menuDrawSelect(generatedMenu, "Stellar Object Selection");

    gSystem.stellarObject.diceRoll = -1;
    gSystem.stellarObject.index = StellarObjectIndex;
    gSystem.stellarObject.details = stellarObjectTable[StellarObjectIndex].result;

    generateFullSystem();
}



static void generateSpecificPlanet(void) {
    setColor(menuTitleColor);

    auto generatedMenu = stringListToMenu(planetTypeStrings);

    int specificPlanetType = menuDrawSelect(generatedMenu, "Planet Type Selection");

    Planet planet = generatePlanetDetails(0, specificPlanetType);

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

static void changeSettingsFunc(void) {

    while (1)
    {
        int changeSettingValue = menuDrawSelect(settingsM, "Change Global Settings", true);

        if (changeSettingValue == Settings_Exit) {
            break;
        }
        else {

            auto generatedMenu = stringListToMenu(settingsM[changeSettingValue].values);

            int specificPlanetType = menuDrawSelect(generatedMenu, "Select: " + settingsM[changeSettingValue].menuText);

            settingsM[changeSettingValue].value = specificPlanetType;
        }
    }
}

static void confirmExit(void) {

    std::cout << "\nAre you sure you want to exit? (y/n): ";
    char saveOption;
    std::cin >> saveOption;
    if (saveOption == 'y' || saveOption == 'Y')
        exitProgram = true;
    
    std::cout << "\nExiting program.\n";
}




//---------------------------------------------------------------------
// Main function with menu loop and persistent global settings.
//---------------------------------------------------------------------
int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Set locale for comma punctuation.
    std::locale commaLocale(std::locale::classic(), new comma_numpunct);
    std::cout.imbue(commaLocale);
    cursorBlinkOff();

    std::locale::global(std::locale(""));


    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to get console handle.\n";
        return 1;
    }

    // Define the desired dimensions.
    const SHORT columns = 120;
    const SHORT rows = 50;

    // Set the console screen buffer size.


    // Define the window size.
    SMALL_RECT windowSize = { 0, 0, columns - 1, rows - 1 };
    if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize)) {
        std::cerr << "Error: Unable to set window size.\n";
        return 1;
    }
   
    HWND window = GetConsoleWindow();
    if (window == NULL) {
        std::cerr << "Error: Unable to get console window handle." << std::endl;
        return 1;
    }

    // Get the current window style.
    LONG style = GetWindowLong(window, GWL_STYLE);

    // Remove the resizing border (WS_THICKFRAME) and maximize button (WS_MAXIMIZEBOX).
    style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);

    // Apply the new style.
    SetWindowLong(window, GWL_STYLE, style);

    // Inform the system that the window style has changed.
    SetWindowPos(window, NULL, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    // Global settings: megastructure chance and region.
    std::vector<sMenuItem_t> mainMenu = {
        { '0' , menuUnselectedColor, 0, generateRandomFullSystem, "Generate a full star system (Random Star)." },
        { '1' , menuUnselectedColor, 0, generateSpecificFullSystem, "Generate a full star system (Specific Star)." },
        { '2' , menuUnselectedColor, 0, generateSpecificPlanet, "Roll for a specific planet type." },
        { '3' , menuUnselectedColor, 0, changeSettingsFunc, "Change global settings." },
        { '4' , menuUnselectedColor, 0, confirmExit, "Exit." },
    };


 
    while (!exitProgram) {
        setColor(menuTitleColor);
        system("cls");
        borderDrawWithTitle(0, 0, 120, 50, titleString + " - " + versionString, borderColor);


        int menuValue = menuDrawSelect(mainMenu, "Main Menu");

        mainMenu[menuValue].action();
    }
    return 0;
}
