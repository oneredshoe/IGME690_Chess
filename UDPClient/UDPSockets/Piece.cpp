#pragma once
#include "Piece.h"

Piece::Piece(PieceType name, int x, int y, bool isBlack, sf::RenderWindow* win)
{
	m_name = name;

	m_position[0] = x;
	m_position[1] = y;
	m_isBlack = isBlack;
	m_window = win;
}


Piece::Piece(sf::RenderWindow* win)
{
	m_name = PAWN;
	m_position[0] = 0;
	m_position[1] = 0;
	m_isBlack = false;
	m_window = win;
}

Piece::Piece() //: m_window(sf::RenderWindow(sf::VideoMode(50 * 8, 50 * 8), "Chess"))
{
	m_name = PAWN;
	m_position[0] = 0;
	m_position[1] = 0;
	m_isBlack = false;
	m_window = nullptr;
	//m_window.create(sf::RenderWindow(sf::VideoMode(50 * 8, 50 * 8), "Chess"));
} //nulptr

Piece::~Piece()
{

}

PieceType Piece::getName() {
	return m_name;
}

int* Piece::getPosition() {
	return m_position;
}

bool Piece::isBlack() {
	return m_isBlack;
}

int Piece::getGlobalMultiplier()
{
	return 50;
}




void Piece::Draw()
{
	int origin[2];
	int p_TopRadius = 3;//6
	int p_HatRadius = 7;//14 //8
	int p_BodyHeight = 15;
	int p_BaseHeight = 3;
	int p_BottomHeight = 3;//5 //13

	//should be short af
	sf::CircleShape p_Top(p_TopRadius);
	//triangle hat
	sf::CircleShape p_Hat(p_HatRadius, 3); //(size, 3);
	sf::RectangleShape p_Body(sf::Vector2f(5, p_BodyHeight));
	sf::RectangleShape p_Base(sf::Vector2f(7, p_BaseHeight));
	sf::RectangleShape p_Bottom(sf::Vector2f(9, p_BottomHeight));
	sf::ConvexShape king;
	sf::ConvexShape queen;
	int b_TopHeight = 3;
	int b_HeadHeight = 6;
	int b_BodyHeight = 20;
	sf::CircleShape b_Top(b_TopHeight);
	sf::CircleShape b_Head(b_HeadHeight);
	sf::RectangleShape b_Body(sf::Vector2f(5, b_BodyHeight));
	sf::RectangleShape b_Base(sf::Vector2f(13, 5));
	sf::ConvexShape horse;
	int r_TopHeight = 10;
	int r_HeadHeight = 5;
	int r_BodyHeight = 20;


	sf::RectangleShape r_Top(sf::Vector2f(12, r_TopHeight));
	sf::RectangleShape r_Head(sf::Vector2f(8, r_HeadHeight));
	sf::RectangleShape r_Body(sf::Vector2f(5, r_BodyHeight));
	sf::RectangleShape r_Base(sf::Vector2f(15, 5));


	switch (m_name)
	{
	case PAWN:
		std::cout << "Pawn Draw!" << std::endl;
		
		//Corner of square the piece is on
		origin[0] = m_position[1] * getGlobalMultiplier();
		origin[1] = m_position[0] * getGlobalMultiplier();

	

		//outlines are needed if we keep the game only 2 colors
		//textures can be put in later
		if (m_isBlack)
		{
			p_Top.setFillColor(sf::Color::Black);
			p_Hat.setFillColor(sf::Color::Black);
			p_Body.setFillColor(sf::Color::Black);
			p_Base.setFillColor(sf::Color::Black);
			p_Bottom.setFillColor(sf::Color::Black);
			p_Top.setOutlineColor(sf::Color::White);
			p_Hat.setOutlineColor(sf::Color::White);
			p_Body.setOutlineColor(sf::Color::White);
			p_Base.setOutlineColor(sf::Color::White);
			p_Bottom.setOutlineColor(sf::Color::White);

		}
		else
		{
			p_Top.setFillColor(sf::Color::White);
			p_Hat.setFillColor(sf::Color::White);
			p_Body.setFillColor(sf::Color::White);
			p_Base.setFillColor(sf::Color::White);
			p_Bottom.setFillColor(sf::Color::White);
			p_Top.setOutlineColor(sf::Color::Black);
			p_Hat.setOutlineColor(sf::Color::Black);
			p_Body.setOutlineColor(sf::Color::Black);
			p_Base.setOutlineColor(sf::Color::Black);
			p_Bottom.setOutlineColor(sf::Color::Black);

		}

		p_Top.setPosition(origin[0] += 10, origin[1] += 10);
		p_Hat.setPosition(origin[0] -= p_TopRadius * 1.1, origin[1] += (p_TopRadius)-2);
		p_Body.setPosition(origin[0] += p_TopRadius * 1.5, origin[1] += (p_HatRadius));
		p_Base.setPosition(origin[0] -= 1, origin[1] += p_BodyHeight);
		p_Bottom.setPosition(origin[0] -= 1, origin[1] += p_BaseHeight);


		m_window->draw(p_Top);
		m_window->draw(p_Hat);
		m_window->draw(p_Body);
		m_window->draw(p_Base);
		m_window->draw(p_Bottom);
		break;
	case KING:
		
		//Corner of square the piece is on
		origin[0] = m_position[1] * getGlobalMultiplier();
		origin[1] = m_position[0] * getGlobalMultiplier();

		

		king.setPointCount(21);

		king.setPoint(0, sf::Vector2f(7, 2));

		king.setPoint(1, sf::Vector2f(5, 5));
		king.setPoint(2, sf::Vector2f(2, 0));
		king.setPoint(3, sf::Vector2f(2, 9));
		king.setPoint(4, sf::Vector2f(0, 9));
		king.setPoint(5, sf::Vector2f(0, 11));
		king.setPoint(6, sf::Vector2f(7, 11));
		king.setPoint(7, sf::Vector2f(2, 15));
		king.setPoint(8, sf::Vector2f(2, 36));
		king.setPoint(9, sf::Vector2f(-1, 38));
		king.setPoint(10, sf::Vector2f(-1, 40));
		king.setPoint(11, sf::Vector2f(14, 40));
		king.setPoint(12, sf::Vector2f(14, 38));
		king.setPoint(13, sf::Vector2f(11, 36));
		king.setPoint(14, sf::Vector2f(11, 15));
		king.setPoint(15, sf::Vector2f(7, 11));
		king.setPoint(16, sf::Vector2f(13, 11));
		king.setPoint(17, sf::Vector2f(13, 9));
		king.setPoint(18, sf::Vector2f(11, 9));
		king.setPoint(19, sf::Vector2f(11, 0));
		king.setPoint(20, sf::Vector2f(9, 5));


		if (m_isBlack)
		{
			king.setFillColor(sf::Color::Black);
		}
		else
		{
			king.setFillColor(sf::Color::White);
		}

		king.setPosition(origin[0] + 10, origin[1] + 10);
		m_window->draw(king);
		break;
	case QUEEN:
		
		//Corner of square the piece is on
		origin[0] = m_position[1] * getGlobalMultiplier();
		origin[1] = m_position[0] * getGlobalMultiplier();

	


		queen.setPointCount(23);
		queen.setPoint(0, sf::Vector2f(10, 1));

		queen.setPoint(1, sf::Vector2f(7, 3));
		queen.setPoint(2, sf::Vector2f(4, 0));
		queen.setPoint(3, sf::Vector2f(4, 5));

		queen.setPoint(4, sf::Vector2f(1, 5));
		queen.setPoint(5, sf::Vector2f(1, 7));
		queen.setPoint(6, sf::Vector2f(3, 7));
		queen.setPoint(7, sf::Vector2f(3, 9));
		queen.setPoint(8, sf::Vector2f(5, 9));
		queen.setPoint(9, sf::Vector2f(5, 30));
		queen.setPoint(10, sf::Vector2f(1, 37));
		queen.setPoint(11, sf::Vector2f(1, 40));
		queen.setPoint(12, sf::Vector2f(19, 40));
		queen.setPoint(13, sf::Vector2f(19, 37));
		queen.setPoint(14, sf::Vector2f(15, 30));
		queen.setPoint(15, sf::Vector2f(15, 9));
		queen.setPoint(16, sf::Vector2f(17, 9));
		queen.setPoint(17, sf::Vector2f(17, 7));
		queen.setPoint(18, sf::Vector2f(19, 7));
		queen.setPoint(19, sf::Vector2f(19, 5));

		queen.setPoint(20, sf::Vector2f(16, 5));
		queen.setPoint(21, sf::Vector2f(16, 0));
		queen.setPoint(22, sf::Vector2f(13, 3));

		if (m_isBlack)
		{
			queen.setFillColor(sf::Color::Black);
		}
		else
		{
			queen.setFillColor(sf::Color::White);
		}

		queen.setPosition(origin[0] + 10, origin[1] + 10);
		m_window->draw(queen);
		break;
	case BISHOP:

		
		//Corner of square the piece is on
		origin[0] = m_position[1] * getGlobalMultiplier();
		origin[1] = m_position[0] * getGlobalMultiplier();

		
		if (m_isBlack)
		{
			b_Top.setFillColor(sf::Color::Black);
			b_Head.setFillColor(sf::Color::Black);
			b_Body.setFillColor(sf::Color::Black);
			b_Base.setFillColor(sf::Color::Black);
			b_Top.setOutlineColor(sf::Color::White);
			b_Head.setOutlineColor(sf::Color::White);
			b_Body.setOutlineColor(sf::Color::White);
			b_Base.setOutlineColor(sf::Color::White);

		}
		else
		{
			b_Top.setFillColor(sf::Color::White);
			b_Head.setFillColor(sf::Color::White);
			b_Body.setFillColor(sf::Color::White);
			b_Base.setFillColor(sf::Color::White);
			b_Top.setOutlineColor(sf::Color::Black);
			b_Head.setOutlineColor(sf::Color::Black);
			b_Body.setOutlineColor(sf::Color::Black);
			b_Base.setOutlineColor(sf::Color::Black);

		}

		b_Top.setPosition(origin[0] += 10, origin[1] += 10);
		b_Head.setPosition(origin[0] -= b_TopHeight, origin[1] += b_TopHeight * 1.5);
		b_Body.setPosition(origin[0] += 4.5, origin[1] += b_HeadHeight * 1.5);
		b_Base.setPosition(origin[0] -= b_TopHeight * 1.1, origin[1] += b_BodyHeight);


		m_window->draw(b_Top);
		m_window->draw(b_Head);
		m_window->draw(b_Body);
		m_window->draw(b_Base);
		break;
	case HORSE:
	
		
		//Corner of square the piece is on
		origin[0] = m_position[1] * getGlobalMultiplier();
		origin[1] = m_position[0] * getGlobalMultiplier();


		horse.setPointCount(14);
		horse.setPoint(0, sf::Vector2f(10, 10));
		horse.setPoint(1, sf::Vector2f(14, 14));
		horse.setPoint(2, sf::Vector2f(18, 24));
		horse.setPoint(3, sf::Vector2f(20, 29));
		horse.setPoint(4, sf::Vector2f(20, 39));
		horse.setPoint(5, sf::Vector2f(23, 39));
		horse.setPoint(6, sf::Vector2f(23, 44));
		horse.setPoint(7, sf::Vector2f(2, 44));
		horse.setPoint(8, sf::Vector2f(2, 39));
		horse.setPoint(9, sf::Vector2f(5, 39));
		horse.setPoint(10, sf::Vector2f(5, 29));
		horse.setPoint(11, sf::Vector2f(0, 29));
		horse.setPoint(12, sf::Vector2f(2, 24));
		horse.setPoint(13, sf::Vector2f(6, 14));

		if (m_isBlack)
		{
			horse.setFillColor(sf::Color::Black);
		}
		else
		{
			horse.setFillColor(sf::Color::White);
		}
		horse.setPosition(origin[0] += 10, origin[1] += 10);
		m_window->draw(horse);
		break;
	case CASTLE:
		
		//Corner of square the piece is on
		origin[0] = m_position[1] * getGlobalMultiplier();
		origin[1] = m_position[0] * getGlobalMultiplier();

		
		if (m_isBlack)
		{
			r_Top.setFillColor(sf::Color::Black);
			r_Head.setFillColor(sf::Color::Black);
			r_Body.setFillColor(sf::Color::Black);
			r_Base.setFillColor(sf::Color::Black);
			r_Top.setOutlineColor(sf::Color::White);
			r_Head.setOutlineColor(sf::Color::White);
			r_Body.setOutlineColor(sf::Color::White);
			r_Base.setOutlineColor(sf::Color::White);

		}
		else
		{
			r_Top.setFillColor(sf::Color::White);
			r_Head.setFillColor(sf::Color::White);
			r_Body.setFillColor(sf::Color::White);
			r_Base.setFillColor(sf::Color::White);
			r_Top.setOutlineColor(sf::Color::Black);
			r_Head.setOutlineColor(sf::Color::Black);
			r_Body.setOutlineColor(sf::Color::Black);
			r_Base.setOutlineColor(sf::Color::Black);

		}

		r_Top.setPosition(origin[0] += 10, origin[1] += 10);
		r_Head.setPosition(origin[0] += 2, origin[1] += r_TopHeight);
		r_Body.setPosition(origin[0] += 1.5f, origin[1] += r_HeadHeight);
		r_Base.setPosition(origin[0] -= 4.5f, origin[1] += r_BodyHeight);

		m_window->draw(r_Top);
		m_window->draw(r_Head);
		m_window->draw(r_Body);
		m_window->draw(r_Base);
		break;
	Default: std::cout << "Default :)" << std::endl;
		break;

	}
}


