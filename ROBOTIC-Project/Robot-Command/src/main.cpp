// #define STEP_1

#include "robot.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <sstream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <cmath>

constexpr unsigned int WINDOWS_SIZE_X = 800;
constexpr unsigned int WINDOWS_SIZE_Y = 600;

using namespace std::chrono_literals;


int main(int argc, char ** argv)
{
    std::string hostIpAddress("127.0.0.1");
    uint16_t tcpPort = 6543;

    if (argc == 3)
    {
        hostIpAddress = std::string(argv[1]);
        std::istringstream iss(argv[2]);
        iss.exceptions(std::istringstream::failbit);
        iss >> tcpPort;
    }

    std::cout << "Try to connect to " << hostIpAddress << ":" << tcpPort << " ..." << std::endl;
    Robot robot(hostIpAddress, tcpPort);
    robot.waitReady();

#ifdef STEP_1
    try
    {
        while (true)
        {
            constexpr float basePowerSpeed = 0.5;
            // Wait for line track event
            // Dummy implementation, just check if the line track is detected and move the robot
            auto event = robot.waitChanged(EventType::LINE_TRACKS_IS_DETECTED, 0.5s);
            bool lineTrackValue = robot.getLineTracksIsDetected(0);
            if (!event)
            {
                // No event, make the robot turn to get back to the track
                robot.setMotorsPower(0, basePowerSpeed);
            }
            else
            {
                // Event detected, check the line track value
                if (lineTrackValue)
                {
                    // If the line track is detected, move right
                    robot.setMotorsPower(0, basePowerSpeed);
                }
                else
                {
                    // If the line track is not detected, move left
                    robot.setMotorsPower(basePowerSpeed, 0);
                }
            }
        }
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
#else
    sf::RenderWindow window(sf::VideoMode(WINDOWS_SIZE_X, WINDOWS_SIZE_Y),
                            "robot-command",
                            sf::Style::Titlebar | sf::Style::Close);

    window.setVerticalSyncEnabled(true);

    // Rectangle setup, representing the robot
    constexpr float ROBOT_SIZE = 20.f;
    sf::Vector2f squareSize(ROBOT_SIZE, ROBOT_SIZE);
    sf::RectangleShape squarePost(squareSize);
    squarePost.setFillColor(sf::Color::Blue);
    squarePost.setOrigin(ROBOT_SIZE / 2, ROBOT_SIZE / 2); // Set the origin to the center
    squarePost.setPosition(80, 80); // Hardcoded position for the rectangle (defined in simulator)


        // Get the robot's encoder values
        const std::size_t ENCODER_SENSOR_0 = robot.getEncoderWheelValue(0);
        const std::size_t ENCODER_SENSOR_1 = robot.getEncoderWheelValue(1);

        // Exactly revert the calculation done in the robot simulator
        constexpr float WHEEL_DIAMETER = 6.5f; // in pixels
        constexpr float LATTICE_STEP = WHEEL_DIAMETER * std::numbers::pi / ROBOT_SIZE; // in pixels

        // Same here, exacty revert the calculation done in the robot simulator
        float ENCODER_SENSOR_0_IN_PIXEL = ENCODER_SENSOR_0 * ROBOT_SIZE * LATTICE_STEP;
        float ENCODER_SENSOR_1_IN_PIXEL = ENCODER_SENSOR_1 * ROBOT_SIZE * LATTICE_STEP;

        // Compute the linear and angular step to follow the robot in the simulator
        // This line is not working properly, the angularStep goes to something around INT_MAX (way too big)
        float linearStep = (ENCODER_SENSOR_0_IN_PIXEL + ENCODER_SENSOR_1_IN_PIXEL) / 2;
        float angularStep = (ENCODER_SENSOR_1_IN_PIXEL - ENCODER_SENSOR_0_IN_PIXEL)  / ROBOT_SIZE;

    // Init the trail of the robot
    // The trail is a line that will be drawn on the screen to show the robot's path
    // MAX_POINTS is the maximum number of points that can be drawn on the screen (again hadcoded as the subject says)
    //
    // The solution that will be proposed is not the most efficient one
    // To make it more efficient, we could:
    // - use a circular buffer to store the points and draw them in one go
    // - have a dymamic array without heavy allocation
    constexpr int MAX_POINTS = 1000;
    sf::VertexArray trail(sf::Points, MAX_POINTS);
    int trailSize = 0;
    int trailIndex = 0;

    try
    {
      // This prevLinearStep will be used to compute the robot's position
      std::size_t prevLinearStep = 0;

      while (window.isOpen())
      {
        sf::Event event;
        while (window.pollEvent(event))
        {
          if (event.type == sf::Event::Closed)
          {
            window.close();
          }
        }

        // Add the point to the trail (in red)
        trail[trailIndex].position = squarePost.getPosition();
        trail[trailIndex].color = sf::Color::Red;

        // Calculate the trail index and trail size according to the maximum number of points
        trailIndex = (trailIndex + 1) % MAX_POINTS
;
        trailSize = std::min(trailSize + 1, MAX_POINTS
); // Check if we reached the maximum number of points (and prevent overflow)

        window.clear(sf::Color::Black); // Clear with black background
        window.draw(squarePost);        // Draw the rectangle

        // Draw the trail of the robot point by point
        for (int i = 0; i < trailSize; ++i)
        {
          int drawIndex = (trailIndex + i) % MAX_POINTS
    ;
          window.draw(&trail[drawIndex], 1, sf::Points);
        }

        window.display();               // Display everything on the screen

        // Update the robot's position (this breaks everything and we don't see the square on the screen)
        squarePost.setPosition(
            squarePost.getPosition().x + (linearStep - prevLinearStep) * std::cos(angularStep),
            squarePost.getPosition().y + (linearStep - prevLinearStep) * std::sin(angularStep));

        prevLinearStep = linearStep;
      }

    }
    catch (std::exception & e)
    {
      std::cerr << e.what() << std::endl;
    }
#endif

    return 0;
}
