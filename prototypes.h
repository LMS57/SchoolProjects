typedef struct player{
	char name[20];
        int i ;         //i and j are for location on the board
        int j ;
        int money;
        int jail;

}player;

char board[13][13];
int l = 0; //determines whether user goes first or second.
int cjail = 0, counter = 0, test = 0, doubles = 0, fp = 100, cgetOutOfJail = 0, chanceGetOutOfJail = 0, ccgetOutOfJail = 0, chestGetOutOfJail = 0;
int pjail = 0, pbroke = 0, cbroke = 0, choldings = 0, pholdings = 0, gameOver = 0, pRR = 0, cRR = 0, cU = 0, pU = 0, pgetOutOfJail = 0;
player player1;
player comp;
void printBoard();
void createBoard();
int gotoJail(player *tmp);
void sum();
int checkOwnership(player *tmp);
void payOwner(player *tmp);
void possiblePurchase(player *tmp);

void buyHouse(player *tmp);
void bankrupt(player *tmp);
int rollDice();
void move(player *tmp, int sums);
void playGame();
void changeLoc();
void freeParking(player *tmp);
void passGo(player *tmp);
void sell(player *tmp);
void printPropertiesOwned(player *tmp);
void checkLoc(player *tmp);
void incomeTax(player *tmp);
void luxaryTax(player *tmp);
void chance(player *tmp);
void communityChest(player *tmp);
void broke(player *tmp);

#define Red "\x1b[31m" //chances color of the text
#define White "\x1b[0m"
#define Purple "\x1b[35m"
#define BrightBlue "\x1b[1;36m"
#define Magenta "\x1b[1;35m"
#define Orange "\x1b[1;31m"
#define Yellow "\x1b[1;33m"
#define Green "\x1b[32m"
#define Blue "\x1b[34m"
#define Road "\x1b[33m"
#define Tax "\x1b[1;32m"
#define Chest "\x1b[1;34m"
#define BrightWhite "\x1b[1;37m"
#define Chance "\x1b[36m"