/////////////Classes////////////////////////////////////////////



Horse::Horse(int x, int y, bool isBlack, sf::RenderWindow* win) : Piece(HORSE, x, y, isBlack, win) {}
void Horse::Draw()
{
	sf::ConvexShape horse;
	int origin[2];
	//Corner of square the piece is on
	origin[0] = m_position[0] * getGlobalMultiplier();
	origin[1] = m_position[1] * getGlobalMultiplier();


	horse.setPointCount(14);
	horse.setPoint(0, sf::Vector2f(10, 10));
	horse.setPoint(1, sf::Vector2f(14, 14));
	horse.setPoint(2, sf::Vector2f(18, 24));
	horse.setPoint(3, sf::Vector2f(20, 29));
	horse.setPoint(4, sf::Vector2f(20, 39));
	horse.setPoint(5, sf::Vector2f(23, 39));
	horse.setPoint(6, sf::Vector2f(23, 44));
	horse.setPoint(7, sf::Vector2f(2, 44));
	horse.setPoint(8, sf::Vector2f(2, 39));
	horse.setPoint(9, sf::Vector2f(5, 39));
	horse.setPoint(10, sf::Vector2f(5, 29));
	horse.setPoint(11, sf::Vector2f(0, 29));
	horse.setPoint(12, sf::Vector2f(2, 24));
	horse.setPoint(13, sf::Vector2f(6, 14));

	if (m_isBlack)
	{
		horse.setFillColor(sf::Color::Black);
	}
	else
	{
		horse.setFillColor(sf::Color::White);
	}
	horse.setPosition(origin[0] += 10, origin[1] += 10);
	m_window->draw(horse);
}

