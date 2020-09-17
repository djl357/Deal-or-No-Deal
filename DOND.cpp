//Dilan Lakhani
//Deal or No Deal Game
//Last Edited: June 13, 2016

#include <lvp\gui_top.h>

#include <lvp\string.h>
#include <lvp\vector.h>
#include <lvp\random.h>
#include <math.h>
#include <lvp\bool.h>



class Button {
            public:
				Button(String text, int xx1,int yy1, int xx2, int yy2, COLORREF color);
				/* Creates a button with upper left corner at X1,Y1 and lower
				right corner at X2,Y2 with Text centered in box */
				Button();
				void SetButton(String text, int xx1,int yy1, int xx2, int yy2, COLORREF color);
				void Paint();
				bool Clicked(int x, int y);
				// Returns true if (x,y) is on the button
            private:
                        int x1, y1, x2, y2;
                        String buttonText;
						COLORREF backgroundColor;
};
//-------------------------------------------------------------------
Button::Button()
{
}
//-------------------------------------------------------------------
Button::Button(String text, int xx1,int yy1, int xx2, int yy2, COLORREF color)
:buttonText(text), x1(xx1), y1(yy1), x2(xx2), y2(yy2), backgroundColor(color)

{
}

//-------------------------------------------------------------------
void Button::SetButton(String text, int xx1,int yy1, int xx2, int yy2, COLORREF color)

{
	buttonText=text;
	x1=xx1;
	y1=yy1;
	x2=xx2;
	y2=yy2;
	backgroundColor=color;
}
//-------------------------------------------------------------------
void Button::Paint()
{
            SetColor(BLACK);
			SetThickness(2);
			SetFillColor(backgroundColor);
            FilledRectangle(x1, y1, x2, y2);
            gotoxy( (x1 + x2) / 2, 5 + (y1 + y2) / 2);
            DrawCenteredText(buttonText);
}
//-------------------------------------------------------------------
bool Button::Clicked(int x, int y)
/* Returns true if point (x,y) is on the button */
{
            return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}
//-------------------------------------------------------------------
void drawMoney(double money, int x, int y)  //formats all money amounts
{
	gotoxy(x + 1, y);
	DrawText("$");

	if (money < 1)
	{
		DrawText("0.");
		gotoxy(x + 20, y);

		if (money < 0.1)
			DrawText("01");

	}
	else if (money >= 1 && money <= 999)
	{
		gotoxy(x + 10, y);
		DrawText(money);
	}
	else if (money >= 1000 && money < 10000)
	{
		double hundredsPlace = fmod(money, 1000);
		double thousandsPlace = (money - hundredsPlace)/1000;

		gotoxy(x + 10, y);
		DrawText(int(thousandsPlace));
		gotoxy(x + 17, y);
		DrawText(",");
		gotoxy(x + 20, y);

		if (hundredsPlace != 0)
			DrawText(int(hundredsPlace));
		else
			DrawText("000");
	}
	else if (money >= 10000 && money < 100000)
	{

		double thousandsPlace = money/1000;

		gotoxy(x + 10, y);
		DrawText(int(thousandsPlace));
		gotoxy(x + 25, y);
		DrawText(",");
		gotoxy(x + 29, y);
		DrawText("000");
	}
	else if (money >= 100000 && money < 1000000)
	{
		double thousandsPlace = money / 1000;

		gotoxy(x + 10, y);
		DrawText(int(thousandsPlace));
		gotoxy(x + 35, y);
		DrawText(",");
		gotoxy(x + 37, y);
		DrawText("000");

	}
	else if (money == 1000000)
		DrawText("1,000,000");
}
//-------------------------------------------------------------------

class Briefcase
{
public:
	Briefcase(); // prototype default constructor
	Briefcase(String aModel, double amoney , int aBox, int mx, int my, int mwidth, int mheight) ;
	//initializes Briefcases
	double getMoney();
	int getBox();

