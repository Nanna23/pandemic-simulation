<!-- omit in toc -->
# pandemic-simulation
## Introduzione
Il programma simula la propagazione di una pandemia utilizzando il modello SIR (Suscettibili, Infetti, Rimossi). L'intero progetto è stato sviluppato nell'ambiente di programmazione C++.
## Il modello SIR
Il modello SIR è un modello matematico utilizzato per studiare lo sviluppo di una pandemia. Questo considera la popolazione come divisa in tre parti: coloro che possono essere infetti dalla malattia, ovvero i suscettibili, gli infetti e i rimossi, ovvero coloro che non possono contrarre nuovamente la malattia. In aggiunta di questi, il modello SIR tiene in considerazione due paramentri $\beta$ e $\gamma$, da 0 a 1, che indicano rispettivamente la probabilità di contagio e di guarigione.
Le leggi matematiche sulla quale si basa il modello SIR sono le seguenti:

$$\begin{align*}
\frac{dS}{dt} &= -\beta \frac{S}{N} I\\
\frac{dI}{dt} &= \beta \frac{S}{N} I - \gamma I\\
\frac{dR}{dt} &= \gamma I
\end{align*}$$

## Implementazione del modello SIR
Svolgendo le equazioni differenziali sopra descritte per $\Delta T = 1$ si hanno le seguenti equazioni utilizzate nel progetto:

$$\begin{align*}
S_i &= S_{i-1} - \beta \frac{S_{i-1}}{N} I_{i-1}\\
I_i &= I_{i-1} + \beta \frac{S_{i-1}}{N} I_{i-1} - \gamma I_{i-1}\\
R_i &= R_{i-1} + \gamma I_{i-1}
\end{align*}$$

I paramentri $\beta$ e $\gamma$ nella realtà possono variare in base a vaccinazioni e quarantene, tuttavia nel programma vengono considerati costanti.
Nel progetto come utità di tempo vengo utilizzati gli stadi (stages) della simuazione, in cui 1 stadio corrisponde a $\Delta T = 1$.
Essendo i risultati delle equazioni numeri decimali, mentre il numero di persone deve essere un intero, si è riscontrato il problema che arrotondando i valori ottenuti la popolazione con il passare del tempo diminuiva di grandezza. Per riscontrare questo problema, a ogni stadio le persone "mancanti" vengono aggiunte al valore più meritevole, ovvero il valore con un decimale più alto. Nel caso in cui ci fosse parità nei valori decimali, il valore in più viene assegnato in maniera casuale.
## Istruzioni per l'uso
È necessario che nella cartella dalla quale viene eseguito il programma sia presente il file *arial.ttf*, contente il font usato dalla libreria SFML.
### g++
Per compilare:

```
$ g++ -std=c++2a -Wall -Wextra -fsanitize=address,undefined model/pandemic.cpp model/person.cpp model/population.cpp model/position.cpp view/consoleInterface.cpp controller/simulation.cpp main.cpp -o app -lsfml-window -lsfml-system -lsfml-graphics -O3
```
Per eseguire:

```
$ ./app
```
### CMake
Per compilare:

```
$ cmake -S . -B build -DCMAKE_BUILD_TYPE=Release cmake --build build
```
Per eseguire:

```
$ ./build/app
```

Per testate:

```
$ cmake --build build --target test
```
## Guida utente
Il programma quando fatto partire, chiede se si vuole utilizzare un file di configurazione nel caso in cui questo fosse presente nella cartella. In caso contrario o se non è servito utilizzarlo, il programma prosegue chiedendo all'utente i seguenti valori in input: il numero iniziale di suscettibili, infetti e rimossi; i valori dei parametri $\beta$ e $\gamma; gli stadi, di cui si vuole osservare lo sviluppo della pandemia. Una volta creata con successo la simulazione, il programma chiede se l'utente desidera una rappresentazione grafica dei valori della popolazione. Infine, in output mostrerà una tabella in cui a ogni stadio corrisponde il rispettivo valore dei suscettibili, infetti e rimossi. Nel caso in cui si vuole il grafico, questo apparirà in una finestra differente in cui saranno presenti le tre funzioni dei valori S, I e R.
Il file di configurazione deve contenere i dati, separati da uno spazio, nel seguente ordine: suscettibili, infetti, rimossi, beta, gamma, stadi (es.```10 6 0 0.5 0.5 5```).
