<!-- omit in toc -->
# Simulazione dell'evoluzione di un'epidemia - Progetto di "Programmazione per la Fisica" di Annabel Giles

- [Introduzione](#Introduzione)
- [Il modello SIR](#Il-modello-SIR)
- [Implementazione del modello SIR](#Implementazione-del-modello-SIR)
- [Progettazione](#Progettazione)
- [Test](#Test)
- [Istruzioni per l'uso](#Istruzioni-per-luso)
    - [g++](#g)
    - [CMake](#CMake)
- [Guida utente](#Guida-utente)
- [Conclusione](#Conclusione)

## Introduzione

Il programma simula la propagazione di una pandemia utilizzando il modello SIR (Suscettibili, Infetti, Rimossi). L'intero progetto è stato sviluppato utilizzando come linguaggio di programmazione C++ e come libreria grafica SFML, ed è accedibile sulla piattaforma GitHub a questo [link](https://github.com/Nanna23/pandemic-simulation).

## Il modello SIR

Il modello SIR è un modello matematico utilizzato per studiare lo sviluppo di una pandemia all'interno di una popolazione divisa in persone suscettibili, infette e rimosse. In aggiunta a ciò, il modello SIR tiene in considerazione due parametri, con valori compresi tra 0 e 1: $\beta$ e $\gamma$, che indicano rispettivamente la probabilità di contagio e di guarigione.
Le leggi matematiche sulla quale si basa il modello SIR sono le seguenti:

$$\begin{align*}
\frac{dS}{dt} &= -\beta \frac{S}{N} I\\
\frac{dI}{dt} &= \beta \frac{S}{N} I - \gamma I\\
\frac{dR}{dt} &= \gamma I
\end{align*}$$

Osservando le equazioni si può notare che le persone suscettibili possono solo diminuire poiché diventano infette. A loro volta, le persone rimosse possono solo aumentare in quanto il loro stato è quello finale. Gli infetti sono quindi uno stato transitivo tra quello di suscettibile e quello di rimosso.

## Implementazione del modello SIR

Svolgendo per $\Delta T = 1$ le equazioni differenziali sopra descritte, si hanno le equazioni utilizzate nel progetto:

$$\begin{align*}
S_i &= S_{i-1} - \beta \frac{S_{i-1}}{N} I_{i-1}\\
I_i &= I_{i-1} + \beta \frac{S_{i-1}}{N} I_{i-1} - \gamma I_{i-1}\\
R_i &= R_{i-1} + \gamma I_{i-1}
\end{align*}$$

I parametri $\beta$ e $\gamma$ nella realtà possono variare in base a vaccinazioni e quarantene, tuttavia nel programma questi vengono considerati costanti.
Nel progetto come unità di tempo viene utilizzato lo stadio (stage) della simulazione, in cui 1 stadio corrisponde a $\Delta T = 1$.
Essendo i risultati delle equazioni numeri decimali, questi vanno arrotondati a valori interi (e.g. non è possibile avere 4.5 persone infette). Questo passatto viene svolto da una funzione della classe Pandemic.

## Progettazione

Il programma è stato progettato utilizzando il modello MVC (Model-View-Controller). Questo design divide il codice in tre parti:

- Model (modello): è la parte che gestisce i dati e contiene le classi che rispecchiano gli elementi facenti parte della simulazione;
- View (vista): si occupa della presentazione all'utente, mostrando i dati in maniera comprensibile;
- Controller (controllore): è la parte che funge da intermediario tra il model e la view.

Inoltre è presente il file *main.cpp* che è il punto di entrata del programma e si occupa di avviare la view.
Ho utilizzato questo design per mantenere il codice in ordine separandolo in più parti indipendenti tra loro. Questo facilita l'implementazione di nuove funzionalità espandendo le capacità del programma.
Per rendere più semplice la compilazione del programma si è scelto di usare CMake, quindi i file e le impostazioni necessarie alla compilazione non devono essere riscritte ogni volta nella linea di comando in quanto sono già presenti in *CMakeLists.txt*. Quest'ultimo file facilita la portabilità poiché non è necessario memorizzare alcun comando specifico ma è tutto presente al suo interno.

#### Population

La classe Population è all'interno della cartella model ed è caratterizzata dalle tre variabili S, I e R. 
Ha al suo interno un metodo per verificare se i valori sono accettabili: ovvero valori interi non negativi, e il totale delle persone non può mai essere uguale a 0. In caso contrario i valori non vengono utlizzati.
Contiene al suo interno funzioni (i getters) per ottenere i valori e il numero totale della popolazione.
Ha inoltre la funzione update, di tipo bool, che viene utilizzata per aggiornare i valori di S, I e R; se questi non sono accetabili la funzione ritorna falso e non vengono aggiornati i valori.

#### Pandemic

La classe pandemic è composta dai due paramentri $\beta$ e $\gamma$, anche in questo caso viene controllato se i valori sono accettabili. Ques'ultimi possono essere accessi tramite trispettivi getters.
Pandemic ha una funzione membro chiamata calculateNextStage, di tipo bool. Questa si occupa di calcolare i valori di S, I e R alla stadio successivo, utilizzando le formule sopra descritte.
Poiché ques'ultime possono generare numeri decimali è stato necessario implementare un metodo di arrotondamento. Inanzitutto è stata utilizzata la funzione Round da cui, dopo l'utilizzo, può verificarsi una discrepanza tra la popolazione totale, N, e la somma dei nuovi valori arrotondati di un unità. Per correggere questo errore nel caso in cui N sia inferiore andiamo a sommare la differenza al valore più alto tra S, I e R; nel caso contrario, questo viene levato dal più piccolo. Il calcolo viene svolto in questo modo per minimizzare l'impatto dell'aggiustamento.

#### Simulation

Simulation è una classe composta dalla classe population, dalla classe pandemic e dallo stadio della sviluppo di quest’ultima. 
Simulation si occupa dunque di legare population e pandemic in modo tale da simulare lo sviluppo della pandemia. 
Contiene al suo interno la funzione advanceStage di tipo bool, che contiene al suo interno un ciclo di tipo if, in cui affinché il valore attuale dello stage non raggiunte quello richiesto dall’utente calcola lo stadio successivo della classe pandemic. 
La classe simulation contiene inoltre dei getters:
- getPopulation, per ottenere i valori di S, I e R;
- getCount, per ottenere lo stadio attuale della pandemia.
A differenza degli altri file questa non è associato ad un rispettivo file .hpp perché..

#### Console Interface

Il file di console interface si occupa dell'interfaccia grafica. Contiene quindi le funzioni per l'input dei valori chiesti all'utente e di output. Di quest'ultimo si indica la rappresentazione in forma tabellare dei valori S, I e R ad ogni stadio e la rappresentazione grafica in SFML.

## Test

I test sono stati scritti utilizzando il framework doctest. Questi riguardano le classi che svolgono funzioni non elementari ma fondamentali per il buon funzionamento del programma:
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

Il programma, una volta avviato, chiede se si vuole utilizzare un file di configurazione nel caso in cui questo fosse presente nella cartella. In caso contrario o se si è scelto di non utilizzarlo, il programma prosegue chiedendo all'utente i seguenti valori in input: il numero iniziale di suscettibili, infetti e rimossi; i valori dei parametri $\beta$ e $\gamma; e il numero degli stadi di cui si vuole osservare lo sviluppo della pandemia. Una volta creata con successo la simulazione, il programma chiede se l'utente desidera una rappresentazione grafica dei valori della popolazione. Infine, in output verrà stampata una tabella in cui a ogni stadio corrisponde il rispettivo valore dei suscettibili, infetti e rimossi. Nel caso in cui si volesse il grafico, questo apparirà in una finestra differente in cui saranno raffigurati i valori S, I e R ad ogni stadio.
Il file di configurazione con nome *simulation.conf* deve contenere i dati separati da uno spazio e nel seguente ordine: suscettibili, infetti, rimossi, beta, gamma, stadi (e.g. ```10 6 0 0.5 0.5 5```). Se formattato scorrettamente il programma proseguirà come se non ci fosse il file.
In aggiunta si possono passare a linea di comando i valori necessari per la simulazione, questi devono essere formattati come il file di configurazione.

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
 |      2      |    7   |    3   |    6   | 
 ------------------------------------------
 |      3      |    6   |    2   |    8   | 
 ------------------------------------------
 |      4      |    6   |    1   |    9   | 
 ------------------------------------------
 |      5      |    6   |    0   |   10   | 
 ------------------------------------------
```

<p align="center">
<img src="https://github.com/Nanna23/pandemic-simulation/blob/main/graph.png"  width="350">

## Conclusione

Eseguendo il programma con valori differenti si può notare facilmente l'influenza dei due parametri $\beta$ e $\gamma$. Se il valore di $\beta$ è elevato, si nota che l'epidemia è molto più contagiosa. Se il valore di $\gamma$ è alto, si può osservare una guarigione più veloce. Studiare questi parametri è fondamentale per capire l'influenza che potrebbero avere il lockdown o la vaccinazione: il primo si può simulare diminuendo il parametro $\beta$, il secondo diminuendo invece entrambi i parametri.
