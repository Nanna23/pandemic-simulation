<!-- omit in toc -->
# Simulazione dell'evoluzione di un'epidemia - Progetto di "Programmazione per la Fisica" di Annabel Giles
- [Introduzione](#Introduzione)
- [Il modello SIR](#Il_modello_SIR)
- [Implementazione del modello SIR](#Implementazione_del_modello_SIR)
- [Progettazione](#Progettazione)
- [Test](#Test)
- [Istruzioni per l'uso](#Istruzioni_per_l'uso)
- [Guida utente](#Guida_utente)
## Introduzione
Il programma simula la propagazione di una pandemia utilizzando il modello SIR (Suscettibili, Infetti, Rimossi). L'intero progetto è stato sviluppato utilizzando come linguaggio di programmazione C++.
## Il modello SIR
Il modello SIR è un modello matematico utilizzato per studiare lo sviluppo di una pandemia all'interno di popolazione divisa in persone suscettibili, infette e rimosse. In aggiunta a questi, il modello SIR tiene in considerazione due parametri, con valori compresi tra 0 e 1: $\beta$ e $\gamma$, che indicano rispettivamente la probabilità di contagio e di guarigione.
Le leggi matematiche sulla quale si basa il modello SIR sono le seguenti:

$$\begin{align*}
\frac{dS}{dt} &= -\beta \frac{S}{N} I\\
\frac{dI}{dt} &= \beta \frac{S}{N} I - \gamma I\\
\frac{dR}{dt} &= \gamma I
\end{align*}$$

Le persone suscettibili possono solo diminuire di numero in quanto 
!!!

## Implementazione del modello SIR
Svolgendo per $\Delta T = 1$ le equazioni differenziali sopra descritte, si hanno le equazioni utilizzate nel progetto:

$$\begin{align*}
S_i &= S_{i-1} - \beta \frac{S_{i-1}}{N} I_{i-1}\\
I_i &= I_{i-1} + \beta \frac{S_{i-1}}{N} I_{i-1} - \gamma I_{i-1}\\
R_i &= R_{i-1} + \gamma I_{i-1}
\end{align*}$$

I parametri $\beta$ e $\gamma$ nella realtà possono variare in base a vaccinazioni e quarantene, tuttavia nel programma questi vengono considerati costanti.
Nel progetto come unità di tempo viene utilizzato lo stadio (stage) della simulazione, in cui 1 stadio corrisponde a $\Delta T = 1$.
Essendo i risultati delle equazioni numeri decimali, questi vanno arrotondati a valori interi (e.g. non è possibile avere 4.5 persone infette). L'arrotondamento deve però tener conto che il numero totale di persone all'interno della popolazione deve rimanere costante, arrotondare per difetto o eccesso non sarebbe quindi corretto. La soluzione adottata consiste prima nel calcolare le unità mancanti, che possono essere al massimo 2, sommando le parti decimali dei valori S, I ed R appena calcolati. In seguito, si assegnano le unità mancanti ai gruppi (S, I o R) in ordine decrescente per parte decimale.
## Progettazione
Il programma è stato progettato utilizzando il modello MVC (Model-View-Controller). Questo design divide il codice in tre parti in modo tale da tenerlo organizzato:
- Modello (model): è la parte che gestisce i dati e contiene la logica del programma; !!
- Vista (view): si occupa della presentazione all'utente, mostrando i dati in maniera comprensibile;
- Controllore (controller): è la parte che funge da intermediario tra il model e la view.

Inoltre è presente il file *main.cpp* che è il punto di entrata del programma e si occupa di avviare la view.
Ho utilizzato questo design per mantenere il codice in ordine e poter implementare facilmente nuove funzionalità espandendo le capacità del programma.
Per lo stesso motivo la classe Population è caratterizzata da un vettore di Person. Questo è inoltre diviso in sezioni con il seguente ordine: suscettibili, infetti e rimossi. Inoltre ogni persona ha una propria posizione, che nel progetto è ridonandante ma si è fatta la scelta di tenerlo nel codice, proprio per tenere la possibilità di implementare una simulazione della pandemia tramite automa cellulare.

CMake è stato utilizzato per rendere più semplice la compilazione del programma: i file e le impostazioni necessarie alla compilazione non devono essere riscritte ogni volta nella linea di comando in quanto sono già presenti in *CMakeLists.txt*. Quest'ultimo file facilita la portabilità poiché non è necessario memorizzare alcun comando specifico.
## Test
I test sono stati scritti utilizzando il framework doctest. I test riguardano le classi che svolgono funzioni non elementari ma fondamentali per il buon funzionamento del programma, queste sono:
- la classe Population, della quale se ne verifica il corretto aggiornamento nel caso di valori corretti e scorretti;
- la classe Pandemic, della quale se ne verifica la corretta gestione di una popolazione vuota ed evoluzione di una popolazione allo stage seguente;
- la classe Simulation, della quale se ne verifica il corretto conteggio degli stage.
## Istruzioni per l'uso
È necessario che nella cartella dalla quale viene eseguito il programma sia presente il file *arial.ttf*, contenente il font usato dalla libreria SFML.
### g++
Per compilare:

```
$ g++ -std=c++2a -Wall -Wextra -fsanitize=address,undefined model/pandemic.cpp model/person.cpp model/population.cpp model/position.cpp view/consoleInterface.cpp controller/simulation.cpp main.cpp -o app -lsfml-window -lsfml-system -lsfml-graphics
```
Per eseguire:

```
$ ./app
```
### CMake
rende pià facile compilare perché è piò corto, rende facile aggiungere flag e non serve riscriverle perché sta in un file lho messo perché era semplice emperché non sapevo come compilare includendo librerie sfml gpp
Per compilare:

```
$ cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```
Per eseguire:

```
$ ./build/app
```

Per testare:

```
$ cmake --build build --target test
```
## Guida utente
Il programma, una volta avviato, chiede se si vuole utilizzare un file di configurazione nel caso in cui questo fosse presente nella cartella. In caso contrario o se si è scelto di non utilizzarlo, il programma prosegue chiedendo all'utente i seguenti valori in input: il numero iniziale di suscettibili, infetti e rimossi; i valori dei parametri $\beta$ e $\gamma; e il numero degli stadi di cui si vuole osservare lo sviluppo della pandemia. Una volta creata con successo la simulazione, il programma chiede se l'utente desidera una rappresentazione grafica dei valori della popolazione. Infine, in output mostrerà una tabella in cui ad ogni stadio corrisponde il rispettivo valore dei suscettibili, infetti e rimossi. Nel caso in cui si volesse il grafico, questo apparirà in una finestra differente in cui saranno presenti le tre funzioni dei valori S, I e R.
Il file di configurazione con nome *simulation.conf* deve contenere i dati separati da uno spazio e nel seguente ordine: suscettibili, infetti, rimossi, beta, gamma, stadi (e.g. ```10 6 0 0.5 0.5 5```). Se formattato scorrettamente il programma proseguirà come se non ci fosse il file.
In aggiunta si possono passare a linea di comando i valori necessari per la simulazione, che devono essere formattati come il file di configurazione.

<p align="center">
<img src="https://github.com/Nanna23/pandemic-simulation/blob/main/graph.png"  width="350">

```
A configuration file was found in the root directory of the program, do you want to use it? [y/n] y
Simulation successfully created!
Do you want a graphic representation of the simulation? [y/n] y
------------------------------------------
| Stage count |    S   |    I   |    R   |
------------------------------------------
|      0      |   10   |    6   |    0   |
------------------------------------------
|      1      |    8   |    5   |    3   |
------------------------------------------
|      2      |    7   |    4   |    5   |
------------------------------------------
|      3      |    6   |    3   |    7   |
------------------------------------------
|      4      |    5   |    2   |    9   |
------------------------------------------
|      5      |    5   |    1   |   10   |
------------------------------------------
```

