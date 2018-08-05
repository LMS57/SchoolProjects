        //                              Documentation goes here:
        //              What we have here is a monopoly game, I bet I know what you are
        //              thinking, "But Logan why does it take you over 2000 line of code
        //              to make a simple monopoly game?" Short answer is, this is not a
        //              simple monopoly game. This is life or death win or lose mankind
        //              vs the machine. My only hope is that the user does not look
        //              through everything and find tiny holes by which mistakes
        //              can occur. Take this as a whole and prepare yourself for an
        //              adventure of the senses.

        //              Just don't prepare yourself too much as this only involves 2
        //              2 senses max.
        //                                                      By Logan Stratton

        //      1. Pass by Reference
        //      2. Structures
        //      3. Custom Header files
        //      4. Strings
        //      5. 2-dimensional array
        //      6. linked lists
        //      7. Also there is a hidden recursion function, if you can find it you win, otherwise if you give up you can just search for it by using the word resursive




        // to play the game correctly read everything and press 1 most of the time
        // to skip into "The Future" pres "1 1 1 1 " a bunch of times; helped me test the program out
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "rules.h"
#include "prototypes.h"
#include "properties.h"
#include "bonusCards.h"

void printHouses(int i, int j)//prints who owns the property or how many houses are present
{
        int q = 0,w = 0,e = 0;
        for(q = 0; q < 22; q++)
        {
                if(props[q].loci == i && props[q].locj == j){
                        break;
                }
                else if(q == 21)
                        q++;

        }

        if(q > 21){
                for(w = 0; w < 2; w++)
                {
                        if(utilities[w].loci == i && utilities[w].locj ==j)
                                break;
                        else if(w == 1)
                                w++;
                }
        }
        if(w > 1){
                for(e = 0; e < 4; e++)
                {
                        if(railroad[e].loci == i && railroad[e].locj == j)
                                break;
                        else if(e == 3)
                                return;
                }
        }
        if(j == 11)
                j++;
        if(i == 11)
                i++;
        if(i == 1)
                i--;
        if(j == 1)
                j--;
        if(i == 6 || j == 6)
        {
                if(railroad[e].whoOwns == 'c' && railroad[e].mortgage == 1 || railroad[e].whoOwns == 'p' && railroad[e].mortgage == 1)
                        printf(Red);
                board[i][j] = railroad[e].whoOwns;
        }
        else if((i == 9 && j == 0) || (i == 0 && j == 9))
        {
                if(utilities[w].whoOwns == 'c' && utilities[w].mortgage == 1 || utilities[w].whoOwns == 'p' && utilities[w].mortgage == 1)
                                printf(Red);
                board[i][j] = utilities[w].whoOwns;
        }

        else if(((i == 0 && (j == 0 || j == 1 || j == 11 || j == 12)) || (i == 1 && (j == 0 && j == 12) || (i == 12 && ( j == 0 || j == 1|| j == 11 || j == 12) || j == 4 || j == 7 || j == 9)) || ( i == 11 && (j == 11)) || (j == 0 && i == 3) || (j == 12 && (i == 7 || i == 9)) && (i !=0 && j != 4)) && (i != 0 && j != 8) ) printf("1");

        else
        {

                if(props[q].numHouses == 1)
                        board[i][j] = '1';
                else if(props[q].numHouses == 2)
                        board[i][j] = '2';
                else if(props[q].numHouses == 3)
                        board[i][j] = '3';
                else if(props[q].numHouses == 4)
                        board[i][j] = '4';
                else if(props[q].numHouses == 5)
                        board[i][j] = 'H';
                else
                        board[i][j] =  props[q].whoOwns;

                if(props[q].whoOwns == 'c' && props[q].mortgage == 1 || props[q].whoOwns == 'p' && props[q].mortgage == 1)
                        printf(Red);
        }
        return;
}
int checkMortgageOwner(player *tmp)//checks the propoperty for who owns returns 1 for player1 0 for computer
{
        int t;
        if(tmp->i == 9 || tmp->j == 9)
        {
                if(tmp->i == 9)
                {
                        if(utilities[0].whoOwns == 'p')
                                return 1;
                        else if(utilities[0].whoOwns == 'c')
                                return 0;
                }
                else
                {
                        if(utilities[1].whoOwns == 'c')
                                return 0;
                        else if(utilities[1].whoOwns == 'p')
                                return 1;
                }

        }
        else if(tmp->i == 6 || tmp->j == 6)
        {
                if(tmp->i == 11)
                {
                        if(railroad[0].whoOwns == 'c')
                                return 0;
                        else if(railroad[0].whoOwns == 'p')
                                return 1;
                }
                else if(tmp->j == 1)
                {
                        if(railroad[1].whoOwns == 'c')
                                return 0;
                        else if(railroad[1].whoOwns == 'p')
                                return 1;
                }
                else if(tmp->i == 1)
                {
                        if(railroad[2].whoOwns == 'c')
                                return 0;
                        else if(railroad[2].whoOwns == 'p')
                                return 1;
                }
                else
                {
                        if(railroad[3].whoOwns == 'c')
                                return 0;
                        else if(railroad[3].whoOwns == 'p')
                                return 1;
                }
        }
        for(t = 0; t <22;t++)
        {
                if(props[t].loci == tmp->i && props[t].locj == tmp->j)
                        break;
                else if(t == 21)
                {       printf("Error in checkMortgageOwnership; 1");
                        exit(1);
                }
        }
                if(props[t].whoOwns  == 'c')
                        return 0;
                else if(props[t].whoOwns == 'p')
                        return 1;
}
void buyBack(player *tmp)//function to allow players to buy back mortgaged properties
{
        int p,t,trust = 0;
        while(1){
                if(l != counter % 2 && comp.money < 750)
                        break;
                if(l == counter % 2)
                {
                        printMortgagedProperties(tmp);
                        printf("What property would you like to buy back (-1 to print mortgaged properties or -2 to leave)\n");
                        scanf("%d", &p);
                        if(p == -1)
                                printMortgagedProperties(tmp);
                        else if(p == -2)
                                break;

                        else if(p > 21 && p < 24)
                        {
                                if(utilities[p-22].whoOwns != 'p'){
                                        printf("Sorry you do not own this propertyd!\n");
                                        break;
                                }
                                if(player1.money < 83){
                                        printf("You are too poor to buy this back");
                                        break;
                                }
                                utilities[p-22].mortgage = 0;
                                player1.money -= 83;
                                pholdings++;
                                pU++;
                                printf("You have bought %s back\n", utilities[p-22].name);
                        }
                        else if(p > 23 && p < 28)
                        {
                                if(railroad[p-24].whoOwns != 'p'){
                                        printf("Sorry you do not own this propertyd!\n");
                                        break;
                                }
                                if(player1.money < 110){
                                        printf("You are too poor to buy this back");
                                        break;
                                }
                                railroad[p-24].mortgage = 0;
                                player1.money -= 110;
                                pholdings++;
                                printf("You have bought %s back\n", railroad[p-24].name);
                                  pRR++;
                         }
                        else if(p > -1 && p < 22)
                         {
                                if(props[p].whoOwns != 'p'){
                                        printf("Sorry you do not own this propertyd!\n");
                                        break;
                                }
                                if(player1.money < props[p].sell + props[p].sell * .1){
                                        printf("You are too poor to buy this back");
                                        break;
                                }
                                props[p].mortgage = 0;
                                player1.money -= props[p].sell + props[p].sell * .1;
                                pholdings++;
                                printf("You have bought %s back\n", props[p].name);
                        }
                        else
                                printf("Try Again\n");

                }
                else
                {
                        while(1){
                                for(t = 0; t < 22; t++)
                                {
                                        if(props[t].whoOwns == 'c' && props[t].mortgage == 1)
                                                break;
                                        else if(t == 21)
                                                t = 24;
                                }
                                if(t == 25)
                                        for(t = 0; t < 2; t++)
                                        {
                                                if(utilities[t].whoOwns == 'c' && utilities[t].mortgage == 1)
                                                {
                                                        t += 21;
                                                        break;
                                                }
                                                else if(t == 1)
                                                        t = 49;
                                        }
                                if( t == 50)
                                        for(t = 0; t < 4; t++)
                                        {
                                                if(railroad[t].whoOwns == 'c' && railroad[t].mortgage == 1)
                                                {       t += 24;
                                                        break;
                                                }
                                                else if (t == 3)
                                                        return;
                                        }
                        }
                        if(t > 21 && t < 23)
                        {
                                comp.money += utilities[t-21].sell + utilities[t-21].sell * .1;
                                utilities[t-21].mortgage = 0;
                                choldings++;
                                cU++;
                        }
                        else if(p > 23 && p < 28)
                        {
                                comp.money -= railroad[t-24].sell + railroad[t-24].sell * .1;
                                railroad[t-24].mortgage = 1;
                                choldings++;
                                cRR++;
                        }
                        else{
                                comp.money -= props[t].sell + props[t].sell * .1;
                                props[t].mortgage = 1;
                                choldings++;
                        }
                        break;

                }
        }
        return;
}
void specialProperty(int b)//allows purchase of railroad or utilities
{
        int q;
        if(b == 1 && l == counter % 2)
        {
                for(q = 0; q < 4; q++)
                {
                        if(player1.i == railroad[q].loci && player1.j == railroad[q].locj)
                                break;
                        else if(q == 3)
                        {
                                printf("Error in special Property; 1");
                                exit(1);
                        }
                }
                        printRR(q);
                        printf("Would you like to purchase this plot for $200? (1 = yes, Anything else = no)\n");
                        scanf("%d", &b);
                        if(b == 1 && player1.money > 200)
                        {
                                player1.money -= 200;
                                railroad[q].whoOwns = 'p';
                                pRR++;
                                pholdings++;
                                printf("You have just purchased %s\n", railroad[q].name);
                        }
                        else if (player1.money < 200)

                                printf("You are too poor for this establishment");

        }
        else if(b == 2 && l == counter % 2)
        {
                for(q = 0; q < 2; q++)
                {
                        if(player1.i == utilities[q].loci && player1.j == utilities[q].locj)
                                break;
                        else if(q == 1)
                        {
                                printf("Error in special Property; 2");
                                exit(1);
                        }
                }
                        printU(q);
                        printf("Would you like to purchase this plot for $150? (1 = yes, Anything else = no)\n");
                        scanf("%d", &b);
                        if(b == 1 && player1.money > 150)
                        {
                                printf("You have just purchased %s\n", utilities[q].name);
                                player1.money -= 150;
                                utilities[q].whoOwns = 'p';
                                pU++;
                                pholdings++;
                        }
                        else if(player1.money < 150)
                                printf("You are too poor to buy this");
        }
        else if(b == 1)
        {
                for(q = 0; q < 4; q++)
                {
                        if(comp.i == railroad[q].loci && comp.j == railroad[q].locj)
                                break;
                        else if(q == 3)
                        {
                                printf("Error in special Property; 3");
                                exit(1);
                        }
                }
                        printRR(q);
                        sleep(1);
                        b = rand() % 2;
                        if(b == 1 && comp.money > 200)
                        {
                                printf("The computer has just purchased %s\n", railroad[q].name);
                                comp.money -= 200;
                                railroad[q].whoOwns = 'c';
                                choldings++;
                                cRR++;
                                sleep(1);
                        }
                        else
                                printf("The computer has passed on this land");




        }
        else{
                for(q = 0; q < 2; q++)
                {
                        if(comp.i == utilities[q].loci && comp.j == utilities[q].locj)
                                break;
                        else if(q == 1)
                        {
                                printf("Error in special Property; 4");
                                exit(1);
                        }
                }
                        printU(q);
                        b = rand() % 2;
                        sleep(1);
                        if(b == 1 && comp.money > 150)
                        {
                                printf("The computer has just purchased %s\n", utilities[q].name);
                                comp.money -= 150;
                                utilities[q].whoOwns = 'c';
                                cU++;
                                pholdings++;
                                sleep(1);
                        }
                        else
                                printf("The computer has passed on this land");
        }

                //reads in 1 for railroad, 2 for utilities asks for purchase and pritns

        return;
}
void payOwnerUtilities(player *tmp)//function to figure out payment for landing on a utility
{
        int owner = checkOwnership(tmp), num;
        if(l == counter % 2 && !owner)
        {

                if(cU == 1)
                {
                        printf("Roll the dice and pay 4 times the amount shown\n");
                        num = rollDice();
                        player1.money -= num *4;
                        comp.money += num * 4;
                }
                else if(cU == 2)
                {
                        printf("Roll the dice and pay 10 time the amount shown\n");
                        num = rollDice();
                        player1.money -= num * 10;
                        comp.money += num * 10;
                }
                if(player1.money < 0)
                        sell(&player1);
        }
        else if(l == counter % 2 && owner == 2)
        {
                int b;
                if(player1.money > 150){
                        printf("Would you like to look at this property? (1 = yes, Anything Else = No");
                        scanf("%d", &b);
                        if(b == 1 )
                                specialProperty(2);
                }
                else
                        printf("Too poor to buy\n\n");
        }
        else if(owner == 1)
        {
                if(pU == 1)
                {
                        printf("Roll the dice and pay 4 time the amount shown\n");
                        num = rollDice();
                        player1.money += num * 4;
                        comp.money -= num *4;
                }
                else if(pU == 2)
                {
                        printf("Roll the dice and pay 4 time the amount shown\n");
                        num = rollDice();
                        player1.money += num * 10;
                        comp.money -= num * 10;
                }
                if(comp.money < 0)
                        sell(&comp);
        }
        else if(owner == 2)
        {
                int b = rand()%2;
                if(comp.money > 200){
                        if(b == 1 )
                                specialProperty(2);
                }
                else
                        printf("Too poor to buy\n\n");
        }


        return;
}
void payOwnerRailroad(player *tmp)//function to allow payment for landing on a railroad
{
        int owner = checkOwnership(tmp);
        if(l == counter % 2 && !owner)
        {
                if(cRR == 1)
                {
                        printf("You landed on the computer's land you owe them $25\n");
                        player1.money -= 25;
                        comp.money += 25;
                }
                else if(cRR == 2)
                {
                        printf("You landed on the computer's land you owe them $50\n");
                        player1.money -= 50;
                        comp.money += 50;
                }
                else if(cRR == 3)
                {
                        printf("You landed on the computer's land you owe them $100\n");
                        player1.money -= 100;
                        comp.money += 100;
                }
                else
                {
                        printf("You landed on the computer's land you owe them $200\n");
                        player1.money -= 200;
                        comp.money += 200;
                }
                if(player1.money < 0)
                        sell(&player1);
        }
        else if(l == counter % 2 && owner == 2)
        {
                int b;
                if(player1.money > 200){
                        printf("Would you like to look at this property? (1 = yes, Anything Else = No");
                        scanf("%d", &b);
                        if(b == 1 )
                                specialProperty(1);
                }
                else
                        printf("Too poor to buy\n\n");
        }
        else if(owner == 1)
        {
                if(pRR == 1)
                {
                        printf("The computer landed on your land they owe you $25\n");
                        player1.money += 25;
                        comp.money -= 25;
                }
                else if(pRR == 2)
                {
                        printf("The computer landed on your land they owe you $50\n");
                        player1.money += 50;
                        comp.money -= 50;
                }
                else if(pRR == 3)
                {
                        printf("The computer landed on your land they owe you $100\n");
                        player1.money += 100;
                        comp.money -= 100;
                }
                else
                {
                        printf("The computer landed on your land they owe you $200\n");
                        player1.money += 200;
                        comp.money -= 200;
                }
                if(comp.money < 0)
                        sell(&comp);
        }
        else if(owner == 2)
        {
                int b = rand()%2;
                if(comp.money > 200){
                        if(b == 1 )
                                specialProperty(1);
                }
                else
                        printf("Too poor to buy\n\n");
        }




        return;
}
int allThreeProps(int scan){//checks to see if all three properties are owned to allow for purchase of housing
        if(scan == 0 || scan == 1)
                if(props[0].whoOwns == 'p' && props[1].whoOwns == 'p')
                        return 1;
        else if(scan > 1 && scan < 19)
                        if((scan - 2)%3 == 2)
                                scan -= 2;
                        else if((scan -2)%3 == 1)
                                scan -= 1;
                        if(props[scan].whoOwns == 'p' && props[scan+1].whoOwns == 'p' && props[scan+2].whoOwns == 'p')
                                return 1;
        else
                if(props[20].whoOwns == 'p' && props[21].whoOwns == 'p')
                        return 1;
                else
                        return 0;

        //retrun 1 if all are owned


}
int computerBuyHouse(){//function to allow the computer to buy a house
        if(props[0].whoOwns == 'c' && props[1].whoOwns == 'c' && props[0].numHouses != 5 && props[1].numHouses != 5)
                return 0;
        for(int t = 2; t <= 18; t += 3)
        {
                if(props[t].whoOwns == 'c' && props[t+1].whoOwns == 'c' && props[t+2].whoOwns == 'c' && props[t].numHouses != 5 && props[t+1].numHouses != 5 && props[t+2].numHouses != 5 )
                        return t;
        }
        if(props[20].whoOwns == 'c' && props[21].whoOwns == 'c' && props[20].numHouses !=5 && props[21].numHouses != 5)
                return 20;
        else
                return 1;

        //returns the starting property from the list of three that the computer owns

}
void buyHouse(player *tmp){//function to set up output to purchase a house
        if(l == counter % 2){
                int scan, numhouses;
                while(1)
                {
                        while(1)
                        {
                                printf("Where would you like to build a house? (-1 to print Property, otherwise property num, or -2 to quit)\n");
                                scanf("%d", &scan);
                                        if(scan == -1)
                                                printPropertiesOwned(tmp);
                                        else if(scan == -2)
                                                return;
                                        else if(props[scan].whoOwns != 'p'){
                                                printf("Sorry you do not own that land, try again\n");

                                        }
                                        else if(!allThreeProps(scan)){
                                                printf("You do not own all the properties, Try again\n");
                                        }
                                        else if(scan < 22 && scan > -1)
                                                break;
                        }
                        while(1){
                                printf("%s is a lovely place to build a house. There are currently %d house(s) there already and it costs $%d to build each house. How many houses would you like to build? (0 to leave)\n", props[scan].name, props[scan].numHouses, props[scan].priceperhouse);
                                scanf("%d", &numhouses);
                                if(numhouses > 5|| numhouses < 0 || numhouses + props[scan].numHouses > 5)
                                        printf("Sorry that input does not work either because it is too many, too few, or there are already houses there.\n");
                                else if(numhouses == 0)
                                        break;
                                else if(player1.money < numhouses*props[scan].priceperhouse){
                                        printf("You do not have that much money. Try Again\n\n");
                                }
                                else
                                {
                                        player1.money -= numhouses*props[scan].priceperhouse;
                                        props[scan].numHouses += numhouses;
                                        if(props[scan].numHouses > 1)
                                        {
                                                props[scan].oneHouse = 1;
                                                if(props[scan].numHouses > 2)
                                                {
                                                        props[scan].twoHouse = 1;
                                                        if(props[scan].numHouses > 3)
                                                        {
                                                                props[scan].threeHouse = 1;
                                                                if(props[scan].numHouses > 4)
                                                                {
                                                                        props[scan].fourHouse = 1;
                                                                        if(props[scan].numHouses > 5)
                                                                        {
                                                                                props[scan].hotel = 1;
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                        printf("Would you like to buy more houses (1 = yes, anything else = no)\n");
                        scanf("%d", &scan);
                        if(scan != 1)
                                break;
                }
        }
        else{
                int property = computerBuyHouse();
                if(property == 1)
                        return;
                else if(props[property].rent == 2 || props[property].rent == 350 ){
                        comp.money -= 2*props[property].priceperhouse;
                        for(int q = 0; q < 2; q++)
                        {
                                props[property].numHouses++;
                                if(props[property].numHouses > 1)
                                {
                                        props[property].oneHouse = 1;
                                        if(props[property].numHouses > 2)
                                        {
                                                props[property].twoHouse = 1;
                                                if(props[property].numHouses > 3)
                                                {
                                                        props[property].threeHouse = 1;
                                                        if(props[property].numHouses > 4)
                                                        {
                                                                props[property].fourHouse = 1;
                                                                if(props[property].numHouses > 5)
                                                                {
                                                                        props[property].hotel = 1;
                                                                }
                                                        }
                                                }
                                        }
                                }
                                property++;
                        }
                }
                else
                {
                        comp.money -= 3*props[property].priceperhouse;
                        for(int q = 0; q < 3; q++)
                        {
                                props[property].numHouses++;
                                if(props[property].numHouses > 1)
                                {
                                        props[property].oneHouse = 1;
                                        if(props[property].numHouses > 2)
                                        {
                                                props[property].twoHouse = 1;
                                                if(props[property].numHouses > 3)
                                                {
                                                        props[property].threeHouse = 1;
                                                        if(props[property].numHouses > 4)
                                                        {
                                                                props[property].fourHouse = 1;
                                                                if(props[property].numHouses > 5)
                                                                {
                                                                        props[property].hotel = 1;
                                                                }
                                                        }
                                                }
                                        }
                                }
                                property++;
                        }
                }
        }
        return;
}

void payOwner(player *tmp)//function to pay the owner
{
        int t, numHouses;
        for(t = 0; t < 22; t++)
        {
                 if(tmp->i == props[t].loci && props[t].locj == tmp->j)
                        break;
                else if(t ==21){
                        printf("An error has occured in payOwner; 0");
                        exit(1);
                }
        }

        if(l == counter % 2)
        {
                switch(props[t].numHouses){
                        case 0:
                                printf("You landed on the computer's land you owe them $%d.\n\n", props[t].rent);
                                player1.money -= props[t].rent;
                                comp.money += props[t].rent;
                                break;
                        case 1:
                                printf("You landed on the computer's land you owe them $%d.\n\n", props[t].oneHouse);
                                player1.money -= props[t].oneHouse;
                                comp.money += props[t].oneHouse;
                                break;
                        case 2:
                                printf("You landed on the computer's land you owe them $%d.\n\n", props[t].twoHouse);
                                player1.money -= props[t].twoHouse;
                                comp.money += props[t].twoHouse;
                                break;
                        case 3:
                                printf("You landed on the computer's land you owe them $%d.\n\n", props[t].threeHouse);
                                player1.money -= props[t].threeHouse;
                                comp.money += props[t].threeHouse;
                                break;
                        case 4:
                                printf("You landed on the computer's land you owe them $%d.\n\n", props[t].fourHouse);
                                player1.money -= props[t].fourHouse;
                                comp.money += props[t].fourHouse;
                                break;
                        case 5:
                                printf("You landed on the computer's land you owe them $%d.\n\n", props[t].hotel);
                                player1.money -= props[t].hotel;
                                comp.money += props[t].hotel;
                                break;
                        default:
                                printf("An error has occured in the payOwner; 1\n");
                                exit(1);
                }
                if(player1.money < 0)
                        sell(&player1);

        }
        else{
                switch(props[t].numHouses){
                        case 0:
                                sleep(1);
                                printf("The computer landed on your land they owe you $%d.\n\n", props[t].rent);
                                player1.money += props[t].rent;
                                comp.money -= props[t].rent;
                                break;
                        case 1:
                                sleep(1);
                                printf("The computer landed on your land they owe you $%d.\n\n", props[t].oneHouse);
                                player1.money += props[t].oneHouse;
                                comp.money -= props[t].oneHouse;
                                break;
                        case 2:
                                sleep(1);
                                printf("The computer landed on your land they owe you $%d.\n\n", props[t].twoHouse);
                                player1.money += props[t].twoHouse;
                                comp.money -= props[t].twoHouse;
                                break;
                        case 3:
                                sleep(1);
                                printf("The computer landed on your land they owe you $%d.\n\n", props[t].threeHouse);
                                player1.money += props[t].threeHouse;
                                comp.money -= props[t].threeHouse;
                                break;
                        case 4:
                                sleep(1);
                                printf("The computer landed on your land they owe you $%d.\n\n", props[t].fourHouse);
                                player1.money += props[t].fourHouse;
                                comp.money -= props[t].fourHouse;
                                break;
                        case 5:
                                sleep(1);
                                printf("The computer landed on your land they owe you $%d.\n\n", props[t].hotel);
                                player1.money += props[t].hotel;
                                comp.money -= props[t].hotel;
                                break;
                        default:
                                printf("An error has occured in the payOwner; 2\n");
                                exit(1);
                }
                if(comp.money < 0)
                        sell(&comp);
        }

        return;
}

void possiblePurchase(player *tmp)//function to add final step before buying a property
{
        int t,scan;
        for(t = 0; t < 22; t++)
        {
                 if(tmp->i == props[t].loci && props[t].locj == tmp->j)
                        break;
                else if(t ==21)
                        exit(1);
        }

        if(l == counter % 2)
        {
                printProperties(t);
                if(tmp->money < props[t].price)
                {       printf("You are too poor to purchase this property\n");
                        return;
                }
                printf("Your current balance is $%d, Would you like to buy this property for $%d? (1 = yes, Anything Else = no)\n",tmp->money, props[t].price);
                scanf("%d", &scan);
                if(scan == 1)
                {

                        tmp->money -= props[t].price;
                        props[t].whoOwns = 'p';
                        pholdings++;
                        props[t].mortgage = 0;
                }
        }
        else{
                if(props[t].whoOwns == ' ' || props[t].mortgage == 1)
                {
                        comp.money -= props[t].price;
                        choldings++;
                        props[t].whoOwns = 'c';
                        props[t].mortgage = 0;
                        printf("The computer has just bought %s\n", props[t].name);
                }
        }
        return;
}


int checkOwnership(player* tmp){//checks who owns the property or if it mortgaged
        int t;
        if(tmp->i == 9 || tmp->j == 9)
        {
                if(tmp->i == 9)
                {
                        if(utilities[0].mortgage == 1)
                                return 3;
                        if(utilities[0].whoOwns == 'p')
                                return 1;
                        else if(utilities[0].whoOwns == 'c')
                                return 0;

                        else
                                return 2;
                }
                else
                {
                        if(utilities[1].mortgage == 1)
                                return 3;
                        if(utilities[1].whoOwns == 'c')
                                return 0;
                        else if(utilities[1].whoOwns == 'p')
                                return 1;
                        else
                                return 2;
                }

        }
        else if(tmp->i == 6 || tmp->j == 6)
        {
                if(tmp->i == 11)
                {
                        if(railroad[0].mortgage == 1)
                                return 3;
                        if(railroad[0].whoOwns == 'c')
                                return 0;
                        else if(railroad[0].whoOwns == 'p')
                                return 1;
                        else
                                return 2;
                }
                else if(tmp->j == 1)
                {
                        if(railroad[1].mortgage == 1)
                                return 3;
                        if(railroad[1].whoOwns == 'c')
                                return 0;
                        else if(railroad[1].whoOwns == 'p')
                                return 1;
                        else
                                return 2;
                }
                else if(tmp->i == 1)
                {
                        if(railroad[2].mortgage == 1)
                                return 3;
                        if(railroad[2].whoOwns == 'c')
                                return 0;
                        else if(railroad[2].whoOwns == 'p')
                                return 1;
                        else
                                return 2;
                }
                else
                {
                        if(railroad[3].mortgage == 1)
                                return 3;
                        if(railroad[3].whoOwns == 'c')
                                return 0;
                        else if(railroad[3].whoOwns == 'p')
                                return 1;
                        else
                                return 2;

                }
        }
        for(t = 0; t <22;t++)
        {
                if(props[t].loci == tmp->i && props[t].locj == tmp->j)//Code may not work future me
                        break;
                else if(t == 21)
                {       printf("Error in checkOwnership; 1");
                        exit(1);
                }
        }
                if(props[t].mortgage == 1)
                        return 3;

                if(props[t].whoOwns  == 'c')
                        return 0;
                else if(props[t].whoOwns == 'p')
                        return 1;
                else
                        return 2;

}
void bankrupt(player *tmp)//checks to see if the player is bankrupt
{       gameOver = 1;
        for(int t = 0; t < 50; t++)
                printf("\n");
        sleep(2);
        printf("\n\nThe game is finally over\n");
        sleep(2);
        if(strcmp(tmp->name,player1.name) == 0)
                printf("\n\nThe computer has bested %s\n\n",player1.name);
        else
                printf("\n\nHumans have bested the machine, Good on to you %s", player1.name);
        sleep(2);
        printf("\n\nThank you for playing, your game took %d Turns\n\n", counter/2);
        exit(1);
        return;
}
void sell(player *tmp)//function to allow selling properties
{
        int p = 0,trust = 0;
        while(1)
        {
                if(l != counter % 2 && comp.money > 500)
                {
                        buyBack(tmp);
                        return;
                }
                else if(l != counter % 2 && comp.money < 0)
                        break;
                if(tmp->money<0)
                        break;
                printf("Would you like to sell property (1) or buy property back(2) or leave(3)\n");
                scanf("%d", &p);

                if(p == 2)
                        buyBack(tmp);
                else if(p == 1)
                        break;
                else if(p == 3)
                        return;
                else
                        printf("Try Again\n");
        }
        printPropertiesOwned(tmp);
        while(1){
                if(pholdings == 0 && player1.money < 0){
                        bankrupt(&player1);
                        exit(0);
                }
                printf("Current money = $%d, What property would you like to mortgage (-1 to list properties owned, -2 to go leave)\n", tmp->money);
                if(strcmp(tmp->name, player1.name) != 0)
                        p = rand() % 28;
                else
                        scanf("%d", &p);
                if(p == -1)
                        printPropertiesOwned(tmp);
                else if(p == -2 && tmp->money > 0)
                        break;
                else if(p > 28 || p < 0)
                        printf("Sorry that property is not real, Try Again\n");
                else if(l == counter % 2 &&( p == 22 || p == 23) && utilities[p-22].whoOwns == 'p' && utilities[p-22].mortgage == 0)
                {
                        player1.money += utilities[p-22].sell;
                        utilities[p-22].mortgage = 1;
                        pholdings--;
                        pU--;
                        printf("You have recieved $%d, your new balance is $%d and %s has been mortgaged\n",utilities[p-22].sell, player1.money, utilities[p-22].name);
                        if(pholdings == 0 && player1.money < 0)
                                bankrupt(&player1);
                        if(gameOver)
                                exit(0);
                        printf("Would you like to sell another property? (1 = Yes, 0 = No);\n");
                        scanf("%d", &p);
                        if(p == 0 && tmp->money > 0)
                                break;

                }
                else if(l == counter % 2 && p > 23 && p < 28 && railroad[p-24].whoOwns == 'p' && railroad[p-24].mortgage == 0)
                {
                        player1.money += railroad[p-24].sell;
                        railroad[p-24].mortgage = 1;
                        pholdings--;
                        pRR--;
                        printf("You have recieved $%d, your new balance is $%d and %s has been mortgaged\n",railroad[p-24].sell, player1.money, railroad[p-24].name);
                        if(pholdings == 0 && player1.money < 0)
                                bankrupt(&player1);
                        if(gameOver)
                                exit(0);
                        printf("Would you like to sell another property? (1 = Yes, 0 = No);\n");
                        scanf("%d", &p);
                        if(p == 0 && tmp->money > 0)
                                break;

                }

                else if(strcmp(tmp->name, player1.name) == 0 && props[p].whoOwns == 'p' && props[p].mortgage == 0){
                        player1.money += props[p].sell;
                        props[p].mortgage = 1;
                        pholdings--;
                        printf("You have recieved $%d, your new balance is $%d and %s has been mortgaged\n",props[p].sell, player1.money, props[p].name);
                        if(pholdings == 0 && player1.money < 0)
                                bankrupt(&player1);
                        if(gameOver)
                                exit(1);
                        printf("Would you like to sell another property? (1 = Yes, 0 = No);\n");
                        scanf("%d", &p);
                        if(p == 0 && tmp->money > 0)
                                break;
                }
                else if(strcmp(tmp->name, player1.name) == 0 && (props[p].whoOwns != 'p' || props[p].mortgage == 1 || utilities[p-22].whoOwns != 'p' || utilities[p-22].mortgage == 1 || railroad[p-24].whoOwns != 'p' || railroad[p-24].mortgage == 1))
                {
                        printf("Sorry you do not own this property or it is mortaged!\n");
                }
                else{
                        while(1)
                                if(p > 21 && p < 24 && utilities[p-22].whoOwns == 'c' && utilities[p-22].mortgage == 0)
                                        break;
                                else if(p > 23 && p < 28 && railroad[p-24].whoOwns == 'c' && railroad[p-24].mortgage == 0)
                                        break;
                                else if(p > -1 && p < 22 && props[p].whoOwns == 'c' && props[p].mortgage == 0)
                                        break;
                                else{
                                        p = rand() % 28;
                                        trust++;
                                        if(trust > 35){
                                                if(choldings < 1 && comp.money < 0){
                                                        bankrupt(&comp);
                                                        if(gameOver)
                                                                return;}
                                        }}
                        if(p > 21 && p < 23)
                        {
                                printf("%s has been mortgaged\n", utilities[p-21].name);
                                comp.money += utilities[p-21].sell;
                                utilities[p-21].mortgage = 1;
                                choldings--;
                                cU--;
                                if(comp.money >= 0)
                                        break;
                                else if(comp.money < 0 && choldings == 0){
                                        bankrupt(tmp);
                                        if(gameOver)
                                                return;
                                        }
                        }
                        else if(p > 23 && p < 28)
                        {
                                printf("%s has been mortgaged\n", railroad[p-24].name);
                                comp.money += railroad[p-24].sell;
                                railroad[p-24].mortgage = 1;
                                choldings--;
                                cRR--;
                                if(comp.money >= 0)
                                        break;
                                else if(comp.money < 0 && choldings == 0){
                                        bankrupt(tmp);
                                                if(gameOver)
                                                        return;
                                }
                        }
                        else{
                                printf("%s has been mortgaged\n", props[p].name);
                                comp.money += props[p].sell;
                                props[p].mortgage = 1;
                                choldings--;
                                if(comp.money >= 0)
                                        break;
                                else if(comp.money < 0 && choldings == 0){
                                        bankrupt(tmp);
                                        if(gameOver)
                                                return;
                                }
                        }
                }
        }
        return;
}
void broke(player *tmp)//checks to see if a player is broke
{
        while(tmp->money < 0)
        {       sell(tmp);
                if(gameOver)
                        break;
        }
        return;

}
void chance(player *tmp)//checks and grabs the chance card
{
        int random = rand() % 16;
        chanceCards *temp = head;
        while(1)
        if(chanceGetOutOfJail == 0 || random != 5)
        {       for(int b = 0; b < random;b++)
                {
                        temp = temp->next;
                }
                temp->fp(tmp);
                break;
        }
        else
                random = rand()%16;
        return;
}
void communityChest(player *tmp)//checks and grabs the chest card
{
        int random = rand() % 16;
        while(1)
        if(chestGetOutOfJail == 0 || random != 15)
        {       cf[random]->fp(tmp);
                break;
        }
        else
                random = rand() % 16;
        return;
}
void luxaryTax(player *tmp)//payment for landing on luxary tax
{
        printf("You have to pay $100 for luxary tax!\n");
        tmp->money -= 100;
        fp += 100;
        broke(tmp);

        return;
}
void incomeTax(player *tmp)//payment for landing on incometax
{
        printf("You have to pay $200 for income tax!\n");
        tmp->money -= 200;
        fp += 200;
        broke(tmp);

        return;
}
void passGo(player *tmp)//function for passing go
{
        printf("You passed go collect $200!\n");
        tmp->money += 200;
        return;
}

void freeParking(player *tmp)//function for free parking
{
        printf("You landed on free parking you get $%d!!\n", fp);
        tmp->money += fp;
        fp = 100;
        return;
}


void sum(){//rolls dice and checks for doubes, enacts movement as well
        int sums = rollDice();
        test = counter;
        for(int i = 0; i < 1; i++)
                if(sums > 100)
                {
                        sums -= 100;
                        if(l == counter % 2)
                                move(&player1, sums);
                        else
                                move(&comp, sums);
                        if(++doubles == 3)
                                break;
                        counter--;
                        printf("Doubles Roll Again\n");
                }
                else
                        if(l == counter % 2)
                                move(&player1, sums);
                        else
                                move(&comp, sums);
        if(doubles > 2 && l != counter % 2){
                cjail = gotoJail(&comp);
                counter++;
        }
        else if(doubles > 2 && l == counter % 2){
                printf("check");
                pjail = gotoJail(&player1);
                counter++;
        }
        else{
                sleep(1);
                counter++;

        }

        return;
}
int gotoJail(player *tmp)//send a player to jail if called
{
        doubles = 0;
        tmp->i = 11;
        tmp->j = 1;
        tmp->jail = 1;
        printf("You are sent to jail\n");
        return 1;
}
void checkLoc(player *tmp)//checks the player's location
{
        if(tmp->i == 1 && tmp->j == 11)
                gotoJail(tmp);
        else if(tmp->i == 11 && tmp->j == 11);

        else if(tmp->i == 1 && tmp->j == 1)
                freeParking(tmp);
        else if(tmp->i == 11 && tmp->j == 7)
                incomeTax(tmp);
        else if(tmp->i == 9 && tmp->j == 11)
                luxaryTax(tmp);
        else if((tmp->i == 11 && tmp->j == 4) || (tmp->i == 1 && tmp->j == 3) || (tmp->i == 7 && tmp->j == 11))
        {
                printf("You landed on Chance pick up a card and read it\n");
                sleep(1);
                chance(tmp);
        }
        else if((tmp->i == 11 && tmp->j == 9) || (tmp->i == 3 && tmp->j == 1) || (tmp->i == 4 && tmp->j == 11))
        {
                printf("You landed on Community Chest pick up a card and read it\n");
                sleep(1);
                communityChest(tmp);
        }
        else if(tmp->i == 11 && tmp->j == 1)
                printf("Just visting\n");
        else if((tmp->i == 11 && tmp->j == 6 ||tmp->i == 6 && tmp->j == 1 || tmp->i == 1 && tmp->j == 6 || tmp->i == 6 && tmp->j == 11) && l == counter % 2){
                int owner = checkOwnership(tmp);
                if (owner==0)
                        payOwnerRailroad(tmp);
                else if(owner == 2){
                        printf("Would you like to look at this location? (1 = Yes, Anythin Else = No)\n");
                        scanf("%d", &owner);
                        if(owner == 1)
                                specialProperty(1);
                }
                else if(owner == 3)
                {
                        owner = checkMortgageOwner(tmp);
                        if(owner == 0)
                        {       printf("Would you like to look at this location? (1 = Yes, Anythin Else = No)\n");
                                scanf("%d", &owner);
                                if(owner == 1)
                                        specialProperty(1);
                        }
                }
        }
        else if(tmp->i == 11 && tmp->j == 6 ||tmp->i == 6 && tmp->j == 1 || tmp->i == 1 && tmp->j == 6 || tmp->i == 6 && tmp->j == 11){
                int owner = checkOwnership(tmp);
                if (owner == 1)
                        payOwnerRailroad(tmp);
                else if(owner == 2)
                        if(rand() % 2 )
                                specialProperty(1);
                else if(owner == 3)
                {
                        owner = checkMortgageOwner(tmp);
                        if(owner == 1)
                                if(rand() % 2)
                                        specialProperty(1);
                }
        }
        else if((tmp->i == 9 && tmp->j == 1 || tmp->i == 1 && tmp->j == 9) && l == counter % 2)
        {
                int owner = checkOwnership(tmp);
                if (owner == 0)///////////////////////////////////
                        payOwnerUtilities(tmp);

                else if(owner == 2){
                        printf("Would you like to look at this location? (1 = Yes, Anythin Else = No)\n");
                        scanf("%d", &owner);
                        if(owner == 1)
                                specialProperty(2);
                }
                else if(owner == 3)
                {
                        owner = checkMortgageOwner(tmp);
                        if(owner == 0)
                        {       printf("Would you like to look at this location? (1 = Yes, Anythin Else = No)\n");
                                scanf("%d", &owner);
                                if(owner == 1)
                                        specialProperty(2);
                        }
                }
        }
        else if(tmp->i == 9 && tmp->j == 1 || tmp->i == 1 && tmp->j == 9)
        {
                int owner = checkOwnership(tmp);
                if (owner == 1)/////////////////////////////////////////
                        payOwnerUtilities(tmp);
                else if(owner == 2)
                        if(rand() % 2)
                                specialProperty(2);
                else if(owner == 3)
                {
                        owner = checkMortgageOwner(tmp);
                        if(owner == 1)
                                if(rand() % 2)
                                        specialProperty(2);


                }
        }
        else if(strcmp(tmp->name,player1.name) == 0)
        {
                int owner = checkOwnership(tmp);
                if (owner == 0)
                        payOwner(tmp);
                else if(owner == 2){
                        printf("Would you like to look at this location? (1 = Yes, Anythin Else = No)\n");
                        scanf("%d", &owner);
                        if(owner == 1)
                                possiblePurchase(tmp);
                }
                else if(owner == 3)
                {
                        owner = checkMortgageOwner(tmp);
                        if(owner == 0){
                                printf("Would you like to look at this location? (1 = Yes, Anythin Else = No)\n");
                                scanf("%d", &owner);
                                if(owner == 1)
                                        possiblePurchase(tmp);
                                }
                }
        }
        else{
                int owner = checkOwnership(tmp);
                if (owner==1)
                        payOwner(tmp);
                else if(owner == 2){
                        owner = rand() % 7;
                        if(0 == owner % 2 || owner == 5)
                                possiblePurchase(tmp);
                        else
                                printf("The computer has decided not to buy this property\n");

                }
                else if(owner == 3){
                        owner = checkMortgageOwner(tmp);
                        if(owner == 1)
                        {
                                owner = rand() % 7;
                                if(0 == owner % 2 || owner == 5)
                                        possiblePurchase(tmp);
                                else
                                        printf("The computer has decided not to buy this property\n");
                        }
                }
        }
        return;
}

void changeLoc(){//changes a players location, as puts the 1 or 0 where the player is located
        createBoard();
        board[player1.i][player1.j]= '1';
        board[comp.i][comp.j] = '0';
        if(player1.i == comp.i && player1.j == comp.j)
                board[comp.i][comp.j] = '2';
        if(player1.i == 11 && player1.j == 11 && l == counter % 2)
                passGo(&player1);
        if(comp.i == 11 && comp.j == 11 && l != counter % 2)
                passGo(&comp);

        return;
}
void createBoard() // Creates Board
{
        for(int i = 0;i < 13; i++)
        {
                for(int j = 0; j < 13; j++)
                        {
                        board[i][j] = ' ';
                        if(i==1 || i == 11){

                                if(j == 1 || j == 11)
                                        board[i][j] = 176;
                                else if(j > 0 && j<12)
                                        board[i][j] = '-';
                                else
                                        board[i][j] = ' ';
                        }
                        else if(i == 0|| i ==12||j == 0||j==12)
                                board[i][j] = ' ';
                        else if((i>0 && i< 12) && (j == 1 || j == 11))
                                board[i][j] = '-';
                        else
                                board[i][j] = ' ';
                }
        }

        return;
}
void printBoard() //Print Board
 {
        for(int i = 0;i < 13; i++)
        {
                for(int j = 0; j < 13; j++){
                        printf(White);
                        if(i == 0)
                        {
                                printHouses(i+1,j);
                                printf("%c ", board[i][j]);
                        }
                        else if(j == 0)
                        {
                                printHouses(i,j+1);
                                printf("%c ", board[i][j]);
                        }
                        else if(i == 12)
                        {
                                printHouses(i-1,j);
                                printf("%c ", board[i][j]);
                        }
                        else if(j == 12)
                        {
                                printHouses(i,j-1);
                                printf("%c ", board[i][j]);
                        }
                        else if(i == 11 && (j == 10 || j == 8))
                                printf(Purple "%c ", board[i][j]);
                        else if(i == 11 && (j == 2 || j == 3 || j == 5))
                                printf(BrightBlue "%c ", board[i][j]);
                        else if(j == 1 && (i == 10 || i == 8 || i == 7))
                                printf(Magenta "%c ", board[i][j]);
                        else if(j == 1 && (i == 2 || i == 4 || i == 5))
                                printf(Orange "%c ", board[i][j]);
                        else if(i == 1 && (j == 2 || j == 4 || j == 5))
                                printf(Red "%c ", board[i][j]);
                        else if(i == 1 && (j == 7 || j == 8 || j == 10))
                                printf(Yellow "%c ", board[i][j]);
                        else if(j == 11 && (i == 2 || i == 3 || i == 5))
                                printf(Green "%c ", board[i][j]);
                        else if(j == 11 && (i == 8 || i == 10))
                                printf(Blue "%c ", board[i][j]);
                        else if(j == 6 || i == 6)
                                printf(Road "%c ", board[i][j]);
                        else if(i == 11 && j == 9 || i == 9 && j == 11)
                                printf(Tax "%c ", board[i][j]);
                        else if(i == 11 && j == 4 || i == 1 && j == 3 || i == 7 && j == 11)
                                printf(Road "%c ", board[i][j]);
                        else if(i == 11 && j == 9 || i == 3 && j == 1 || i == 4 && j == 11)
                                printf(Chest "%c ", board[i][j]);
                        else if(i == 9 && j == 1 || i == 1 && j == 9)
                                printf(Chance "%c ", board[i][j]);
                        else
                                printf(White  "%c ", board[i][j]);



                }

                printf(White"\n");

        }

}
int rollDice()//rolls dice
{
        srand(time(NULL)+rand()%rand());
//      int d1 = rand() % 6 + 1;
//      int d2 = rand() % 6 + 1;
        int d1 = 7;
        int d2 = 0;
//      if(l == counter % 2)
//      d1 = 14;        //used for testing specific rolls
        printf("Dice 1: %d\nDice 2: %d \n",d1,d2);
        int sums = d1 + d2;
        if (d1 == d2)
                sums += 100;
        return sums;
}
void move(player* tmp, int sums)//moves the player step by step
{
        for(int t = 0; t < sums; t++){

                if(tmp->i == 11){
                        if(tmp->j == 1)
                                --tmp->i;
                        else
                                --tmp->j;
                }
                else if(tmp->j == 1)
                {
                        if(tmp->i==1)
                                ++tmp->j;
                        else
                                --tmp->i;
                }
                else if(tmp->i ==1)
                {
                        if(tmp->j ==11)
                                ++tmp->i;
                        else
                                ++tmp->j;
                }
                else
                {
                        if(tmp->j == 11)
                                ++tmp->i;
                        else
                                ++tmp->j;
                }
                        changeLoc();

        }
        printBoard();
        checkLoc(tmp);
        return;
}

void playGame()//general setup for each player's turn
{
        int sums,  choice = 0;
        int input;
        int  jailc = 0, jailp = 0;
        char garbage;
        while(!gameOver){
                printf("Computer's money = $%d\nPlayer's money = $%d\n",comp.money,player1.money);
                if(test != counter)
                        doubles = 0;
                pjail = player1.jail;
                cjail = comp.jail;
                if(l == counter % 2 && !pjail)
                {
                        if(player1.money < 0)
                                sell(&player1);
                        printf("\n\nWhat would you like to do? \n");
                        while(!gameOver){
                                input = 0;
                                printf("1 = rolling dice, 2 = sell/buyback property, 3 = rules again, 4 to buy houses, 5 = quit\n");
                                scanf("%d", &input);
                                scanf("%c", &garbage);
                                if ((input < 1 || input > 5))
                                        printf("Sorry Try Again\n");

                                else
                                        if(input == 1)
                                                break;
                                        switch (input){
                                                case 2:
                                                        printf("Current Money : %d\n", player1.money);
                                                        sell(&player1);
                                                        break;
                                                case 3:
                                                        printRules();
                                                        break;
                                                case 4:
                                                        buyHouse(&player1);
                                                        break;
                                                case 5:
                                                        printf("Sorry to see you go\n");
                                                        return;
                                                        }

                                }
                }
                else if (!cjail && l != counter % 2){
                        if(comp.money<0 || comp.money > 500)
                                sell(&comp);
                        printf("\n\nComputer's Turn:\n", comp.name);
                        if(comp.money > 750)
                                buyHouse(&comp);
                        sleep(1);
                }



                if(pjail && l == counter % 2)
                {
                        if(player1.money<0)
                                sell(&player1);
                        printf("\n\nYou are in jail!! What would you like to do? \n");
                        while(1){
                                input = 0;
                                printf("1 = roll dice, 2 = sell/buyBack property, 3 = rules again, 4 = buyHouses 5 = quit, 6 = Pay off the guards and walk out($50), 7 = use get out of jail free card (If Present), \n");
                                scanf("%d", &input);
                                scanf("%c", &garbage);
                                if ((input < 1 || input > 7))
                                        printf("Sorry Try Again\n");

                                else
                                        switch (input){
                                                case 1:
                                                        sums = rollDice();
                                                        if(sums > 100)
                                                        {
                                                                test = counter;
                                                                sums -= 100;
                                                                doubles = 1;
                                                                move(&player1, sums);
                                                                pjail = 0;
                                                                jailp = 0;
                                                                player1.jail = 0;
                                                        }
                                                        else{
                                                                if(++jailp == 3){
                                                                        printf("You have to pay $50 to get out of jail now\n");
                                                                        player1.money -= 50;
                                                                        if(player1.money < 0)
                                                                                sell(&player1);
                                                                        pjail = 0;
                                                                        jailp = 0;
                                                                        player1.jail = 0;
                                                                        move(&player1, sums);
                                                                }

                                                                counter++;
                                                        }
                                                        break;
                                                case 2:
                                                        sell(&player1);
                                                        if(gameOver)
                                                                return;
                                                        break;
                                                case 3:
                                                        printRules();
                                                        break;
                                                case 4:
                                                        buyHouse(&player1);
                                                        break;
                                                case 5:
                                                        return;
                                                case 6:
                                                        player1.money -= 50;
                                                        if(player1.money<0)
                                                                sell(&player1);
                                                        jailp = 0;
                                                        pjail = 0;
                                                        doubles = 0;
                                                        player1.jail = 0;
                                                        sum();
                                                        break;

                                                case 7:
                                                        if(pgetOutOfJail == 0)
                                                        {
                                                                printf("No cards available\n");
                                                        }
                                                        else
                                                        {
                                                                pgetOutOfJail--;
                                                                jailp = 0;
                                                                pjail = 0;
                                                                player1.jail = 0;
                                                                doubles = 0;
                                                                sum();
                                                                if(chanceGetOutOfJail == 1)
                                                                         chanceGetOutOfJail = 0;
                                                                else
                                                                        chestGetOutOfJail = 0;
                                                        }
                                                }
                                if(input == 1 || input == 6 || input == 7)
                                        break;
                        }

                }
                else if(cjail && l != counter % 2){
                        if(comp.money < 0 || comp.money > 500){

                        }
                        printf("\n\nComputer's Turn:\n");
                        doubles == 0;
                        choice = rand() % 2;
                        if(comp.money > 1000)
                                buyHouse(&comp);
                        if(cgetOutOfJail > 0)
                        {
                                cgetOutOfJail--;
                                cjail = 0;
                                jailc = 0;
                                comp.jail = 0;
                                sum();
                                if(chanceGetOutOfJail == 1)
                                         chanceGetOutOfJail = 0;
                                else
                                        chestGetOutOfJail = 0;
                        }
                        else if(choice == 0 && comp.money > 50){
                                printf("The computer payed $50 to get out of jail\n");
                                comp.money -= 50;
                                cjail = 0;
                                jailc = 0;
                                comp.jail = 0;
                                sum();
                                }
                        else{
                                sums = rollDice();
                                if(sums > 100)
                                {
                                        test = counter;
                                        sums -= 100;
                                        doubles = 1;
                                        move(&comp, sums);
                                        cjail = 0;
                                        comp.jail = 0;
                                        jailc = 0;
                                }
                                else{
                                        if(++jailc == 3){
                                                comp.money -= 50;
                                                if(comp.money < 0)
                                                        sell(&comp);
                                                cjail = 0;
                                                jailc = 0;
                                                comp.jail = 0;
                                                doubles = 0;
                                                sum();
                                        }
                                        counter++;

                                }
                        }
                }

                else{
                        if(gameOver)
                                return;
                        sum();
                }
        printf("\n\n\n\n\n");
        if(comp.money<0)
                sell(&comp);
        if(player1.money< 0)
                sell(&player1);
        if(gameOver)
                return;
        printBoard();

        }
        return;
}
void startGame()//starts the game and innitializes everythin
{
        printf("What is your name Player 1? ");
        fgets(player1.name, 20, stdin);
        player1.i = 11;
        player1.j = 11;
        player1.money = 1500;

        initializeProperties();
        initializeChance();
        initializeChest();

        comp.i = 11;
        comp.j = 11;
        comp.money = 1500;
        createBoard(board);
        printBoard(board);

        srand(time(NULL)+rand()%rand());
        l = rand() % 2; //returns 0 or 1 show whether player 1 is going first or second
        if(l == 0)
                printf("Congratz you get to go First %s", player1.name);
        else
                printf("You are going second, %s", player1.name);
        playGame();

        return;

}
int main()//main
{


        startGame();




        return 0;
}

















































//recursive
//You found me, There is no recursion function. That would be pointless