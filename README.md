
# swordx

 
## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Man
E' possibile passare a swordx i seguenti parametri:

 - help e -h: stampa a video l'help del programma;
 - recursive e -r : se viene passato questo argomento, nella collezione delle informazioni di una directory vengono seguite tutte le sottodirectory;
 - follow e -f: nell'elaborazione di una directory vengono seguiti i link;
 - explude <file> e -e <file>: <file> non viene considerato nell'elaborazione (questo parametro ha senso solo se si sta elaborando una directory);
 - alpha e -a: vengono considerate nella statistica solo le parole contenenti caratteri alfabetici;
 - min <num> e -m <num>: vengono considerate nella statistiche solo le parole con una lunghezza maggiore o uguale a <num>;
 - ignore <file> e -i <file>: <file> è un elenco di parole (una per riga) che vengono ignorate nella statistica;
 - sortbyoccurrency e -s: le parole vengono inserite nel file di output ordinate per numero di occorrenze;
 - log <file> e -l <file>: genera un file di log (identificato da <file>) dove viene riportate viene riportata, per ogni file analizzato viene riportata una riga della forma <name> cw iw time dove
	 - <**name**> è il nome del file analizzato;
	 - **cw** è il numero delle parole registrate;
	 - **iw** è il numero delle parole ignorate;
	 - **time** è il tempo necessario all'elaborazione del file. 
- update <**file**> se presente il file swordx.out (o il file indicato con l'opzione -o) scrive nel file <**file**>, con lo stesso formato del file di output, l'elenco delle parole con le rispettive variazioni rispetto all'esecuzione precedente del programma.


time è il tempo necessario all'elaborazione del file.
–update <file> se presente il file swordx.out (o il file indicato con l'opzione -o) scrive nel file <file>, con lo stesso formato del file di output, l'elenco delle parole con le rispettive variazioni rispetto all'esecuzione precedente del programma.

## Authors

* **Davide Monnati** - *Initial work* - [davidemonnati](https://github.com/davidemonnati)

See also the list of [contributors](https://github.com/Erthor96/swordx/contributors) who participated in this project.

## License

This project is licensed under the GNU General Public License v.3.0 - see the [LICENSE](LICENSE) file for details
