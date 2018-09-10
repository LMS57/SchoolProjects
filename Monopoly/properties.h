typedef struct properties{//structure for regular properties
        char name[25];
        int price;
        int rent;
        int oneHouse;
        int twoHouse;
        int threeHouse;
        int fourHouse;
        int hotel;
        int numHouses;
        int sell;
        int priceperhouse;
        char whoOwns;
        int mortgage;
        int loci;
        int locj;
}properties;
properties props[22];
typedef struct railroads{//structure for railroads
        char name[25];
        int price;
        int rent;
        int sell;
        int loci;
        int locj;
        char whoOwns;
        int mortgage;

}railroads;
railroads railroad[4];
typedef struct utilitie{//structure for utilities
        char name[25];
        int price;
        int sell;
        int loci;
        int locj;
        char whoOwns;
        int mortgage;

}utilitie;
utilitie utilities[2];
void printU(int t)//print layout for utilites
{
        printf("%d:\n", t+22);
        printf("-------------------------------------\n");
        printf("     -------------------------_     \n");
        printf("     %s\n", utilities[t].name);
        printf("     --------------------------     \n");
        if(utilities[t].mortgage)
        printf(Red "\n           MORTGAGE\n\n" White);
        printf(" If one 'Utility' is owned rent is 4 \n");
        printf("time amount shown on dice.\n");
        printf(" If both 'Utilities' are owned rent is\n");
        printf("10 time amount shown on dice.\n");
        printf("        Mortgage Value      $75.\n");
        printf("--------------------------------------\n\n");
        return;
}
void printRR(int t){//print layout for railroad
        printf("%d:\n", t+24);
        printf("------------------------------------\n");
        printf("     -------------------------_     \n");
        printf("     %s\n", railroad[t].name);
        printf("     --------------------------     \n");
        if(railroad[t].mortgage)
        printf(Red "\n           MORTGAGED\n\n" White);
        printf("    Rent                   $25.\n");
        printf("    If 2 R.R's are owned   $50.\n");
        printf("    If 3 ''    ''   ''     $100.\n");
        printf("    If 4 ''    ''   ''     $200.\n\n");
        printf("    Mortgage Value         $100.\n");
        printf("-------------------------------------\n");


        return;
}
void printProperties(int t)//print layout for properties
{
        printf("%d:\n", t);
        printf("------------------------------------\n");
        printf("        %s\n", props[t].name);
        if(props[t].mortgage)
        printf(Red"\n           MORTGAGED\n\n" White);
        printf("              Rent $%d.\n",props[t].rent);
        printf("With 1 House                 $%d.\n", props[t].oneHouse);
        printf("With 2 Houses                $%d.\n", props[t].twoHouse);
        printf("With 3 Houses                $%d.\n", props[t].threeHouse);
        printf("With 4 Houses                $%d.\n", props[t].fourHouse);
        printf("        With Hotel $%d\n\n", props[t].hotel);
        printf("      Mortgage Value $%d\n", props[t].sell);
        printf("     Houses cost $%d. Each\n", props[t].priceperhouse);
        printf("   Hotels, $%d. Plus 4 Houses\n\n", props[t].priceperhouse);
        printf("-------------------------------------\n");
        return;
}
void printMortgagedProperties(player *tmp)//checks to see if a location is mortgaged and prints it, used in buyback function
{
        int t;
        for(t = 0; t < 22; t++)
        {
                if(strcmp(tmp->name, player1.name) == 0)
                {
                        if(props[t].whoOwns == 'p' && props[t].mortgage == 1)
                        {
                                printProperties(t);
                        }

                }
                else
                        if(props[t].whoOwns == 'c' && props[t].mortgage == 1)
                                printProperties(t);
        }
        for(t = 0; t < 2; t++)
        {
                if(strcmp(tmp->name, player1.name) == 0)
                {
                        if(utilities[t].whoOwns == 'p' && utilities[t].mortgage == 1)
                        {
                                printU(t);
                        }

                }
                else
                        if(props[t].whoOwns == 'c' && utilities[t].mortgage == 1)
                                printU(t);
        }
        for(t = 0; t < 4; t++)
        {
                if(strcmp(tmp->name, player1.name) == 0)
                {
                        if(railroad[t].whoOwns == 'p' && railroad[t].mortgage == 1)
                        {
                                printRR(t);
                        }

                }
                else
                        if(railroad[t].whoOwns == 'c' && railroad[t].mortgage == 1)
                                printRR(t);
        }



        return;
}
void printPropertiesOwned(player *tmp){//prints all properties owned mortgaged or otherwise
        int t;
        for(t = 0; t < 22; t++)
        {
                if(strcmp(tmp->name, player1.name) == 0)
                {
                        if(props[t].whoOwns == 'p')
                        {
                                printProperties(t);
                        }

                }
                else
                        if(props[t].whoOwns == 'c')
                                printProperties(t);
        }
        for(t = 0; t < 2; t++)
        {
                if(strcmp(tmp->name, player1.name) == 0)
                {
                        if(utilities[t].whoOwns == 'p')
                        {
                                printU(t);
                        }

                }
                else
                        if(props[t].whoOwns == 'c')
                                printU(t);
        }
        for(t = 0; t < 4; t++)
        {
                if(strcmp(tmp->name, player1.name) == 0)
                {
                        if(railroad[t].whoOwns == 'p')
                        {
                                printRR(t);
                        }

                }
                else
                        if(railroad[t].whoOwns == 'c')
                                printRR(t);
        }

        return;
}

