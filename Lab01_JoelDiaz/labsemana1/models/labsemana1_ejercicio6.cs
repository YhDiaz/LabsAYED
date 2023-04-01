using System;

//Codigo creado en Visual Studio Code (Lenguaje de programacion: C#)

namespace labsemana1.models
{
    public class Jugador
    {
        //Atributos (especificados en el recurso guia)
        private string tipo {get; set;} = string.Empty;
        private string nombre {get; set;} = string.Empty;
        private int vida {get; set;} = 0;
        private string poder { get; set;} = string.Empty;
        private int velocidad { get; set; } = 0;

        //Metodos

        //Metodo para asignar valores a los atributos del jugador
        public void datos(int vida, int velocidad, string tipo, string nombre, string poder)
        {
            this.vida = vida;
            this.velocidad = velocidad;
            this.tipo = tipo;
            this.nombre = nombre;
            this.poder = poder;
        }

        //Al ejecutar este metodo, el jugador recuperaria puntos de vida (energia)
        public void recuperarEnergia()
        {
            vida += 25;
        }

        //Al ejecutar este metodo, se descontaria la vida del enemigo, la cual es necesaria recibirla como argumento
        public void atacar(int vidaEnemigo)
        {
            vidaEnemigo -= 15;
        }

        /*Considerando una variable booleana que permite el uso del poder o hechizo del jugador, se pasaria
        como argumento de la funcion para activarla y permitir la utilizacion del poder/hechizo*/
        public bool cargarHechizo_Poder(bool habilitarPoder)
        {
            Console.WriteLine("Cargando hechizo/poder del jugador...");

            habilitarPoder = true;

            return habilitarPoder;
        }
    }
}
