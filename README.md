<!-- omit in toc -->
# Simulazione dell'evoluzione di un'epidemia - Progetto di "Programmazione per la Fisica" di Annabel Giles
- [Introduzione](#Introduzione)
- [Il modello SIR](#Il-modello-SIR)
- [Implementazione del modello SIR](#Implementazione-del-modello-SIR)
- [Progettazione](#Progettazione)
- [Test](#Test)
- [Istruzioni per l'uso](#Istruzioni-per-luso)
- [Guida utente](#Guida-utente)
- [Conclusione](#Conclusione)
## Introduzione
Il programma simula la propagazione di una pandemia utilizzando il modello SIR (Suscettibili, Infetti, Rimossi). L'intero progetto è stato sviluppato utilizzando come linguaggio di programmazione C++ e come libreria grafica SFML, è accedibile sulla piattaforma GitHub a [questo link](https://github.com/Nanna23/pandemic-simulation).
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
Essendo i risultati delle equazioni numeri decimali, questi vanno arrotondati a valori interi (e.g. non è possibile avere 4.5 persone infette). L'arrotondamento deve però tener conto che il numero totale di persone all'interno della popolazione deve rimanere costante, arrotondare per difetto o per eccesso non sarebbe quindi corretto. La soluzione adottata consiste prima nel calcolare le unità mancanti, che possono essere al massimo 2, sommando le parti decimali dei valori S, I ed R appena calcolati. In seguito, si assegnano le unità mancanti ai gruppi (S, I o R) in ordine decrescente per parte decimale.
## Progettazione
Il programma è stato progettato utilizzando il modello MVC (Model-View-Controller). Questo design divide il codice in tre parti in modo tale da tenerlo ben organizzato:
- Model (modello): è la parte che gestisce i dati e contiene le classi che rispecchiano gli elementi facenti parte della simulazione;
- View (vista): si occupa della presentazione all'utente, mostrando i dati in maniera comprensibile;
- Controller (controllore): è la parte che funge da intermediario tra il model e la view.

Inoltre è presente il file *main.cpp* che è il punto di entrata del programma e si occupa di avviare la view.
Ho utilizzato questo design per mantenere il codice in ordine separandolo in più parti indipendenti tra loro. Questo facilita l'implementazione di nuove funzionalità espandendo le capacità del programma.
Per lo stesso motivo la classe Population è caratterizzata da un vettore di Person invece che da tre semplici variabili S, I e R. Questo, assieme al fatto che la classe Person ha un attributo position, permette di implementare facilmente in futuro una simulazione della pandemia tramite automa cellulare, poichè questa non sia già stato implementata per questioni di tempo.
Per rendere più semplice la compilazione del programma si è scelto di usare CMake, quindi i file e le impostazioni necessarie alla compilazione non devono essere riscritte ogni volta nella linea di comando in quanto sono già presenti in *CMakeLists.txt*. Quest'ultimo file facilita la portabilità poiché non è necessario memorizzare alcun comando specifico ma è tutto presente al suo interno.
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
|      2      |    7   |    4   |    5   |
------------------------------------------
|      3      |    6   |    3   |    7   |
------------------------------------------
|      4      |    5   |    2   |    9   |
------------------------------------------
|      5      |    5   |    1   |   10   |
------------------------------------------
```

<p align="center">
<img src="https://github.com/Nanna23/pandemic-simulation/blob/main/graph.png"  width="350">

## Conclusione
Eseguendo il programma con valori differenti si può notare facilmente l'influenza dei due parametri $\beta$ e $\gamma$. Se il valore di $\beta$ è elevato, si nota che l'epidemia è molto più contagiosa. Se il valore di $\gamma$ è alto, si può osservare una guarigione più veloce. Studiare questi parametri è fondamentale per capire l'influenza che potrebbero avere il lockdown o la vaccinazione: il primo si può simulare diminuendo il parametro $\beta$, il secondo diminuendo invece entrambi i parametri.
