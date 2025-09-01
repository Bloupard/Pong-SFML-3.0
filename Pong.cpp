// Pong.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

int main()
{
    //Creation de l'objet video mode
    VideoMode vm({ 1920, 1080 });

    //Creation et ouverture de la fenetre pour le jeu
    RenderWindow window(vm, "Pong", State::Fullscreen);

    int score = 0;
    int lives = 3;

    //Creation de la batte au centre bas de l'ecran
    Bat bat(1920.f / 2.f, 1080.f - 20.f);

    //Creation de la balle
    Ball ball(1920.f / 2.f, 0.f);

    //Creation d'un objet texte appelle HUD et de la police font
    Font font("fonts/DS-DIGI.ttf");
    Text hud(font);
    hud.setCharacterSize(75);
    hud.setFillColor(Color::White);
    hud.setPosition({ 20, 20 });

    //Horloge pour tout time
    Clock clock;

    while (window.isOpen())
    {
        //Gestion des inputs joueurs
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
        {
            window.close();
        }

        //Gestion de la pression et relachement des touches directionnelles
        if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        {
            bat.moveLeft();
        }
        else
        {
            bat.stopLeft();
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Right))
        {
            bat.moveRight();
        }
        else
        {
            bat.stopRight();
        }

        //MAJ de la batte, la balle et l'HUD
        //MAJ le delta temps
        Time dt = clock.restart();
        bat.update(dt);
        ball.update(dt);
        //MAJ du texte HUD
        std::stringstream ss;
        ss << "Score : " << score << " - Vies : " << lives;
        hud.setString(ss.str());

        // Gestion de la balle tapant le bas
        if (ball.getPosition().position.y > window.getSize().y)
        {
            // inverse la direction de la balle
            ball.reboundBottom();
            // Enleve une vie
            lives--;
            // Check si 0 vie
            if (lives < 1) {
                // reset le score
                score = 0;
                // reset les vies
                lives = 3;
            }
        }

        //Gestion de la balle tapant le haut
        if (ball.getPosition().position.y < 0.f)
        {
            ball.reboundBatOrTop();
            //Ajout d'un point au joueur
            score++;
        }

        //Gestion de la balle sur les cotes
        if (ball.getPosition().position.x < 0.f || ball.getPosition().position.x + ball.getPosition().size.x > window.getSize().x)
        {
            ball.reboundSides();
        }

        // Gestion de la balle tapant la barre
        if (ball.getPosition().findIntersection(bat.getPosition()))
        {
            // inverse la direction de la balle
            ball.reboundBatOrTop();
        }

        //Dessin de la batte, la balle et l'HUD
        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();
    }

    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