	void Draw(int x, int y);
	bool IsClicked(int mx, int my);
	bool getChosen();
	void setChosen(bool b);
	void set(String aModel, double amoney , int abox, int mx, int my, int mwidth, int mheight);
	String getModel();
	void setPlayerCase(bool b);
	bool getPlayerCase();
	void SetBriefcase(Briefcase a);
private:
	double money;
	String model;
	int box;
	int x, y;
	int width, height;
	bool chosen;
	bool playerCase;
};


Briefcase::Briefcase()
:chosen(false), playerCase(false)
{
}

Briefcase::Briefcase(String aModel, double amoney , int aBox, int mx, int my, int mwidth, int mheight)
:chosen(false), playerCase(false)
{
	model=aModel;
	money = amoney ;
	box = aBox;
	x=mx;
	y=my;
	width=mwidth;
	height=mheight;
}

bool Briefcase::getPlayerCase()
{
	return playerCase;
}

void Briefcase::setPlayerCase(bool b)
{
	playerCase = b;
}

void Briefcase::set(String aModel, double amoney , int aBox, int mx, int my, int mwidth, int mheight)
{
	model = aModel;
	money = amoney ;
	box = aBox;
	x = mx;
	y = my;
	width = mwidth; //75
	height = mheight; //38
}

void Briefcase::SetBriefcase(Briefcase a)
{
	model = a.getModel();
	box = a.getBox();
	money = a.getMoney();
}

int Briefcase::getBox()
{
	return box;
}

double Briefcase::getMoney()
{
	return money;
}

String Briefcase::getModel()
{
	return model;
}
void Briefcase::Draw(int x, int y)
{

	int x2 = x + width;
	int y2 = y + height;

	SetFillColor(RED);
	FilledRectangle(x+20,y - 10,x + 62,y - 20); //top of handle 42 wide, 10 height
	FilledRectangle(x+ 30,y,x + 20,y - 20); //left handle 10 wide, 20 height
	FilledRectangle(x + 52,y,x + 62,y - 20); //right handle 10 wide, 20 height
	FilledRectangle(x,y,x+82,y+35);  //case,  82 wide, 35 height

}

bool Briefcase::IsClicked(int mX, int mY)
{
	if(mX > x && mX < x+82 && mY > y  && mY < y+35  ||  mX>x+20 && mX<x+30 && mY<y && mY>y-20 ||  	mX>x+52 && mX<x+62 && mY<y && mY>y-20  || mX>x+20 && mX<x+62 && mY<y-10 && mY>y-20)  //x is the x position of the case, y is the y position
		return true;  //mX is clicked area
	return false;
}

bool Briefcase::getChosen()
{
	return chosen;
}

void Briefcase::setChosen(bool val)
{
	chosen = val;
}
//----------------------------------------------------------------------
bool contains(vector<int> &array, int searchFor)
{
	for (int i = 0; i < array.length(); i++)
		if (array[i] == searchFor)
			return true;
	return false;
}

//----------------------------------------------------------------
class SubPanel
{
	public:
		SubPanel();
		double getMoney();
		void Paint(int x,int y);
		void setMoney(double m);
		void setUsed();
		bool getUsed();
	private:
		int x;
		int y;
		double money;
		bool used;

};
SubPanel::SubPanel()
:x(0),y(0),money(0.01)
{
	used=false;
}
double SubPanel::getMoney()
{
	return money;
}
void SubPanel::setUsed()
{
	used=true;
}
bool SubPanel::getUsed()
{
	return used;
}

void SubPanel::setMoney(double m)
{
	money=m;
}
void SubPanel::Paint(int x,int y)
{
	FilledRectangle(x,y,x+200,y+40);
	drawMoney(money,x+75,y+20);

}
//-------------------------------------------------
class Panel
{
	public:
		Panel();
		void initializePanel();
		void setUsed(int index);
		bool getUsed(int index);
		double getMoney(int index);
	private:
		vector <SubPanel> panels;
		vector <double> values;
		vector <bool> used;

	};

