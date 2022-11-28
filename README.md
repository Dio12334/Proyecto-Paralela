# Proyecto-Paralela
## Parallel TSP
- Jean Paul Huby
- Diego Paredes
- Efraín Córdova

## Ejecución
1. Utilizar **make** para crear el ejecutable *./tsp.out*
2. Ejecutar ./tsp.out <nombre_del_archivo> <numero_de_threads>. Por ejemplo: ./tsp.out map12.tsp 10

### Otras consideraciones
* El algoritmo no es polinomial y usa llamadas recursivas: es necesario mantener una cantidad baja de vértices. No recomendamos utilizar grafos por encima de los 18 vértices.
* Khipu no cuenta con un módulo de SDL2, por lo que deberá desactivar esta flag en el Makefile si desea probar el código a través de este servicio. También deberá remover toda referencia a los archivos de la carpeta *Display* en los archivos: graph.cpp y Makefile. Asímismo, recomendamos hacer este proceso si desea correr el archivo tester.py, pues la visualización del grafo no es muy relevante.
* En el informe no se ha incluído versiones *beta* del código. Consideramos que adjuntar este repositorio cumple básicamente la misma función.