King::King(int x, int y, bool isBlack, sf::RenderWindow* win) : Piece(KING, x, y, isBlack, win) {}
void King::Draw()
{
	int origin[2];
	//Corner of square the piece is on
	origin[0] = m_position[0] * getGlobalMultiplier();
	origin[1] = m_position[1] * getGlobalMultiplier();

	sf::ConvexShape king;

	king.setPointCount(21);

	king.setPoint(0, sf::Vector2f(7, 2));

	king.setPoint(1, sf::Vector2f(5, 5));
	king.setPoint(2, sf::Vector2f(2, 0));
	king.setPoint(3, sf::Vector2f(2, 9));
	king.setPoint(4, sf::Vector2f(0, 9));
	king.setPoint(5, sf::Vector2f(0, 11));
	king.setPoint(6, sf::Vector2f(7, 11));
	king.setPoint(7, sf::Vector2f(2, 15));
	king.setPoint(8, sf::Vector2f(2, 36));
	king.setPoint(9, sf::Vector2f(-1, 38));
	king.setPoint(10, sf::Vector2f(-1, 40));
	king.setPoint(11, sf::Vector2f(14, 40));
	king.setPoint(12, sf::Vector2f(14, 38));
	king.setPoint(13, sf::Vector2f(11, 36));
	king.setPoint(14, sf::Vector2f(11, 15));
	king.setPoint(15, sf::Vector2f(7, 11));
	king.setPoint(16, sf::Vector2f(13, 11));
	king.setPoint(17, sf::Vector2f(13, 9));
	king.setPoint(18, sf::Vector2f(11, 9));
	king.setPoint(19, sf::Vector2f(11, 0));
	king.setPoint(20, sf::Vector2f(9, 5));


	if (m_isBlack)
	{
		king.setFillColor(sf::Color::Black);
	}
	else
	{
		king.setFillColor(sf::Color::White);
	}

	king.setPosition(origin[0] + 10, origin[1] + 10);
	m_window->draw(king);
}