Panel::Panel()
:panels(26),values(26),used(26)
{
	values[0]=.01;
	values[1]=1;
	values[2]=5;
	values[3]=10;
	values[4]=25;
	values[5]=50;
	values[6]=75;
	values[7]=100;
	values[8]=200;
	values[9]=300;
	values[10]=400;
	values[11]=500;
	values[12]=750;
	values[13]=1000;
	values[14]=5000;
	values[15]=10000;
	values[16]=25000;
	values[17]=50000;
	values[18]=75000;
	values[19]=100000;
	values[20]=200000;
	values[21]=300000;
	values[22]=400000;
	values[23]=500000;
	values[24]=750000;
	values[25]=1000000;
}
void Panel::setUsed(int index)
{
	panels[index].setUsed();
}
bool Panel::getUsed(int index)
{
	return panels[index].getUsed();
}
double Panel::getMoney(int index)
{
	return panels[index].getMoney();
}
void Panel::initializePanel()
{

	int x=0,y=0;
	for(int i=0;i<26;i++)
	{
		panels[i].setMoney(values[i]);
		if(panels[i].getUsed()==true)
			SetFillColor(GRAY);
		else
			SetFillColor(GREEN);
		panels[i].Paint(y,50+x);

		x=x+60;
		if(i==12)
		{
			y=y+1070;
			x=0;
		}
	}
}

void DrawLoseScreen(Briefcase chosenCase, double offer,double highest)
{
	SetColor(BLACK);
	SetFillColor(RED);
	FilledRectangle(0,0,GetMaxX(),GetMaxY());
	gotoxy(GetMaxX()/2,GetMaxY()/2);
	DrawText("YOU LOSE!");
	gotoxy(550,100);
	DrawCenteredText("The Suitcase you picked had ");
	gotoxy(640,100);
	drawMoney(chosenCase.getMoney(), 640,100);
	gotoxy(737,100);
	DrawCenteredText(" Dollars");
	gotoxy(550,300);
	DrawCenteredText("The Banker Offered ");
	gotoxy(645,300);
	drawMoney(offer, 625, 300);
	gotoxy(704,450);
	DrawCenteredText(" Dollars, and the Highest Offer was ");
	gotoxy(800,450);
	drawMoney(highest,900,450);

}

void DrawWinScreen(Briefcase chosenCase, double offer)
{
	SetColor(BLACK);
	SetFillColor(GREEN);
	FilledRectangle(0,0,GetMaxX(),GetMaxY());
	gotoxy(GetMaxX()/2,GetMaxY()/2);
	DrawText("YOU WIN!");
	gotoxy(550,100);
	DrawCenteredText("The Suitcase you picked had ");
	gotoxy(640,100);
	drawMoney(chosenCase.getMoney(), 640,100);
	gotoxy(737,100);
	DrawCenteredText(" Dollars");
	gotoxy(540,300);
	DrawCenteredText("The Banker Offered ");
	gotoxy(645,300);
	drawMoney(offer, 625, 300);
	gotoxy(704,300);
	DrawCenteredText(" Dollars");

}
// ---------------------------------------------------------------------------------------------------------
class GamePlay
{
	public:
		GamePlay();
		void DrawBriefcases();
		double GetOffer();
		void setPersonalCase(Briefcase own);
		int numCasesLeft();
		Briefcase GetPersonalCase();
		bool dealOrNoDeal(int lastX, int lastY);
		void PickCases(int x, int y);
		void Game(int x,int y);
		void WinOrLose(double offer);
	private:
		vector <Briefcase> cases;
		Briefcase ownCase;
		vector <int> xPos;
		vector <int> yPos;
		Panel myPanel;
		vector <SubPanel> panels;
		vector <double> values;
		vector <String> modelNames;
		double highest;
		int round;
		int casesLeft;
		int x,y;
		int num;
		Button deal;
		Button noDeal;
};
// ---------------------------------------------------------------------------------------------------------

