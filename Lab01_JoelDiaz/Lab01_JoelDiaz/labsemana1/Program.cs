using System;
using labsemana1.models;

//Codigo creado en Visual Studio Code (Lenguaje de programacion: C#)

namespace labsemana1
{
    public class Program
    {
        static void Main(string[] args)
        {
            //Objetos (vehiculos) para el menu de seleccion ()
            Vehiculo vehiculo01 = new Vehiculo("McLaren Automotive", "P1", 2014, 89, 92);
            Vehiculo vehiculo02 = new Vehiculo("Bugatti Automobiles S.A.S.", "Veyron", 2015, 91, 90);
            Vehiculo vehiculo03 = new Vehiculo("Hennessey Special Vehicles", "Venom F5", 2022, 95, 94);

            //Lista de vehiculos
            List<Vehiculo> vehicles = new List<Vehiculo>();

            vehicles.Add(vehiculo01);
            vehicles.Add(vehiculo02);
            vehicles.Add(vehiculo03);
            
            //Variables
            int i = 0, option = 0;
            bool firstTime = true;

            Console.WriteLine("\n-------------------- BIENVENIDO A LA PANTALLA DE SELECCION DE VEHICULOS --------------------");

            do
            {
                if(!firstTime)
                {
                    Console.WriteLine("\n\t\t***** Error (El vehiculo seleccionado no esta definido) *****");
                }

                Console.WriteLine("\nMenu de seleccion de vehiculos:");

                for(i = 0; i < vehicles.Count; i++)
                {
                    vehicles[i].datos(i + 1);
                }

                /*foreach(var vehicle in vehicles)
                {
                    vehicle.datos();
                }*/

                Console.Write("\n\t* Seleccione un vehiculo (numero): ");
                option = Convert.ToInt32(Console.ReadLine());

                firstTime = false;
            }
            while(option <= 0 || option > i);

            Console.WriteLine("\n\t***** Felicidades, has seleccionado el vehiculo {0} *****", option);
            vehicles[option - 1].datos(option);

            Console.WriteLine("\n-------------------- FIN DEL PROGRAMA --------------------");
        }
    }
}