void initializeProperties(){//initializes all properties
        int t;
        for(t = 0; t < 22; t++)
        {
                props[t].mortgage = 0;
                props[t].numHouses = 0;
                props[t].whoOwns = ' ';
        }
        for(t = 0; t < 2; t++)
        {
                utilities[t].mortgage = 0;
                utilities[t].whoOwns = ' ';
        }
        for(t = 0; t < 4; t++)
        {
                railroad[t].mortgage = 0;
                railroad[t].whoOwns = ' ';
        }

        strcpy(props[0].name, "Mediterranean Avenue");
        props[0].price = 60;
        props[0].rent = 2;
        props[0].oneHouse =10;
        props[0].twoHouse = 30;
        props[0].threeHouse = 90;
        props[0].fourHouse = 160;
        props[0].hotel = 250;
        props[0].sell = 30;
        props[0].priceperhouse = 50;
        props[0].loci = 11;
        props[0].locj = 10;

        strcpy(props[1].name, "Baltic Avenue");
        props[1].price = 60;
        props[1].rent = 4;
        props[1].oneHouse = 20;
        props[1].twoHouse = 60;
        props[1].threeHouse = 180;
        props[1].fourHouse = 320;
        props[1].hotel = 450;
        props[1].sell = 30;
        props[1].priceperhouse = 50;
        props[1].loci = 11;
        props[1].locj = 8;

        strcpy(props[2].name, "Oriental Avenue");
        props[2].price = 100;
        props[2].rent = 6;
        props[2].oneHouse = 30;
        props[2].twoHouse = 90;
        props[2].threeHouse = 270;
        props[2].fourHouse = 400;
        props[2].hotel = 550;
        props[2].sell = 50;
        props[2].priceperhouse = 50;
        props[2].loci = 11;
        props[2].locj = 5;

        strcpy(props[3].name, "Vermont Avenue");
        props[3].price = 100;
        props[3].rent = 6;
        props[3].oneHouse = 30;
        props[3].twoHouse = 90;
        props[3].threeHouse = 270;
        props[3].fourHouse = 400;
        props[3].hotel = 550;
        props[3].sell = 50;
        props[3].priceperhouse = 50;
        props[3].loci = 11;
        props[3].locj = 3;

        strcpy(props[4].name, "Connecticut Avenue");
        props[4].price = 120;
        props[4].rent = 8;
        props[4].oneHouse = 40;
        props[4].twoHouse = 100;
        props[4].threeHouse = 300;
        props[4].fourHouse = 450;
        props[4].hotel = 600;
        props[4].sell = 60;
        props[4].priceperhouse = 50;
        props[4].loci = 11;
        props[4].locj = 2;

        strcpy(props[5].name, "St. Charles Place");
        props[5].price = 140;
        props[5].rent = 10;
        props[5].oneHouse = 50;
        props[5].twoHouse = 150;
        props[5].threeHouse = 450;
        props[5].fourHouse = 625;
        props[5].hotel = 750;
        props[5].sell = 70;
        props[5].priceperhouse = 100;
        props[5].loci = 10;
        props[5].locj = 1;

        strcpy(props[6].name, "States Avenue");
        props[6].price = 150;
        props[6].rent = 10;
        props[6].oneHouse = 50;
        props[6].twoHouse = 150;
        props[6].threeHouse = 450;
        props[6].fourHouse = 625;
        props[6].hotel = 750;
        props[6].sell = 70;
        props[6].priceperhouse = 100;
        props[6].loci = 8;
        props[6].locj = 1;

        strcpy(props[7].name, "Virginia  Avenue");
        props[7].price = 160;
        props[7].rent = 12;
        props[7].oneHouse = 60;
        props[7].twoHouse = 180;
        props[7].threeHouse = 500;
        props[7].fourHouse = 700;
        props[7].hotel = 900;
        props[7].sell = 80;
        props[7].priceperhouse = 100;
        props[7].loci = 7;
        props[7].locj = 1;

        strcpy(props[8].name, "St. James Place");
        props[8].price = 180;
        props[8].rent = 14;
        props[8].oneHouse = 70;
        props[8].twoHouse = 200;
        props[8].threeHouse = 550;
        props[8].fourHouse = 750;
        props[8].hotel = 950;
        props[8].sell = 90;
        props[8].priceperhouse = 100;
        props[8].loci = 5;
        props[8].locj = 1;

        strcpy(props[9].name, "Tennessee Avenue");
        props[9].price = 180;
        props[9].rent = 14;
        props[9].oneHouse = 70;
        props[9].twoHouse = 200;
        props[9].threeHouse = 550;
        props[9].fourHouse = 750;
        props[9].hotel = 950;
        props[9].sell = 90;
        props[9].priceperhouse = 100;
        props[9].loci = 4;
        props[9].locj = 1;

        strcpy(props[10].name, "New York Avenue");
        props[10].price = 200;
        props[10].rent = 16;
        props[10].oneHouse = 70;
        props[10].twoHouse = 220;
        props[10].threeHouse = 600;
        props[10].fourHouse = 800;
        props[10].hotel = 1000;
        props[10].sell = 100;
        props[10].priceperhouse = 100;
        props[10].loci = 2;
        props[10].locj = 1;

        strcpy(props[11].name, "Kentucky Avenue");
        props[11].price = 220;
        props[11].rent = 18;
        props[11].oneHouse = 90;
        props[11].twoHouse = 250;
        props[11].threeHouse = 700;
        props[11].fourHouse = 875;
        props[11].hotel = 1050;
        props[11].sell = 110;
        props[11].priceperhouse = 150;
        props[11].loci = 1;
        props[11].locj = 2;

        strcpy(props[12].name, "Indiana Avenue");
        props[12].price = 220;
        props[12].rent = 18;
        props[12].oneHouse = 90;
        props[12].twoHouse = 250;
        props[12].threeHouse = 700;
        props[12].fourHouse = 875;
        props[12].hotel = 1050;
        props[12].sell = 110;
        props[12].priceperhouse = 150;
        props[12].loci = 1;
        props[12].locj = 4;

        strcpy(props[13].name, "Illinois Avenue");
        props[13].price = 240;
        props[13].rent = 20;
        props[13].oneHouse = 100;
        props[13].twoHouse = 300;
        props[13].threeHouse = 750;
        props[13].fourHouse = 925;
        props[13].hotel = 1100;
        props[13].sell = 120;
        props[13].priceperhouse = 150;
        props[13].loci = 1;
        props[13].locj = 5;

        strcpy(props[14].name, "Atlantic Avenue");
        props[14].price = 260;
        props[14].rent = 22;
        props[14].oneHouse = 110;
        props[14].twoHouse = 330;
        props[14].threeHouse = 800;
        props[14].fourHouse = 975;
        props[14].hotel = 1150;
        props[14].sell = 130;
        props[14].priceperhouse = 150;
        props[14].loci = 1;
        props[14].locj = 7;

        strcpy(props[15].name, "Ventnor Avenue");
        props[15].price = 260;
        props[15].rent = 22;
        props[15].oneHouse = 110;
        props[15].twoHouse = 330;
        props[15].threeHouse = 800;
        props[15].fourHouse = 975;
        props[15].hotel = 1150;
        props[15].sell = 130;
        props[15].priceperhouse = 150;
        props[15].loci = 1;
        props[15].locj = 8;

        strcpy(props[16].name, "Marvin Gardens");
        props[16].price = 280;
        props[16].rent = 24;
        props[16].oneHouse = 120;
        props[16].twoHouse = 360;
        props[16].threeHouse = 850;
        props[16].fourHouse = 1025;
        props[16].hotel = 1200;
        props[16].sell = 140;
        props[16].priceperhouse = 150;
        props[16].loci = 1;
        props[16].locj = 10;

        strcpy(props[17].name, "Pacific Avenue");
        props[17].price = 300;
        props[17].rent = 26;
        props[17].oneHouse = 130;
        props[17].twoHouse = 390;
        props[17].threeHouse = 900;
        props[17].fourHouse = 1100;
        props[17].hotel = 1275;
        props[17].sell = 150;
        props[17].priceperhouse = 200;
        props[17].loci = 2;
        props[17].locj = 11;
        strcpy(props[18].name, "North Carolina Avenue");
        props[18].price = 300;
        props[18].rent = 26;
        props[18].oneHouse = 130;
        props[18].twoHouse = 390;
        props[18].threeHouse = 900;
        props[18].fourHouse = 1100;
        props[18].hotel = 1275;
        props[18].sell = 150;
        props[18].priceperhouse = 200;
        props[18].loci = 3;
        props[18].locj = 11;

        strcpy(props[19].name, "Pennsylvania Avenue");
        props[19].price = 320;
        props[19].rent = 28;
        props[19].oneHouse = 150;
        props[19].twoHouse = 450;
        props[19].threeHouse = 1000;
        props[19].fourHouse = 1200;
        props[19].hotel = 1400;
        props[19].sell = 160;
        props[19].priceperhouse = 200;
        props[19].loci = 5;
        props[19].locj = 11;

        strcpy(props[20].name, "Park Place");
        props[20].price = 350;
        props[20].rent = 35;
        props[20].oneHouse = 175;
        props[20].twoHouse = 500;
        props[20].threeHouse = 1100;
        props[20].fourHouse = 1300;
        props[20].hotel = 1500;
        props[20].sell = 175;
        props[20].priceperhouse = 200;
        props[20].loci = 8;
        props[20].locj = 11;


        strcpy(props[21].name, "Boardwalk");
        props[21].price = 400;
        props[21].rent = 50;
        props[21].oneHouse = 200;
        props[21].twoHouse = 600;
        props[21].threeHouse = 1400;
        props[21].fourHouse = 1700;
        props[21].hotel = 2000;
        props[21].sell = 200;
        props[21].priceperhouse = 200;
        props[21].loci = 10;
        props[21].locj = 11;

        strcpy(railroad[0].name, "Reading Railroad");
        railroad[0].price = 200;
        railroad[0].rent = 25;
        railroad[0].sell = 100;
        railroad[0].loci = 11;
        railroad[0].locj = 6;

        strcpy(railroad[1].name, "Pennsylvania Railroad");
        railroad[1].price = 200;
        railroad[1].rent = 25;
        railroad[1].sell = 100;
        railroad[1].loci = 6;
        railroad[1].locj = 1;

        strcpy(railroad[2].name, "B&O Railroad");
        railroad[2].price = 200;
        railroad[2].rent = 25;
        railroad[2].sell = 100;
        railroad[2].loci = 1;
        railroad[2].locj = 6;

        strcpy(railroad[3].name, "Short Line Railroad");
        railroad[3].price = 200;
        railroad[3].rent = 25;
        railroad[3].sell = 100;
        railroad[3].loci = 6;
        railroad[3].locj = 11;

        strcpy(utilities[0].name, "Electric Company");
        utilities[0].price = 150;
        utilities[0].sell = 75;
        utilities[0].loci = 9;
        utilities[0].locj = 1;

        strcpy(utilities[1].name, "Water Works");
        utilities[1].price = 150;
        utilities[1].sell = 75;
        utilities[1].loci = 1;
        utilities[1].locj = 9;

        return;
}
