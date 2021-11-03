#include <SFML/Graphics.hpp>
#include <iostream>

#define DELAY 0.200f
#define DIM 100.0f


int main(){


	//load the textures and the font
	sf::Texture boardTexture, circleTexture, crossTexture;
	sf::Font font;

	if(!boardTexture.loadFromFile("assets/board.png") ||!crossTexture.loadFromFile("assets/cross.png") ||!circleTexture.loadFromFile("assets/circle.png") || !font.loadFromFile("assets/font.ttf") )
	{
		std::cout << "assets failed to load\n";
		return 0;
	}

	//create the winner Text
	sf::Text text;
	text.setFont(font);
	//text.setString("Cross won");
	text.setCharacterSize(30);//TODO: regarder la taille
	text.setFillColor(sf::Color::Red);
	text.setPosition(sf::Vector2f(DIM*0.55f, DIM*1.4f));
	//create the sprites
	sf::Sprite boardSprite;
	boardSprite.setTexture(boardTexture);
	
	sf::Sprite crossSprite;
	crossSprite.setTexture(crossTexture);
	
	sf::Sprite circleSprite;
	circleSprite.setTexture(circleTexture);

	sf::RenderWindow window(sf::VideoMode(300, 300), "tic tac toe");
	
	//game logic
	//1 -> cross | 2 -> circle | 0 -> empty
	int x(0), y(0);
	int field[9] {0, 0, 0, 0, 0, 0, 0, 0, 0};
	bool isCrossTurn(true);
	int winner(0), remaningSpot(9);
	//time related stuff
	sf::Clock clock;
	float deltaTime(0.0f);
	

	while(window.isOpen())
	{
	
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if(event.key.code == sf::Keyboard::Escape)
						window.close();
					break;
			
			}
		}
	
		//-----update-----
		
		//mouse detection
		
		deltaTime += (deltaTime > DELAY)?0:clock.getElapsedTime().asSeconds();
		clock.restart();
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&& deltaTime > DELAY && winner == 0 && remaningSpot > 0)
		{

			deltaTime = 0.0f;
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			x = localPosition.x /DIM;
			y = localPosition.y /DIM;
			//just in case :)
			x = (x>2)?2:x;
			y = (y>2)?2:y;
			
			if(field[y*3+x] == 0)
			{
				field[y*3 +x] = (isCrossTurn)?1:2;
				isCrossTurn = !isCrossTurn;
				remaningSpot--;
			}
		}


		//win condition
		//  ---
		for(int i = 0; i < 3; i++){
			if (field[i*3] == field[i*3+1] && field[i*3] == field[i*3+2] && field[i*3] !=0)
				winner = field[i*3];
		
		

		//  |||
			if (field[0 +i] == field[3+i] && field[0+i] == field[6+i] && field[0 +i] !=0)
				winner = field[0+i];
		
		}
		//  /
			if(field[0] == field[4] && field[0] == field[8] && field[0] != 0)
				winner = field[0];
		//  \(n)
			if(field[2] == field[4] && field[2] == field[6] && field[2] != 0)
				winner = field[2];
		
		if(winner != 0){
			//std::cout << "winner is " << ((winner == 1)?"cross":"circle") << " !\n";
			text.setString((winner==1)?"cross won":"circle won");
		//	window.close();
		}
		if(remaningSpot <=0){
		//	std::cout << "and this is a draw !\n";
			text.setString("draw!!!");
		//	window.close();
		}

		//-----draw------
		
		window.clear();

		window.draw(boardSprite);
		for(int i = 0; i < 9; i++)
		{
			if(field[i] == 1)
			{
				crossSprite.setPosition(sf::Vector2f(i%3 * DIM, i/3* DIM));
				window.draw(crossSprite);
			}else if(field[i] == 2)
			{
				circleSprite.setPosition(sf::Vector2f(i%3 * DIM, i/3* DIM));
				window.draw(circleSprite);
			}
		}
		if(winner !=0 || remaningSpot <=0){
			window.clear();
			window.draw(text);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				for(int i = 0; i < 9; i++)
					field[i] = 0;
				winner = 0;
				remaningSpot = 9;			
			}
		}

		window.display();

	}


	return 0;
}