Queen::Queen(int x, int y, bool isBlack, sf::RenderWindow* win) : Piece(QUEEN, x, y, isBlack, win) {}
void Queen::Draw()
{
	int origin[2];
	//Corner of square the piece is on
	origin[0] = m_position[0] * getGlobalMultiplier();
	origin[1] = m_position[1] * getGlobalMultiplier();

	sf::ConvexShape queen;


	queen.setPointCount(23);
	queen.setPoint(0, sf::Vector2f(10, 1));

	queen.setPoint(1, sf::Vector2f(7, 3));
	queen.setPoint(2, sf::Vector2f(4, 0));
	queen.setPoint(3, sf::Vector2f(4, 5));

	queen.setPoint(4, sf::Vector2f(1, 5));
	queen.setPoint(5, sf::Vector2f(1, 7));
	queen.setPoint(6, sf::Vector2f(3, 7));
	queen.setPoint(7, sf::Vector2f(3, 9));
	queen.setPoint(8, sf::Vector2f(5, 9));
	queen.setPoint(9, sf::Vector2f(5, 30));
	queen.setPoint(10, sf::Vector2f(1, 37));
	queen.setPoint(11, sf::Vector2f(1, 40));
	queen.setPoint(12, sf::Vector2f(19, 40));
	queen.setPoint(13, sf::Vector2f(19, 37));
	queen.setPoint(14, sf::Vector2f(15, 30));
	queen.setPoint(15, sf::Vector2f(15, 9));
	queen.setPoint(16, sf::Vector2f(17, 9));
	queen.setPoint(17, sf::Vector2f(17, 7));
	queen.setPoint(18, sf::Vector2f(19, 7));
	queen.setPoint(19, sf::Vector2f(19, 5));

	queen.setPoint(20, sf::Vector2f(16, 5));
	queen.setPoint(21, sf::Vector2f(16, 0));
	queen.setPoint(22, sf::Vector2f(13, 3));

	if (m_isBlack)
	{
		queen.setFillColor(sf::Color::Black);
	}
	else
	{
		queen.setFillColor(sf::Color::White);
	}

	queen.setPosition(origin[0] + 10, origin[1] + 10);
	m_window->draw(queen);
}



