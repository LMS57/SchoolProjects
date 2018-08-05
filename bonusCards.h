typedef struct chance{//struct for chance cards
        void ((*fp)());//points to chance function
        struct chance *next;
}chanceCards;

typedef struct chest{//struct for chest cards
        void ((*fp)());
}chestCards;
chanceCards *head;
chestCards *cf[16];
//chance card functions
void chance0(player *tmp)
{
printf("Advance to the nearest railroad, if unowned you can buy it from the bank, if owned, pay the owner\n");
        printf("\n");
        if(tmp->i ==7){
                tmp->i = 11;
                tmp->j = 6;
                passGo(tmp);
        }
        else if(tmp->i == 11){
                tmp->i = 6;
                tmp->j = 1;
        }
        else if(tmp->i == 1){
                tmp->i = 1;
                tmp->j = 6;
        }
        else
        {
                exit(1);
                printf("Error in chance0; 1");
        }
        checkLoc(tmp);//check for ownership codesdkflnwenionfkld
        printBoard();

        return;
}
void chance1(player *tmp)
{
        printf("Life insurance matures collect $100!\n");
        tmp->money += 100;
        return;
}
void chance2(player *tmp)
{
        printf("Advance to go\n");
        tmp->i = 11;
        tmp->j = 11;
        passGo(tmp);

        return;
}
void chance3(player *tmp)
{
        printf("Advance to Illinois Ave.\n");
        if(tmp->i == 7)
                passGo(tmp);
        tmp->i = 1;
        tmp->j = 5;
        checkLoc(tmp);


        return;
}
void chance4(player *tmp)
{
        printf("Bank pays you a dividend of $50!\n");
        tmp->money += 50;


        return;
}
void chance5(player *tmp)
{
        printf("Get out of jail free card!\n");
        if(l ==  counter % 2)
                pgetOutOfJail++;
        else
                cgetOutOfJail++;
        chanceGetOutOfJail = 1;


        return;
}
void chance6(player *tmp)
{
        printf("Go back 3 spaces\n");
        if(tmp->i == 1){
                tmp->i = 2;
                tmp->j = 1;
        }
        else if(tmp->i == 7)
                tmp->i = 4;
        else
                tmp->j = 7;
        checkLoc(tmp);
        printBoard();
        return;
}
void chance7(player *tmp)
{
        printf("Go to Jail\n");
        gotoJail(tmp);
        counter++;
        return;
}
void chance8(player *tmp)
{
        printf("Make general repairs on all your property pay $25 for each house $115 per hotel\n");
        //function to check for houses
        //function to check for hotels
        int houses = 0, hotels = 0;
        for(int t = 0; t < 22; t++)
        {
                if(strcmp(tmp->name, player1.name) == 0)
                {
                        if(props[t].whoOwns == 'p')
                        {
                                if(props[t].numHouses == 5)
                                        hotels++;
                                else if(props[t].numHouses < 5 && props[t].numHouses > 0);
                                        houses += props[t].numHouses;
                        }

                }
                else
                        if(props[t].whoOwns == 'c')
                        {
                                if(props[t].numHouses == 5)
                                        hotels++;
                                else if(props[t].numHouses < 5 && props[t].numHouses > 0);
                                        houses += props[t].numHouses;
                        }
        }
        sleep(2);
        printf("You have to pay $%d for %d Houses and %d Hotels", (hotels*115 + houses*25), houses, hotels);
        tmp->money -= (hotels*115 + houses*25);
        fp += (hotels*115 + houses*25);
        if(tmp->money < 0)
                sell(tmp);



        return;
}
void chance9(player *tmp){
        printf("Pay a poor tax of $15\n");
        tmp->money -=15;
        fp += 15;
        if(tmp->money < 0)
                sell(tmp);
        return;
}
void chance10(player *tmp)
{
        printf("Take a trip to reading railroad\n");
        passGo(tmp);
        tmp->i = 11;
        tmp->j = 6;
        checkLoc(tmp);

        return;
}
void chance11(player *tmp)
{
        printf("Take a walk on the boardwalk, advance to boardwalk\n");
        tmp->i = 10;
        tmp->j = 11;
        checkLoc(tmp);
        return;
}
void chance12(player *tmp)
{
        printf("Pay each player $50\n");
        if(strcmp(tmp->name, player1.name) != 0){
                comp.money -= 50;
                player1.money += 50;
        }
        else{
                player1.money -= 50;
                comp.money += 50;
        }
        if(tmp->money<0)
                sell(tmp);
        return;
}
void chance13(player *tmp)
{
        printf("You have won a crosswod competition, collect $100\n");
        tmp->money +=100;
        return;
}
void chance14(player *tmp)
{
        printf("Advance to the nearest utility, if unowned you can buy it from the bank, if owned pay the owner\n");
        if(tmp->j == 3)
                tmp -> j = 9;
        else{
                if(tmp -> i == 7){
                        passGo(tmp);
                }
                        tmp->i = 9;
                        tmp->j = 1;

        }
        //check for ownership;
        checkLoc(tmp);
        return;
}
void chance15(player *tmp)
{
        printf("Advance to St. Charles Place\n");
        if(tmp->i == 1 || tmp->i == 7)
                passGo(tmp);
        tmp->i = 10;
        tmp->j = 1;
        checkLoc(tmp);
        return;
}
//chest card functions
void chest0(player *tmp)
{
        printf("Doctor's fees pay $50\n");
        tmp->money -= 50;
        fp += 50;
        return;
}
void chest1(player *tmp)
{
        printf("Advanve to Go\n");
        tmp->i = 11;
        tmp->j = 11;
        passGo(tmp);

        return;
}
void chest2(player *tmp)
{
        printf("Bank error in your favor collect $200\n");
        tmp->money += 200;

        return;
}
void chest3(player *tmp)
{
        printf("Go to Jail\n");
        gotoJail(tmp);
        counter++;
        return;
}
void chest4(player *tmp)
{
        printf("Grand opera night, collect $50 from every person!\n");
        if(strcmp(tmp->name, player1.name)!=0)
        {       comp.money += 50;
                player1.money -= 50;
                if(player1.money<0)
                        sell(&player1);
        }
        else
        {
                player1.money += 50;
                comp.money -= 50;
                if(comp.money<0)
                        sell(&comp);
        }

        return;
}
void chest5(player *tmp)
{
        printf("Holiday fund matures collect $100\n");
        tmp->money += 100;
        return;
}
void chest6(player *tmp)
{
        printf("Income tax refund collect $20\n");
        tmp->money += 20;
        return;
}
void chest7(player *tmp)
{
        printf("Its your birthday collect $10 from every player\n");
        if(strcmp(tmp->name,player1.name)!=0)
        {
                comp.money += 10;
                player1.money -= 10;
                if(player1.money<0)
                        sell(&player1);
        }
        else{
                comp.money -= 10;
                player1.money += 10;
                if(comp.money<0)
                        sell(&comp);
        }

        return;
}
void chest8(player *tmp)
{
        printf("Life insurance matures collect $100\n");
        tmp->money += 100;
        return;
}
void chest9(player *tmp)
{
        printf("Pay school fees of $150\n");
        tmp->money -= 150;
        fp += 150;
        if(tmp->money < 0)
                sell(tmp);
        return;
}
void chest10(player *tmp)
{
        printf("Recieve consultancy fee of $25\n");
        tmp->money += 25;
        return;
}
void chest11(player *tmp)
{
        printf("You are assessed for street repairs $40 per house 115 per hotel\n");
        //code to determine how many houses and how many hotels
        int houses = 0, hotels = 0;
        for(int t = 0; t < 22; t++)
        {
                if(strcmp(tmp->name, player1.name) == 0)
                {
                        if(props[t].whoOwns == 'p')
                        {
                                if(props[t].numHouses == 5)
                                        hotels++;
                                else if(props[t].numHouses < 5 && props[t].numHouses > 0);
                                        houses += props[t].numHouses;
                        }

                }
                else
                        if(props[t].whoOwns == 'c')
                        {
                                if(props[t].numHouses == 5)
                                        hotels++;
                                else if(props[t].numHouses < 5 && props[t].numHouses > 0);
                                        houses += props[t].numHouses;
                        }
        }
        sleep(2);
        printf("You have to pay $%d for %d Houses and %d Hotels", (hotels*115 + houses*40), houses, hotels);
        tmp->money -= (hotels*115 + houses*40);
        fp += (hotels*115 + houses*40);
        if(tmp->money < 0)
                sell(tmp);

        return;
}
void chest12(player *tmp)
{
        printf("You got second in a beauty pagent collect $10\n");
        tmp->money += 10;
        return;
}
void chest13(player *tmp)
{
        printf("You inherit $100\n");
        tmp->money += 100;

        return;
}
void chest14(player *tmp)
{
        printf("Pay hospital fees of $100\n");
        tmp->money -= 100;
        fp += 100;
        if(tmp->money < 0)
                sell(tmp);
        return;
}
void chest15(player *tmp)
{
        printf("Get out of Jail free card\n");
        if(l == counter % 2)
                pgetOutOfJail++ ;
        else
                ccgetOutOfJail++;
        chestGetOutOfJail = 1;


        return;
}
void initializeChance(){//this was just to get a topic done and we both know it was easier the way I had it before;
                chanceCards *temp;
                head = malloc(sizeof(chanceCards));
        head->fp = chance0;
                head->next = malloc(sizeof(chanceCards));
                temp = head->next;
        temp->fp = chance1;

                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance2;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance3;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance4;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance5;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance6;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance7;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance8;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance9;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance10;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance11;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance12;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance13;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance14;
                temp->next = malloc(sizeof(chanceCards));
                temp = temp->next;
        temp->fp = chance15;
                temp->next = NULL;




/*
        chanceFunctions[1]->fp = chance1;

        chanceFunctions[2]->fp = chance2;

        chanceFunctions[3]->fp = chance3;

        chanceFunctions[4]->fp = chance4;

        chanceFunctions[5]->fp = chance5;

        chanceFunctions[6]->fp = chance6;

        chanceFunctions[7]->fp = chance7;

        chanceFunctions[8]->fp = chance8;

        chanceFunctions[9]->fp = chance9;

        chanceFunctions[10]->fp = chance10;

        chanceFunctions[11]->fp = chance11;

        chanceFunctions[12]->fp = chance12;

        chanceFunctions[13]->fp = chance13;

        chanceFunctions[14]->fp = chance14;

        chanceFunctions[15]->fp = chance15;

*/



        return;
}
void initializeChest(){
        for(int j = 0; j < 16; j++)
                cf[j] = malloc(sizeof(chestCards));

        cf[1]->fp = chest1;

        cf[2]->fp = chest2;

        cf[3]->fp = chest3;

        cf[4]->fp = chest4;

        cf[5]->fp = chest5;

        cf[6]->fp = chest6;

        cf[7]->fp = chest7;

        cf[8]->fp = chest8;

        cf[9]->fp = chest9;

        cf[10]->fp = chest10;

        cf[11]->fp = chest11;

        cf[12]->fp = chest12;

        cf[13]->fp = chest13;

        cf[14]->fp = chest14;

        cf[15]->fp = chest15;

        cf[0]->fp = chest0;
        return;
}
