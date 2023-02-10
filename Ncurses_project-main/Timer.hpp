#ifndef TIMER_HPP
#define TIMER_HPP

/**
 *	Classe per la temporizzazione di azioni.
 *	Ogni Timer è legato a una specifica azione di gioco,
 *	e ne scandisce l'utilizzo.
 */
class Timer {
public:
	/**
	 *	Incrementa il tempo nel timer,
	 *	fino al massimo previsto.
	 */
	void update();

	/**
	 *	Avvia il timer.
	 */
	void start();

	/**
	 *  Ferma e resetta il timer.
	 */
	void stop();

	bool hasStarted() const;

	int currentTime() const;

	/**
	 *	Ritorna true se il tempo richiesto
	 *	è stato raggiunto: l'azione è ora eseguibile e
	 *	il timer viene azzerato.
	 */
	bool wait();

	const int time;

	Timer(int time, bool start=false);

private:
	int current;

	bool active;
};
#endif