Bishop::Bishop(int x, int y, bool isBlack, sf::RenderWindow* win) : Piece(BISHOP, x, y, isBlack, win) {}
void Bishop::Draw()
{
	int origin[2];
	//Corner of square the piece is on
	origin[0] = m_position[0] * getGlobalMultiplier();
	origin[1] = m_position[1] * getGlobalMultiplier();

	int b_TopHeight = 3;
	int b_HeadHeight = 6;
	int b_BodyHeight = 20;
	sf::CircleShape b_Top(b_TopHeight);
	sf::CircleShape b_Head(b_HeadHeight);
	sf::RectangleShape b_Body(sf::Vector2f(5, b_BodyHeight));
	sf::RectangleShape b_Base(sf::Vector2f(13, 5));
	if (m_isBlack)
	{
		b_Top.setFillColor(sf::Color::Black);
		b_Head.setFillColor(sf::Color::Black);
		b_Body.setFillColor(sf::Color::Black);
		b_Base.setFillColor(sf::Color::Black);
		b_Top.setOutlineColor(sf::Color::White);
		b_Head.setOutlineColor(sf::Color::White);
		b_Body.setOutlineColor(sf::Color::White);
		b_Base.setOutlineColor(sf::Color::White);

	}
	else
	{
		b_Top.setFillColor(sf::Color::White);
		b_Head.setFillColor(sf::Color::White);
		b_Body.setFillColor(sf::Color::White);
		b_Base.setFillColor(sf::Color::White);
		b_Top.setOutlineColor(sf::Color::Black);
		b_Head.setOutlineColor(sf::Color::Black);
		b_Body.setOutlineColor(sf::Color::Black);
		b_Base.setOutlineColor(sf::Color::Black);

	}

	b_Top.setPosition(origin[0] += 10, origin[1] += 10);
	b_Head.setPosition(origin[0] -= b_TopHeight, origin[1] += b_TopHeight * 1.5);
	b_Body.setPosition(origin[0] += 4.5, origin[1] += b_HeadHeight * 1.5);
	b_Base.setPosition(origin[0] -= b_TopHeight * 1.1, origin[1] += b_BodyHeight);


	m_window->draw(b_Top);
	m_window->draw(b_Head);
	m_window->draw(b_Body);
	m_window->draw(b_Base);
}




