/*
#include <osnovna.h>

// Mogu li nekako napraviti da nekako koračno krenemo.
// Zadatak 1. napravi xy
// ---> isprobaj
// ...

// 1. Zdatak, inicijalizirati gumbe.
// ---> Čuje se zvok kad se klikne, vide se boje.

// 2. Zadatak, nešto napraviti s gumbima. Bilo bi idealno mijenjati boju playera. Init player i game.
// ---> Isprobati promjenu boja playera.

// 3. Zadatak, Inicijalizirati kocku. Ako je više od dva playera odabralo boju, aktiviraj kocku. Pritiskom na kocku se mora pokrenuti igra.
// ---> Bacanje i animacija kocke

// 4. Zadatak, Napraviti da se plaeyeri mići
// ---> Vidjeti da igra radi.

// 5. Zadatak, Napraviti kraj igre.
// ---> Vidjeti da igra radi.

int loop3()
{
    buttons.init();
    dice.init();
    players.init();
    game.inti();
    // Još neki init?
}

int main3()
{
    switch (button.player)
    {
    case Player1:
        playerAction(1);
    case Player2:
        playerAction(2);
    case Player3:
        playerAction(3);
    case Player4:
        playerAction(4);
    case Dice:
        if (game.state == begining)
            game.start();
        else
            ()
                dice.roll();
    }

    if (players.activeMoreThan(2))
    {
        dice.enable();
    }

    if (players.anyWon())
    {
        game.endGame();
        game.winer(playes.whoWon());
    }

    // Neki update?
}

void playerAction(int pn)
{
    if (game.state == pocetak)
    {
        switch (button.action)
        {
        case left:
            p.changeColorLeft();
        case right:
            p.changeColorRight();
        case submit:
            p.selectColor();
        }
    }
    else if (game.state == game)
    {
        p = players.get(pn);
        p.activate();
        switch (button.action)
        {
        case left:
            p.selectFigureLeft();
        case right:
            p.selectFigureRight();
        case submit:
            p.figureAction(p.figure);
        }
    }
}

void figureAction(figure f)
{
    if (f.canMove)
    {
        f.move(dice.getNumber());
    }
}*/