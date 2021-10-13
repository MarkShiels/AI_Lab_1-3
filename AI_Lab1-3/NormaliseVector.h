#pragma once
#include <SFML/Graphics.hpp>

sf::Vector2f normaliseVector(sf::Vector2f t_vec)
{
	float vecMag = sqrt((t_vec.x * t_vec.x) + (t_vec.y * t_vec.y));

	sf::Vector2f returnVec = sf::Vector2f(t_vec.x / vecMag, t_vec.y / vecMag);

	return returnVec;
}