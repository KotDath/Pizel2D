#include "ConfigReader.h"

Config ConfigReader::LoadConfig(const std::string &filename)
{
    // Create a variable to hold the JSON data
    nlohmann::json jsonData;

    std::cout << "Filename: " << filename << std::endl;

    // Open the file
    std::ifstream inputFile(filename);

    Config config;

    if (inputFile.is_open())
    {
        // Parse the JSON data from the file
        try
        {
            inputFile >> jsonData;
            inputFile.close();

            // Access data
            config.width = jsonData["width"];
            config.height = jsonData["height"];
            config.speed = jsonData["speed"];
            config.rColor = jsonData["color"]["r"];
            config.gColor = jsonData["color"]["g"];
            config.bColor = jsonData["color"]["b"];
            config.scale = jsonData["scale"];
            config.angle = jsonData["angle"];
            config.angle *= M_PI / 180.f;
            for (const auto &item : jsonData["logos"])
            {
                config.logos.push_back(item);
            }
        } catch (std::exception& e) {
            std::cout << "Failed to parse default value of config. Use defaults." << std::endl;
        }
    }
    else
    {
        std::cout << "Could not open the file!" << std::endl;
    }

    return config;
}