Castle::Castle(int x, int y, bool isBlack, sf::RenderWindow* win) : Piece(CASTLE, x, y, isBlack, win) {}
void Castle::Draw()
{
	int origin[2];
	//Corner of square the piece is on
	origin[0] = m_position[0] * getGlobalMultiplier();
	origin[1] = m_position[1] * getGlobalMultiplier();

	int r_TopHeight = 10;
	int r_HeadHeight = 5;
	int r_BodyHeight = 20;


	sf::RectangleShape r_Top(sf::Vector2f(12, r_TopHeight));
	sf::RectangleShape r_Head(sf::Vector2f(8, r_HeadHeight));
	sf::RectangleShape r_Body(sf::Vector2f(5, r_BodyHeight));
	sf::RectangleShape r_Base(sf::Vector2f(15, 5));
	if (m_isBlack)
	{
		r_Top.setFillColor(sf::Color::Black);
		r_Head.setFillColor(sf::Color::Black);
		r_Body.setFillColor(sf::Color::Black);
		r_Base.setFillColor(sf::Color::Black);
		r_Top.setOutlineColor(sf::Color::White);
		r_Head.setOutlineColor(sf::Color::White);
		r_Body.setOutlineColor(sf::Color::White);
		r_Base.setOutlineColor(sf::Color::White);

	}
	else
	{
		r_Top.setFillColor(sf::Color::White);
		r_Head.setFillColor(sf::Color::White);
		r_Body.setFillColor(sf::Color::White);
		r_Base.setFillColor(sf::Color::White);
		r_Top.setOutlineColor(sf::Color::Black);
		r_Head.setOutlineColor(sf::Color::Black);
		r_Body.setOutlineColor(sf::Color::Black);
		r_Base.setOutlineColor(sf::Color::Black);

	}

	r_Top.setPosition(origin[0] += 10, origin[1] += 10);
	r_Head.setPosition(origin[0] += 2, origin[1] += r_TopHeight);
	r_Body.setPosition(origin[0] += 1.5f, origin[1] += r_HeadHeight);
	r_Base.setPosition(origin[0] -= 4.5f, origin[1] += r_BodyHeight);

	m_window->draw(r_Top);
	m_window->draw(r_Head);
	m_window->draw(r_Body);
	m_window->draw(r_Base);
}


