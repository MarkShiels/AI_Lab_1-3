#include "NPC.h"

NPC::NPC()
{
	body.setPosition(550, 550);
	body.setOrigin(106, 118.5);
	body.setScale(0.2, 0.2);
}

NPC::~NPC()
{
}

void NPC::setPosition(sf::Vector2f t_pos)
{
	body.setPosition(t_pos);
}

sf::Vector2f NPC::getPosition()
{
	return body.getPosition();
}

sf::Sprite NPC::getBody()
{
	return body;
}

void NPC::setTetxure(sf::Texture* t_txtr)
{
	body.setTexture(*t_txtr);
}

void NPC::setSpeed(float t_speed)
{
	speed = t_speed;
}

float NPC::getSpeed()
{
	return speed;
}

void NPC::setMoveVec(sf::Vector2f t_moveVec)
{
	moveVec = t_moveVec;
}

sf::Vector2f NPC::getMoveVec()
{
	return moveVec;
}

void NPC::move()
{
	body.move(moveVec * speed);
}

void NPC::facing(float t_pi)
{
	float pX = body.getPosition().x;
	float pY = body.getPosition().y;

	float mX = pX + moveVec.x;
	float mY = pY + moveVec.y;

	float angle = atan2f((mY - pY), (mX - pX));
	angle = angle * (180 / t_pi);

	body.setRotation(angle + 90);
}

void NPC::update(float t_pi, sf::Vector2f t_target)
{
	if (behaviour == Behaviour::Wander)
	{
		knmtcWander(t_pi);
	}
	else if (behaviour == Behaviour::Seek)
	{
		seek(t_target);
	}
	move();
	facing(t_pi);
}

void NPC::changeBehaviour(Behaviour t_b)
{
	behaviour = t_b;
}

void NPC::boundaryCheck(float t_screenSize)
{
	if (body.getPosition().x < 0)
	{
		body.setPosition(sf::Vector2f(t_screenSize, body.getPosition().y));
	}
	else if (body.getPosition().x > t_screenSize)
	{
		body.setPosition(sf::Vector2f(0, body.getPosition().y));
	}

	if (body.getPosition().y < 0)
	{
		body.setPosition(sf::Vector2f(body.getPosition().x, t_screenSize));
	}
	else if (body.getPosition().y > t_screenSize)
	{
		body.setPosition(sf::Vector2f(body.getPosition().x, 0));
	}
}

sf::Vector2f NPC::normaliseVector(sf::Vector2f t_vec)
{
	float vecMag = sqrt((t_vec.x * t_vec.x) + (t_vec.y * t_vec.y));

	sf::Vector2f returnVec = sf::Vector2f(t_vec.x / vecMag, t_vec.y / vecMag);

	return returnVec;
	
}

void NPC::knmtcWander(float t_pi)
{
	srand(time(0));
	float rAngle = (rand() % 9) - 5;

	if (rAngle > 0)
	{	
		rAngle = rAngle * (t_pi / 180);
		sf::Vector2f newVec;

		newVec.x = (moveVec.x * cos(rAngle) + moveVec.y * sin(rAngle));
		newVec.y = (moveVec.y * cos(rAngle) - moveVec.x * sin(rAngle));

		moveVec = normaliseVector(newVec);
	}
	else if (rAngle < 0)
	{
		rAngle = (rAngle * -1) * (t_pi / 180);
		sf::Vector2f newVec;

		newVec.x = (moveVec.x * cos(rAngle) - moveVec.y * sin(rAngle));
		newVec.y = (moveVec.y * cos(rAngle) + moveVec.x * sin(rAngle));

		moveVec = normaliseVector(newVec);
	}
	else
	{

	}
}

void NPC::seek(sf::Vector2f t_target)
{

	moveVec = t_target - body.getPosition();
	moveVec = normaliseVector(moveVec);

}

void NPC::render(sf::RenderWindow* t_window)
{
	t_window->draw(body);
}
