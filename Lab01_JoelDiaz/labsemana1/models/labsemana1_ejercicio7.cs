using System;

//Codigo creado en Visual Studio Code (Lenguaje de programacion: C#)

namespace labsemana1.models
{
    public class Vehiculo
    {
        //Atributos (especificados en el recurso guia)
        private string fabricante { get; set; } = string.Empty;
        private string modelo { get; set; } = string.Empty;
        private int year { get; set; } = 0;
        private int velocidad { get; set; } = 0;
        private int maniobrabilidad { get; set; } = 0;

        //Metodos

        //Se muestran los datos del vehiculo (una vez cargados)
        public void datos(int numVehicle)
        {
            Console.WriteLine("\n- Vehiculo {0}:\n\n\t* Fabricante: {1}\n\t* Modelo: {2}\n\t* Year: {3}\n\t* Porcentaje de velocidad: {4}%\n\t* Porcentaje de maniobrabilidad: {5}%", numVehicle, this.fabricante, this.modelo, this.year, this.velocidad, this.maniobrabilidad);
        }

        //Constructores

        public Vehiculo()
        {

        }

         //Asignacion de valores a los atributos del vehiculo a traves del constructor
        public Vehiculo(string fabricante, string modelo, int year, int velocidad, int maniobrabilidad)
        {
            this.fabricante = fabricante;
            this.modelo = modelo;
            this.year = year;
            this.velocidad = velocidad;
            this.maniobrabilidad = maniobrabilidad;
        }
    }
}