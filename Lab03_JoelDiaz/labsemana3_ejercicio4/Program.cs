using System;
using labsemana3_ejercicio4.models;

namespace labsemana3_ejercicio4
{
    public class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("\n--------------- BIENVENIDO A LA VERSION DEMO DEL JUEGO DE COMBATE ---------------");
            Console.WriteLine("\n\tInformacion importante:\n\n\t1. Debe definir la cantidad de jugadores que participaran en cada equipo (maximo 5)\n\t2. Debe ingresar el nombre/alias de cada jugador\n\t3. Por defecto, la vida comienza en 100 puntos, el nivel inicial sera el 1, el puntaje comienza en 0 y la barra de energia comienza en 10\n\t4. El maximo de vida (o salud) son 100 puntos, mientras que el minimo son 0 puntos, momento en el que el jugador queda fuera de combate\n\t5. La barra de energia tiene un maximo de 10 puntos y un minimo de 0\n\t6. Un dado determinara si el jugador puede atacar a otro o si debera pasar\n\t7. Para atacar se requiere de un minimo de energia\n\t8. La partida tendra un maximo de 20 turnos\n\t9. El ganador se decidira a partir del puntaje realizado por todo el equipo");

            Console.WriteLine("\n---------- CANTIDAD DE JUGADORES ----------");

            int numPlayers = 0, turns = 30, exit = 0, i = 0, j = 0;

            List<Player> team1 = new List<Player>();
            List<Player> team2 = new List<Player>();

            while(exit != 1)
            {
                try
                {
                    if(numPlayers != -1)
                    {
                        Console.Write("\n\t* Indique la cantidad de jugadores por equipo (minimo: 1, maximo: 5): ");
                    }
                    
                    numPlayers = Convert.ToInt16(Console.ReadLine());

                    while(numPlayers < 1 || numPlayers > 5)
                    {
                        Console.Write("\n\t\t* (Error: Valor fuera de rango) Por favor, ingrese un dato valido: ");
                        numPlayers = Convert.ToInt16(Console.ReadLine()); 
                    }

                    for(i = 0; i < 2; i++)
                    {
                        for(j = 0; j < numPlayers; j++)
                        {
                            Player p = new Player();
                            p.enterData(j + 1, i + 1);
                            
                            if(i == 0)
                            {
                                team1.Add(p);
                            }
                            else
                            {
                                team2.Add(p);
                            }

                            p.stats(j + 1);
                        }

                        exit = 1;
                    }                    
                }
                catch (System.Exception)
                {
                    Console.Write("\n\t\t* (Error: Dato no valido) Por favor, ingrese un dato valido: ");
                    numPlayers = -1;
                    exit = 0;
                }
            }

            Console.WriteLine("\n---------- COMIENZA EL JUEGO ----------");

            Random rand = new Random();
            Player player = new Player();
            int dice = 0, turnTm1 = 1, turnTm2 = 1, ko1 = 0, ko2 = 0;

            for(i = 0; i < turns; i++)
            {
                Console.WriteLine("\nTurno {0}", i + 1);

                if(i % 2 == 0)
                {
                    Console.WriteLine("\n\tTurno del equipo 1");

                    dice = rand.Next(0, 10) + 1;

                    if(dice % 2 == 0 || dice % 3 == 0)
                    {
                        if(team1[turnTm1 - 1].health > 0 && team1[turnTm1 - 1].energy > 0)
                        {
                            team2 = player.attack(team2, team1, turnTm1, ref ko1);
                        }
                        else if(team1[turnTm1 - 1].health > 0 && team1[turnTm1 - 1].energy == 0)
                        {
                            team1[turnTm1 - 1].energy = 10;
                            Console.WriteLine("\n\t\t***** {0} ha recargado su energia *****", team1[turnTm1 - 1].name);
                        }
                        else if(team1[turnTm1 - 1].health == 0)
                        {
                            i--;
                        }       
                    }
                    else
                    {
                        Console.WriteLine("\n\tEl jugador NO puede atacar");
                    }

                    if(turnTm1 == numPlayers)
                    {
                        turnTm1 = 1;
                    }
                    else
                    {
                        turnTm1++;
                    }

                    if(ko1 == numPlayers)
                    {
                        i = turns;
                    }
                }
                else
                {
                    Console.WriteLine("\n\tTurno del equipo 2");

                    dice = rand.Next(0, 10) + 1;

                    if(dice % 2 == 0 || dice % 3 == 0)
                    {
                        if(team2[turnTm2 - 1].health > 0 && team2[turnTm2 - 1].energy > 0)
                        {
                            team1 = player.attack(team1, team2, turnTm2, ref ko2);
                        }
                        else if(team2[turnTm2 - 1].health > 0 && team2[turnTm2 - 1].energy == 0)
                        {
                            team2[turnTm2 - 1].energy = 10;
                            Console.WriteLine("\n\t\t***** {0} ha recargado su energia *****", team2[turnTm2 - 1].name);
                        }
                        else if(team2[turnTm2 - 1].health == 0)
                        {
                            i--;
                        }
                    }
                    else
                    {
                        Console.WriteLine("\n\tEl jugador NO puede atacar");
                    }

                    if(turnTm2 == numPlayers)
                    {
                        turnTm2 = 1;
                    }
                    else
                    {
                        turnTm2++;
                    }

                    if(ko2 == numPlayers)
                    {
                        i = turns;
                    }
                }
            }

            Console.WriteLine("\n\tEstadisticas finales:");

            int xp1 = 0, xp2 = 0;

            for(i = 0; i < 2; i++)
            {
                j = 1;

                if(i == 0)
                {
                    Console.WriteLine("\n\tEquipo 1:\n");

                    foreach(var x in team1)
                    {
                        x.stats(1);
                        xp1 += x.score;
                        j++;
                    }
                }
                else
                {
                    Console.WriteLine("\n\tEquipo 1:\n");

                    foreach(var x in team2)
                    {
                        x.stats(j);
                        xp2 += x.score;
                        j++;
                    }
                }
            }

            Console.WriteLine("\n\tPuntos de experiencia por equipo:\n\n\t* Equipo 1: {0}\n\t* Equipo 2: {1}", xp1, xp2);

            if(xp1 > xp2)
            {
                Console.WriteLine("\n\t********** EL EQUIPO 1 ES EL GANADOR **********");
            }
            else
            {
                Console.WriteLine("\n\t********** EL EQUIPO 2 ES EL GANADOR **********");
            }

            Console.WriteLine("\n-------------------- FIN DEL JUEGO --------------------");
        }
    }
}