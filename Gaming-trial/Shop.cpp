#include "Shop.h"


/*
	Η παρακάτω μέθοδος ορίζει ουσιαστικά τα αρχικό κομμάτι του διαλόγου από το shop προς τον παίχτη.Δίνεται στον player η δυνατότητα 
	να επιλέψει αν θέλει να αγοράσει κάτι πατώντας [Y,N]
*/

void Shop::SetStartMenuStats() 
{
	m_text_x = m_state->getCanvasWidth() / 2.0f - 4.0f;
	m_dialog_sting = "Hello, Do you want to buy something ? [Y, N]";
	m_dialog_string1 = "";
	m_dialog_string2 = "";
	m_dialogButton = "StartMenu";
}

/*
	Σε περίπτωση που πατήσει Y εμφανίζονται στην οθόνη 3 επιλογές από τις οποίες οι πρώτες δύο παρέχουν στον player ζωή και damage 
	και η τρίτη επιλογή είναι να παεί πίσω στην αρχή του διαλόγου.Ο χρήστης μπορεί να πατήσει 1,2,3 αντίστοιχα για τις επιλογές που 
	προαναφερθηκαν.
*/

void Shop::SetMainMenuStats()
{
	m_dialog_sting = "1 life -> 50 coins | Press 1";
	m_dialog_string1 = "Increase Damage -> 20 coins | Press 2";
	m_dialog_string2 = "Go Back | Press 3";
	m_dialogButton = "MainMenu";
	m_text_x = m_state->getCanvasWidth() / 2.0f - 3.0;
	Press1Allowed = true;
	Press2Allowed = true;
}

/*
	Σε περίπτωση που πατήσει Ν έχει τελειώσει η συναλλαγή αλλά του δίνεται η επιλογή να κάνει return στο προηγούμενο part του
	διαλόγου πατώντας 3.
*/

void Shop::SetLastMenuStats()
{
	m_dialog_sting = "Bye Bye my friend!!";
	m_text_x = m_state->getCanvasWidth() / 2.0f - 1.8f;
	m_dialog_string1 = "";
	m_dialog_string2 = "Go Back | Press 3";
	m_dialogButton = "LastMenu";
}

/*
	Σε περίπτωση που πατήσει 1 ή 2 ο διάλογος συνέχιζει δίνοντας στον player την επιλογή να επιλέξει αν θέλει να αγοράσει κάτι αλλό
	πατώντας [Y,N] .
*/

void Shop::SetElseMenuStats() 
{
	m_text_x = m_state->getCanvasWidth() / 2.0f - 4.0;
	m_dialog_string1 = " ";
	m_dialog_string2 = " ";
	m_dialog_sting = "Do you want to buy something else? [Y,N]";
	m_dialogButton = "ElseMenu";
}

/*
	Σε περίπτωση που πατήσει Ν έχει τελειώσει η συναλλαγή αλλά του δίνεται η επιλογή να κάνει return στο προηγούμενο part του 
	διαλόγου πατώντας 3.
*/

void Shop::SetPreLastMenuStats()
{
	m_dialog_sting = "Bye Bye my friend!!";
	m_text_x = m_state->getCanvasWidth() / 2.0f - 1.8f;
	m_dialog_string1 = "";
	m_dialog_string2 = "Go Back | Press 3";
	m_dialogButton = "PreLastMenu";
}


/*
	Ο διάλογος ξεκίναει όταν Ο Player τοποθετηθεί ακριβώς στο κέντρο του shop . Επείτα χρησιμοποιώντας τις μεθόδους που έχουμε 
	υλοποιήσει παραπάνω θέτει τις σωστές φράσεις αναλόγως το κουμπί που θα πατήσει ο χρήστης . Στο συγκεκρίμενο part γίνεται χρήση
	της μεθόδου (graphics::getKeyState()).
*/

