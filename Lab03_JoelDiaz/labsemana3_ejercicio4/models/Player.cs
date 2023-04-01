using System;

namespace labsemana3_ejercicio4.models
{
    public class Player
    {
        public string name {get; set;}
        public int level {get; set;}
        public int health {get; set;}
        public int score {get; set;}
        public int energy {get; set;}

        public void enterData(int num, int team)
        {
            Console.WriteLine("\n\tBienvenido jugador {0} del equipo {1}. Por favor, ingrese los datos que se solicitan;", num, team);
            
            Console.Write("\n\t* Nombre/alias (minimo: 1 caracter, maximo: 25 caracteres; SOLO LETRAS): ");
            this.name = Console.ReadLine();

            while(this.name.Length < 1 || this.name.Length > 25)
            {
                Console.Write("\n\t\t* (Error: Extension invalida) Por favor, ingrese un nombre/alias razonable: ");
                this.name = Console.ReadLine();
            }

            this.level = 1;
            this.health = 100;
            this.score = 0;
            this.energy = 10;
        }

        public void stats(int num)
        {
            Console.WriteLine("\n\tJugador {0}\n\n\t* Nombre/alias: {1}\n\t* Nivel: {2}\n\t* Salud: {3}\n\t* Puntaje: {4}\n\t* Energia: {5}", num, this.name, this.level, this.health, this.score, this.energy);
        }

        public List<Player> attack(List<Player> enemies, List<Player> myTeam, int myPos, ref int ko)
        {
            int exit = 0, attPlayer = 0, j = 1;

            Console.WriteLine("\n\tLista de enermigos:");

            j = 1;
                        
            foreach(var enemy in enemies)
            {
                if(enemy.health > 0)
                {
                    Console.Write("\n\t{0}. {1}", j, enemy.name);
                }
                else
                {
                    Console.Write("\n\t{0}. {1} (Fuera de combate)", j, enemy.name);
                }

                j++;            
            }

            while(exit != 1)
            {
                try
                {
                    if(attPlayer != -1)
                    {
                        Console.Write("\n\n\tSeleccione a quien quiere atacar (SOLO EL NUMERO): ");       
                    }
                            
                    attPlayer = Convert.ToInt16(Console.ReadLine());

                    while(attPlayer < 1 || attPlayer > enemies.Count || enemies[attPlayer - 1].health == 0)
                    {
                        Console.Write("\n\t\t* (Error: El jugador no esta en la lista o esta fuera de combate) Por favor, seleccione unuevamente: ");
                        attPlayer = Convert.ToInt16(Console.ReadLine());
                    }

                    exit = 1;
                }
                catch (System.Exception)
                {
                    Console.Write("\n\t\t* (Error: Dato no valido) Por favor, ingrese un numero valido: ");
                    attPlayer = -1;
                }    
            }

            Random rand = new Random();
            int damage = rand.Next(10, 20);

            enemies[attPlayer - 1].health -= damage;

            if(enemies[attPlayer - 1].health <= 0)
            {
                enemies[attPlayer - 1].health = 0;
                ko++;
            }

            myTeam[myPos - 1].score += damage;

            myTeam[myPos - 1].energy--;

            Console.WriteLine("\n\t***** {0} acaba de quitarle {1} puntos de vida a {2} *****", myTeam[myPos - 1].name, damage, enemies[attPlayer - 1].name);

            Console.WriteLine("\n\t\tActualizacion de estadisticas:\n\n\t\t* Atacante\n\n\t\t- Nombre/alias: {0}\n\t\t- Puntaje: {1}\n\t\t- Energia: {2}\n\n\t\t* Jugador atacado\n\n\t\t- Nombre/alias: {3}\n\t\t- Salud: {4}", myTeam[myPos - 1].name, myTeam[myPos - 1].score, myTeam[myPos - 1].energy, enemies[attPlayer - 1].name, enemies[attPlayer - 1].health);

            if(enemies[attPlayer - 1].health <= 0)
            {
                Console.WriteLine("\n\t\t***** {0} esta fuera de combate *****", enemies[attPlayer - 1].name);
            }

            return enemies;
        }
    }
}