GamePlay::GamePlay()  //loads briefcase values
:highest(0),cases(26),xPos(26),yPos(26),myPanel(),values(26),panels(26),modelNames(26),num(6),round(0)
{
	deal=Button("Deal", GetMaxX()/2 - 400, GetMaxY()/2+1, GetMaxX()/2-330, GetMaxY()/2 + 101,GREEN);
	noDeal=Button("No Deal", GetMaxX()/2-400 , GetMaxY()/2 - 100, GetMaxX()/2 -330, GetMaxY()/2,RED);
	//initializes deal and noDeal buttons
	values[0]=.01;
	values[1]=1;
	values[2]=5;
	values[3]=10;
	values[4]=25;
	values[5]=50;
	values[6]=75;
	values[7]=100;
	values[8]=200;
	values[9]=300;
	values[10]=400;
	values[11]=500;
	values[12]=750;
	values[13]=1000;
	values[14]=5000;
	values[15]=10000;
	values[16]=25000;
	values[17]=50000;
	values[18]=75000;
	values[19]=100000;
	values[20]=200000;
	values[21]=300000;
	values[22]=400000;
	values[23]=500000;
	values[24]=750000;
	values[25]=1000000;

	vector <int> chosenIndex(26);

	int pickedCount = 0;
	int posAdded = 0;

	modelNames[0]="Marta";
	modelNames[1]="Stacey";
	modelNames[2]="Lisa";
	modelNames[3]="Suzanne";
	modelNames[4]="Mary";
	modelNames[5]="Megan";
	modelNames[6]="Sara";
	modelNames[7]="Allison";
	modelNames[8]="Patricia";
	modelNames[9]="Rachel";
	modelNames[10]="Katie";
	modelNames[11]="Lauren";
	modelNames[12]="Leila";
	modelNames[13]="Danielle";
	modelNames[14]="Brooke";
	modelNames[15]="Julia";
	modelNames[16]="Jenelle";
	modelNames[17]="Maria";
	modelNames[18]="Amanda";
	modelNames[19]="Jane";
	modelNames[20]="Tanisha";
	modelNames[21]="Crystal";
	modelNames[22]="Becky";
	modelNames[23]="Lazar";
	modelNames[24]="Bob";
	modelNames[25]="Julie";

	for (int j = 0; j < 13; j++)
	{
		for (int k = 0; k < 2; k++)
		{
			xPos[posAdded] = (GetMaxX()/2 - 200) + (k * 300);  //spaces out the x coordinates of each briefcase
			yPos[posAdded++] = GetMaxY()/20 + (j * 60); //spaces out the y coordinates of each briefcase
		}
	}

	for (int i = 0; i < cases.length(); i++)
	{

		double money = 0;

		// the index of the moneyValues array
		int chosen = 0;

		randomize();
		do
		{

			chosen = random(chosenIndex.length());

		} while (contains(chosenIndex, chosen));

		chosenIndex[pickedCount++] = chosen;
		money = values[chosen];

		// set up the briefcase

		cases[i].set(modelNames[i], money , i + 1, xPos[i], yPos[i], 75, 38);
	}
}


void GamePlay::DrawBriefcases()
{

	for (int i = 0; i < cases.length(); i++)
	{
		cases[i].Draw(xPos[i],yPos[i]);
		gotoxy(xPos[i],yPos[i]-5);
		DrawText(i+1);  //box number
		gotoxy(xPos[i]-80,yPos[i]);
		DrawText(cases[i].getModel());
	}
	myPanel.initializePanel();
}
// ---------------------------------------------------------------------------------------------------------