Pawn::Pawn(int x, int y, bool isBlack, sf::RenderWindow* win) : Piece(PAWN, x, y, isBlack, win) {
}
void Pawn::Draw()
{
	std::cout << "Pawn Draw!" << std::endl;
	int origin[2];
	//Corner of square the piece is on
	origin[0] = m_position[0] * getGlobalMultiplier();
	origin[1] = m_position[1] * getGlobalMultiplier();

	int p_TopRadius = 3;//6
	int p_HatRadius = 7;//14 //8
	int p_BodyHeight = 15;
	int p_BaseHeight = 3;
	int p_BottomHeight = 3;//5 //13

	//should be short af
	sf::CircleShape p_Top(p_TopRadius);
	//triangle hat
	sf::CircleShape p_Hat(p_HatRadius, 3); //(size, 3);
	sf::RectangleShape p_Body(sf::Vector2f(5, p_BodyHeight));
	sf::RectangleShape p_Base(sf::Vector2f(7, p_BaseHeight));
	sf::RectangleShape p_Bottom(sf::Vector2f(9, p_BottomHeight));

	//outlines are needed if we keep the game only 2 colors
	//textures can be put in later
	if (m_isBlack)
	{
		p_Top.setFillColor(sf::Color::Black);
		p_Hat.setFillColor(sf::Color::Black);
		p_Body.setFillColor(sf::Color::Black);
		p_Base.setFillColor(sf::Color::Black);
		p_Bottom.setFillColor(sf::Color::Black);
		p_Top.setOutlineColor(sf::Color::White);
		p_Hat.setOutlineColor(sf::Color::White);
		p_Body.setOutlineColor(sf::Color::White);
		p_Base.setOutlineColor(sf::Color::White);
		p_Bottom.setOutlineColor(sf::Color::White);

	}
	else
	{
		p_Top.setFillColor(sf::Color::White);
		p_Hat.setFillColor(sf::Color::White);
		p_Body.setFillColor(sf::Color::White);
		p_Base.setFillColor(sf::Color::White);
		p_Bottom.setFillColor(sf::Color::White);
		p_Top.setOutlineColor(sf::Color::Black);
		p_Hat.setOutlineColor(sf::Color::Black);
		p_Body.setOutlineColor(sf::Color::Black);
		p_Base.setOutlineColor(sf::Color::Black);
		p_Bottom.setOutlineColor(sf::Color::Black);

	}

	p_Top.setPosition(origin[0] += 10, origin[1] += 10);
	p_Hat.setPosition(origin[0] -= p_TopRadius * 1.1, origin[1] += (p_TopRadius)-2);
	p_Body.setPosition(origin[0] += p_TopRadius * 1.5, origin[1] += (p_HatRadius));
	p_Base.setPosition(origin[0] -= 1, origin[1] += p_BodyHeight);
	p_Bottom.setPosition(origin[0] -= 1, origin[1] += p_BaseHeight);


	m_window->draw(p_Top);
	m_window->draw(p_Hat);
	m_window->draw(p_Body);
	m_window->draw(p_Base);
	m_window->draw(p_Bottom);
}