void Shop::update(float dt)
{
	

	if (fabs(m_pos_x - m_state->getPlayer()->m_pos_x) <= 0.5f && fabs(m_pos_y - m_state->getPlayer()->m_pos_y) <= 1.0)
	{
		if (graphics::getKeyState(graphics::SCANCODE_Y) && m_dialogButton == "StartMenu")
		{
			SetMainMenuStats();
			
		}
		else if (graphics::getKeyState(graphics::SCANCODE_N) && m_dialogButton == "StartMenu")
		{
			SetLastMenuStats();
		}
		if (graphics::getKeyState(graphics::SCANCODE_1) && Press1Allowed)
		{
			if (m_state->getPlayer()->getWallet() - 50 >= 0 && m_state->getPlayer()->life <= 8)
			{
				m_state->getPlayer()->life = m_state->getPlayer()->life + 2;
				m_state->getPlayer()->reduceFromWallet(50);
				SetElseMenuStats();
			}
			else if ((m_state->getPlayer()->getWallet() - 50 >= 0 && m_state->getPlayer()->life > 8 && m_state->getPlayer()->life < 10))
			{
				m_state->getPlayer()->life = m_state->getPlayer()->life = 10;
			}
			Press1Allowed = false;
		}
		else if (graphics::getKeyState(graphics::SCANCODE_2) && Press2Allowed)
		{
			if (m_state->getPlayer()->getWallet() - 20 >= 0 && m_state->getPlayer()->getDamage() < 0.050f)
			{
				m_state->getPlayer()->inscreaseDamage();
				m_state->getPlayer()->reduceFromWallet(20);
				SetElseMenuStats();
			} 
			Press2Allowed = false;
		}
		else if (graphics::getKeyState(graphics::SCANCODE_3) && m_dialogButton == "MainMenu")
		{
			SetStartMenuStats();
		}
		else if (graphics::getKeyState(graphics::SCANCODE_Y) && m_dialogButton == "ElseMenu")
		{
			SetMainMenuStats();
		}
		else if (graphics::getKeyState(graphics::SCANCODE_N) && m_dialogButton == "ElseMenu")
		{
			SetPreLastMenuStats();
		}
		else if ((graphics::getKeyState(graphics::SCANCODE_Y) || graphics::getKeyState(graphics::SCANCODE_N)) && m_dialogButton == "LastMenu")
		{
			SetLastMenuStats();
		}
		else if (graphics::getKeyState(graphics::SCANCODE_N) && m_dialogButton == "MainMenu")SetMainMenuStats();

		else if (m_dialogButton == "LastMenu" && graphics::getKeyState(graphics::SCANCODE_3)) SetStartMenuStats();	
		else if ((graphics::getKeyState(graphics::SCANCODE_Y) || graphics::getKeyState(graphics::SCANCODE_N)) && m_dialogButton == "PreLastMenu")
		{
			SetPreLastMenuStats();
		}
	}
	else 
	{
		SetStartMenuStats();
	}
	
}

void Shop::drawDebug()
{
}

void Shop::init()
{
	staticObj::init();
	m_staticObj_br.texture = m_state->DecorationsPaths[11];

	m_br_text.fill_color[0] = 1.0f;
	m_br_text.fill_color[1] = 1.0f;
	m_br_text.fill_color[2] = 1.0f;
	
	m_br_text1.fill_color[0] = 1.0f;
	m_br_text1.fill_color[1] = 1.0f;
	m_br_text1.fill_color[2] = 1.0f;

	m_br_text2.fill_color[0] = 1.0f;
	m_br_text2.fill_color[1] = 1.0f;
	m_br_text2.fill_color[2] = 1.0f;
}

void Shop::draw()
{
	staticObj::draw();
	if (fabs(m_pos_x - m_state->getPlayer()->m_pos_x) <= 0.5f && fabs(m_pos_y - m_state->getPlayer()->m_pos_y) <= 1.0)
	{
		graphics::drawText(m_text_x,m_text_y, 0.4f, m_dialog_sting, m_br_text); 
		graphics::drawText(m_text_x, m_text_y - 0.4f, 0.4f, m_dialog_string1, m_br_text1);
		graphics::drawText(m_text_x, m_text_y - 0.8f, 0.4f, m_dialog_string2, m_br_text2);

	}

}

Shop::Shop(float x, float y, float width, float height, float staticObjSize):staticObj(x,y,width,height,staticObjSize)
{
}