int GamePlay::numCasesLeft()
// returns playable cases plus 1
{
	casesLeft=0;
	for ( int i = 0; i < cases.length(); i++ ) // Adds one to every time a case has not been selected
	{
		if (!(cases[i].getChosen()))
			casesLeft++;
	}
	return casesLeft;
}
// ---------------------------------------------------------------------------------------------------------
void GamePlay::setPersonalCase(Briefcase own)
//sets up personal case
{
	ownCase.set(own.getModel(),own.getMoney(),own.getBox(), 200, GetMaxY() - 200,75,38);
}
//-------------------------------------------------------------------

Briefcase GamePlay::GetPersonalCase()
{
	return ownCase;
}
// ---------------------------------------------------------------------------------------------------------

double GamePlay::GetOffer()
{
	double avgValue = 0;// the average value of the briefcases
	double sum = 0; // sum of all the case values
	int caseCount = 0;	// number of briefcases
	vector <Briefcase> leftCases;

	for (int k = 0; k < cases.length(); k++)
	{
		if (cases[k].getChosen() == false)
		{
			caseCount++;
			leftCases.resize(caseCount);
			leftCases[caseCount - 1] = cases[k];
		}
	}
	// find the sum of the cases
	for (int i = 0; i < caseCount; i++)
		sum = sum + leftCases[i].getMoney();

	return avgValue = sum / caseCount;

}
// ---------------------------------------------------------------------------------------------------------
void GamePlay::WinOrLose(double offer)
// Determines whether or not it was a win or not after choosing deal or at the end of the game
{
	Briefcase a=GetPersonalCase();
	if (offer >= highest && offer>=a.getMoney())
		DrawWinScreen(GetPersonalCase(),offer);
	else
		DrawLoseScreen(GetPersonalCase(),offer,highest);
}
//-------------------------------------------------------------------

bool GamePlay::dealOrNoDeal(int x, int y)
// Returns either "deal" or "no deal" as 'true' or 'false' and displays Deal or No Deal buttons
{
	double offer = GetOffer();
	if(offer>highest)
		highest=offer;
	deal.Paint();
	noDeal.Paint();
	drawMoney(offer,GetMaxX()/2-50, GetMaxY()/2 + 245);
	gotoxy(GetMaxX()/2-50, GetMaxY()/2 + 230);
	DrawCenteredText("The bank's offer is:");
	if (deal.Clicked(x,y))
	{
		WinOrLose(offer);
		return true;
	}
	else if (noDeal.Clicked(x,y))
	{
		SetTextColor(WHITE);
		drawMoney(offer,GetMaxX()/2-50, GetMaxY()/2 + 245);
		gotoxy(GetMaxX()/2-50, GetMaxY()/2 + 230);
		DrawCenteredText("The bank's offer is:");
		SetTextColor(BLACK);
		MessageBox("NO DEAL!","Deal Or No Deal");
		return false;
	}
	else
		return false;
}
// ---------------------------------------------------------------------------------------------------------
void GamePlay::PickCases(int x, int y)
{

	if(round==0)	// If it is the first round then let the user pick his personal case
	{
		gotoxy(GetMaxX()/2, 150);
		DrawCenteredText("Pick Your Case");
	}
	for (int i = 0; i < cases.length(); i++) // Loops through the entire array 'cases'
	{
		if(cases[i].getChosen())  //allows cases that were clicked to keep displaying money amount
		{
			gotoxy(xPos[i]+40,yPos[i]+20);
			drawMoney(cases[i].getMoney(),xPos[i]+10,yPos[i]+20);
		}
		if (cases[i].IsClicked(x, y) && cases[i].getPlayerCase()==false) // If you click on the briefcase 'cases[i]' then excute the following
		{
			if (round == 0)
			{
				setPersonalCase(cases[i]);
				cases[i].setPlayerCase(true);
				SetTextSize(4);
				gotoxy(xPos[i]+50,yPos[i]+20);
				DrawCenteredText("Chosen Case");
				SetTextSize(12);
				round++;
			}
			else
			{
				for(int i=0;i<26;i++)
				{
					if(cases[i].IsClicked(x,y))
					{
						cases[i].setChosen(true);
						for(int x=0;x<panels.length();x++)
						{
							if(cases[i].getMoney()==myPanel.getMoney(x))
								myPanel.setUsed(x);
						}
						myPanel.initializePanel();
						gotoxy(xPos[i]+40,yPos[i]+20);
						drawMoney(cases[i].getMoney(),xPos[i]+10,yPos[i]+20);
					}
				}
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------
void GamePlay::Game(int x, int y)
{
		if ( round >= 6) // If it is round 6 or above then pick 1
		{
			num=1;
			for(num=1;num>0;num--)
			{
				if (num >= 1)
					num--;
				PickCases(x, y);

			}
			round++;

		}
		else if ( round == 5) // If it is round 5 then pick 2
		{
			num=2;
			for(num=2;num>0;num--)
			{
				if (num >= 1)
					num--;
				PickCases(x, y);

			} while ( num>0 );
			round++;

		}
		else if ( round == 4) // If it is round 4 then pick 2
		{
			num=2;
			for(num=2;num>0;num--)
			{

				if (num >= 1)
						num--;
				PickCases(x, y);

			}
			round++;

		}
		else if ( round == 3) // If it is round 3 then 2
		{
			num=2;
			for(num=2;num>0;num--)
			{
				if (num >= 1)
					num--;
				PickCases(x, y);

			}
			round++;

		}
		else if ( round == 2) // If it is round 2 then pick 5
		{
			num=5;
			for(num=5;num>0;num--)
			{

				if (num >= 1)
					num--;
				PickCases(x, y);

			}
			round++;
		}
		else if ( round == 1) // If it is round 1 then pick 6
		{

			for(num=6;num>0;num--)
			{

				if (num >= 1)
					num--;
				PickCases(x, y);

			}
			round++;
		}
		else if ( round == 0)
		{
			PickCases(x, y);
			if (num >= 1)
				num--;
		}

	numCasesLeft();  //checks to see how many playable cases remain
	if(casesLeft==1)
	{
		Briefcase a=GetPersonalCase();
		WinOrLose(a.getMoney());
	}

	if(casesLeft==2)
		dealOrNoDeal(x,y);
	if(casesLeft==3)
		dealOrNoDeal(x,y);
	if(casesLeft==4)
		dealOrNoDeal(x,y);
	if(casesLeft==5)
		dealOrNoDeal(x,y);
	if(casesLeft==6)
		dealOrNoDeal(x,y);
	if(casesLeft==7)
		dealOrNoDeal(x,y);
	if(casesLeft==8)
		dealOrNoDeal(x,y);
	if(casesLeft==9)
		dealOrNoDeal(x,y);
	if(casesLeft==11)
		dealOrNoDeal(x,y);
	if(casesLeft==13)
		dealOrNoDeal(x,y);
	if(casesLeft==15)
		dealOrNoDeal(x,y);
	if(casesLeft==20)
		dealOrNoDeal(x,y);
}

//-------------------------------------------------------------------------------
class GuiClass
{
	public:
	GuiClass();
	void GuiMouseClick(int lastx, int lasty);
	void GuiPaint();
	String Title();
	private:
		GamePlay a;
		int x;
		int y;
};
//--------------------------------------------------------------------------------
GuiClass::GuiClass()
{
}
//--------------------------------------------------------------------------------
String GuiClass::Title()
{
	return "Deal or No Deal";
}
//--------------------------------------------------------------------------------
void GuiClass::GuiMouseClick(int lastx, int lasty)
{
	x=lastx;
	y=lasty;
}
//--------------------------------------------------------------------------------
void GuiClass::GuiPaint()
{
	GamePlay();
	a.DrawBriefcases();
	a.Game(x,y);
}
//--------------------------------------------------------------------------------
#include <lvp\gui_bot.h>
